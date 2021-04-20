// ThermostatDataClass.h, 4/20/21c
const char szThermostatDataClassFileName[]  = "BeckDisplayClass.cpp";
const char szThermostatDataClassFileDate[]  = "4/20/21b";

#include <BeckThermostatDataClass.h>
#include <Streaming.h>

ThermostatDataClass ThermostatData;

ThermostatDataClass::ThermostatDataClass() {
  Serial << "ThermostatDataClass::ThermostatDataClass(): " <<
      szThermostatDataClassFileName << ", " << szThermostatDataClassFileDate << endl;
} //constructor


ThermostatDataClass::~ThermostatDataClass() {
  Serial << "~SystemClass(): Destructing" << endl;
} //destructor


void ThermostatDataClass::Setup(){
  return;
} //Setup


void ThermostatDataClass::Handle(){
  return;
} //Handle

void ThermostatDataClass::SetSetpoint(float fNewSetpoint){
  //Serial << "ThermostatDataClass::SetSetpoint(" << fNewSetpoint << "): Begin" << endl;
  float fOriginalSetpoint= Setpoint;
  if((fNewSetpoint >= MinSetpoint) && (fNewSetpoint <= MaxSetpoint)){
    if(fNewSetpoint != fOriginalSetpoint){
      Setpoint= fNewSetpoint;
      ThermoOffDeg = Setpoint + MaxHeatRange;
      Serial << "ThermostatDataClass::SetSetpoint(): Set Setpoint to " << Setpoint << endl;
    } //if(fSetpoint!=_fSetpoint)
  } //if((fSetpoint>=...
  if(Setpoint == fOriginalSetpoint){
    //Serial << "ThermostatDataClass::SetSetpoint(): Setpoint remains at " << Setpoint << endl;
  } //if((_fSetpoint==fLastSetpoint)
  return;
} //SetSetpoint(float)


float ThermostatDataClass::GetSetpoint(){
  return Setpoint;
}


void ThermostatDataClass::SetCurrentDegF(float NewCurrentDegF){
  CurrentDegF= NewCurrentDegF;
  return;
}


void ThermostatDataClass::SetProposedSetpoint (float NewProposedSetpoint){
  ProposedSetpoint= NewProposedSetpoint;
  return;
}
float ThermostatDataClass::GetProposedSetpoint (void){
  return ProposedSetpoint;
}


float ThermostatDataClass::GetCurrentDegF(){
  return CurrentDegF;
}


void ThermostatDataClass::SetMaxHeatRange(float NewMaxHeatRange){
  MaxHeatRange= NewMaxHeatRange;
  return;
}


float ThermostatDataClass::GetMaxHeatRange(){
  return MaxHeatRange;
}


void ThermostatDataClass::SetMinSetpoint(float NewMinSetpoint){
  MinSetpoint= NewMinSetpoint;
  return;
}

float ThermostatDataClass::GetMinSetpoint(void){
  return MinSetpoint;
}


void ThermostatDataClass::SetMaxSetpoint(float NewMaxSetpoint){
  MaxSetpoint= NewMaxSetpoint;
  return;
}

float ThermostatDataClass::GetMaxSetpoint(void){
  return MaxSetpoint;
}


void ThermostatDataClass::SetThermostatOn(bool NewThermoOn){
  ThermoOn= NewThermoOn;
  return;
}


bool ThermostatDataClass::GetThermostatOn(){
  return ThermoOn;
}  //GetThermostatOn


void ThermostatDataClass::SetHeatOn(bool NewHeatOn){
  HeatOn= NewHeatOn;
  return;
}


bool ThermostatDataClass::GetHeatOn(){
  return HeatOn;
}
//Last line.
