// BeckSensorClass.h, copied from BeckProbeClass.h, 3/16/22c
#pragma once
#include <BeckE32_Defines.h>
#if USE_OLD_DATA_ARRAY
  #include <BeckSampleDataClass.h>
#endif
#include <BeckTCoupleSensorClass.h>

class BeckSensorClass{
public:
  BeckSensorClass();
  BeckSensorClass(int wSensorID, int wI2CAddress);
  virtual ~BeckSensorClass();

  bool    bBegin           ();
  //float   fReadSensor      (uint32_t uwSampleTime, int wSensorID);
  float   fReadSensor      ();

private:
  bool                      _bSensorOK        {true};
  int                       _wSensorID        {0};
  int                       _wI2CAddress      {0};
  BeckTCoupleSensorClass*   _poTCoupleSensor  {nullptr};
};  //BeckSensorClass
//Last line.
