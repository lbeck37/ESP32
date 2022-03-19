// BeckReadingDataClass.h, 3/18/22a4
#pragma once
#include <BeckE32_Defines.h>

class BeckReadingDataClass{
public:
  BeckReadingDataClass           ();
  BeckReadingDataClass           (int wSensorSetID, int wSensorID);
  virtual ~BeckReadingDataClass  ();

  uint32_t              uwGetReadingTime      ();
  void                  SetReadingTime        (uint32_t uwReadingTime);

  void                  SetDegF               (float fDegF);
  float                 fGetDegF              ();

  void                  SetLastDegF           (float fLastDegFValue);
  float                 fGetLastDegF          ();

  void                  SetDegFChanged        ();
  bool                  bGetDegFChanged       ();

private:
  int                   _wSensorID            = 0;
  int                   _wSensorSetID         = 0;
  uint32_t              _uwReadingTime        = 0;    //Also called Epoch time
  float                 _fDegF                = 37.0;
  float                 _fLastDegF            = 0.0;
  bool                  _bDegF_FirstTime      = true;
  bool                  _bDegFChanged         = true;
  bool                  _bSensorOK            = true;
};  //BeckReadingDataClass
//Last line.
