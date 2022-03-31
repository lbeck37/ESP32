// BeckCarSetClass.h, 3/31/22c
#pragma once
#include <BeckE32_Defines.h>
#include <BeckDataMgrClass.h>
#include <BeckSensorSetClass.h>
#include <BeckButtonsClass.h>
#include <BeckDisplayClass.h>
#include <BeckTireTempNTPClass.h>

class BeckCarSetClass{
public:
  BeckCarSetClass               ();
  virtual ~BeckCarSetClass      ();

  void  Begin                   ();
  void  HandleLoop              ();

private:
  void  ReadSensorSet           (int wSensorSetID);
  void  DisplaySensorSet        (int wSensorSetID);
  void  ReadLogData             ();
  void  DisplayLogData          ();
  void  PrintLogData            ();
  void  BuildObjectData         ();

  static int    _wButtonWasPressed;

  BeckSensorSetClass*         _apoSensorSet             [_wNumSensorSets + 1];
  BeckDataMgrClass*           _poDataMgr                {nullptr};
  BeckDisplayClass*           _poDisplay                {nullptr};
  BeckTireTempNTPClass*       _poNTP                    {nullptr};
  BeckButtonsClass*           _poButtons                {nullptr};

  uint32_t                    _uwEpochTime;
};  //BeckCarSetClass
//Last line.
