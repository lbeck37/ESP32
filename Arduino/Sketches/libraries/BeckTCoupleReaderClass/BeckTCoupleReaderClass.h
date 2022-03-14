// BeckTCoupleReaderClass.h, 3/14/22b
#pragma once
#include <BeckE32_Defines.h>
#include<SparkFun_MCP9600.h>

class BeckTCoupleReaderClass{
public:
  BeckTCoupleReaderClass            ();
  BeckTCoupleReaderClass            (uint8_t ucI2CAddress);
  virtual ~BeckTCoupleReaderClass   ();

  bool    begin                     (uint8_t ucI2CAddress);
  void    Handle                    ();
  bool    bGetProbeOK               ();
  float   fGetDegF                  ();

private:
  void    SetupMCP9600              (int8_t cI2CAddress);

  MCP9600*      _poMCP9600_TCouple;
  uint8_t       _ucI2CAddress;
  float         _fDegF            = 37.03;
  bool          _bTCoupleOK       = true;
};  //BeckTCoupleReaderClass
//Last line.
