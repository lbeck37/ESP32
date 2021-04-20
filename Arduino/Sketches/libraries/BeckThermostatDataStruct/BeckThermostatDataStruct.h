// 4/19/21b, BeckThermostatDataStruct.h
#pragma once

struct ThermostatDataStruct {
  float   fCurrentDegF        = 68.0;
  float   fSetpoint           = 70.0;
  float   fProposedSetpoint   = 70.0;
  float   fMinSetpoint        = 40.0;
  float   fMaxSetpoint        = 90.0;
  float   fMaxHeatRange       = 0.10;
  bool    bThermoOn           = true;
  bool    bHeatOn             = true;
};

extern ThermostatDataStruct ThermostatData;
//Last line.
