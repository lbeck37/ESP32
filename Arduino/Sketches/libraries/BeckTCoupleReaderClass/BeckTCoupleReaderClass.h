// BeckTCoupleReaderClass.h, 2/27/22b
#pragma once
#include <BeckBiotaDefines.h>
#include <max6675.h>

class BeckTCoupleReaderClass{
public:
  BeckTCoupleReaderClass();
  BeckTCoupleReaderClass(byte cSPI_MISO_Pin, byte cSPI_CLK_Pin, byte cCS_Pin);
  virtual ~BeckTCoupleReaderClass();

  double  Handle          (void);

protected:
//  MAX6675     _oMAX6675_Thermocouple;
//  MAX6675     *_poMAX6675_Thermocouple;
  //MAX6675     _oMAX6675_Thermocouple;
  uint8_t       _ucSPI_MISO_Pin    = 0;
  uint8_t       _ucSPI_CLK_Pin     = 0;
  uint8_t       _ucSPI_CS_Pin      = 0;
  uint16_t      _usDegF_Value      = 0;
};  //BeckTCoupleReaderClass
//Last line.
