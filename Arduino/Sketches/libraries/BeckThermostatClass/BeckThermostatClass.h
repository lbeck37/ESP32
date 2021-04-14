// BeckThermostatClass.h 4/14/21b
#pragma once
#include <BeckSwitchLib.h>
#include <DallasTemperature.h>
#include <OneWire.h>

class Thermostat{
protected:
  int             sThermoTimesInRow       = 3;      //Max times temperature is outside range before switch
  float           fMaxHeatRangeF          = 0.10;     //Temp above setpoint before heat is turned off
  float           fLastDegF               = 99.9;     //Last temperature reading.
  float           fSetpointF              = 70.0;
  float           fMinSetpoint            = 40.0;
  float           fMaxSetpoint            = 80.0;
  float           fThermoOffDegF          = fSetpointF + fMaxHeatRangeF;
  int             sThermoTimesCount       = 0;        //Number of times temperature out of range
  bool            bThermoOn               = false;    //Whether thermostat is running, set in BeckBiotaLib
  bool            bHeatOn                 = false;    //If switch is on to turn on Heat.
  unsigned long   ulNextThermPrintMsec    = 0;
  unsigned long   ulThermPrintPeriodMsec  = 10 * lMsecPerSec; //mSec between running system handler
  OneWire         OneWireInstance         = OneWire(sOneWireGPIO);
  DallasTemperature  DallasTemperatureInstance= DallasTemperature(&OneWireInstance);

  //Create OneWire instance and tell Dallas Temperature Library to use oneWire Library
  //OneWire             OneWire(sOneWireGPIO);
  //DallasTemperature   DallasTempSensor(&OneWire);


  void    LogThermostatData         (float fDegF);
  void    HandleHeatSwitch          (void);
  void    TurnHeatOn                (bool bTurnOn);
  void    UpdateDisplay             (void);

  public:
  Thermostat();
  virtual ~Thermostat();

  void    HandleThermostat          (void);
  void    Set_Setpoint              (float fSetpoint);
  void    Set_Setpoint              (unsigned char ucSetpoint);
  float   Get_Setpoint              (void);
  float   Get_CurrentDegF           (void);
  void    Set_MaxHeatRangeF         (float fNewMaxHeatRangeF);
  float   Get_MaxHeatRangeF         (void);
  bool    ThermostatIsOn            (void);
  bool    HeatIsOn                  (void);
};  //Thermostat class

extern Thermostat          BiotaThermostat;

//Last line.
