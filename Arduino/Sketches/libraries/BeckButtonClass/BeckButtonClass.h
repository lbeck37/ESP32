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
  BeckButtonClass           ();
  BeckButtonClass           (int wButtonNumber);
  virtual ~BeckButtonClass  ();

  void          HandleLoop        ();
  void          ReadButton        ();
  //static void   ButtonCallback    ();
  static void   ButtonCallback_1  ();
  static void   ButtonCallback_2  ();
  static void   ButtonCallback_3  ();
  static void   ButtonCallback_4  ();

private:
  int           _wButtonNumber    {0};
  EasyButton    _oPhysicalButton;
  CallbackPtr   apfCallbacks[5]   {nullptr, ButtonCallback_1, ButtonCallback_2, ButtonCallback_3, ButtonCallback_4};

};  //BeckButtonClass
//Last line.
