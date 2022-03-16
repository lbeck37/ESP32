// BeckSampleDataClass.h, 3/16/22a
#pragma once
#include <BeckE32_Defines.h>

class BeckSampleDataClass{
public:
  BeckSampleDataClass           ();
  BeckSampleDataClass           (int wSensorSetID, int wSensorID);
  virtual ~BeckSampleDataClass  ();

  uint32_t              uwGetSampleTime       (int wSensorSetID, int wSensorID);
  void                  SetSampleTime         (int wSensorSetID, int wSensorID, uint32_t uwSampleTime);

  void                  SetDegF               (int wSensorSetID, int wSensorID, float fNewDegFValue);
  float                 fGetDegF              (int wSensorSetID, int wSensorID);

  void                  SetLastDegF           (int wSensorSetID, int wSensorID, float fLastDegFValue);
  float                 fGetLastDegF          (int wSensorSetID, int wSensorID);

  void                  SetDegFChanged        (int wSensorSetID, int wSensorID);
  bool                  bGetDegFChanged       (int wSensorSetID, int wSensorID);

private:
  int                   _wSensorID            = 0;
  int                   _wSensorSetID         = 0;
  uint32_t              _uwSampleTime         = 0;    //Also called Epoc time
  float                 _fDegF                = 0.0;
  float                 _fLastDegF            = 0.0;
  bool                  _bDegF_FirstTime      = true;
  bool                  _bDegFChanged         = true;
  bool                  _bSensorOK            = true;
};  //BeckSampleDataClass
//Last line.
