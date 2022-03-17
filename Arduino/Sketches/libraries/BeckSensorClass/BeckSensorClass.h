// BeckSensorClass.h, 3/17/22a
#pragma once
//#include <BeckSampleDataClass.h>
#include <BeckE32_Defines.h>
#include <BeckTCoupleSensorClass.h>

class BeckSensorClass{
public:
  BeckSensorClass();
  BeckSensorClass(int wSensorID, int wI2CAddress);
  virtual ~BeckSensorClass();

  bool    bBegin           ();
  float   fReadSensor      ();

private:
  bool                      _bSensorOK        {true};
  int                       _wSensorID        {0};
  int                       _wI2CAddress      {0};
  BeckTCoupleSensorClass*   _poTCoupleSensor  {nullptr};
};  //BeckSensorClass
//Last line.
