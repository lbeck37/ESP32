// BeckProbeSetClass.h, 3/13/22b
#pragma once
#include <BeckProbeClass.h>
#include <BeckE32_Defines.h>

class BeckProbeSetClass{
public:
  BeckProbeSetClass           (void);
  BeckProbeSetClass           (int8_t cProbeSetID);
  virtual ~BeckProbeSetClass  (void);

  void  BuildProbes           (void);
  void  PrintProbeSetData     (void);

  void    Handle              (uint32_t uwSampleTime);

private:
  int8_t                _cProbeSetID;          //1, 2, 3, 4, possibly for RF, LF, LR, RR
  uint32_t              _uwSampleTime;
  BeckProbeClass*       _apoProbe         [_wNumProbes + 1];
  uint8_t               _aucI2CAdresses   [_wNumProbes + 1];
  float                 _afProbeDegF      [_wNumProbes + 1];
  //BeckSampleDataClass   _aoSampleData   [_wNumProbes + 1];

};  //BeckProbeSetClass
//Last line.
