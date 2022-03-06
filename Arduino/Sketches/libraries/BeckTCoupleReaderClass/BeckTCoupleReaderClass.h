// BeckTCoupleReaderClass.h, 3/5/22c
#pragma once
#include <BeckE32_Defines.h>
#if DO_MAX6675
  #include <BeckMAX6675Lib.h>
#else
  #include<Adafruit_MCP9600.h>
#endif

class BeckTCoupleReaderClass{
public:
  BeckTCoupleReaderClass            ();
  BeckTCoupleReaderClass            (int8_t  cSPI_CS_Pin);
  BeckTCoupleReaderClass            (uint8_t ucI2CAddress);
  virtual ~BeckTCoupleReaderClass   ();

  double  Handle                    (void);

protected:
  int8_t            _cSPI_CS_Pin;
#if DO_MAX6675
  BeckMAX6675Class  _oMAX6675_Thermocouple;
#else
  Adafruit_MCP9600  _oMCP9600_TCouple;
  uint8_t          _ucI2CAddress;
#endif
  uint16_t          _usDegF_Value      = 0;
};  //BeckTCoupleReaderClass
//Last line.
