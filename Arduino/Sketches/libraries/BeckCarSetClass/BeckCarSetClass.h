// BeckCarSetClass.h, 3/19/22b
#pragma once
#include <BeckE32_Defines.h>
#include <BeckDataMgrClass.h>
#include <BeckSensorSetClass.h>
#include <BeckTireTempDisplayClass.h>

class BeckCarSetClass{
public:
  BeckCarSetClass             ();
  virtual ~BeckCarSetClass    ();

  void  Begin                 ();
  void  ReadSensorSet         (uint32_t uwSampleTime, int wSensorSetID);
  void  UpdateDisplay         ();
  void  PrintLogData          ();

private:
  void  BuildObjectData       ();

  BeckSensorSetClass*         _apoSensorSet   [_wNumSensorSets + 1];
  BeckDataMgrClass*           _poDataMgr      {nullptr};
  BeckTireTempDisplayClass*   _poDisplay      {nullptr};
};  //BeckCarSetClass
//Last line.
