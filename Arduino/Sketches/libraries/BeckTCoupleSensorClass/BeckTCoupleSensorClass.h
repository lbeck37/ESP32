// BeckTCoupleSensorClass.h, 3/16/22a
#pragma once
#include <BeckE32_Defines.h>
#include<SparkFun_MCP9600.h>

class BeckTCoupleSensorClass{
public:
  BeckTCoupleSensorClass            ();
  BeckTCoupleSensorClass            (int wI2CAddress);
  virtual ~BeckTCoupleSensorClass   ();

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
};  //BeckTCoupleSensorClass
//Last line.
