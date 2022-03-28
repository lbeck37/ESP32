const char szSystemFileName[]  = "BeckButtonsClass.cpp";
const char szSystemFileDate[]  = "3/28/22c";

#include <BeckButtonsClass.h>
#include <BeckCarSetClass.h>
#include <Streaming.h>

BeckButtonsClass::BeckButtonsClass() {
  Serial << "BeckButtonsClass(): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;

  Serial << "\BeckButtonsClass(): Default CTR, Do _poButton= new BeckButtonClass() for " << _wNumButtons << " buttons" << endl;
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
  for(int wButton= 1; wButton <= _wNumButtons; wButton++){
    _poButtons[wButton]->HandleLoop();
  } //for
  return;
} //HandleLoop
//Last line.
