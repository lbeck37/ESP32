// BeckThermostatClass.h 4/23/21b
#pragma once
#include <BeckThermostatDataClass.h>
#include <DallasTemperature.h>
#include <OneWire.h>

class ThermostatClass{
protected:
  unsigned long     ulNextSensorReadMsec    = 0;
  unsigned long     ulSensorReadPeriodMsec  = 500; //mSec between reading sensor
  unsigned long     ulNextPrintMsec         = 0;
  unsigned long     ulPrintPeriodMsec       = 5000; //mSec between reading sensor

  //Protected methods
  void    LogThermostatData         (float fDegF);
  float   ReadCurrentDegF           (void);

public:
  ThermostatClass();
  virtual ~ThermostatClass();

  void    Setup                     (void);
  void    Handle                    (void);
};  //ThermostatClass

extern ThermostatClass    BiotaThermostat;      //Gives access from other files

//Last line.
