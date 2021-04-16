//4/15/21a, BeckAlexaClass.h
#pragma once

#include <BeckBiotaLib.h>
#include <fauxmoESP.h>        //Alexa Phillips Hue light emulation

/*
extern int            wAlexaHandleCount;
extern bool           _bAlexaChanged;
*/

class AlexaClass{
protected:
  int   wAlexaHandleCount   = 0;
  bool  bAlexaChanged       = false;

  bool          LastThermostatOnState     = false;
  float         LastTemperatureSetting     = 80.0;
  fauxmoESP     AlexaDevice;                          //Alexa emulation of Philips Hue Bulb

  //void DoAlexaCommand         (unsigned char ucDdeviceID, const char* szDeviceName, bool bState, unsigned char ucValue);
  //void  HandleThermostatProject (bool bState, unsigned char ucValue);
public:
  AlexaClass();
  virtual ~AlexaClass();

//void  Setup                         (char acAlexaName[]);
void  Setup                         (char acAlexaName[]);
void  Handle                        (void);
float GetCurrentTemperatureSetting  (void);
bool  GetLastThermostatOnState      (void);

};  //AlexaClass
