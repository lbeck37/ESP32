//4/15/21a, BeckSystemClass.h
#pragma once

#include <BeckBiotaLib.h>
#include <BeckAlexaClass.h>


class System{
protected:
  Alexa   SystemAlexa;

public:
  System();
  virtual ~System();

void  Setup                         ();
void  Handle                        (void);

};  //System class
