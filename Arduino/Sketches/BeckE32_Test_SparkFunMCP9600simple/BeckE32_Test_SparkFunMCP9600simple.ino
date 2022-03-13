const char szSketchName[]  = "BeckE32_Test_SparkFunMCP9600simple.ino";
const char szFileDate[]    = "3/13/22a";
//Beck: This uses a basic test case format which has WiFi and OTA support
#include <BeckE32_Defines.h>

#if !DO_OTA
  #undef DO_OTA
  #define DO_OTA  true
#endif

#define DO_OTA          true

#if DO_OTA
  #include <BeckE32_OTALib.h>
  #include <WiFi.h>
#endif
#include <Streaming.h>
#include <SparkFun_MCP9600.h>

const char*       szRouterName            = "Aspot24b";
const char*       szRouterPW              = "Qazqaz11";
const char*       szWebHostName           = "Test_SF_MCP9600";

unsigned long     ulNextHandleLoopMsec    =    0;
unsigned long     ulHandleLoopPeriodMsec  = 5000; //mSec between handling probes

//Protos
void setup      ();
void loop       ();
void SetupCode  ();
void LoopCode   ();

MCP9600 tempSensor;

void SetupCode() {
  //Put code for setting up test here.
  tempSensor.begin();       // Uses the default address (0x60) for SparkFun Thermocouple Amplifier
  //tempSensor.begin(0x66); // Default address (0x66) for SparkX Thermocouple Amplifier

  //check if the sensor is connected
  if(tempSensor.isConnected()){
      Serial.println("Device will acknowledge!");
  }
  else {
      Serial.println("Device did not acknowledge! Freezing.");
      while(1); //hang forever
  }

  //check if the Device ID is correct
  if(tempSensor.checkDeviceID()){
      Serial.println("Device ID is correct!");
  }
  else {
      Serial.println("Device ID is not correct! Freezing.");
      while(1);
  }

  return;
} //SetupCode


void LoopCode() {
  if (millis() > ulNextHandleLoopMsec){
    ulNextHandleLoopMsec= millis() + ulHandleLoopPeriodMsec;
    Serial << "LoopCode(): HandleLoop timer fired" << endl;
    //Put code here to do every time the HandleLoop timer fires.
    if(tempSensor.available()){
        Serial.print("Thermocouple: ");
        Serial.print(tempSensor.getThermocoupleTemp());
        Serial.print(" °C   Ambient: ");
        Serial.print(tempSensor.getAmbientTemp());
        Serial.print(" °C   Temperature Delta: ");
        Serial.print(tempSensor.getTempDelta());
        Serial.print(" °C");
        Serial.println();
        //delay(20); //don't hammer too hard on the I2C bus
    }

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
