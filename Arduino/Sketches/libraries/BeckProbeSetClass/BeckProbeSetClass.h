// BeckProbeSetClass.h, 3/15/22b
#pragma once
#include <BeckProbeClass.h>
#include <BeckE32_Defines.h>

class BeckProbeSetClass{
public:
  BeckProbeSetClass           ();
  BeckProbeSetClass           (int wProbeSetID);
  virtual ~BeckProbeSetClass  ();

  void  BuildProbes           ();
  bool  bBegin                ();
  void  PrintProbeSetData     ();
  void  ReadProbeSet          (uint32_t uwSampleTime, int wProbeID);

private:
  int                   _wProbeSetID;          //1, 2, 3, 4, possibly for RF, LF, LR, RR
  uint32_t              _uwSampleTime;
  BeckProbeClass*       _apoProbe         [_wNumProbes + 1];
  //uint8_t               _aucI2CAdresses   [_wNumProbes + 1];
  const int             _awI2CAdresses   [4] {_wI2C_Pressure, _wI2C_DegF1, _wI2C_DegF2, _wI2C_DegF3};
};  //BeckProbeSetClass
//Last line.
