const char szSystemFileName[]  = "BeckButtonClass.cpp";
const char szSystemFileDate[]  = "3/22/22c"
    ""
    "-";

#include <BeckButtonClass.h>
#include <BeckCarSetClass.h>
#include <Streaming.h>

BeckButtonClass::BeckButtonClass() : _oTestButton(_cButton_Pin1) {
  Serial << "BeckButtonClass(): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
/*
  Serial << "BeckButtonClass(): Default CTR, Call _oTestButton= EasyButton(_cButton_Pin1)" << endl;
  _oTestButton= EasyButton(_cButton_Pin1);
*/

  Serial << "BeckButtonClass(): Default CTR, Call _oTestButton.begin()" << endl;
  _oTestButton.begin();

  Serial << "BeckButtonClass(): Default CTR, Call _oTestButton.onPressed(ButtonCallback)" << endl;
  sprintf(_sz100Char, "BeckButtonClass(): Default CTR, OnPressedTest address= %x\n", ButtonCallback);
  Serial << _sz100Char;
  _oTestButton.onPressed(ButtonCallback);

  Serial << "BeckButtonClass(): Default CTR, Done" << endl;
  return;
} //constructor


BeckButtonClass::~BeckButtonClass() {
  Serial << "~BeckButtonClass(): Destructor" << endl;
  return;
} //destructor


void BeckButtonClass::ReadButton(){
  _oTestButton.read();
  return;
} //ReadButton


void BeckButtonClass::HandleLoop(){
  //_oTestButton.read();
  ReadButton();
  return;
} //HandleLoop


void BeckButtonClass::SetCallback(EasyButtonBase::callback_t ButtonCallback){
  Serial << "BeckButtonClass::SetCallback(): Call EasyButton _oTestButton.onPressed(CallbackRoutine)" << endl;
  //_CarSetCallback= CarSetCallback;
  //sprintf(_sz100Char, "BeckButtonClass::SetCallback(): CallbackRoutine address= %x\n", CallbackRoutine);
  //Serial << _sz100Char;
/*
  Serial << "BeckButtonClass::SetCallback(): See if we can call the _CarSetCallback() routine" << endl;
  CarSetCallback();

  _oTestButton.onPressed(CarSetCallback);
*/
  _oTestButton.onPressed(ButtonCallback);
  return;
} //SetCallback


void BeckButtonClass::ButtonCallback(){
  Serial << "BeckButtonClass::ButtonCallback: You pressed the TESTy Green button" << endl;
  Serial << "BeckButtonClass::ButtonCallback: Set _wButtonWasPressed= 1" << endl;
  //BeckButtonClass::_wButtonWasPressed= 1;
  _wButtonWasPressed= 1;
  return;
} //ButtonCallback


/*
void BeckButtonClass::DoCallback(){
  Serial << "BeckButtonClass::DoCallback: Call _CarSetCallback()" << endl;
  _CarSetCallback();
  return;
} //DoCallback
*/
//Last line.
