//4/15/21a, BeckSystemClass.h
#pragma once

#include <BeckBiotaLib.h>
#include <BeckAlexaClass.h>
#include <BeckThermostatClass.h>


class SystemClass{
protected:
  char        szAlexaName[50];
  //char        *pAlexaName         = "Larry's Device";
  float         fSetpoint     = 88.0;

  AlexaClass        SystemAlexa;
  ThermostatClass   SystemThermostat;

public:
  SystemClass();
  virtual ~SystemClass();

void  Setup                         ();
void  Handle                        (void);

};  //System class
