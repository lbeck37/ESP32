// BeckButtonClass.h, 3/28/22f
#pragma once
#include <BeckE32_Defines.h>
#include <EasyButton.h>

#include <functional>

//static int    _wButtonWasPressed;
static int    _wLastButtonPressed= 0;

using CallbackPtr = void(*)();

class BeckButtonClass{
public:
  BeckButtonClass           ();
  BeckButtonClass           (int wButtonNumber);
  virtual ~BeckButtonClass  ();

  int           wHandleLoop       ();
  void          ReadButton        ();
  static void   ButtonCallback_1  ();
  static void   ButtonCallback_2  ();
  static void   ButtonCallback_3  ();
  static void   ButtonCallback_4  ();

private:
  int           _wMyButtonNumber      {0};
  //static int    _wLastButtonPressed;
  EasyButton    _oPhysicalButton;
  CallbackPtr   apfCallbacks[5]       {nullptr, ButtonCallback_1, ButtonCallback_2,
                                                ButtonCallback_3, ButtonCallback_4};

};  //BeckButtonClass
//Last line.
