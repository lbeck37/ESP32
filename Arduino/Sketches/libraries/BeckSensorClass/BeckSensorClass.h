// BeckSensorClass.h, copied from BeckProbeClass.h, 3/16/22b
#pragma once
#include <BeckSampleDataClass.h>
#include <BeckE32_Defines.h>
#include <BeckTCoupleSensorClass.h>

class BeckSensorClass{
public:
  BeckSensorClass();
  BeckSensorClass(int wSensorID, int wI2CAddress);
  virtual ~BeckSensorClass();

  bool    bBegin           ();
  float   fReadSensor      (uint32_t uwSampleTime, int wSensorID);

private:
  int                       _wSensorID        {0};
  int                       _wI2CAddress      {0};
  //BeckTCoupleReaderClass*   _poTCoupleReader  {nullptr};
  BeckTCoupleSensorClass*   _poTCoupleSensor  {nullptr};
};  //BeckSensorClass
//Last line.
