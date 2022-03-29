const char szSystemFileName[]  = "BeckButtonClass.cpp";
const char szSystemFileDate[]  = "3/28/22g";

#include <BeckButtonClass.h>
#include <BeckCarSetClass.h>
#include <Streaming.h>

BeckButtonClass::BeckButtonClass() : _oPhysicalButton(_cButton_Pin1) {
  Serial << "BeckButtonClass(void): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;

  Serial << "BeckButtonClass(void): Default CTR, ERROR: Not sure how we got here." << endl;
  Serial << "BeckButtonClass(void): Default CTR, Done" << endl;
  return;
} //BeckButtonClass(void)constructor


BeckButtonClass::BeckButtonClass(int wButtonNumber) : _oPhysicalButton(_acButtonPins[wButtonNumber]) {
  Serial << "BeckButtonClass(wButtonNumber): CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
  _wMyButtonNumber= wButtonNumber;
  Serial << "BeckButtonClass(wButtonNumber): CTR, Building Button #" << _wMyButtonNumber << endl;

  Serial << "BeckButtonClass(wButtonNumber): CTR, Call _oPhysicalButton.begin()" << endl;
  _oPhysicalButton.begin();

  Serial << "BeckButtonClass(wButtonNumber): CTR, Call _oPhysicalButton.onPressed(apfCallbacks[" << wButtonNumber << "])" << endl;
  _oPhysicalButton.onPressed(apfCallbacks[_wMyButtonNumber]);

  Serial << "BeckButtonClass(int): CTR, Done" << endl;
  return;
} //BeckButtonClass(int)constructor


void BeckButtonClass::ReadButton(){
  _oPhysicalButton.read();
  return;
} //ReadButton


int BeckButtonClass::wHandleLoop(){
  int wReturn= 0;
  ReadButton();
  if(_wLastButtonPressed == _wMyButtonNumber){
    wReturn= _wMyButtonNumber;
    _wLastButtonPressed= 0;
  }
  return wReturn;
} //wHandleLoop


void BeckButtonClass::ButtonCallback_1(){
  int  wMyButtonNumber= 1;
  _wLastButtonPressed= wMyButtonNumber;
  Serial << "BeckButtonClass::ButtonCallback_1: You pressed the Green button #1" << endl;
  return;
} //ButtonCallback


void BeckButtonClass::ButtonCallback_2(){
  int  wMyButtonNumber= 2;
  _wLastButtonPressed= wMyButtonNumber;
  Serial << "BeckButtonClass::ButtonCallback_2: You pressed the Yellow button #2" << endl;
  return;
} //ButtonCallback_2


void BeckButtonClass::ButtonCallback_3(){
  int  wMyButtonNumber= 3;
  _wLastButtonPressed= wMyButtonNumber;
  Serial << "BeckButtonClass::ButtonCallback_3: You pressed the Red button #3" << endl;
  return;
} //ButtonCallback_3


void BeckButtonClass::ButtonCallback_4(){
  int  wMyButtonNumber= 4;
  _wLastButtonPressed= wMyButtonNumber;
  Serial << "BeckButtonClass::ButtonCallback_4: You pressed the Blue button #4" << endl;
  return;
} //ButtonCallback_4


BeckButtonClass::~BeckButtonClass() {
  Serial << "~BeckButtonClass(): Destructor" << endl;
  return;
} //destructor
//Last line.
