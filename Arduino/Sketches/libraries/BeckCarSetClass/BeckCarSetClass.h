// BeckCarSetClass.h, 3/29/22a
#pragma once
#include <BeckE32_Defines.h>
#include <BeckDataMgrClass.h>
#include <BeckSensorSetClass.h>
#include <BeckButtonsClass.h>
#include <BeckTireTempDisplayClass.h>
#include <BeckTireTempNTPClass.h>

class BeckCarSetClass{
public:
  BeckCarSetClass               ();
  virtual ~BeckCarSetClass      ();

  void  Begin                   ();
  void  ReadSensorSet           (int wSensorSetID);
  void  HandleLoop              ();
  void  DisplayUpdate           (int wSensorID);
  bool  bHandleLogging          ();
  void  PrintLogData            ();

private:
  void          BuildObjectData ();

  static int    _wButtonWasPressed;

  BeckSensorSetClass*         _apoSensorSet             [_wNumSensorSets + 1];
  BeckDataMgrClass*           _poDataMgr                {nullptr};
  BeckTireTempDisplayClass*   _poDisplay                {nullptr};
  BeckTireTempNTPClass*       _poNTP                    {nullptr};
  BeckButtonsClass*           _poButtons                {nullptr};

  uint32_t                    _uwEpochTime;
  unsigned long               _ulNextHandleLoggingMsec   =    0;
  unsigned long               _ulHandleSensorsPeriodMsec = 5000;     //mSec between logging to serial and bottom of screen
};  //BeckCarSetClass
//Last line.
