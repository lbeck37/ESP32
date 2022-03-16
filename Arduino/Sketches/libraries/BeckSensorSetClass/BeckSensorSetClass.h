// BeckSensorSetClass.h, 3/16/22c
#pragma once
#include <BeckSensorClass.h>
#include <BeckE32_Defines.h>

class BeckSensorSetClass{
public:
  BeckSensorSetClass           ();
  //BeckSensorSetClass           (int wSensorSetID);
  //BeckSensorSetClass           (BeckSampleDataClass* _apoCarSamples [][_wNumSensors + 1], int wSensorSetID);
  BeckSensorSetClass           (BeckSampleDataClass* apoCarSamples[_wNumSensorSets + 1][_wNumSensors + 1], int wSensorSetID);
  virtual ~BeckSensorSetClass  ();

  void  BuildSensors           ();
  bool  bBegin                ();
  void  ReadSensorSet          (uint32_t uwSampleTime);
  void  PrintSensorSetData     ();

private:
  int                   _wSensorSetID;          //1, 2, 3, 4, possibly for RF, LF, LR, RR
  uint32_t              _uwSampleTime;
  BeckSensorClass*      _apoSensor          [_wNumSensors + 1];
  //BeckSampleDataClass*  _apoCarSamples      [_wNumSensorSets + 1] [];
  //BeckSampleDataClass*  _apoCarSamples      [] [_wNumSensors + 1];
  BeckSampleDataClass*  _apoCarSamples      [_wNumSensorSets + 1] [_wNumSensors + 1];
  const int             _awI2CAdresses      [4] {_wI2C_Pressure, _wI2C_DegF1, _wI2C_DegF2, _wI2C_DegF3};
};  //BeckSensorSetClass
//Last line.
