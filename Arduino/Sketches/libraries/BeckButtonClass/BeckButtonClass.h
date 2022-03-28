// BeckButtonClass.h, 3/28/22a
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
  void          SetCallback     (EasyButtonBase::callback_t CallbackRoutine);
  static void   ButtonCallback  ();
  //void          DoCallback      ();
/*
  static void  onPressed1   	  ();
  static void  onPressed2      	();
  static void  onPressed3      	();
  static void  onPressed4      	();
*/
  //static int    _wButtonWasPressed;
private:
  //int           _wButtonWasPressed;
  EasyButton                    _oTestButton;
  //EasyButtonBase::callback_t    _CarSetCallback;
  /*
  EasyButton TireButton1= EasyButton(_cButton_Pin1);
  EasyButton TireButton2= EasyButton(_cButton_Pin2);
  EasyButton TireButton3= EasyButton(_cButton_Pin3);
  EasyButton TireButton4= EasyButton(_cButton_Pin4);
*/
};  //BeckButtonClass
//Last line.
