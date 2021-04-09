// BeckThermoLib.h 4/8/21a
#pragma once

const long          sThermoTimesInRow = 3;      //Max times temp is outside range before switch

extern bool         _bThermoOn;
extern bool         _bHeatOn;
extern float        _fLastDegF;
extern float        _fSetpointF;
extern float        _fMaxHeatRangeF;
extern float        _fThermoOffDegF;
extern float        _fMinSetpoint;
extern float        _fMaxSetpoint;

void    HandleThermostat      (void);
void    LogThermostatData     (float fDegF);
float   fSetThermoSetpoint    (unsigned char ucSetpoint);
float   fSetThermoSetpoint    (float fSetpoint);

//void    HandleHeatSwitch      ();
float   fGetDegF              (void);
void    TurnHeatOn            (bool bTurnOn);
void    UpdateDisplay         (void);
//Last line.
