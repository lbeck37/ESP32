// BeckSwitchLib.cpp 12/28/19a
#include <BeckSwitchLib.h>
#include <BeckLogLib.h>

int   asSwitchState[]       = {0, 0, 0, 0, 0};
int   asSwitchLastState[]   = {sNotInit, sNotInit, sNotInit, sNotInit, sNotInit};

void SetupSwitches(){
  Serial << LOG0 << "SetupSwitches(): Begin" << endl;
  for (int sSwitch= 1; sSwitch <= sNumSwitches; sSwitch++){
    if(asSwitchPin[sSwitch] != sNoSwitch){
      pinMode(asSwitchPin[sSwitch], OUTPUT);
      //SetSwitch(sSwitch, sSwitchOpen);
    } //if(asSwitchPin[sSwitch]!=sNoSwitch)
  } //for
  return;
} //SetupSwitches


void SetHeatSwitch(int sSwitchState){
  Serial << "BeckSwitchLib.cpp: SetHeatSwitch(): call SetSwitch(), Heat Switch State= " << sSwitchState << endl;
  SetSwitch(sHeatSwitchNum, sSwitchState);
  return;
} //SetHeatSwitch


void SetThermoSwitch(int sSwitchState){
  Serial << "BeckSwitchLib.cpp: SetThermoSwitch(): call SetSwitch(), Thermo Switch State= " << sSwitchState << endl;
  SetSwitch(sThermoSwitchNum, sSwitchState);
  return;
} //SetThermoSwitch


void SetSwitch(int sSwitch, int sSwitchState){
  int sSwitchPin= asSwitchPin[sSwitch];
  bool bPinSetting;
  asSwitchState[sSwitch]= sSwitchState;
  if (abSwitchInverted[sSwitch]){
    bPinSetting= !sSwitchState;
  } //if(abSwitchInverted[sSwitch])
  else{
    bPinSetting= sSwitchState;
  } //if(abSwitchInverted[sSwitch])else
/*
  String szLogString= "SetSwitch:  ";
  szLogString += sSwitch;
  szLogString += ",";
  szLogString += sSwitchState;
  szLogString += ",";
  szLogString += sSwitchPin;
  szLogString += ",";
  szLogString += bPinSetting;
  LogToSerial(szLogString);
*/

  Serial << LOG0 << "SetSwitch(): Switch= " << sSwitch << ", Switch State= " << sSwitchState << ", Switch Pin= " << sSwitchPin <<
      ", Pin Setting= " << bPinSetting << endl;
  //Some switch positions don't have pins, just Blynk LEDs.
  if (sSwitchPin >= 0){
    digitalWrite(sSwitchPin, bPinSetting);
    asSwitchState[sSwitch]= sSwitchState;
  } //if(sSwitchPin>=0)
  return;
} //SetSwitch
//Last line
