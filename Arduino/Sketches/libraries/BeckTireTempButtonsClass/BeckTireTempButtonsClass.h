// BeckTireTempButtonsClass.h, 3/20/22a
#pragma once
#include <BeckE32_Defines.h>
#include <BeckCarSetClass.h>
#include <EasyButton.h>
#include <BeckDataMgrClass.h>

#include <functional>

class BeckTireTempButtonsClass{
public:
  BeckTireTempButtonsClass();
  //BeckTireTempButtonsClass(BeckCarSetClass* poCarSet);
  virtual ~BeckTireTempButtonsClass();

  void  SetupButtons          	();
  void  ReadButtons           	();
  static void  HandleButton     (int wSensorSet);
  static void  onPressed1   	  ();
  static void  onPressed2      	();
  static void  onPressed3      	();
  static void  onPressed4      	();
private:
  BeckDataMgrClass*    _poCarSet;

  EasyButton TireButton1= EasyButton(_cButton_Pin1);
  EasyButton TireButton2= EasyButton(_cButton_Pin2);
  EasyButton TireButton3= EasyButton(_cButton_Pin3);
  EasyButton TireButton4= EasyButton(_cButton_Pin4);
};  //BeckTireTempButtonsClass
//Last line.
