//BeckAlexaClass.h, 5/9/21a
#pragma once

#include <fauxmoESP.h>        //Alexa Phillips Hue light emulation

class AlexaClass{
public:
  AlexaClass();
  virtual ~AlexaClass();

  void  Setup		(char acAlexaName[]);
  void  Handle		(void);

protected:
  fauxmoESP     AlexaDevice;                  //Alexa emulation of Philips Hue Bulb
};  //AlexaClass

extern AlexaClass           BiotaAlexa;       //This is so every module can use the same Alexa object

//Last line.
