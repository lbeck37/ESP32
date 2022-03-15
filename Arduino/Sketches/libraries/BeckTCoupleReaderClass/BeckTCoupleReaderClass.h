// BeckTCoupleReaderClass.h, 3/14/22c
#pragma once
#include <BeckE32_Defines.h>
#include<SparkFun_MCP9600.h>

class BeckTCoupleReaderClass{
public:
  BeckTCoupleReaderClass            ();
  BeckTCoupleReaderClass            (int wI2CAddress);
  virtual ~BeckTCoupleReaderClass   ();

  bool    begin                     (int wI2CAddress);
  float   fReadProbe                ();
  bool    bGetProbeOK               ();
  float   fGetDegF                  ();

private:
  void    SetupMCP9600              (int wI2CAddress);

  MCP9600*      _poMCP9600_TCouple;
  int           _wI2CAddress;
  float         _fDegF            = 37.03;
  bool          _bTCoupleOK       = true;
};  //BeckTCoupleReaderClass
//Last line.
