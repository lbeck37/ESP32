// 4/15/21a, BeckThermoDataClass.h
#pragma once

#include <BeckBiotaLib.h>

class ThermoDataClass{
protected:
  float   fCurrentDegF;
  float   fSetpointDegF;
  float   fMaxHeatRangeF;
  bool    bThermoOn;
  bool    bHeatOn;

public:
  ThermoDataClass();
  virtual ~ThermoDataClass();

  void  SetCurrentTemperature         (float fNewTemperature);
  void  SetCurrentSetpoint            (float fNewSetpoint);
  void  SetMaxHeatRange               (float fNewMaxHeatRang);
  void  SetThermoOn                   (bool bNewThermoOn);
  void  SetHeatOn                     (bool bNewHeatOn);

  float GetCurrentTemperature         (void);
  float GetCurrentSetpoint            (void);
  float GetMaxHeatRange               (void);
  bool  GetThermoOn                   (void);
  bool  GetHeatOn                     (void);
};  //ThermoDataClass

extern ThermoDataClass   ThermostatData;

//Last line.
