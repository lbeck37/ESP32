// BeckThermostatClass.h 4/14/21a
#pragma once
#include <BeckSwitchLib.h>
#include <DallasTemperature.h>
#include <OneWire.h>

class Thermostat{
protected:
  const long    sThermoTimesInRow = 3;      //Max times temp is outside range before switch
  //bool          bThermoOn;
  //bool          bHeatOn;
  //float         fLastDegF;
  //float         fSetpointF;
  //float         fMaxHeatRangeF;
  //float         fThermoOffDegF;
  //float         fMinSetpoint;
  //float         fMaxSetpoint;

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
float   fGet_CurrentDegF          (void);
};  //Thermostat class

//Last line.
