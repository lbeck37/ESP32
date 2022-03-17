// BeckSampleDataClass.h, 3/16/22c
#pragma once
#include <BeckE32_Defines.h>

class BeckSampleDataClass{
public:
  BeckSampleDataClass           ();
  BeckSampleDataClass           (int wSensorSetID, int wSensorID);
  virtual ~BeckSampleDataClass  ();

  uint32_t              uwGetSampleTime       ();
  void                  SetSampleTime         (uint32_t uwSampleTime);

  void                  SetDegF               (float fNewDegFValue);
  float                 fGetDegF              ();

  float                 fGetLastDegF          ();

  void                  SetDegFChanged        ();
  bool                  bGetDegFChanged       ();

private:
  void                  SetLastDegF           (float fLastDegFValue);

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
