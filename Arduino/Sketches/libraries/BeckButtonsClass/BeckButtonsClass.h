// BeckButtonsClass.h, 3/28/22b
#pragma once
#include <BeckE32_Defines.h>
#include <BeckButtonClass.h>
#include <EasyButton.h>

#include <functional>

//static int    _wButtonWasPressed;

class BeckButtonsClass{
public:
  BeckButtonsClass();
  virtual ~BeckButtonsClass();

  void                HandleLoop        ();
  void                ReadButtons       ();
private:
  BeckButtonClass*    _poButtons[_wNumButtons + 1];
};  //BeckButtonsClass
//Last line.
