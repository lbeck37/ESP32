// BeckProbeClass.h, 3/14/22c
#pragma once
#include <BeckSampleDataClass.h>
#include <BeckE32_Defines.h>
#include <BeckTCoupleReaderClass.h>

class BeckProbeClass{
public:
  BeckProbeClass();
  BeckProbeClass(int wProbeID, int wI2CAddress);
  virtual ~BeckProbeClass();

  void    Begin           ();
  float   fReadProbe      (uint32_t uwSampleTime, int wProbeID);
  //float   fGetDegF      ();

private:
  int                       _wProbeID;
  int                       _wI2CAddress     {0};
  //SampleDataStruct          _stSampleData;
  BeckTCoupleReaderClass*   _poTCoupleReader  {nullptr};
};  //BeckProbeClass
//Last line.
