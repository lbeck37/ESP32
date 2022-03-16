// BeckTCoupleReaderClass.h, 3/15/22f
#pragma once
#include <BeckE32_Defines.h>
#include<SparkFun_MCP9600.h>

class BeckTCoupleReaderClass{
public:
  BeckTCoupleReaderClass            ();
  BeckTCoupleReaderClass            (int wI2CAddress);
  virtual ~BeckTCoupleReaderClass   ();

  void    SetupMCP9600              ();
  float   fReadProbe                ();
  bool    bGetProbeOK               ();
  float   fGetDegF                  ();

private:
  bool    bBegin                    ();

  MCP9600*      _poMCP9600_TCouple;
  int           _wI2CAddress;
  float         _fDegF            = 37.03;
  bool          _bTCoupleOK       = true;
};  //BeckTCoupleReaderClass
//Last line.
