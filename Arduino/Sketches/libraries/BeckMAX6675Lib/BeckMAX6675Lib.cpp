// BeckMAX6675Lib.cpp, 3/2/22b

// www.ladyada.net/learn/sensors/thermocouple

#include <stdlib.h>
#include <BeckMAX6675Lib.h>
#include <Streaming.h>

#define DEBUG_MAX6675    true

BeckMAX6675Class::BeckMAX6675Class(int8_t CLK, int8_t CS, int8_t MISO) {
  _CLK    = CLK;
  _CS     = CS;
  _MISO   = MISO;

  //define pin modes
  Serial << "BeckMAX6675Class(): Set pins " << _CS << " and " << _CLK << " to OUTPUT, set pin " << _MISO << " to INPUT" << endl;
  pinMode(_CS, OUTPUT);
  pinMode(_CLK, OUTPUT);
  pinMode(_MISO, INPUT);

  digitalWrite(_CS, HIGH);
} //constructor


BeckMAX6675Class::~BeckMAX6675Class() {
  Serial << "~BeckMAX6675Class(): Destructing" << endl;
} //destructor


double BeckMAX6675Class::ReadDegC(void) {
  uint16_t usValue;

  digitalWrite(_CS, LOW);
  delay(1);

  usValue = ucReadSPI();
  usValue <<= 8;
  usValue |= ucReadSPI();

  digitalWrite(_CS, HIGH);

  if (usValue & 0x4) {
    // uh oh, no thermocouple attached!
    return NAN;
    //return -100;
  }
  usValue >>= 3;
  return usValue * 0.25;
} //ReadDegC


double BeckMAX6675Class::ReadDegF(void) {
  double dfDegF;
  double dfDegC;

  dfDegC= ReadDegC();
  dfDegF= (dfDegC * (9.0/5.0)) + 32.0;

#if DEBUG_MAX6675
  Serial << "BeckMAX6675Class::ReadDegF(): dfDegF= " << dfDegF << ", CS= " << _CS << ", CLK= " << _CLK << ", MISO= " << _MISO << endl;
#endif
  return dfDegF;
} //ReadDegF


uint8_t BeckMAX6675Class::ucReadSPI(void) {
  uint8_t   ucByte= 0;

  for (int wBit= 7; wBit >= 0; wBit--)
  {
    digitalWrite(_CLK, LOW);
    delay(1);
    if (digitalRead(_MISO)) {
      //set the bit to 0 no matter what
      ucByte |= (1 << wBit);
    }

    digitalWrite(_CLK, HIGH);
    delay(1);
  }
  return ucByte;
}	//ucReadSPI
//Last line
