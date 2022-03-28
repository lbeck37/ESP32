const char szSystemFileName[]  = "BeckButtonClass.cpp";
const char szSystemFileDate[]  = "3/28/22d";

#include <BeckButtonClass.h>
#include <BeckCarSetClass.h>
#include <Streaming.h>

BeckButtonClass::BeckButtonClass() : _oPhysicalButton(_cButton_Pin1) {
  Serial << "BeckButtonClass(): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;

  Serial << "BeckButtonClass(): Default CTR, Call _oPhysicalButton.begin()" << endl;
  _oPhysicalButton.begin();

  Serial << "BeckButtonClass(): Default CTR, Call _oPhysicalButton.onPressed(ButtonCallback_1)" << endl;
  //_oPhysicalButton.onPressed(ButtonCallback);
  //_oPhysicalButton.onPressed(ButtonCallback_1);
  _oPhysicalButton.onPressed(apfCallbacks[1]);

  Serial << "BeckButtonClass(): Default CTR, Done" << endl;
  return;
} //constructor


void BeckButtonClass::ReadButton(){
  _oPhysicalButton.read();
  return;
} //ReadButton


void BeckButtonClass::HandleLoop(){
  ReadButton();
  return;
} //HandleLoop


void BeckButtonClass::ButtonCallback(){
  Serial << "BeckButtonClass::ButtonCallback: You pressed the TESTy Green button" << endl;
  Serial << "BeckButtonClass::ButtonCallback: Set _wButtonWasPressed= 1" << endl;
  _wButtonWasPressed= 1;
  return;
} //ButtonCallback


void BeckButtonClass::ButtonCallback_1(){
  Serial << "BeckButtonClass::ButtonCallback_1: You pressed the Green button #1" << endl;
  return;
} //ButtonCallback


BeckButtonClass::~BeckButtonClass() {
  Serial << "~BeckButtonClass(): Destructor" << endl;
  return;
} //destructor
//Last line.
