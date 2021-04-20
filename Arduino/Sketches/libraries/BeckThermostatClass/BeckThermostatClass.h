// BeckThermostatClass.h 4/19/21c
#pragma once
#include <BeckSwitchLib.h>
#include <BeckThermostatDataStruct.h>
#include <DallasTemperature.h>
#include <OneWire.h>

class ThermostatClass{
protected:
  int             sThermoTimesInRow       = 3;      //Max times temperature is outside range before switch
  //float           fMaxHeatRange           = 0.10;     //Temp above setpoint before heat is turned off
  //float           fLastDegF               = 99.9;     //Last temperature reading.
  //float           fSetpoint               = 80.0;
  //float           fMinSetpoint            = 40.0;
  //float           fMaxSetpoint            = 80.0;
  float           fThermoOffDeg           = ThermostatData.fSetpoint + ThermostatData.fMaxHeatRange;
  int             sThermoTimesCount       = 0;        //Number of times temperature out of range
  //bool            bThermoOn               = true;    //Whether thermostat is running, set in BeckBiotaLib
  //bool            bHeatOn                 = true;    //If switch is on to turn on Heat.
  unsigned long   ulNextThermPrintMsec    = 0;
  unsigned long   ulThermPrintPeriodMsec  = 10 * lMsecPerSec; //mSec between running system handler

  OneWire         OneWireInstance         = OneWire(sOneWireGPIO);
  DallasTemperature  DallasTemperatureInstance= DallasTemperature(&OneWireInstance);

  //Create OneWire instance and tell Dallas Temperature Library to use oneWire Library
  //OneWire             OneWire(sOneWireGPIO);
  //DallasTemperature   DallasTempSensor(&OneWire);

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
};  //ThermostatClass

extern ThermostatClass          BiotaThermostat;      //Gives access from other files

//Last line.
