// BeckCarSetClass.h, 3/16/22c
#pragma once
//#include <BeckSampleDataClass.h>
#include <BeckSensorSetClass.h>
#include <BeckE32_Defines.h>

class BeckCarSetClass{
public:
  BeckCarSetClass             ();
  virtual ~BeckCarSetClass    ();

  void  BuildSensorSets       ();
  bool  bBegin                ();
  void  ReadSensorSet         (uint32_t uwSampleTime, int wSensorSetID);
  void  PrintLogData          ();

private:
  BeckSensorSetClass*         _apoSensorSet[_wNumSensorSets + 1];
};  //BeckCarSetClass
//Last line.
