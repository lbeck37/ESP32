// BeckCarSetClass.h, 3/29/22d
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
  void  HandleLoop              ();

private:
  void  ReadSensorSet           (int wSensorSetID);
  bool  bDisplayLog             ();
  void  PrintLogData            ();
  void  BuildObjectData         ();

  static int    _wButtonWasPressed;

  BeckSensorSetClass*         _apoSensorSet             [_wNumSensorSets + 1];
  BeckDataMgrClass*           _poDataMgr                {nullptr};
  BeckTireTempDisplayClass*   _poDisplay                {nullptr};
  BeckTireTempNTPClass*       _poNTP                    {nullptr};
  BeckButtonsClass*           _poButtons                {nullptr};

  uint32_t                    _uwEpochTime;
  unsigned long               _ulNextDispLogMsec    =    0;
  unsigned long               _ulDispLogPeriodMsec  = 1000;     //mSec between updating current temp on display
};  //BeckCarSetClass
//Last line.
