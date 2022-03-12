const char szSketchName[]  = "BeckE32_Test_Template.ino";
const char szFileDate[]    = "3/13/22b";
//Beck: This uses a basic test case format which has WiFi and OTA support
//Program to test MAX6675 Thermocouple reader using SPI
//Good basis for any simple test
// this example is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple

#define DO_OTA          true

#if DO_OTA
  #include <BeckE32_OTALib.h>
  #include <WiFi.h>
#endif
#include <Streaming.h>

const char*       szRouterName            = "Aspot24b";
const char*       szRouterPW              = "Qazqaz11";
const char*       szWebHostName           = "Test_Template";

unsigned long     ulNextHandleLoopMsec    =    0;
unsigned long     ulHandleLoopPeriodMsec  = 5000; //mSec between handling probes

//Protos
void setup      ();
void loop       ();
void SetupCode  ();
void LoopCode   ();

void SetupCode() {
  //Put code for setting up test here.

  return;
} //SetupCode


void LoopCode() {
  if (millis() > ulNextHandleLoopMsec){
    ulNextHandleLoopMsec= millis() + ulHandleLoopPeriodMsec;
    Serial << "LoopCode(): HandleLoop timer fired" << endl;
    //Put code here to do every time the HandleLoop timer fires.

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
