// BeckButtonClass.h, 3/28/22d
#pragma once
#include <BeckE32_Defines.h>
#include <EasyButton.h>

#include <functional>

static int    _wButtonWasPressed;

using CallbackPtr = void(*)();
//CallbackPtr   apfCallbacks[2] {nullptr, ButtonCallback_1};

class BeckButtonClass{
public:
  BeckButtonClass();
  virtual ~BeckButtonClass();

  void          HandleLoop        ();
  void          ReadButton        ();
  static void   ButtonCallback    ();
  static void   ButtonCallback_1  ();

private:
  EasyButton    _oPhysicalButton;
  CallbackPtr   apfCallbacks[2] {nullptr, ButtonCallback_1};

};  //BeckButtonClass
//Last line.
