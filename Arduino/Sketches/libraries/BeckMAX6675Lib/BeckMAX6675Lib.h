// BeckMAX6675Lib.h, 3/1/22e

// www.ladyada.net/learn/sensors/thermocouple
#pragma once

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class BeckMAX6675Class {
 public:
  BeckMAX6675Class             (int8_t CLK, int8_t CS, int8_t MISO);
  virtual ~BeckMAX6675Class    ();

  double ReadDegC   (void);
  double ReadDegF   (void);

 private:
  int8_t    _CLK;
  int8_t    _MISO;
  int8_t    _CS;

  uint8_t   ucReadSPI(void);
};
//Last line.
