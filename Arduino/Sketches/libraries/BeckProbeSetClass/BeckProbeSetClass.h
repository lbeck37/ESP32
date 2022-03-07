// BeckProbeSetClass.h, 3/6/22d
#pragma once
#include <BeckProbeClass.h>
#include <BeckE32_Defines.h>

class BeckProbeSetClass{
public:
  BeckProbeSetClass           (void);
  virtual ~BeckProbeSetClass  (void);

  void  BuildProbes           (void);
  void  PrintProbeSetData     (void);

  void    Handle              (uint32_t uwSampleTime);

protected:
  uint32_t              _uwSampleTime;
  BeckProbeClass        _aoProbes       [_wNumProbes + 1];
  BeckSampleDataClass   _aoSampleData   [_wNumProbes + 1];
  uint8_t               _aucI2CAdresses [_wNumProbes + 1];
  float                 _afProbeDegF    [_wNumProbes + 1];

};  //BeckProbeSetClass
//Last line.
