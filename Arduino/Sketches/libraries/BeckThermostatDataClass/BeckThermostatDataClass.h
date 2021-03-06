// ThermostatDataClass.h, 5/21/21a
#pragma once

class ThermostatDataClass{
protected:
  float   CurrentTemperature        = 68.0;
  float   Setpoint           = 70.0;
  float   MinSetpoint        = 40.0;
  float   MaxSetpoint        = 90.0;
  float   MaxHeatRange       = 0.10;
  float   ThermostatOffDeg   = Setpoint + MaxHeatRange;
  bool    ThermostatOn       = true;
  bool    HeatOn             = true;
  bool    LastThermostatOn   = ThermostatOn;
  bool    LastHeatOn         = HeatOn;

  void    SetThermostatOffDeg       (void);
public:
  ThermostatDataClass();
  virtual ~ThermostatDataClass();

  void    Setup                     (void);
  void    Handle                    (void);

  void    SetSetpoint               (float NewSetpoint);
  float   GetSetpoint               (void);

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

  void    SetLastThermostatOn       (bool NewThermostatOn);
  bool    GetLastThermostatOn       (void);

  void    SetLastHeatOn             (bool NewHeatOn);
  bool    GetLastHeatOn             (void);
};  //ThermostatDataClass

extern ThermostatDataClass ThermostatData;
//Last line.
