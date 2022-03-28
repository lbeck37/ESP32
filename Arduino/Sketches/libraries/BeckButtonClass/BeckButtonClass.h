// BeckButtonClass.h, 3/28/22b
#pragma once
#include <BeckE32_Defines.h>
#include <EasyButton.h>

#include <functional>

static int    _wButtonWasPressed;

class BeckButtonClass{
public:
  BeckButtonClass();
  virtual ~BeckButtonClass();

  //void  SetupButton           ();
  void          HandleLoop      ();
  void          ReadButton      ();
  //void          SetCallback     (EasyButtonBase::callback_t CallbackRoutine);
  static void   ButtonCallback  ();

private:
  EasyButton    _oPhysicalButton;

};  //BeckButtonClass
//Last line.
