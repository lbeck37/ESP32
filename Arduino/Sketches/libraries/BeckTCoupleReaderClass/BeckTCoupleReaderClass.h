// BeckTCoupleReaderClass.h, 2/28/22b
#pragma once
#include <BeckTireTempDefines.h>
#include <max6675.h>

class BeckTCoupleReaderClass{
public:
  BeckTCoupleReaderClass            ();
  BeckTCoupleReaderClass            (int8_t cSPI_CS_Pin);
  BeckTCoupleReaderClass& operator=(const BeckTCoupleReaderClass& t){
    return *this;
  }
  virtual ~BeckTCoupleReaderClass   ();

  double  Handle                    (void);

//protected:
private:
  MAX6675     _oMAX6675_Thermocouple;
  uint16_t    _usDegF_Value      = 0;
};  //BeckTCoupleReaderClass
//Last line.
