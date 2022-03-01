// BeckE32_Test_MAX6675.ino, 2/28/22b
// this example is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple

#include "max6675.h"

int8_t    cSPI_CLK    = 18;
int8_t    cSPI_MISO   = 19;
int8_t    cSPI_CS     =  2;

//Create object to read thermostat
MAX6675 oMAX6675_Reader(cSPI_CLK, cSPI_CS, cSPI_MISO);

void setup() {
  Serial.begin(115200);

  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  delay(500);
  return;
} //setup


void loop() {
  // basic readout test, just print the current temp

   Serial.print("F = ");
   Serial.println(oMAX6675_Reader.readFahrenheit());

   delay(1000);
   return;
} //loop
