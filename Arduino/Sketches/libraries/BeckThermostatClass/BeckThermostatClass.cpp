const char szFileName[]  = "BeckThermostatClass.cpp";
const char szFileDate[]  = "4/15/21a";

#include <BeckThermostatClass.h>
//#include <BeckMiniLib.h>
#include <BeckSwitchLib.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <BeckLogLib.h>
#include <Streaming.h>

//Create OneWire instance and tell Dallas Temperature Library to use oneWire Library
/*
OneWire             oOneWire(sOneWireGPIO);
DallasTemperature   oDallasTempSensor(&oOneWire);
*/
OneWire             BiotaOneWire(sOneWireGPIO);
DallasTemperature   BiotaTempSensor(&BiotaOneWire);

Thermostat          BiotaThermostat;

Thermostat::Thermostat() {
  Serial << "Thermostat::Thermostat(): " << szFileName << ", " << szFileDate << endl;
} //constructor


Thermostat::~Thermostat() {
  Serial << "~Thermostat(): Destructing" << endl;
} //destructor


void Thermostat::HandleThermostat(){
  //Serial << LOG0 << "Thermostat::HandleThermostat(): Begin" << endl;
  static bool     bStateChanged= false;
  unsigned long   ulStartTime;

  //Read the Dallas One-wire temperature sensor
  float fDegF= Get_CurrentDegF();

  if (bThermoOn){
    if (bHeatOn){
      if (fDegF >= fThermoOffDegF){
        bStateChanged= true;
        if (++sThermoTimesCount >= sThermoTimesInRow){
          TurnHeatOn(false);
          //DidHeatOnChange= true;
          sThermoTimesCount= 0;
        } //if(sThermoTimesCount>=sThermoTimesInRow)
      } //if(fDegF>=_fThermoOffDegF)
      else{
        sThermoTimesCount= 0;
      } //if(fDegF>=_fThermoOffDegF)else
    } //if(_bHeatOn)
    else{
      if (fDegF <= fSetpoint){
        bStateChanged= true;
        if (++sThermoTimesCount >= sThermoTimesInRow){
          TurnHeatOn(true);
          //DidHeatOnChange= true;
          sThermoTimesCount= 0;
        } //if(sThermoTimesCount>=sThermoTimesInRow)
      } //if(fDegF<_fSetpoint)
      else{
        sThermoTimesCount= 0;
      } //if(fDegF<_fSetpoint)else
    } //if(_bHeatOn)else
  } //if(_bThermoOn)
  else{
    //String szLogString= "HandleThermostat(): bThermoOn is false, Thermostat is off";
    //LogToSerial(szLogString);
  } //if(_bThermoOn)else
  if(bStateChanged || (millis() >= ulNextThermPrintMsec)){
    bStateChanged= false;
    ulNextThermPrintMsec= millis() + ulThermPrintPeriodMsec;
    if(bThermoOn) {
      LogThermostatData(fDegF);
    } //if(_bThermoOn)
    else {
      //String szLogString= "HandleThermostat(): bThermoOn is false, Thermostat is off";
      //LogToSerial(szLogString);
    } //if(_bThermoOn)else
  }
  //Serial << LOG0 << "Thermostat::HandleThermostat(): Call HandleHeatSwitch()" << endl;
  HandleHeatSwitch();
  return;
} //HandleThermostat


void Thermostat::HandleHeatSwitch(){
  static bool   bLastHeatOn= false;
  //Serial << LOG0 << "Thermostat::HandleHeatSwitch(): Begin, bLastHeatOn= " << bLastHeatOn << endl;
  if (bHeatOn != bLastHeatOn){
    bLastHeatOn= bHeatOn;
    if (bHeatOn){
      asSwitchState[sHeatSwitchNum]= sOn;
      Serial << LOG0 << "Thermostat::HandleHeatSwitch(): bHeatOn is now TRUE, Call SetSwitch(" <<
          sHeatSwitchNum << ", " << sOff << ")" << endl;
      SetSwitch(sHeatSwitchNum, sOn);
    } //if(_bHeatOn)
    else{
      asSwitchState[sHeatSwitchNum]= sOff;
      Serial << LOG0 << "Thermostat::HandleHeatSwitch(): bHeatOn is now FALSE, Call SetSwitch(" <<
          sHeatSwitchNum << ", " << sOff << ")" << endl;
      SetSwitch(sHeatSwitchNum, sOff);
    } //if(_bHeatOn)else
  } //if (bHeatOn != bLastHeatOn)
  //Serial << LOG0 << "Thermostat::HandleHeatSwitch(): End, bLastHeatOn= " << bLastHeatOn << endl;
  return;
} //HandleHeatSwitch


void Thermostat::LogThermostatData(float fDegF){
  static char    sz100CharBuffer[100];
  sprintf(sz100CharBuffer, " %d %d %4.2f %4.2f %4.2f", bHeatOn, sThermoTimesCount, fDegF, fSetpoint, fThermoOffDegF);
  LogToSerial(sz100CharBuffer);
  return;
} //LogThermostatData


void Thermostat::Set_Setpoint(unsigned char ucSetpoint){
  float fSetpoint= round( ((float)ucSetpoint / 255.0) * 100.0);
  Set_Setpoint(fSetpoint);
  return;
} //Set_Setpoint(unsigned char)


void Thermostat::Set_Setpoint(float fNewSetpoint){
  Serial << LOG0 << "Thermostat::Set_Setpoint(" << fNewSetpoint << "): Begin" << endl;
  float fOriginalSetpoint= fSetpoint;
  if( (fNewSetpoint >= fMinSetpoint) && (fNewSetpoint <= fMaxSetpoint)){
    if(fNewSetpoint != fOriginalSetpoint){
      fSetpoint      = fNewSetpoint;
      fThermoOffDegF = fSetpoint + fMaxHeatRangeF;
      Serial << LOG0 << "Thermostat::Set_Setpoint(): Set fSetpoint to " << fSetpoint << endl;
    } //if(fSetpoint!=_fSetpoint)
  } //if((fSetpoint>=...
  if(fSetpoint == fOriginalSetpoint){
    Serial << LOG0 << "Thermostat::Set_Setpoint(): fSetpoint remains at " << fSetpoint << endl;
  } //if((_fSetpoint==fLastSetpoint)
  return;
} //Set_Setpoint(float)


float Thermostat::Get_CurrentDegF(){
  //This routine reads and also sets the new current temperature.
  BiotaTempSensor.requestTemperatures(); // Send the command to get temperatures
  fLastDegF= BiotaTempSensor.getTempFByIndex(0);

  return fLastDegF;
}  //Get_CurrentDegF


float Thermostat::Get_Setpoint(){
  return fSetpoint;
}  //fGet_Setpoint


void Thermostat::Set_MaxHeatRangeF(float fNewMaxHeatRangeF){
  return;
} //Set_MaxHeatRangeF


float Thermostat::Get_MaxHeatRangeF(){
  return fMaxHeatRangeF;
}  //Get_MaxHeatRangeF


bool Thermostat::ThermostatIsOn(){
  return bThermoOn;
}  //ThermostatIsOn


bool Thermostat::HeatIsOn(){
  return bHeatOn;
}  //HeatIsOn


void Thermostat::TurnHeatOn(bool bTurnOn){
  if (bTurnOn){
    String szLogString= "TurnHeatOn(): ON";
    LogToSerial(szLogString);
    bHeatOn= true;
    SetHeatSwitch(sSwitchClosed);
    sThermoTimesCount= 0;
  } //if(bTurnOn)
  else{
    String szLogString= "TurnHeatOn(): OFF";
    LogToSerial(szLogString);
    bHeatOn= false;
    SetHeatSwitch(sSwitchOpen);
    sThermoTimesCount= 0;
  } //if(bTurnOn)else
  return;
} //TurnHeatOn
//Last line.
