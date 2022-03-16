// BeckProbeClass.h, 3/15/22c
#pragma once
#include <BeckSampleDataClass.h>
#include <BeckE32_Defines.h>
#include <BeckTCoupleReaderClass.h>

class BeckProbeClass{
public:
  BeckProbeClass();
  BeckProbeClass(int wProbeID, int wI2CAddress);
  virtual ~BeckProbeClass();

  bool    bBegin          ();
  float   fReadProbe      (uint32_t uwSampleTime, int wProbeID);

private:
  int                       _wProbeID         {0};
  int                       _wI2CAddress      {0};
  BeckTCoupleReaderClass*   _poTCoupleReader  {nullptr};
};  //BeckProbeClass
//Last line.
