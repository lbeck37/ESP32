// BeckSensorSetClass.h, copied from BeckProbeSetClass.h, 3/16/22a
#pragma once
#include <BeckSensorClass.h>
#include <BeckE32_Defines.h>

class BeckSensorSetClass{
public:
  BeckSensorSetClass           ();
  BeckSensorSetClass           (int wSensorSetID);
  virtual ~BeckSensorSetClass  ();

  void  BuildSensors           ();
  bool  bBegin                ();
  void  PrintSensorSetData     ();
  void  ReadSensorSet          (uint32_t uwSampleTime, int wSensorID);

private:
  int                   _wSensorSetID;          //1, 2, 3, 4, possibly for RF, LF, LR, RR
  uint32_t              _uwSampleTime;
  BeckSensorClass*      _apoSensor         [_wNumSensors + 1];
  const int             _awI2CAdresses   [4] {_wI2C_Pressure, _wI2C_DegF1, _wI2C_DegF2, _wI2C_DegF3};
};  //BeckSensorSetClass
//Last line.
