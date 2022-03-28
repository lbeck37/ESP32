// BeckButtonClass.h, 3/28/22c
#pragma once
#include <BeckE32_Defines.h>
#include <EasyButton.h>

#include <functional>

static int    _wButtonWasPressed;

class BeckButtonClass{
public:
  BeckButtonClass();
  virtual ~BeckButtonClass();

  void          HandleLoop      ();
  void          ReadButton      ();
  static void   ButtonCallback  ();

private:
  EasyButton    _oPhysicalButton;

};  //BeckButtonClass
//Last line.
