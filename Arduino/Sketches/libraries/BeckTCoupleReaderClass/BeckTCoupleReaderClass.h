// BeckTCoupleReaderClass.h, 3/5/22d
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

  bool    begin                     (uint8_t ucI2CAddress);
  double  Handle                    (void);

protected:
#if DO_MAX6675
  BeckMAX6675Class  _oMAX6675_TCouple;
#else
  Adafruit_MCP9600  _oMCP9600_TCouple;
#endif
  int8_t            _cSPI_CS_Pin;
  uint8_t           _ucI2CAddress;
  float             _fDegF_Value      = 0.0;
};  //BeckTCoupleReaderClass
//Last line.
