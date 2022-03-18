// BeckDataMgrClass.h, 3/18/22b
#pragma once
#include <BeckE32_Defines.h>
#include <BeckReadingDataClass.h>

class BeckDataMgrClass{
public:
  BeckDataMgrClass           ();
  virtual ~BeckDataMgrClass  ();

  uint32_t              uwGetReadingTime       (int wSensorSetID, int wSensorID);
  void                  SetReadingTime         (int wSensorSetID, int wSensorID, uint32_t uwReadingTime);

  void                  SetDegF               (int wSensorSetID, int wSensorID, float fNewDegFValue);
  float                 fGetDegF              (int wSensorSetID, int wSensorID);

  float                 fGetLastDegF          (int wSensorSetID, int wSensorID);

  void                  SetDegFChanged        (int wSensorSetID, int wSensorID);
  bool                  bGetDegFChanged       (int wSensorSetID, int wSensorID);

private:
  void                  BuildSensorData       ();
  //void                  SetLastDegF           (int wSensorSetID, int wSensorID, float fLastDegFValue);

  BeckReadingDataClass*  _apoCarReadings[_wNumSensorSets + 1] [_wNumSensors + 1];

};  //BeckDataMgrClass

extern BeckDataMgrClass      _oSensorDataMgr;
//Last line.
