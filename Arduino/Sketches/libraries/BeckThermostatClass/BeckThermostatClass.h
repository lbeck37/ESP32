// BeckThermostatClass.h 4/20/21c
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
  unsigned long     ulNextSensorReadMsec    = 0;
  unsigned long     ulSensorReadPeriodMsec  = 10 * lMsecPerSec; //mSec between running system handler

  OneWire           OneWireInstance            = OneWire(sOneWireGPIO);
  DallasTemperature DallasTemperatureInstance  = DallasTemperature(&OneWireInstance);

  //Protected methods
  void    LogThermostatData         (float fDegF);
  void    HandleHeatSwitch          (void);
  void    TurnHeatOn                (bool bTurnOn);
  void    UpdateDisplay             (void);
  float   ReadCurrentDegF           (void);

public:
  ThermostatClass();
  virtual ~ThermostatClass();

  void    Setup                     (void);
  void    Handle                    (void);
};  //ThermostatClass

extern ThermostatClass          BiotaThermostat;      //Gives access from other files

//Last line.
