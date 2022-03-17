// BeckTCoupleSensorClass.h, 3/17/22b
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

private:
  bool    bBegin                    ();
  float   fGetDegF                  ();

  //MCP9600*      _poMCP9600_TCouple  {nullptr};
  MCP9600*      _poMCP9600_TCouple;
  int           _wI2CAddress;
  float         _fDegF            = 37.03;
  bool          _bTCoupleOK       = true;
};  //BeckTCoupleSensorClass
//Last line.
