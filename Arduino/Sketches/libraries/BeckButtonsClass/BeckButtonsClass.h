// BeckButtonsClass.h, 3/28/22e
#pragma once
#include <BeckE32_Defines.h>
#include <BeckButtonClass.h>

#include <functional>

class BeckButtonsClass{
public:
  BeckButtonsClass                ();
  virtual ~BeckButtonsClass       ();

  int                wHandleLoop  ();
private:
  BeckButtonClass*    _poButtons[_wNumButtons + 1];

};  //BeckButtonsClass
//Last line.
