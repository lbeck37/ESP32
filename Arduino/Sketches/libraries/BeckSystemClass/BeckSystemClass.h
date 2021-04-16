//4/16/21a, BeckSystemClass.h
#pragma once

#include <BeckBiotaLib.h>
#include <BeckAlexaClass.h>
#include <BeckThermostatClass.h>
#include <BeckThermoDisplayClass.h>

//extern AlexaClass        SystemAlexa;

//Externs defined in BeckBiotaLib.cpp
extern bool         _bThermoOn;
extern bool         _bHeatOn;
extern float        _fLastDegF;
extern float        _fSetpointF;
extern float        _fMaxHeatRangeF;
extern float        _fThermoOffDegF;
extern float        _fMinSetpoint;
extern float        _fMaxSetpoint;

class SystemClass{
protected:
  char          szAlexaName[50]= "Larry's Device";
  //char        *pAlexaName         = "Larry's Device";
  float         fSetpoint     = 88.0;
  bool          bThermostatOn ;

  //ThermostatClass   SystemThermostat;

public:
  SystemClass();
  virtual ~SystemClass();

  void  Setup                         ();
  void  Handle                        (void);
};  //SystemClass

extern SystemClass        BiotaSystem;       //This is so every module can use the same object

//Last line.
