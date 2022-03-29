const char szSystemFileName[]  = "BeckButtonClass.cpp";
const char szSystemFileDate[]  = "3/28/22e";

#include <BeckButtonClass.h>
#include <BeckCarSetClass.h>
#include <Streaming.h>

/*
BeckButtonClass::BeckButtonClass() {
  Serial << "BeckButtonClass(void): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;


  Serial << "BeckButtonClass(): Default CTR, Call _oPhysicalButton.begin()" << endl;
  _oPhysicalButton.begin();

  Serial << "BeckButtonClass(): Default CTR, Call _oPhysicalButton.onPressed(ButtonCallback_1)" << endl;
  //_oPhysicalButton.onPressed(ButtonCallback);
  //_oPhysicalButton.onPressed(ButtonCallback_1);
  _oPhysicalButton.onPressed(apfCallbacks[1]);


  Serial << "BeckButtonClass(void): Default CTR, Done" << endl;
  return;
} //BeckButtonClass(void)constructor
*/


//BeckButtonClass::BeckButtonClass(int wButtonNumber) : _oPhysicalButton(_cButton_Pin1) {
BeckButtonClass::BeckButtonClass(int wButtonNumber) : _oPhysicalButton(_acButtonPins[wButtonNumber]) {
  Serial << "BeckButtonClass(wButtonNumber): CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckButtonClass(wButtonNumber): CTR, Building Button #" << wButtonNumber << endl;

  Serial << "BeckButtonClass(wButtonNumber): CTR, Call _oPhysicalButton.begin()" << endl;
  _oPhysicalButton.begin();

  Serial << "BeckButtonClass(wButtonNumber): CTR, Call _oPhysicalButton.onPressed(apfCallbacks[" << wButtonNumber << "])" << endl;
  //_oPhysicalButton.onPressed(ButtonCallback);
  //_oPhysicalButton.onPressed(ButtonCallback_1);
  _oPhysicalButton.onPressed(apfCallbacks[wButtonNumber]);

  Serial << "BeckButtonClass(int): CTR, Done" << endl;
  return;
} //BeckButtonClass(int)constructor


void BeckButtonClass::ReadButton(){
  _oPhysicalButton.read();
  return;
} //ReadButton


void BeckButtonClass::HandleLoop(){
  ReadButton();
  return;
} //HandleLoop


/*
void BeckButtonClass::ButtonCallback(){
  Serial << "BeckButtonClass::ButtonCallback: You pressed the TESTy Green button" << endl;
  Serial << "BeckButtonClass::ButtonCallback: Set _wButtonWasPressed= 1" << endl;
  _wButtonWasPressed= 1;
  return;
} //ButtonCallback
*/


void BeckButtonClass::ButtonCallback_1(){
  Serial << "BeckButtonClass::ButtonCallback_1: You pressed the Green button #1" << endl;
  return;
} //ButtonCallback


void BeckButtonClass::ButtonCallback_2(){
  Serial << "BeckButtonClass::ButtonCallback_2: You pressed the Yellow button #2" << endl;
  return;
} //ButtonCallback_2


void BeckButtonClass::ButtonCallback_3(){
  Serial << "BeckButtonClass::ButtonCallback_3: You pressed the Red button #3" << endl;
  return;
} //ButtonCallback_3


void BeckButtonClass::ButtonCallback_4(){
  Serial << "BeckButtonClass::ButtonCallback_4: You pressed the Blue button #4" << endl;
  return;
} //ButtonCallback_4


BeckButtonClass::~BeckButtonClass() {
  Serial << "~BeckButtonClass(): Destructor" << endl;
  return;
} //destructor
//Last line.
