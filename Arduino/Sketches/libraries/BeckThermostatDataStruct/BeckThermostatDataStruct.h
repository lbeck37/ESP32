// 4/19/21a, BeckThermostatDataStruct.h
#pragma once

struct ThermostatDataStruct {
  float   fCurrentDegF  = 68.0;
  float   fSetpoint     = 70.0;
  float   fMaxHeatRange = 0.10;
  bool    bThermoOn     = false;
  bool    bHeatOn       = false;
};

extern ThermostatDataStruct ThermostatData;
//Last line.
