// BeckTCoupleReaderClass.h, 3/1/22b
#pragma once
#include <BeckTireTempDefines.h>
#include <BeckMAX6675Lib.h>

class BeckTCoupleReaderClass{
public:
  BeckTCoupleReaderClass            ();
  BeckTCoupleReaderClass            (int8_t cSPI_CS_Pin);
  virtual ~BeckTCoupleReaderClass   ();

  double  Handle                    (void);

protected:
  int8_t            _cSPI_CS_Pin;
  BeckMAX6675Class  _oMAX6675_Thermocouple;
  uint16_t          _usDegF_Value      = 0;
};  //BeckTCoupleReaderClass
//Last line.
