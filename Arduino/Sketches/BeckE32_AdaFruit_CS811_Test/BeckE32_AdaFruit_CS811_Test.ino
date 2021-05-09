//BeckE32_AdaFruit_CS811_Test.ino, 5/8/21a
/***************************************************************************
  This is a library for the CCS811 air

  This sketch reads the sensor

  Designed specifically to work with the Adafruit CCS811 breakout
  ----> http://www.adafruit.com/products/3566

  These sensors use I2C to communicate. The device's I2C address is 0x5A

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Dean Miller for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/
#define	DO_CODE		false

#include <Streaming.h>
#if DO_CODE
	#include <Adafruit_CCS811.h>
	Adafruit_CCS811 ccs;
#endif

void setup() {
  Serial.begin(9600);
  delay(500);

  //Serial.println("CCS811 test");
  Serial << "BeckE32_AdaFruit_CS811_Test.ino, 5/8/21: setup(): Begin" << endl;

#if DO_CODE
  if(!ccs.begin()){
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }

  // Wait for the sensor to be ready
  while(!ccs.available());
#endif
  return;
}	//setup


void loop() {
#if DO_CODE
  if(ccs.available()){
    if(!ccs.readData()){
      Serial.print("CO2: ");
      Serial.print(ccs.geteCO2());
      Serial.print("ppm, TVOC: ");
      Serial.println(ccs.getTVOC());
    }
    else{
      Serial.println("ERROR!");
      while(1);
    }
  }
  delay(500);
#endif
  return;
}	//loop
