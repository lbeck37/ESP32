// ThermostatDataClass.h, 4/20/21d
#pragma once

/*
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
*/

class ThermostatDataClass{
protected:
  float   CurrentDegF        = 68.0;
  float   Setpoint           = 70.0;
  float   ProposedSetpoint   = 70.0;
  float   MinSetpoint        = 40.0;
  float   MaxSetpoint        = 90.0;
  float   MaxHeatRange       = 0.10;
  bool    ThermoOn           = true;
  bool    HeatOn             = true;
  float   ThermoOffDeg      = Setpoint + MaxHeatRange;

public:
  ThermostatDataClass();
  virtual ~ThermostatDataClass();

  void    Setup               (void);
  void    Handle              (void);

  void    SetSetpoint         (float NewSetpoint);
  float   GetSetpoint         (void);

  void    SetProposedSetpoint (float NewSetpoint);
  float   GetProposedSetpoint (void);

  void    SetCurrentDegF      (float NewCurrentDegF);
  float   GetCurrentDegF      (void);

  void    SetMaxHeatRange     (float NewMaxHeatRange);
  float   GetMaxHeatRange     (void);

  void    SetMinSetpoint      (float NewMinSetpoint);
  float   GetMinSetpoint      (void);

  void    SetMaxSetpoint      (float NewMaxSetpoint);
  float   GetMaxSetpoint      (void);

  void    SetThermostatOn     (bool NewThermoOn);
  bool    GetThermostatOn     (void);

  void    SetHeatOn           (bool NewHeatOn);
  bool    GetHeatOn           (void);
};  //ThermostatDataClass

extern ThermostatDataClass ThermostatData;
//Last line.
