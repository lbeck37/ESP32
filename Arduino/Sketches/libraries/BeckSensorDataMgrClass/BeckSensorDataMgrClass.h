// BeckSensorDataMgrClass.h, 3/16/22b
#pragma once
#include <BeckE32_Defines.h>
#include <BeckSampleDataClass.h>

class BeckSensorDataMgrClass{
public:
  BeckSensorDataMgrClass           ();
  //BeckSensorDataMgrClass           (int wSensorSetID, int wSensorID);
  virtual ~BeckSensorDataMgrClass  ();

  uint32_t              uwGetSampleTime       (int wSensorSetID, int wSensorID);
  void                  SetSampleTime         (int wSensorSetID, int wSensorID, uint32_t uwSampleTime);

  void                  SetDegF               (int wSensorSetID, int wSensorID, float fNewDegFValue);
  float                 fGetDegF              (int wSensorSetID, int wSensorID);

  float                 fGetLastDegF          (int wSensorSetID, int wSensorID);

  void                  SetDegFChanged        (int wSensorSetID, int wSensorID);
  bool                  bGetDegFChanged       (int wSensorSetID, int wSensorID);

private:
  void                  BuildSensorData       ();
  //void                  SetLastDegF           (int wSensorSetID, int wSensorID, float fLastDegFValue);

  BeckSampleDataClass*  _apoCarSamples[_wNumSensorSets + 1] [_wNumSensors + 1];

/*
  int                   _wSensorID            = 0;
  int                   _wSensorSetID         = 0;
  uint32_t              _uwSampleTime         = 0;    //Also called Epoc time
  float                 _fDegF                = 0.0;
  float                 _fLastDegF            = 0.0;
  bool                  _bDegF_FirstTime      = true;
  bool                  _bDegFChanged         = true;
  bool                  _bSensorOK            = true;
*/
};  //BeckSensorDataMgrClass

extern BeckSensorDataMgrClass      _oSensorDataMgr;
//Last line.
