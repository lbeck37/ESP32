const char szSketchName[]  = "BeckE32_Test_MAX6675.ino";
const char szFileDate[]    = "3/1/22c";
//Program to test MAX6675 Thermocouple reader using SPI
//Good basis for any simple test
// this example is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple

#include "max6675.h"
#include <Streaming.h>

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

void setup() {
  Serial.begin(115200);
  Serial << endl << "setup(): Begin " << szSketchName << ", " << szFileDate << endl;
  delay(500);
  return;
} //setup


void loop() {
   Serial << "DegF1= " << oMAX6675_Reader1.readFahrenheit() <<
           ", Deg2F= " << oMAX6675_Reader2.readFahrenheit() <<
           ", Deg3F= " << oMAX6675_Reader3.readFahrenheit() << endl;
   delay(1000);
   return;
} //loop
