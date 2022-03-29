const char szSystemFileName[]  = "BeckButtonsClass.cpp";
const char szSystemFileDate[]  = "3/28/22d";

#include <BeckButtonsClass.h>
#include <BeckButtonClass.h>
#include <BeckCarSetClass.h>
#include <Streaming.h>

BeckButtonsClass::BeckButtonsClass() {
  Serial << "BeckButtonsClass(): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;

  Serial << "\BeckButtonsClass(): Default CTR, Do _poButton= new BeckButtonClass() for " << _wNumButtons << " buttons" << endl;
  for(int wButton= 1; wButton <= _wNumButtons; wButton++){
    _poButtons[wButton]= new BeckButtonClass(wButton);
  } //for

  Serial << "BeckButtonsClass(): Default CTR, Done" << endl;
  return;
} //constructor


int BeckButtonsClass::wHandleLoop(){
  int wReturn= 0;

  for(int wButton= 1; wButton <= _wNumButtons; wButton++){
    int wButtonPressed= _poButtons[wButton]->wHandleLoop();
    if (wButtonPressed > 0){
      wReturn= wButtonPressed;
    } //if(wButtonPressed>0)
  } //for
  return wReturn;
} //wHandleLoop


BeckButtonsClass::~BeckButtonsClass() {
  Serial << "~BeckButtonsClass(): Destructor" << endl;
  return;
} //destructor
//Last line.
