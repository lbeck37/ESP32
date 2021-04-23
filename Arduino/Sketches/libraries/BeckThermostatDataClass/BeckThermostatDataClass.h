// ThermostatDataClass.h, 4/23/21b
#pragma once

class ThermostatDataClass{
protected:
  float   CurrentTemperature        = 68.0;
  float   Setpoint           = 70.0;
  float   ProposedSetpoint   = 70.0;
  float   MinSetpoint        = 40.0;
  float   MaxSetpoint        = 90.0;
  float   MaxHeatRange       = 0.10;
  float   ThermostatOffDeg   = Setpoint + MaxHeatRange;
  bool    ThermostatOn       = true;
  bool    HeatOn             = true;

  void    SetThermostatOffDeg       (void);

public:
  ThermostatDataClass();
  virtual ~ThermostatDataClass();

  void    Setup                     (void);
  void    Handle                    (void);

  void    SetSetpoint               (float NewSetpoint);
  float   GetSetpoint               (void);

  void    SetProposedSetpoint       (float NewSetpoint);
  float   GetProposedSetpoint       (void);

  void    SetCurrentTemperature     (float NewCurrentTemperature);
  float   GetCurrentTemperature     (void);

  void    SetMaxHeatRange           (float NewMaxHeatRange);
  float   GetMaxHeatRange           (void);

  float   GetThermostatOffDeg       (void);

  void    SetMinSetpoint            (float NewMinSetpoint);
  float   GetMinSetpoint            (void);

  void    SetMaxSetpoint            (float NewMaxSetpoint);
  float   GetMaxSetpoint            (void);

  void    SetThermostatOn           (bool NewThermostatOn);
  bool    GetThermostatOn           (void);

  void    SetHeatOn                 (bool NewHeatOn);
  bool    GetHeatOn                 (void);
};  //ThermostatDataClass

extern ThermostatDataClass ThermostatData;
//Last line.
