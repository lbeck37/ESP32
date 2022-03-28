const char szSystemFileName[]  = "BeckButtonsClass.cpp";
const char szSystemFileDate[]  = "3/22/22c"
    ""
    "-";

#include <BeckButtonsClass.h>
#include <BeckCarSetClass.h>
#include <Streaming.h>

BeckButtonsClass::BeckButtonsClass() : _oTestButton(_cButton_Pin1) {
  Serial << "BeckButtonsClass(): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
/*
  Serial << "BeckButtonsClass(): Default CTR, Call _oTestButton= EasyButton(_cButton_Pin1)" << endl;
  _oTestButton= EasyButton(_cButton_Pin1);
*/

  Serial << "BeckButtonsClass(): Default CTR, Call _oTestButton.begin()" << endl;
  _oTestButton.begin();

  Serial << "BeckButtonsClass(): Default CTR, Call _oTestButton.onPressed(ButtonsCallback)" << endl;
  sprintf(_sz100Char, "BeckButtonsClass(): Default CTR, OnPressedTest address= %x\n", ButtonsCallback);
  Serial << _sz100Char;
  _oTestButton.onPressed(ButtonsCallback);

  Serial << "BeckButtonsClass(): Default CTR, Done" << endl;
  return;
} //constructor


BeckButtonsClass::~BeckButtonsClass() {
  Serial << "~BeckButtonsClass(): Destructor" << endl;
  return;
} //destructor


void BeckButtonsClass::ReadButtons(){
  _oTestButton.read();
  return;
} //ReadButtons


void BeckButtonsClass::HandleLoop(){
  //_oTestButton.read();
  ReadButtons();
  return;
} //HandleLoop


//void BeckButtonsClass::SetCallback(EasyButtonBase::callback_t CarSetCallback){
void BeckButtonsClass::SetCallback(EasyButtonBase::callback_t ButtonsCallback){
  Serial << "BeckButtonsClass::SetCallback(): Call EasyButton _oTestButton.onPressed(CallbackRoutine)" << endl;
  //_CarSetCallback= CarSetCallback;
  //sprintf(_sz100Char, "BeckButtonsClass::SetCallback(): CallbackRoutine address= %x\n", CallbackRoutine);
  //Serial << _sz100Char;
/*
  Serial << "BeckButtonsClass::SetCallback(): See if we can call the _CarSetCallback() routine" << endl;
  CarSetCallback();

  _oTestButton.onPressed(CarSetCallback);
*/
  _oTestButton.onPressed(ButtonsCallback);
  return;
} //SetCallback


void BeckButtonsClass::ButtonsCallback(){
  Serial << "BeckButtonsClass::ButtonsCallback: You pressed the TESTy Green button" << endl;
  Serial << "BeckButtonsClass::ButtonsCallback: Set _wButtonWasPressed= 1" << endl;
  BeckButtonsClass::_wButtonWasPressed= 1;
  return;
} //ButtonsCallback


/*
void BeckButtonsClass::DoCallback(){
  Serial << "BeckButtonsClass::DoCallback: Call _CarSetCallback()" << endl;
  _CarSetCallback();
  return;
} //DoCallback
*/
//Last line.
