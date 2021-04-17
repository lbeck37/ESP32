//4/16/21a, BeckAlexaClass.h
#pragma once

#include <BeckBiotaLib.h>
#include <fauxmoESP.h>        //Alexa Phillips Hue light emulation

class AlexaClass{
protected:
  int   wAlexaHandleCount   = 0;
  bool  bAlexaChanged       = false;

  float         LastSetpoint            = 80.0;
  bool          LastThermostatOnState   = false;

  fauxmoESP     AlexaDevice;                          //Alexa emulation of Philips Hue Bulb

  //void DoAlexaCommand         (unsigned char ucDdeviceID, const char* szDeviceName, bool bState, unsigned char ucValue);
  //void  HandleThermostatProject (bool bState, unsigned char ucValue);
public:
  AlexaClass();
  virtual ~AlexaClass();

  void  Setup                         (char acAlexaName[]);
  void  Handle                        (void);
  void  SetLastSetpoint               (float fNewSetpoint);
  void  SetLastThermostatOnState      (bool bNewThermostatOnState);
  float GetLastSetpoint               (void);
  bool  GetLastThermostatOnState      (void);
};  //AlexaClass

//extern AlexaClass        BiotaAlexa;       //This is so every module can use the same Alexa object
//Last line.
