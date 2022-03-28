// BeckButtonsClass.h, 3/28/22d
#pragma once
#include <BeckE32_Defines.h>
#include <BeckButtonClass.h>

#include <functional>

class BeckButtonsClass{
public:
  BeckButtonsClass();
  virtual ~BeckButtonsClass();

  void                HandleLoop        ();
private:
  BeckButtonClass*    _poButtons[_wNumButtons + 1];

};  //BeckButtonsClass
//Last line.
