const char szSketchName[]  = "BeckE32_Test_MAX6675.ino";
const char szFileDate[]    = "3/1/22f";
//Beck: This uses a basic test case format which has WiFi and OTA support
//Program to test MAX6675 Thermocouple reader using SPI
//Good basis for any simple test
// this example is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple

#define DO_OTA          true

#include "max6675.h"
#if DO_OTA
  #include <BeckE32_OTALib.h>
  #include <WiFi.h>
#endif
#include <Streaming.h>

const char* szRouterName  = "Aspot24b";
const char* szRouterPW    = "Qazqaz11";
const char* szWebHostName = "Test_MAX6675";

//Pin numbers on WROVER-Kit
int8_t    cSPI_CLK    = 18;
int8_t    cSPI_MISO   = 19;
int8_t    cSPI_CS1    =  2;
int8_t    cSPI_CS2    =  4;
int8_t    cSPI_CS3    =  5;

//Create objects to read thermocouples
MAX6675 oMAX6675_Reader1(cSPI_CLK, cSPI_CS1, cSPI_MISO);
MAX6675 oMAX6675_Reader2(cSPI_CLK, cSPI_CS2, cSPI_MISO);
MAX6675 oMAX6675_Reader3(cSPI_CLK, cSPI_CS3, cSPI_MISO);

//Protos
void setup      ();
void loop       ();
void SetupCode  ();
void LoopCode   ();

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
  SetupCode()
  return;
} //setup


void loop() {
#if DO_OTA
  HandleOTAWebserver();
#endif
  LoopCode();
  return;
} //loop


void SetupCode() {
  //Put code for setting up test here.
 return;
} //SetupCode


void LoopCode() {
  //Put code here to do everytime loop is called.
  Serial << "DegF1= " << oMAX6675_Reader1.readFahrenheit() <<
          ", Deg2F= " << oMAX6675_Reader2.readFahrenheit() <<
          ", Deg3F= " << oMAX6675_Reader3.readFahrenheit() << endl;
  delay(3000);
  return;
} //LoopCode
//Last line.