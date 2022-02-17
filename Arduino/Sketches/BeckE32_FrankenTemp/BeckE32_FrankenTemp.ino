const String SketchName  = "BeckE32_FrankenTemp.ino";
const String FileDate    = "Feb 17, 2022p";
#ifndef ESP8266
  #define ESP32
#endif

#define DO_TEMP       false
#define DO_WEBSERVER  false

#if DO_WEBSERVER
  #include <BeckE32_OTALib.h>
#endif
//#include <BeckLogLib.h>
//#include <BeckMiniLib.h>
//#include <SPI.h>
//#include <Adafruit_GFX.h>
#if DO_TEMP
  #include <max6675.h>
#endif
//#include <WiFi.h>
#include <Streaming.h>

#ifdef ESP32
//#include <WROVER_KIT_LCD.h>
#endif


#ifdef ESP8266
// nodeMCU ESP8266
// https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/
static const byte      cSPI_MISO_Pin         = 12;
static const byte      cSPI_MOSI_Pin         = 13;
static const byte      cSPI_CLK_Pin          = 14;    //Pin 14, D5
static const byte      cSPIChipSelectPin     = 15;    //Pin 15, D8
#else
//ESP32
// https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
static const byte      cSPI_MISO_Pin         = 19;
static const byte      cSPI_MOSI_Pin         = 23;
static const byte      cSPI_CLK_Pin          = 18;
static const byte      cSPIChipSelectPin     =  5;
#endif

#if DO_TEMP
  //MAX6675   Thermo1(cSCLK, cMOSI_CS, cMISO);
  MAX6675   Thermo1(cSPI_CLK_Pin, cSPIChipSelectPin, cSPI_MISO_Pin);
#endif

const char* szWebHostName = "Frankentemp";

void setup()   {
  Serial.begin(115200);
  Serial << endl << "setup(): Begin " << SketchName << ", " << FileDate << endl;

#if DO_WEBSERVER
  Serial << "setup(): Call SetupWebServer(" << szWebHostName << ")" << endl;
  SetupWebserver(szWebHostName);
#endif

  Serial << "setup(): Done " << endl;
  return;
}  //setup


void loop() {
  double    dfDegF= 37.37;
#if DO_TEMP
  //dfDegF= Thermo1.readFahrenheit();
#endif
  Serial << "Loop(): Degrees F= " << dfDegF << endl;
  delay(1000);

#if DO_WEBSERVER
  HandleOTAWebserver();
#endif
  return;
}  //loop()
//Last line
