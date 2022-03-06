// BeckTCoupleReaderClass.h, 3/6/22a
#pragma once
#include <BeckE32_Defines.h>
#include<Adafruit_MCP9600.h>

class BeckTCoupleReaderClass{
public:
  BeckTCoupleReaderClass            ();
  BeckTCoupleReaderClass            (uint8_t ucI2CAddress);
  virtual ~BeckTCoupleReaderClass   ();

  bool    begin                     (uint8_t ucI2CAddress);
  double  Handle                    (void);

protected:
  Adafruit_MCP9600    _oMCP9600_TCouple;
  uint8_t             _ucI2CAddress;
  float               _fDegF_Value      = 0.0;
};  //BeckTCoupleReaderClass
//Last line.
