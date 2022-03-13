const char szSketchName[]  = "BeckE32_Test_SparkFunMCP9600.ino";
const char szFileDate[]    = "3/13/22h";
//Beck: This uses a basic test case format which has WiFi and OTA support
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

unsigned long   ulNextHandleLoopMsec    =    0;
unsigned long   ulHandleLoopPeriodMsec  = 5000; //mSec between handling probes

//Protos
void setup      ();
void loop       ();
void SetupCode  ();
void LoopCode   ();

MCP9600 tempSensor;

const uint8_t     _cNumProbes       = 3;

MCP9600*          _apoTCoupleReader [_cNumProbes + 1];
uint8_t           _aucI2CAdresses   [] {0, _ucI2CAddress1, _ucI2CAddress2, _ucI2CAddress3};
bool              _abProbeOK        [4] {true};

//static const uint8_t   _ucI2CAddress1     = 0x67;     //decimal 103

void SetupCode() {
  Wire.begin();
  Wire.setClock(100000);

  //Create pointer to new objects, zero the [0] element since we don't use lowest member of array
  _apoTCoupleReader[0]= nullptr;

  for (int8_t cProbeID= 1; cProbeID <= _cNumProbes; cProbeID++){
    int8_t cI2CAddress= _aucI2CAdresses[cProbeID];
    Serial << "SetupCode(): Use new() to create an MCP9600 object at I2C address " << cI2CAddress << endl;

    //if (_apoTCoupleReader[cProbeID]= new MCP9600()) {
    //_apoTCoupleReader[cProbeID]= new MCP9600();
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
/*
  tempSensor.begin();       // Uses the default address (0x60) for SparkFun Thermocouple Amplifier
  //tempSensor.begin(0x66); // Default address (0x66) for SparkX Thermocouple Amplifier
  //check if the sensor is connected
  if(tempSensor.isConnected()) {
      Serial.println("Device will acknowledge!");
  } //if(tempSensor.isConnected())
  else {
      Serial.println("Device did not acknowledge! Freezing.");
      while(1); //hang forever
  } //if(tempSensor.isConnected())else

  //check if the Device ID is correct
  if(tempSensor.checkDeviceID()) {
      Serial.println("Device ID is correct!");
  } //if(tempSensor.checkDeviceID())
  else {
      Serial.println("Device ID is not correct! Freezing.");
      while(1);
  } //if(tempSensor.checkDeviceID())else
*/
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
  if (millis() > ulNextHandleLoopMsec){
    ulNextHandleLoopMsec= millis() + ulHandleLoopPeriodMsec;
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