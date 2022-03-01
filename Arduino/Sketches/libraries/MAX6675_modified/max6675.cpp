// Beck: max6675.cpp, 2/28/22c
// this library is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple

//#include <avr/pgmspace.h>
//#include <util/delay.h>
#include <stdlib.h>
#include "max6675.h"
#include <Streaming.h>

MAX6675::MAX6675(int8_t SCLK, int8_t CS, int8_t MISO) {
  sclk = SCLK;
  cs = CS;
  miso = MISO;

  //define pin modes
  pinMode(cs, OUTPUT);
  pinMode(sclk, OUTPUT); 
  pinMode(miso, INPUT);

  digitalWrite(cs, HIGH);
} //constructor


double MAX6675::readCelsius(void) {
  uint16_t v;

  digitalWrite(cs, LOW);
  delay(1);

  v = spiread();
  v <<= 8;
  v |= spiread();

  digitalWrite(cs, HIGH);

  if (v & 0x4) {
    // uh oh, no thermocouple attached!
    return NAN; 
    //return -100;
  }
  v >>= 3;
  return v*0.25;
} //readCelsius


double MAX6675::readFahrenheit(void) {
  double dfDegF;
  double dfDegC;
  Serial << "MAX6675::readFahrenheit(): CS= " << cs << ", CLK= " << sclk << ", MISO= " << miso << endl;

  dfDegC= readCelsius();
  dfDegF= (dfDegC * (9.0/5.0)) + 32.0;

  Serial << "MAX6675::readFahrenheit(): dfDegC= " << dfDegC << endl;
  Serial << "MAX6675::readFahrenheit(): dfDegF= " << dfDegF << endl;
  //return readCelsius() * 9.0/5.0 + 32;
  return dfDegF;
} //readFahrenheit


byte MAX6675::spiread(void) { 
  int i;
  byte d = 0;

  for (i=7; i>=0; i--)
  {
    digitalWrite(sclk, LOW);
    delay(1);
    if (digitalRead(miso)) {
      //set the bit to 0 no matter what
      d |= (1 << i);
    }

    digitalWrite(sclk, HIGH);
    delay(1);
  }

  return d;
}
