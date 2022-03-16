// BeckCarSetClass.h, 3/14/22e
#pragma once
#include <BeckSampleDataClass.h>
#include <BeckProbeSetClass.h>
#include <BeckE32_Defines.h>

class BeckCarSetClass{
public:
  BeckCarSetClass             ();
  virtual ~BeckCarSetClass    ();

  bool  bBegin                ();
  void  ReadProbeSet          (uint32_t uwSampleTime, int wProbeID);
  void  PrintLogData          ();

private:
  void  BuildObjectData       ();

  BeckProbeSetClass*      _apoProbeSet  [_wNumProbeSets + 1];
  BeckSampleDataClass*    _apoCarSamples[_wNumProbeSets + 1] [_wNumProbes + 1];
};  //BeckCarSetClass
//Last line.
