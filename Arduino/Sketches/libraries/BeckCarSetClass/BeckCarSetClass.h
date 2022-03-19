// BeckCarSetClass.h, 3/19/22d
#pragma once
#include <BeckE32_Defines.h>
#include <BeckDataMgrClass.h>
#include <BeckSensorSetClass.h>
#include <BeckTireTempDisplayClass.h>
#include <BeckTireTempNTPClass.h>

class BeckCarSetClass{
public:
  BeckCarSetClass             ();
  virtual ~BeckCarSetClass    ();

  void  Begin                 ();
  void  ReadSensorSet         (int wSensorSetID);
  void  UpdateDisplay         ();
  void  HandleLogging         ();
  void  PrintLogData          ();

private:
  void  BuildObjectData       ();

  BeckSensorSetClass*         _apoSensorSet             [_wNumSensorSets + 1];
  BeckDataMgrClass*           _poDataMgr                {nullptr};
  BeckTireTempDisplayClass*   _poDisplay                {nullptr};
  BeckTireTempNTPClass*       _poNTP                    {nullptr};

  uint32_t                    _uwEpochTime;
  unsigned long               _ulNextHandleSensorsMsec   =    0;
  unsigned long               _ulHandleSensorsPeriodMsec = 5000;     //mSec between logging to serial and bottom of screen
};  //BeckCarSetClass
//Last line.
