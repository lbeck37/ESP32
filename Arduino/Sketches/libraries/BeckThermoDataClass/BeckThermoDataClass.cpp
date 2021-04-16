const char szFileName[]  = "BeckThermoDataClass.cpp";
const char szFileDate[]  = "4/15/21a";

#include <BeckThermoDataClass.h>
#include <BeckBiotaLib.h>

ThermoDataClass::ThermoDataClass() {
  Serial << "ThermoDataClass::ThermoDataClass(): " << szFileName << ", " << szFileDate << endl;
} //constructor


ThermoDataClass::~ThermoDataClass() {
  Serial << "~ThermoDataClass(): Destructing" << endl;
} //destructor


void ThermoDataClass::SetCurrentTemperature(float fNewTemperature){
  fCurrentDegF= fNewTemperature;
  return;
}

void ThermoDataClass::SetCurrentSetpoint(float fNewSetpoint){
  fSetpointDegF= fNewSetpoint;
  return;
}

void ThermoDataClass::SetMaxHeatRange(float fNewMaxHeatRange){
  fMaxHeatRangeF= fNewMaxHeatRange;
  return;
}

void ThermoDataClass::SetThermoOn(bool bNewThermoOn){
  bThermoOn= bNewThermoOn;
  return;
}

void ThermoDataClass::SetHeatOn(bool bNewHeatOn){
  fCurrentDegF= bNewHeatOn;
  return;
}


float ThermoDataClass::GetCurrentTemperature(void){
  return fCurrentDegF;
}

float ThermoDataClass::GetCurrentSetpoint(void){
  return fSetpointDegF;
}

float ThermoDataClass::GetMaxHeatRange(void){
  return fMaxHeatRangeF;
}

bool ThermoDataClass::GetThermoOn(void){
  return bThermoOn;
}

bool ThermoDataClass::GetHeatOn(void){
  return bHeatOn;
}

ThermoDataClass   ThermostatData;

//Last line.
