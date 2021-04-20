// BeckThermostatClass.h 4/19/21d
#pragma once
#include <BeckSwitchLib.h>
#include <BeckThermostatDataClass.h>
#include <DallasTemperature.h>
#include <OneWire.h>

class ThermostatClass{
protected:
  int               sThermoTimesInRow       = 3;      //Max times temperature is outside range before switch
  float             fThermoOffDeg           = ThermostatData.GetSetpoint() + ThermostatData.GetMaxHeatRange();
  int               sThermoTimesCount       = 0;        //Number of times temperature out of range
  unsigned long     ulNextThermPrintMsec    = 0;
  unsigned long     ulThermPrintPeriodMsec  = 10 * lMsecPerSec; //mSec between running system handler

  OneWire           OneWireInstance            = OneWire(sOneWireGPIO);
  DallasTemperature DallasTemperatureInstance  = DallasTemperature(&OneWireInstance);

  //Protected methods
  void    LogThermostatData         (float fDegF);
  void    HandleHeatSwitch          (void);
  void    TurnHeatOn                (bool bTurnOn);
  void    UpdateDisplay             (void);

public:
  ThermostatClass();
  virtual ~ThermostatClass();

  void    Setup                     (void);
  void    Handle                    (void);
/*
  void    SetSetpoint               (float Setpoint);
  float   GetSetpoint               (void);
  float   GetCurrentDegF            (void);
  void    SetMaxHeatRange           (float NewMaxHeatRange);
  float   GetMaxHeatRange           (void);
  void    SetMinSetpoint            (float NewMinSetpoint);
  float   GetMinSetpoint            (void);
  void    SetMaxSetpoint            (float NewMaxSetpoint);
  float   GetMaxSetpoint            (void);
  void    SetThermostatOn           (bool bNewThermoOn);
  bool    GetThermostatOn           (void);
  bool    GetHeatOn                 (void);
*/
};  //ThermostatClass

extern ThermostatClass          BiotaThermostat;      //Gives access from other files

//Last line.
