const char szSystemFileName[]  = "BeckTireTempButtonsClass.cpp";
const char szSystemFileDate[]  = "3/16/22a";

#include <BeckTireTempButtonsClass.h>
#include <BeckCarSetClass.h>
#include <Streaming.h>

BeckTireTempButtonsClass::BeckTireTempButtonsClass(void) {
  Serial << "BeckTireTempButtonsClass(void): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
  return;
} //constructor

/*
BeckTireTempButtonsClass::BeckTireTempButtonsClass(BeckCarSetClass* poCarSet) {
  Serial << "BeckTireTempButtonsClass(poCarSet): CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
  _poCarSet= poCarSet;
  return;
} //constructor
*/


BeckTireTempButtonsClass::~BeckTireTempButtonsClass() {
  Serial << "~BeckTireTempButtonsClass(): Destructor" << endl;
  return;
} //destructor

void BeckTireTempButtonsClass::SetupButtons() {
  Serial << "SetupButtons(): Call TireButton1/2/3/4.begin()\n";
  TireButton1.begin();
  TireButton2.begin();
  TireButton3.begin();
  TireButton4.begin();

  Serial << "SetupButtons(): Setup Callback, call onPressed(callback) for the 4 buttons\n";
  TireButton1.onPressed(onPressed1);
  TireButton2.onPressed(onPressed2);
  TireButton3.onPressed(onPressed3);
  TireButton4.onPressed(onPressed4);
  return;
} //SetupButtons

void BeckTireTempButtonsClass::ReadButtons(){
  TireButton1.read();   //This has to get called for onPressed() to get called back
  TireButton2.read();
  TireButton3.read();
  TireButton4.read();
  return;
} //ReadButtons

void BeckTireTempButtonsClass::HandleButton(int wSensorSet){
  Serial << "onPressed1(): You pressed Button " << wSensorSet << "\n";
  _poCarSet->ReadSensorSet(wSensorSet);
  return;
} //HandleButton

void BeckTireTempButtonsClass::onPressed1(){
  int   wSensorSet= 1;
  HandleButton(wSensorSet);
  return;
} //onPressed1

void BeckTireTempButtonsClass::onPressed2(){
  int   wSensorSet= 2;
  HandleButton(wSensorSet);
  return;
} //onPressed2

void BeckTireTempButtonsClass::onPressed3(){
  int   wSensorSet= 3;
  HandleButton(wSensorSet);
  return;
} //onPressed3

void BeckTireTempButtonsClass::onPressed4(){
  int   wSensorSet= 4;
  HandleButton(wSensorSet);
  return;
} //onPressed4
//Last line.
