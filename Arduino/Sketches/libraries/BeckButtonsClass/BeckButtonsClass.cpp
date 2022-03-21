const char szSystemFileName[]  = "BeckButtonsClass.cpp";
const char szSystemFileDate[]  = "3/21/22c";

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

  Serial << "BeckButtonsClass(): Default CTR, Call _oTestButton.onPressed(OnPressedTest)" << endl;
  sprintf(_sz100Char, "BeckButtonsClass(): Default CTR, OnPressedTest address= %x\n", OnPressedTest);
  Serial << _sz100Char;
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
  Serial << "BeckButtonsClass::WhenPressed(): Call EasyButton _oTestButton.onPressed(CallbackRoutine)" << endl;
  sprintf(_sz100Char, "BeckButtonsClass::WhenPressed(): CallbackRoutine address= %x\n", CallbackRoutine);
  Serial << _sz100Char;
  _oTestButton.onPressed(CallbackRoutine);
  return;
} //WhenPressed


void BeckButtonsClass::OnPressedTest(){
  Serial << ": You pressed the TESTy Green button" << endl;
  return;
} //OnPressedTest
//Last line.
