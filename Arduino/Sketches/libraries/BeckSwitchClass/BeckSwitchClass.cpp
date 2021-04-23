const char szSwitchFileName[]  = "BeckSystemClass.cpp";
const char szSwitchFileDate[]  = "4/20/21b";

#include <BeckThermostatDataClass.h>
#include <BeckSwitchClass.h>
#include <Streaming.h>

SwitchesClass       BiotaSwitches;

SwitchClass::SwitchClass() {
  Serial << "SwitchClass::SwitchClass(): " << szSwitchFileName << ", " << szSwitchFileDate << endl;
} //constructor


SwitchClass::~SwitchClass() {
  Serial << "~SwitchClass(): Destructing" << endl;
} //destructor


void SwitchClass::Setup(){
  Serial << "SwitchClass::Setup(): " << szSwitchFileName << ", " << szSwitchFileDate << endl;
  return;
} //Setup

void SwitchClass::Handle(){
  if (bMyLastState != bMyState){
    bMyLastState= bMyState;
    SetMyPin();
  }
  return;
}   //Handle


void SwitchClass::SetMyPin() {
  Serial << "SwitchClass(): SetMyPin" << endl;
  bool  bPinState= bMyState;

  if (bMyPinIsInverted){
    bPinState= !bMyState;
  }
  digitalWrite(wMyPinNumber, bPinState);
  return;
} //SetMyPin


ThermostatSwitchClass::ThermostatSwitchClass() {
  bMyState          = false;
  bMyLastState      = false;
  bMyPinIsInverted  = true;
  wMyPinNumber      = wThermostatPin;
  return;
} //constructor

ThermostatSwitchClass::~ThermostatSwitchClass() {
  Serial << "~ThermostatSwitchClass(): Destructing" << endl;
} //destructor

void ThermostatSwitchClass::Setup(){
  Serial << "ThermostatSwitchClass::Setup(): " << szSwitchFileName << ", " << szSwitchFileDate << endl;
  pinMode(wMyPinNumber, OUTPUT);
  return;
} //Setup

/*
void ThermostatSwitchClass::Handle(){
  bMyState= ThermostatData.GetThermostatOn();
  if (bMyLastState != bMyState){
    bMyLastState= bMyState;
    SetMyPin();
  }
  return;
}   //Handle
*/


HeatSwitchClass::HeatSwitchClass() {
  bMyState          = false;
  bMyLastState      = false;
  bMyPinIsInverted  = true;
  wMyPinNumber      = wHeatSwitchPin;
} //constructor

HeatSwitchClass::~HeatSwitchClass() {
  Serial << "~HeatSwitchClass(): Destructing" << endl;
} //destructor

void HeatSwitchClass::Setup(){
  Serial << "HeatSwitchClass::Setup(): " << szSwitchFileName << ", " << szSwitchFileDate << endl;
  pinMode(wMyPinNumber, OUTPUT);
  return;
} //Setup

/*
void HeatSwitchClass::Handle(){
  bMyState= ThermostatData.GetHeatOn();
  if (bMyLastState != bMyState){
    bMyLastState= bMyState;
    SetMyPin();
  }
  return;
}   //Handle
*/

SwitchesClass::SwitchesClass() {
return;
} //constructor

SwitchesClass::~SwitchesClass() {
  Serial << "~SwitchesClass(): Destructing" << endl;
} //destructor

void SwitchesClass::Setup(){
  Serial << "SwitchesClass::Setup(): " << szSwitchFileName << ", " << szSwitchFileDate << endl;
  ThermostatSwitch.Setup();
  HeatSwitch.Setup();
  return;
} //Setup

void SwitchesClass::Handle(){
  ThermostatSwitch.Handle();
  HeatSwitch.Handle();
  return;
}   //Handle
//Last line.
