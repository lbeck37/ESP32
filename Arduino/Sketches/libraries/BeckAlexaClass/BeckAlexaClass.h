//BeckAlexaClass.h, 4/23/21a
#pragma once

#include <fauxmoESP.h>        //Alexa Phillips Hue light emulation

class AlexaClass{
protected:
  //int           wAlexaHandleCount               = 0;
  fauxmoESP     AlexaDevice;                  //Alexa emulation of Philips Hue Bulb

public:
  AlexaClass();
  virtual ~AlexaClass();

  void  Setup                         (char acAlexaName[]);
  void  Handle                        (void);
};  //AlexaClass

extern AlexaClass           BiotaAlexa;       //This is so every module can use the same Alexa object

//Last line.
