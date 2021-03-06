const char szSketchName[]  = "BeckE32_CCS811_GasSensor.ino";
const char szFileDate[]    = "5/8/21g";

//BeckE32_CCS811_GasSensor.ino, 5/8/21e
/***************************************************************************
  This is a library for the CCS811 air
  This sketch reads the sensor
  Designed specifically to work with the Adafruit CCS811 breakout
  ----> http://www.adafruit.com/products/3566
  These sensors use I2C to communicate. The device's I2C address is 0x5A
  Written by Dean Miller for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include "Adafruit_CCS811.h"
#include <Streaming.h>

Adafruit_CCS811 GasSensor;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial << endl << "setup() Begin, Sketch: " << szSketchName << ", " << szFileDate << endl;

  if (!GasSensor.begin()){
    Serial << "setup(): Failed to start sensor, please check the wiring." << endl;
    while(1);
  }	//if(!GasSensor.begin())

  // Wait for the sensor to be ready
  while(!GasSensor.available());
  return;
} //setup


void loop() {
  uint16_t  CO2_Value;
  uint16_t  TVOC_Value;

  if (GasSensor.available()){
    if (!GasSensor.readData()){
      CO2_Value=GasSensor.geteCO2();
      TVOC_Value=GasSensor.getTVOC();
      Serial << "loop(): CO2= " << CO2_Value << "ppm, TVOC= " << TVOC_Value << endl;
    }	//if(!GasSensor.readData())
    else{
      Serial.println("ERROR!");
      Serial << "loop: readData() returned error" << endl;
      while(1);
    }	//if(!GasSensor.readData())else
  }	//if(GasSensor.available())
  delay(2000);
  return;
} //loop
//Last line.
