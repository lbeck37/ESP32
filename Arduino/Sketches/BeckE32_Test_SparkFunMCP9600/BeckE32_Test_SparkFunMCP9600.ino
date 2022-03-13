const char szSketchName[]  = "BeckE32_Test_SparkFunMCP9600.ino";
const char szFileDate[]    = "3/13/22an";
#include <BeckE32_Defines.h>

#if !DO_OTA
  #undef DO_OTA
  #define DO_OTA  true
#endif

#if DO_OTA
  #include <BeckE32_OTALib.h>
  #include <WiFi.h>
#endif
#include <Streaming.h>
#include <SparkFun_MCP9600.h>

const char*     szRouterName            = "Aspot24b";
const char*     szRouterPW              = "Qazqaz11";
const char*     szWebHostName           = "Test_SF_MCP9600";

uint32_t          _uwNextHandleLoopMsec     =    0;
const uint32_t    _ulHandleLoopPeriodMsec   = 5000; //mSec between handling probes

//Protos
void  setup         ();
void  loop          ();
void  SetupCode     ();
void  LoopCode      ();
void  BeginMCP9600  (int8_t cProbeID);
float fGetDegF      ();

const uint32_t  _uwI2CBusFrequency  = 100000;
const uint8_t   _cNumProbes         = 3;

const uint8_t   _aucI2CAdresses     [] {0, _ucI2CAddress1, _ucI2CAddress2, _ucI2CAddress3};
MCP9600*        _apoTCoupleReader   [_cNumProbes + 1];
bool            _abProbeOK          [_cNumProbes + 1] {true, true, true, true};
float           _afDegF             [_cNumProbes + 1];
float           _afAmbiantF         [_cNumProbes + 1];
float           _afDeltaF           [_cNumProbes + 1];

void SetupCode() {
  Wire.begin(_cI2C_SDA_Pin, _cI2C_SCL_Pin, _uwI2CBusFrequency);

  //Create pointer to new objects, zero the [0] element since we don't use lowest member of array
  _apoTCoupleReader[0]= nullptr;

  for (int8_t cProbeID= 1; cProbeID <= _cNumProbes; cProbeID++){
     BeginMCP9600(cProbeID);
  } //for

  return;
} //SetupCode


void BeginMCP9600(int8_t cProbeID){
  int8_t cI2CAddress= _aucI2CAdresses[cProbeID];

  Serial << "SetupCode(): Use new() to create an MCP9600 object at I2C address " << cI2CAddress << endl;

   _apoTCoupleReader[cProbeID]= new (std::nothrow) MCP9600 {};
  if (_apoTCoupleReader[cProbeID] != nullptr) {
    Serial << "SetupCode(): Call begin() for MCP9600 at address " << cI2CAddress << endl;
    _apoTCoupleReader[cProbeID]->begin(cI2CAddress);
  } //if(_apoTCoupleReader[cProbeID]!=nullptr)
  else{
    Serial << "SetupCode(): new() FAILED for MCP9600 object at address " << cI2CAddress << endl;
    _abProbeOK[cProbeID]= false;
  } //if(_apoTCoupleReader[cProbeID]!=nullptr)else

  Serial << "SetupCode(): Call isConnected() to test for MCP9600 at position #" << cProbeID << endl;
  if(_abProbeOK[cProbeID]) {
    if (_apoTCoupleReader[cProbeID]->isConnected()) {
      Serial << "BeginMCP9600(" << cProbeID << "): Call to isConnected() PASSED " << endl;
    } //if(_apoTCoupleReader[cProbeID]->isConnected())
    else {
        Serial << "BeginMCP9600(" << cProbeID << "): Call to isConnected() FAILED for cProbeID= " << cProbeID << endl;
        _abProbeOK[cProbeID]= false;
    } //if(_apoTCoupleReader[cProbeID]->isConnected())else

    if (_abProbeOK[cProbeID]) {
      //check if the Device ID is correct
      Serial << "SetupCode(): Call checkDeviceID() to test for MCP9600 ID at position #" << cProbeID << endl;
      if(_apoTCoupleReader[cProbeID]->checkDeviceID()) {
        Serial << "BeginMCP9600(" << cProbeID << "): Call to checkDeviceID() PASSED" << endl;
      } //if(_apoTCoupleReader[cProbeID]->checkDeviceID())
      else {
        Serial << "BeginMCP9600(" << cProbeID << "): Call to checkDeviceID() FAILED" << endl;
        _abProbeOK[cProbeID]= false;
      } //if(_apoTCoupleReader[cProbeID]->checkDeviceID())else
    } //if(_abProbeOK[cProbeID])
  } // if(_abProbeOK[cProbeID])
  else {
  } // if(_abProbeOK[cProbeID])else

  return;
} //BeginMCP9600


float fGetDegF(int8_t cProbeID) {
  float fDegC= _apoTCoupleReader[cProbeID]->getThermocoupleTemp();
  float fDegF= (1.80 * fDegC) + 32.00;
  return fDegF;
} //fGetDegF


float fGetAmbiantF(int8_t cProbeID) {
  float fDegC= _apoTCoupleReader[cProbeID]->getAmbientTemp();
  float fDegF= (1.80 * fDegC) + 32.00;
  return fDegF;
} //fGetAmbiantF


float fGetDeltaF(int8_t cProbeID) {
  float fDeltaDegC= _apoTCoupleReader[cProbeID]->getTempDelta();
  float fDeltaDegF= 1.80 * fDeltaDegC;
  return fDeltaDegF;
} //fGetDeltaF


void LoopCode() {
  if (millis() > _uwNextHandleLoopMsec){
    Serial << "LoopCode(): HandleLoop timer fired" << endl;
    _uwNextHandleLoopMsec= millis() + _ulHandleLoopPeriodMsec;

    //Get the values
    for (int8_t cProbeID= 1; cProbeID <= _cNumProbes; cProbeID++){
      Serial << "SetupCode(): Check available() and print value at position #" << cProbeID << endl;
      if (_apoTCoupleReader[cProbeID]->available()) {
        Serial << "Thermocouple: ";
        _afDegF[cProbeID]     = fGetDegF    (cProbeID);
        _afAmbiantF[cProbeID] = fGetAmbiantF(cProbeID);
        _afDeltaF[cProbeID]   = fGetDeltaF  (cProbeID);
      } //if(_apoTCoupleReader[cProbeID]->available())
      else {
        Serial << "LoopCode(): Call to available() FAILED" << endl;
      } //if(_apoTCoupleReader[cProbeID]->available())else
    } //for(int8_t cProbeID=1;...

    //Print out the values.
    for (int8_t cProbeID= 1; cProbeID <= _cNumProbes; cProbeID++){
      Serial << "Thermocouple: ";
      Serial << _afDegF[cProbeID]      << " °F   Ambient: ";
      Serial << _afAmbiantF[cProbeID]  << " °F   Temperature Delta: ";
      Serial << _afDeltaF[cProbeID]    << " °F" << endl;
    } //for(int8_t cProbeID=1;...
  } //if (millis()>ulNextHandleLoopMsec)

  return;
} //LoopCode


void setup() {
  Serial.begin(115200);
  Serial << endl << "setup(): Begin " << szSketchName << ", " << szFileDate << endl;
  delay(500);
#if DO_OTA
  // Start WiFi and wait for connection to the network
  WiFi.begin(szRouterName, szRouterPW);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial << endl << "setup(): Connected to " << szRouterName << ", IP address to connect to is " << WiFi.localIP() << endl;
  Serial << "setup(): Call SetupWebServer(" << szWebHostName << ")" << endl;
  SetupWebserver(szWebHostName);
#endif
  SetupCode();
  return;
} //setup

void loop() {
#if DO_OTA
  HandleOTAWebserver();
#endif
  LoopCode();
  return;
} //loop
//Last line.
