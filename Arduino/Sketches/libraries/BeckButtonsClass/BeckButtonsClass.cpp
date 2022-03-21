const char szSystemFileName[]  = "BeckButtonsClass.cpp";
const char szSystemFileDate[]  = "3/22/22a";

#include <BeckButtonsClass.h>
#include <BeckCarSetClass.h>
#include <Streaming.h>

BeckButtonsClass::BeckButtonsClass(void) : _oTestButton(_cButton_Pin1) {
  Serial << "BeckButtonsClass(void): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
/*
  Serial << "BeckButtonsClass(void): Default CTR, Call _oTestButton= EasyButton(_cButton_Pin1)" << endl;
  _oTestButton= EasyButton(_cButton_Pin1);
*/

  Serial << "\nBeckButtonsClass(void): Default CTR, Call _oTestButton.begin()" << endl;
  _oTestButton.begin();

  Serial << "BeckButtonsClass(void): Default CTR, Call _oTestButton.onPressed(OnPressedTest)" << endl;
  _oTestButton.onPressed(OnPressedTest);
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


void BeckButtonsClass::WhenPressed(EasyButtonBase::callback_t CallbackRoutine){
  //Serial << "BeckButtonsClass::WhenPressed(): Call _oTestButton.onPressed(CallbackRoutine)" << endl;
  sprintf(_sz100Char, "BeckButtonsClass::WhenPressed(CallbackRoutine address= %p | %x\n", CallbackRoutine, CallbackRoutine);
  Serial << _sz100Char;
  _oTestButton.onPressed(CallbackRoutine);
  return;
} //WhenPressed


void BeckButtonsClass::OnPressedTest(){
  Serial << ": You pressed the TESTy Green button" << endl;
  return;
} //OnPressedTest
//Last line.
