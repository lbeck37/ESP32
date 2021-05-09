// ThermostatDataClass.h, 4/23/21a
const char szThermostatDataClassFileName[]  = "ThermostatDataClass.cpp";
const char szThermostatDataClassFileDate[]  = "5/9/21a";

#include <BeckThermostatDataClass.h>
#include <Streaming.h>

ThermostatDataClass ThermostatData;

ThermostatDataClass::ThermostatDataClass() {
} //constructor


ThermostatDataClass::~ThermostatDataClass() {
  Serial << "~SystemClass(): Destructing" << endl;
} //destructor


void ThermostatDataClass::Setup(){
  Serial << "ThermostatDataClass::Setup(): " <<
      szThermostatDataClassFileName << ", " << szThermostatDataClassFileDate << endl;
  return;
} //Setup


void ThermostatDataClass::Handle(){
  return;
} //Handle

void ThermostatDataClass::SetSetpoint(float fNewSetpoint){
  //Change the setpoint as long as the new setpoint is between MinSetpoint and MaxSetpoint.
  Serial << "ThermostatDataClass::SetSetpoint(" << fNewSetpoint << "): Begin" << endl;
  float fOriginalSetpoint= GetSetpoint();

  if((fNewSetpoint >= GetMinSetpoint()) && (fNewSetpoint <= GetMaxSetpoint())){
    if(fNewSetpoint != fOriginalSetpoint){
      Setpoint= fNewSetpoint;
      SetThermostatOffDeg();
      Serial << "ThermostatDataClass::SetSetpoint(): Set Setpoint to " << Setpoint << endl;
    } //if(fSetpoint!=_fSetpoint)
  } //if((fSetpoint>=...
  else{
    Serial << "ThermostatDataClass::SetSetpoint(): Outside of range." << endl;
     }
  return;
} //SetSetpoint(float)


float ThermostatDataClass::GetSetpoint(){
  return Setpoint;
}


void ThermostatDataClass::SetCurrentTemperature(float NewCurrentTemperature){
  CurrentTemperature= NewCurrentTemperature;
  return;
}


float ThermostatDataClass::GetCurrentTemperature(){
  return CurrentTemperature;
}


void ThermostatDataClass::SetMaxHeatRange(float NewMaxHeatRange){
  MaxHeatRange= NewMaxHeatRange;
  SetThermostatOffDeg();
  return;
}


float ThermostatDataClass::GetMaxHeatRange(){
  return MaxHeatRange;
}

void ThermostatDataClass::SetThermostatOffDeg(void){
  ThermostatOffDeg= Setpoint + MaxHeatRange;
  return;
}

float ThermostatDataClass::GetThermostatOffDeg(void){
  return ThermostatOffDeg;
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


void ThermostatDataClass::SetThermostatOn(bool NewThermostatOn){
  ThermostatOn= NewThermostatOn;
  return;
}


bool ThermostatDataClass::GetThermostatOn(){
  return ThermostatOn;
}  //GetThermostatOn


void ThermostatDataClass::SetHeatOn(bool NewHeatOn){
  HeatOn= NewHeatOn;
  return;
}


bool ThermostatDataClass::GetHeatOn(){
  return HeatOn;
}


void ThermostatDataClass::SetLastThermostatOn(bool NewLastThermostatOn){
  LastThermostatOn= NewLastThermostatOn;
  return;
}


bool ThermostatDataClass::GetLastThermostatOn(){
  return LastThermostatOn;
}  //GetThermostatOn


void ThermostatDataClass::SetLastHeatOn(bool NewLastHeatOn){
  LastHeatOn= NewLastHeatOn;
  return;
}


bool ThermostatDataClass::GetLastHeatOn(){
  return LastHeatOn;
}
//Last line.
