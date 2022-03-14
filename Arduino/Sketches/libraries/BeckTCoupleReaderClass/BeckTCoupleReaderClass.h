// BeckTCoupleReaderClass.h, 3/13/22d
#pragma once
#include <BeckE32_Defines.h>
#include<SparkFun_MCP9600.h>

class BeckTCoupleReaderClass{
public:
  BeckTCoupleReaderClass            ();
  BeckTCoupleReaderClass            (uint8_t ucI2CAddress);
  virtual ~BeckTCoupleReaderClass   ();

  bool    begin                     (uint8_t ucI2CAddress);
  float   fHandle                   ();
  bool    bGetProbeOK               ();

private:
  void    SetupMCP9600              (int8_t cI2CAddress);
  float   fGetDegF                  ();

  MCP9600*      _poMCP9600_TCouple;
  uint8_t       _ucI2CAddress;
  float         _fDegF            = 0.0;
  bool          _bTCoupleOK       = true;
};  //BeckTCoupleReaderClass
//Last line.
