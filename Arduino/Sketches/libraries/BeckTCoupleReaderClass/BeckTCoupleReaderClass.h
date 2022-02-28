// BeckTCoupleReaderClass.h, 2/28/22f
#pragma once
#include <BeckTireTempDefines.h>
#include <max6675.h>

class BeckTCoupleReaderClass{
public:
  BeckTCoupleReaderClass            ();
  BeckTCoupleReaderClass            (int8_t cSPI_CS_Pin);
  virtual ~BeckTCoupleReaderClass   ();

  double  Handle                    (void);

protected:
  int8_t      _cSPI_CS_Pin;
  MAX6675     _oMAX6675_Thermocouple;
  uint16_t    _usDegF_Value      = 0;
};  //BeckTCoupleReaderClass
//Last line.
