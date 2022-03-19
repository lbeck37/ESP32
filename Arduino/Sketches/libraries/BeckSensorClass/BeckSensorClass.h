// BeckSensorClass.h, 3/16/22e
#pragma once
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
