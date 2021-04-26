const char szSwitchFileName[]  = "BeckSwitchClass.cpp";
const char szSwitchFileDate[]  = "4/26/21b";

#include <BeckSwitchClass.h>
#include <BeckThermostatDataClass.h>
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


ThermostatSwitchClass::ThermostatSwitchClass() {
  bMyPinIsInverted  = true;
  return;
} //constructor

ThermostatSwitchClass::~ThermostatSwitchClass() {
  Serial << "~ThermostatSwitchClass(): Destructing" << endl;
} //destructor

void ThermostatSwitchClass::Setup(){
  Serial << "ThermostatSwitchClass::Setup(): " << szSwitchFileName << ", " << szSwitchFileDate << endl;
  Serial << "ThermostatSwitchClass::Setup(): Call pinMode(" << wMyPinNumber << ", OUTPUT)" << endl;
  pinMode(wMyPinNumber, OUTPUT);
  return;
} //Setup

void ThermostatSwitchClass::Handle(){
  bool  CurrentThermostatOn           = ThermostatData.GetThermostatOn();
  bool  CurrentLastThermostatOn       = ThermostatData.GetLastThermostatOn();

  if (CurrentThermostatOn != CurrentLastThermostatOn){
    ThermostatData.SetLastThermostatOn(CurrentThermostatOn);
    Serial << "ThermostatSwitchClass::Handle(): Call SetMyPin()" << endl;
    SetPin();
  }
  return;
}   //Handle

void ThermostatSwitchClass::SetPin() {
  bool  PinState= ThermostatData.GetThermostatOn();

  //Relays are set when the input is low.
  if (bMyPinIsInverted){
    PinState= !PinState;
  }
  Serial << "ThermostatSwitchClass::SetPin(): Call digitalWrite(" << wThermostatPin << ", " << PinState << ")" << endl;
  digitalWrite(wThermostatPin, PinState);
  return;
} //SetThermostatPin


HeatSwitchClass::HeatSwitchClass() {
  bMyState          = false;
  bMyLastState      = false;
  bMyPinIsInverted  = true;
  wMyPinNumber      = wHeatPin;
} //constructor

HeatSwitchClass::~HeatSwitchClass() {
  Serial << "~HeatSwitchClass(): Destructing" << endl;
} //destructor

void HeatSwitchClass::Setup(){
  Serial << "HeatSwitchClass::Setup(): " << szSwitchFileName << ", " << szSwitchFileDate << endl;
  Serial << "HeatSwitchClass::Setup(): Call pinMode(" << wMyPinNumber << ", OUTPUT)" << endl;
  pinMode(wMyPinNumber, OUTPUT);
  return;
} //Setup

void HeatSwitchClass::Handle(){
  bool  CurrentHeatOn           = ThermostatData.GetHeatOn();
  bool  CurrentLastHeatOn       = ThermostatData.GetLastHeatOn();

  if (CurrentHeatOn != CurrentLastHeatOn){
    ThermostatData.SetLastHeatOn(CurrentHeatOn);
    Serial << "HeatSwitchClass::Handle(): Call SetMyPin()" << endl;
    SetPin();
  }
  return;
}   //Handle

void HeatSwitchClass::SetPin() {
  bool  PinState= ThermostatData.GetHeatOn();

  //Relays are set when the input is low.
  if (bMyPinIsInverted){
    PinState= !PinState;
  }
  Serial << "HeatSwitchClass::SetPin(): Call digitalWrite(" << wHeatPin << ", " << PinState << ")" << endl;
  digitalWrite(wHeatPin, PinState);
  return;
} //SetThermostatPin


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
