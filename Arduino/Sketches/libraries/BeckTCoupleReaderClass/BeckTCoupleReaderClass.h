// BeckTCoupleReaderClass.h, 3/5/22b
#pragma once
#include <BeckE32_Defines.h>
//#include <BeckMAX6675Lib.h>
#include<Adafruit_MCP9600.h>

class BeckTCoupleReaderClass{
public:
  BeckTCoupleReaderClass            ();
  BeckTCoupleReaderClass            (int8_t cSPI_CS_Pin);
  virtual ~BeckTCoupleReaderClass   ();

  double  Handle                    (void);

protected:
  int8_t            _cSPI_CS_Pin;
  //BeckMAX6675Class  _oMAX6675_Thermocouple;
  Adafruit_MCP9600  _oMCP9600_TCouple;
  uint16_t          _usDegF_Value      = 0;
};  //BeckTCoupleReaderClass
//Last line.
