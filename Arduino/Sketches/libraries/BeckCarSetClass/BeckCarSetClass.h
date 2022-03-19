// BeckCarSetClass.h, 3/18/22c
#pragma once
#include <BeckDataMgrClass.h>
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
};  //BeckCarSetClass
//Last line.
