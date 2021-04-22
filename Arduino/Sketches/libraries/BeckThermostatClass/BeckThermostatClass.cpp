const char szThermostatFileName[]  = "BeckThermostatClass.cpp";
const char szThermostatFileDate[]  = "4/22/21b";

#include <BeckThermostatClass.h>
#include <BeckLogLib.h>
#include <BeckSwitchLib.h>
#include <BeckThermostatDataClass.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <Streaming.h>

//Create OneWire instance and tell Dallas Temperature Library to use oneWire Library
OneWire                 BiotaOneWire(sOneWireGPIO);
DallasTemperature       BiotaTempSensor(&BiotaOneWire);

ThermostatClass         BiotaThermostat;


ThermostatClass::ThermostatClass() {
  Serial << "ThermostatClass::ThermostatClass(): " << szThermostatFileName << ", " << szThermostatFileDate << endl;
} //constructor


ThermostatClass::~ThermostatClass() {
  Serial << "~ThermostatClass(): Destructing" << endl;
} //destructor


void ThermostatClass::Setup(){
  Serial << "ThermostatClass::Setup(): Begin and do nothing" << endl;
  return;
}


void ThermostatClass::Handle(){
  //Update Setpoint after qualifying
  float fProposedSetpoint= ThermostatData.GetProposedSetpoint();
  ThermostatData.SetSetpoint(fProposedSetpoint);

  float fCurrentDegF      = ReadCurrentDegF();
  float fSetpoint         = ThermostatData.GetSetpoint();
  float fThermoOffDeg     = ThermostatData.GetSetpoint() + ThermostatData.GetMaxHeatRange();
  bool  bThermostatIsOn   = ThermostatData.GetThermostatOn();
  bool  bHeatIsOn         = ThermostatData.GetHeatOn();

  //If the Thermostat is OFF, make sure the heat  switch is off, too.
  if (!bThermostatIsOn){
    if (bHeatIsOn){
      TurnHeatOn(false);
    }
    return;
  } //if(!bThermostatIsOn)

  //If the heat is OFF and the temperature is below the set-point, turn the heat ON
  if (!bHeatIsOn && (fCurrentDegF < fSetpoint)){
    TurnHeatOn(true);
  }

  //If the heat is ON and the temperature is above the off-point, then turn the heat OFF
  if (bHeatIsOn && (fCurrentDegF >= fThermoOffDeg)){
      TurnHeatOn(false);
  }

  //If the heat is OFF and the temperature is below the set-point, turn the heat ON
  if (!bHeatIsOn && (fCurrentDegF < fSetpoint)){
    TurnHeatOn(true);
  }

  if(millis() >= ulNextPrintMsec){
    ulNextPrintMsec= millis() + ulPrintPeriodMsec;
    LogThermostatData(ThermostatData.GetCurrentDegF());
  } //if(millis()>=ulNextPrintMsec)

  HandleHeatSwitch();
  return;
} //Handle


float ThermostatClass::ReadCurrentDegF(){
  //This routine reads the Dallas One-wire temperature sensor
  //It sets this value into the ThermostatData object.
  //It returns the newly read value.
  float fCurrentDegF;

  if(millis() >= ulNextSensorReadMsec){
    ulNextSensorReadMsec= millis() + ulSensorReadPeriodMsec;
    //Read the Dallas One-wire temperature sensor
    BiotaTempSensor.requestTemperatures(); // Send the command to get temperatures
    fCurrentDegF= BiotaTempSensor.getTempFByIndex(0);
    ThermostatData.SetCurrentDegF(fCurrentDegF);
  } //if(millis() >= ulNextSensorReadMsec)
  return fCurrentDegF;
} //ReadCurrentDegF


void ThermostatClass::HandleHeatSwitch(){
  bool  bThermostatIsOn   = ThermostatData.GetThermostatOn();
  bool  bHeatIsOn         = ThermostatData.GetHeatOn();
  int   wHeatSwitchValue  = 0;

  //Turn the switch on if the Thermostat is ON and Heat ON is set in ThermoDataClass
  if (bThermostatIsOn && bHeatIsOn){
    wHeatSwitchValue= 1;
  }

  //Only change the switch if it's different.
  if (wHeatSwitchValue != asSwitchState[sHeatSwitchNum]){
    asSwitchState[sHeatSwitchNum]= wHeatSwitchValue;
    SetSwitch(sHeatSwitchNum, wHeatSwitchValue);
    Serial << ": Set heat switch to " << wHeatSwitchValue << endl;
  }
  return;
} //HandleHeatSwitch


void ThermostatClass::LogThermostatData(float fCurrentDegF){
  static char    sz100CharBuffer[100];
  float fThermostatOffDeg= ThermostatData.GetSetpoint() + ThermostatData.GetMaxHeatRange();
  sprintf(sz100CharBuffer, "HeatOn= %d, DegF= %4.2f, Setpoint= %4.2f, ThermoOffDegF= %4.2f",
    ThermostatData.GetHeatOn(), ThermostatData.GetCurrentDegF(),
    ThermostatData.GetSetpoint(), fThermostatOffDeg);
  LogToSerial(sz100CharBuffer);
  return;
} //LogThermostatData


void ThermostatClass::TurnHeatOn(bool bTurnOn){
  if (bTurnOn){
    String szLogString= "ThermostatClass::TurnHeatOn(): ON";
    LogToSerial(szLogString);
    ThermostatData.SetHeatOn(true);
    SetHeatSwitch(sSwitchClosed);
  } //if(bTurnOn)
  else{
    String szLogString= "ThermostatClass::TurnHeatOn(): OFF";
    LogToSerial(szLogString);
    ThermostatData.SetHeatOn(false);
    SetHeatSwitch(sSwitchOpen);
  } //if(bTurnOn)else
  return;
} //TurnHeatOn
//Last line.
