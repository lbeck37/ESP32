// BeckCarSetClass.h, 3/28/22a
#pragma once
#include <BeckE32_Defines.h>
#include <BeckDataMgrClass.h>
#include <BeckSensorSetClass.h>
#include <BeckButtonsClass.h>
#include <BeckTireTempDisplayClass.h>
#include <BeckTireTempNTPClass.h>

//#include <EasyButton.h>

class BeckCarSetClass{
public:
  BeckCarSetClass               ();
  virtual ~BeckCarSetClass      ();

  void  Begin                   ();
  void  ReadSensorSet           (int wSensorSetID);
  void  HandleLoop              ();
  void  UpdateDisplay           ();
  void  HandleLogging           ();
  void  PrintLogData            ();

private:
  static void   CarSetCallback  ();
/*
  static void   CarSetCallback2 ();
  static void   CarSetCallback3 ();
  static void   CarSetCallback4 ();
*/

  void          BuildObjectData ();

  static int    _wButtonWasPressed;

  BeckSensorSetClass*         _apoSensorSet             [_wNumSensorSets + 1];
  BeckDataMgrClass*           _poDataMgr                {nullptr};
  BeckTireTempDisplayClass*   _poDisplay                {nullptr};
  BeckTireTempNTPClass*       _poNTP                    {nullptr};
  BeckButtonsClass*            _poButtons               {nullptr};
  //EasyButton                  _TestButton;

  uint32_t                    _uwEpochTime;
  unsigned long               _ulNextHandleSensorsMsec   =    0;
  unsigned long               _ulHandleSensorsPeriodMsec = 5000;     //mSec between logging to serial and bottom of screen
};  //BeckCarSetClass
//Last line.
