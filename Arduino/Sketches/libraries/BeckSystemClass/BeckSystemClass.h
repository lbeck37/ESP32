//4/15/21b, BeckSystemClass.h
#pragma once

#include <BeckBiotaLib.h>
#include <BeckAlexaClass.h>
#include <BeckThermostatClass.h>

extern AlexaClass        SystemAlexa;

class SystemClass{
protected:
  char        szAlexaName[50];
  //char        *pAlexaName         = "Larry's Device";
  float         fSetpoint     = 88.0;
  bool          bThermostatOn;

  ThermostatClass   SystemThermostat;

public:
  SystemClass();
  virtual ~SystemClass();

  void  Setup                         ();
  void  Handle                        (void);
};  //System class
//Last line.