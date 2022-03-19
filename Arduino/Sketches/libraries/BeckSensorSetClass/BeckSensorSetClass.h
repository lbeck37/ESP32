// BeckSensorSetClass.h, 3/18/22b
#pragma once
#include <BeckSensorClass.h>
#include <BeckE32_Defines.h>
#include <BeckDataMgrClass.h>

class BeckSensorSetClass{
public:
  BeckSensorSetClass           ();
  //BeckSensorSetClass           (BeckSampleDataClass* apoCarSamples[][_wNumSensors + 1], int wSensorSetID);
#if USE_OLD_DATA_ARRAY
  BeckSensorSetClass           (BeckDataMgrClass* poDataMgr, BeckSampleDataClass* apoCarSamples[][_wNumSensors + 1], int wSensorSetID);
#else
  BeckSensorSetClass           (BeckDataMgrClass* poDataMgr, int wSensorSetID);
#endif
  virtual ~BeckSensorSetClass  ();

  void  BuildSensors           ();
  bool  bBegin                 ();
  void  ReadSensorSet          (uint32_t uwSampleTime);
  void  PrintSensorSetData     ();

private:
  int                   _wSensorSetID;          //1, 2, 3, 4, possibly for RF, LF, LR, RR
  uint32_t              _uwSampleTime;
  BeckSensorClass*      _apoSensor          [_wNumSensors + 1];
#if USE_OLD_DATA_ARRAY
  BeckSampleDataClass*  _apoCarSamples      [_wNumSensorSets + 1] [_wNumSensors + 1];
#endif
  BeckDataMgrClass*     _poDataMgr          {};
  const int             _awI2CAdresses      [4] {_wI2C_Pressure, _wI2C_DegF1, _wI2C_DegF2, _wI2C_DegF3};
};  //BeckSensorSetClass
//Last line.
