// BeckCarSetClass.h, 3/18/22b
#pragma once
#include <BeckDataMgrClass.h>
#if USE_OLD_DATA_ARRAY
  #include <BeckSampleDataClass.h>
#endif
#include <BeckSensorSetClass.h>
#include <BeckE32_Defines.h>

class BeckCarSetClass{
public:
  BeckCarSetClass             ();
  virtual ~BeckCarSetClass    ();

  bool  bBegin                ();
  void  ReadSensorSet         (uint32_t uwSampleTime, int wSensorSetID);
  void  PrintLogData          ();

private:
  void  BuildObjectData       ();

  BeckSensorSetClass*         _apoSensorSet   [_wNumSensorSets + 1];
  BeckDataMgrClass*           _poDataMgr      {nullptr};
#if USE_OLD_DATA_ARRAY
  BeckSampleDataClass*        _apoCarSamples  [_wNumSensorSets + 1] [_wNumSensors + 1];
#endif
};  //BeckCarSetClass
//Last line.
