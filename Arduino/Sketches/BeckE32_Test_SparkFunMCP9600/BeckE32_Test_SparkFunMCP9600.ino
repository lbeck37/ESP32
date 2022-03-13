const char szSketchName[]  = "BeckE32_Test_SparkFunMCP9600.ino";
const char szFileDate[]    = "3/13/22ac";
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

/*
unsigned long   ulNextHandleLoopMsec    =    0;
unsigned long   ulHandleLoopPeriodMsec  = 5000; //mSec between handling probes
*/
uint32_t          _uwNextHandleLoopMsec     =    0;
const uint32_t    _ulHandleLoopPeriodMsec   = 5000; //mSec between handling probes


//Protos
void setup      ();
void loop       ();
void SetupCode  ();
void LoopCode   ();

const uint32_t  _uwI2CBusFrequency  = 100000;
const uint8_t   _cNumProbes         = 3;

uint8_t         _aucI2CAdresses     [] {0, _ucI2CAddress1, _ucI2CAddress2, _ucI2CAddress3};
MCP9600*        _apoTCoupleReader   [_cNumProbes + 1];
bool            _abProbeOK          [4] {true};

void SetupCode() {
  Wire.begin(_cI2C_SDA_Pin, _cI2C_SCL_Pin, _uwI2CBusFrequency);

  //Create pointer to new objects, zero the [0] element since we don't use lowest member of array
  _apoTCoupleReader[0]= nullptr;

  for (int8_t cProbeID= 1; cProbeID <= _cNumProbes; cProbeID++){
    int8_t cI2CAddress= _aucI2CAdresses[cProbeID];
    Serial << "SetupCode(): Use new() to create an MCP9600 object at I2C address " << cI2CAddress << endl;

     _apoTCoupleReader[cProbeID]= new (std::nothrow) MCP9600 {};
    if (_apoTCoupleReader[cProbeID] != nullptr) {
      Serial << "SetupCode(): Call begin() for MCP9600 at address " << cI2CAddress << endl;
      _apoTCoupleReader[cProbeID]->begin(cI2CAddress);
    }
    else{
      Serial << "SetupCode(): new() failed for MCP9600 object at address " << cI2CAddress << endl;
      _abProbeOK[cProbeID]= false;
    }
  } //for

  for (int8_t cProbeID= 1; cProbeID <= _cNumProbes; cProbeID++){
    Serial << "SetupCode(): Call isConnected() to test for MCP9600 at position #" << cProbeID << endl;
    if(_abProbeOK[cProbeID] &&_apoTCoupleReader[cProbeID]->isConnected()) {
        Serial.println("Device will acknowledge!");
    } //if(_apoTCoupleReader[cProbeID]->isConnected())
    else {
        Serial.println("Device did not acknowledge!");
        _abProbeOK[cProbeID]= false;
    } //if(_apoTCoupleReader[cProbeID]->isConnected())else

    if (_abProbeOK[cProbeID]) {
      //check if the Device ID is correct
      Serial << "SetupCode(): Call checkDeviceID() to test for MCP9600 ID at position #" << cProbeID << endl;
      if(_apoTCoupleReader[cProbeID]->checkDeviceID()) {
          Serial.println("Device ID is correct!");
      } //if(_apoTCoupleReader[cProbeID]->checkDeviceID())
      else {
          Serial.println("Device ID is not correct!");
          _abProbeOK[cProbeID]= false;
          //while(1); //hang forever
      } //if(_apoTCoupleReader[cProbeID]->checkDeviceID())else
    } //if(_abProbeOK[cProbeID])
  } //for

  return;
} //SetupCode


void LoopCode() {
  if (millis() > _uwNextHandleLoopMsec){
    _uwNextHandleLoopMsec= millis() + _ulHandleLoopPeriodMsec;
    Serial << "LoopCode(): HandleLoop timer fired" << endl;
    //Put code here to do every time the HandleLoop timer fires.
    for (int8_t cProbeID= 1; cProbeID <= _cNumProbes; cProbeID++){
      Serial << "SetupCode(): Check available() and print value at position #" << cProbeID << endl;
      if (_apoTCoupleReader[cProbeID]->available()) {
          Serial.print("Thermocouple: ");
          Serial.print(_apoTCoupleReader[cProbeID]->getThermocoupleTemp());
          Serial.print(" °C   Ambient: ");
          Serial.print(_apoTCoupleReader[cProbeID]->getAmbientTemp());
          Serial.print(" °C   Temperature Delta: ");
          Serial.print(_apoTCoupleReader[cProbeID]->getTempDelta());
          Serial.print(" °C");
          Serial.println();
      } //if(_apoTCoupleReader[cProbeID]->available())
    } //for
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
