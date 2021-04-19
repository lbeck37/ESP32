const char szThermostatFileName[]  = "BeckThermostatClass.cpp";
const char szThermostatFileDate[]  = "4/19/21b";

#include <BeckThermostatClass.h>
#include <BeckLogLib.h>
#include <BeckSwitchLib.h>
#include <BeckThermostatDataStruct.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <Streaming.h>

//Create OneWire instance and tell Dallas Temperature Library to use oneWire Library
OneWire                 BiotaOneWire(sOneWireGPIO);
DallasTemperature       BiotaTempSensor(&BiotaOneWire);

ThermostatClass         BiotaThermostat;
//ThermostatDataStruct    ThermostatData;


ThermostatClass::ThermostatClass() {
  Serial << "ThermostatClass::ThermostatClass(): " << szThermostatFileName << ", " << szThermostatFileDate << endl;
} //constructor


ThermostatClass::~ThermostatClass() {
  Serial << "~ThermostatClass(): Destructing" << endl;
} //destructor


void ThermostatClass::Setup(){
  Serial << LOG0 << "ThermostatClass::Setup(): Begin and do nothing" << endl;
  return;
}


  void ThermostatClass::Handle(){
  //Serial << LOG0 << "ThermostatClass::Handle(): Begin" << endl;
  static bool     bStateChanged= false;
  unsigned long   ulStartTime;

  //Read the Dallas One-wire temperature sensor
  float fDegF= GetCurrentDegF();

  if (bThermoOn){
    if (bHeatOn){
      if (fDegF >= fThermoOffDeg){
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
    //String szLogString= "Handle(): bThermoOn is false, Thermostat is off";
    //LogToSerial(szLogString);
  } //if(_bThermoOn)else
  if(bStateChanged || (millis() >= ulNextThermPrintMsec)){
    bStateChanged= false;
    ulNextThermPrintMsec= millis() + ulThermPrintPeriodMsec;
    if(bThermoOn) {
      LogThermostatData(fDegF);
    } //if(_bThermoOn)
    else {
      //String szLogString= "Handle(): bThermoOn is false, Thermostat is off";
      //LogToSerial(szLogString);
    } //if(_bThermoOn)else
  }
  //Serial << LOG0 << "ThermostatClass::Handle(): Call HandleHeatSwitch()" << endl;
  HandleHeatSwitch();
  return;
} //Handle


void ThermostatClass::HandleHeatSwitch(){
  static bool   bLastHeatOn= false;
  //Serial << LOG0 << "ThermostatClass::HandleHeatSwitch(): Begin, bLastHeatOn= " << bLastHeatOn << endl;
  if (bHeatOn != bLastHeatOn){
    bLastHeatOn= bHeatOn;
    if (bHeatOn){
      asSwitchState[sHeatSwitchNum]= sOn;
      Serial << LOG0 << "ThermostatClass::HandleHeatSwitch(): bHeatOn is now TRUE, Call SetSwitch(" <<
          sHeatSwitchNum << ", " << sOff << ")" << endl;
      SetSwitch(sHeatSwitchNum, sOn);
    } //if(_bHeatOn)
    else{
      asSwitchState[sHeatSwitchNum]= sOff;
      Serial << LOG0 << "ThermostatClass::HandleHeatSwitch(): bHeatOn is now FALSE, Call SetSwitch(" <<
          sHeatSwitchNum << ", " << sOff << ")" << endl;
      SetSwitch(sHeatSwitchNum, sOff);
    } //if(_bHeatOn)else
  } //if (bHeatOn != bLastHeatOn)
  //Serial << LOG0 << "ThermostatClass::HandleHeatSwitch(): End, bLastHeatOn= " << bLastHeatOn << endl;
  return;
} //HandleHeatSwitch


void ThermostatClass::LogThermostatData(float fDegF){
  static char    sz100CharBuffer[100];
  sprintf(sz100CharBuffer, " %d %d %4.2f %4.2f %4.2f", bHeatOn, sThermoTimesCount, fDegF, fSetpoint, fThermoOffDeg);
  LogToSerial(sz100CharBuffer);
  return;
} //LogThermostatData


/*
void ThermostatClass::SetSetpoint(unsigned char ucSetpoint){
  float fSetpoint= round( ((float)ucSetpoint / 255.0) * 100.0);
  SetSetpoint(fSetpoint);
  return;
} //SetSetpoint(unsigned char)
*/


void ThermostatClass::SetSetpoint(float fNewSetpoint){
  Serial << LOG0 << "ThermostatClass::SetSetpoint(" << fNewSetpoint << "): Begin" << endl;
  float fOriginalSetpoint= fSetpoint;
  if( (fNewSetpoint >= fMinSetpoint) && (fNewSetpoint <= fMaxSetpoint)){
    if(fNewSetpoint != fOriginalSetpoint){
      fSetpoint      = fNewSetpoint;
      fThermoOffDeg = fSetpoint + fMaxHeatRange;
      Serial << LOG0 << "ThermostatClass::SetSetpoint(): Set fSetpoint to " << fSetpoint << endl;
    } //if(fSetpoint!=_fSetpoint)
  } //if((fSetpoint>=...
  if(fSetpoint == fOriginalSetpoint){
    Serial << LOG0 << "ThermostatClass::SetSetpoint(): fSetpoint remains at " << fSetpoint << endl;
  } //if((_fSetpoint==fLastSetpoint)
  return;
} //SetSetpoint(float)


float ThermostatClass::GetSetpoint(){
  return fSetpoint;
}


float ThermostatClass::GetCurrentDegF(){
  //This routine reads and also sets the new current temperature.
  BiotaTempSensor.requestTemperatures(); // Send the command to get temperatures
  fLastDegF= BiotaTempSensor.getTempFByIndex(0);
  return fLastDegF;
}


void ThermostatClass::SetMaxHeatRange(float NewMaxHeatRange){
  fMaxHeatRange= NewMaxHeatRange;
  return;
}


float ThermostatClass::GetMaxHeatRange(){
  return fMaxHeatRange;
}


void ThermostatClass::SetMinSetpoint(float NewMinSetpoint){
  fMinSetpoint= NewMinSetpoint;
  return;
}

float ThermostatClass::GetMinSetpoint(void){
  return fMinSetpoint;
}


void ThermostatClass::SetMaxSetpoint(float NewMaxSetpoint){
  fMaxSetpoint= NewMaxSetpoint;
  return;
}

float ThermostatClass::GetMaxSetpoint(void){
  return fMaxSetpoint;
}


void ThermostatClass::SetThermostatOn(bool bNewThermoOn){
  bThermoOn= bNewThermoOn;
  return;
}


bool ThermostatClass::GetThermostatOn(){
  return bThermoOn;
}  //GetThermostatOn


bool ThermostatClass::GetHeatOn(){
  return bHeatOn;
}


void ThermostatClass::TurnHeatOn(bool bTurnOn){
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
