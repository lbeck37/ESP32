// BeckSensorSetClass.h, 4/1/22a
#pragma once
#include <BeckSensorClass.h>
#include <BeckE32_Defines.h>
#include <BeckDataMgrClass.h>
#include <BeckDisplayClass.h>

class BeckSensorSetClass{
public:
  BeckSensorSetClass           ();
  BeckSensorSetClass           (BeckDisplayClass* poDisplay, BeckDataMgrClass* poDataMgr, int wSensorSetID);
  virtual ~BeckSensorSetClass  ();

  void  BuildSensors           ();
  bool  bBegin                 ();
  void  ReadSensorSet          (uint32_t uwSampleTime);
  void  DisplaySensorSet       (int wSensorSetID);
  void  PrintSensorSetData     ();

private:
  int                         _wSensorSetID;          //1, 2, 3, 4, possibly for RF, LF, LR, RR
  uint32_t                    _uwSampleTime;
  const int                   _awI2CAdresses      [4] {_wI2C_Pressure, _wI2C_DegF1, _wI2C_DegF2, _wI2C_DegF3};
  BeckSensorClass*            _apoSensor          [_wNumSensors + 1];
  BeckDataMgrClass*           _poDataMgr          {};
  BeckDisplayClass*           _poDisplay          {};
};  //BeckSensorSetClass
//Last line.
