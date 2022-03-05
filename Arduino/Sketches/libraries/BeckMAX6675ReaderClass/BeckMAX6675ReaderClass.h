// BeckMAX6675ReaderClass.h, 3/5/22b
#pragma once
#include <BeckE32_Defines.h>
#include <BeckMAX6675Lib.h>

class BeckMAX6675ReaderClass{
public:
  BeckMAX6675ReaderClass            ();
  BeckMAX6675ReaderClass            (int8_t cSPI_CS_Pin);
  virtual ~BeckMAX6675ReaderClass   ();

  double  Handle                    (void);

protected:
  int8_t            _cSPI_CS_Pin;
  BeckMAX6675Class  _oMAX6675_Thermocouple;
  uint16_t          _usDegF_Value      = 0;
};  //BeckMAX6675ReaderClass
//Last line.
