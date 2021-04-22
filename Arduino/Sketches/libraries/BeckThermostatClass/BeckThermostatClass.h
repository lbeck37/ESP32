// BeckThermostatClass.h 4/22/21b
#pragma once
#include <BeckSwitchLib.h>
#include <BeckThermostatDataClass.h>
#include <DallasTemperature.h>
#include <OneWire.h>

class ThermostatClass{
protected:
  bool              bLastHeatOn             = false;    //Used in HandleHeatSwitch()
  bool              bLastSetHeatSwitch      = false;
  unsigned long     ulNextSensorReadMsec    = 0;
  unsigned long     ulSensorReadPeriodMsec  = 500; //mSec between reading sensor

  unsigned long     ulNextPrintMsec         = 0;
  unsigned long     ulPrintPeriodMsec       = 5000; //mSec between reading sensor

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
