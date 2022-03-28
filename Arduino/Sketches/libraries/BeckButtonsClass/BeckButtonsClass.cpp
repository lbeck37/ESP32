const char szSystemFileName[]  = "BeckButtonsClass.cpp";
const char szSystemFileDate[]  = "3/22/22c";

#include <BeckButtonsClass.h>
#include <BeckCarSetClass.h>
#include <Streaming.h>

BeckButtonsClass::BeckButtonsClass() {
  Serial << "BeckButtonsClass(): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;

  Serial << "\BeckButtonsClass(): Default CTR, Do _poButton= new BeckButtonClass()" << endl;
  for(int wButton= 1; wButton <= _wNumButtons; wButton++){
    _poButtons[wButton]= new BeckButtonClass();
  } //for

  Serial << "BeckButtonsClass(): Default CTR, Done" << endl;
  return;
} //constructor


BeckButtonsClass::~BeckButtonsClass() {
  Serial << "~BeckButtonsClass(): Destructor" << endl;
  return;
} //destructor


void BeckButtonsClass::HandleLoop(){
  //_oTestButton.read();
  //ReadButtons();
  return;
} //HandleLoop
//Last line.
