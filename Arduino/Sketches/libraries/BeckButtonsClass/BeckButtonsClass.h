// BeckButtonsClass.h, 3/21/22b
#pragma once
#include <BeckE32_Defines.h>
#include <EasyButton.h>

#include <functional>

class BeckButtonsClass{
public:
  BeckButtonsClass();
  virtual ~BeckButtonsClass();

  //void  SetupButtons          ();
  void          HandleLoop      ();
  void          ReadButtons     ();
  void          SetCallback     (EasyButtonBase::callback_t CallbackRoutine);
  static void   ButtonsCallback ();
/*
  static void  onPressed1   	  ();
  static void  onPressed2      	();
  static void  onPressed3      	();
  static void  onPressed4      	();
*/
private:
  EasyButton            _oTestButton;
/*
  EasyButton TireButton1= EasyButton(_cButton_Pin1);
  EasyButton TireButton2= EasyButton(_cButton_Pin2);
  EasyButton TireButton3= EasyButton(_cButton_Pin3);
  EasyButton TireButton4= EasyButton(_cButton_Pin4);
*/
};  //BeckButtonsClass
//Last line.
