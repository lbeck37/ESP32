// BeckCarSetClass.h, 3/16/22b
#pragma once
#include <BeckSampleDataClass.h>
#include <BeckSensorSetClass.h>
#include <BeckE32_Defines.h>

class BeckCarSetClass{
public:
  BeckCarSetClass             ();
  virtual ~BeckCarSetClass    ();

  bool  bBegin                ();
  void  ReadSensorSet         (uint32_t uwSampleTime, int wSensorID);
  void  PrintLogData          ();

private:
  void  BuildObjectData       ();

  BeckSensorSetClass*         _apoSensorSet  [_wNumSensorSets + 1];
  BeckSampleDataClass*        _apoCarSamples[_wNumSensorSets + 1] [_wNumSensors + 1];
};  //BeckCarSetClass
//Last line.
