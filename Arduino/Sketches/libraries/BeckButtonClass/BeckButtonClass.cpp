const char szSystemFileName[]  = "BeckButtonClass.cpp";
const char szSystemFileDate[]  = "3/28/22a";

#include <BeckButtonClass.h>
#include <BeckCarSetClass.h>
#include <Streaming.h>

BeckButtonClass::BeckButtonClass() : _oPhysicalButton(_cButton_Pin1) {
  Serial << "BeckButtonClass(): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;

  Serial << "BeckButtonClass(): Default CTR, Call _oPhysicalButton.begin()" << endl;
  _oPhysicalButton.begin();

  Serial << "BeckButtonClass(): Default CTR, Call _oTestButton.onPressed(ButtonCallback)" << endl;

  sprintf(_sz100Char, "BeckButtonClass(): Default CTR, OnPressedTest address= %x\n", ButtonCallback);
  Serial << _sz100Char;
  _oPhysicalButton.onPressed(ButtonCallback);

  Serial << "BeckButtonClass(): Default CTR, Done" << endl;
  return;
} //constructor


BeckButtonClass::~BeckButtonClass() {
  Serial << "~BeckButtonClass(): Destructor" << endl;
  return;
} //destructor


void BeckButtonClass::ReadButton(){
  _oPhysicalButton.read();
  return;
} //ReadButton


void BeckButtonClass::HandleLoop(){
  ReadButton();
  return;
} //HandleLoop


/*
void BeckButtonClass::SetCallback(EasyButtonBase::callback_t ButtonCallback){
  Serial << "BeckButtonClass::SetCallback(): Call EasyButton _oTestButton.onPressed(CallbackRoutine)" << endl;

  _oPhysicalButton.onPressed(ButtonCallback);
  return;
} //SetCallback
*/


void BeckButtonClass::ButtonCallback(){
  Serial << "BeckButtonClass::ButtonCallback: You pressed the TESTy Green button" << endl;
  Serial << "BeckButtonClass::ButtonCallback: Set _wButtonWasPressed= 1" << endl;
  //BeckButtonClass::_wButtonWasPressed= 1;
  _wButtonWasPressed= 1;
  return;
} //ButtonCallback
//Last line.
