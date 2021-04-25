const char szSwitchFileName[]  = "BeckSwitchClass.cpp";
const char szSwitchFileDate[]  = "4/24/21c";

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
  Serial << "SwitchClass::SetMyPin(): Call digitalWrite(" << wMyPinNumber << ", " << bPinState << ")" << endl;
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
  //Serial << "ThermostatSwitchClass::Setup(): " << szSwitchFileName << ", " << szSwitchFileDate << endl;
  Serial << "ThermostatSwitchClass::Setup(): Call pinMode(" << wMyPinNumber << ", OUTPUT)" << endl;
  pinMode(wMyPinNumber, OUTPUT);
  return;
} //Setup


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
  //Serial << "HeatSwitchClass::Setup(): " << szSwitchFileName << ", " << szSwitchFileDate << endl;
  Serial << "HeatSwitchClass::Setup(): Call pinMode(" << wMyPinNumber << ", OUTPUT)" << endl;
  pinMode(wMyPinNumber, OUTPUT);
  return;
} //Setup


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
