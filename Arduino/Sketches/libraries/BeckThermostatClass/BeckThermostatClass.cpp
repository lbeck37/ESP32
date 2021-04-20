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
  static bool     bStateChanged= false;
  unsigned long   ulStartTime;

  //Read the Dallas One-wire temperature sensor
  Serial << LOG0 << "ThermostatClass::Handle(): Call GetCurrentDegF()" << endl;
  ThermostatData.fCurrentDegF= GetCurrentDegF();

  //Update Setpoint after qualifying
  SetSetpoint(ThermostatData.fProposedSetpoint);

  if (ThermostatData.bThermoOn){
    if (ThermostatData.bHeatOn){
      if (ThermostatData.fCurrentDegF >= fThermoOffDeg){
        //bStateChanged= true;
        if (++sThermoTimesCount >= sThermoTimesInRow){
          TurnHeatOn(false);
          //DidHeatOnChange= true;
          sThermoTimesCount= 0;
        } //if(sThermoTimesCount>=sThermoTimesInRow)
      } //if(fCurrentDegF>=_fThermoOffDegF)
      else{
        sThermoTimesCount= 0;
      } //if(fCurrentDegF>=_fThermoOffDegF)else
    } //if(_ThermostatData.bHeatOn)
    else{
      if (ThermostatData.fCurrentDegF <= ThermostatData.fSetpoint){
        bStateChanged= true;
        if (++sThermoTimesCount >= sThermoTimesInRow){
          TurnHeatOn(true);
          //DidHeatOnChange= true;
          sThermoTimesCount= 0;
        } //if(sThermoTimesCount>=sThermoTimesInRow)
      } //if(fCurrentDegF<_fSetpoint)
      else{
        sThermoTimesCount= 0;
      } //if(fCurrentDegF<_fSetpoint)else
    } //if(_ThermostatData.bHeatOn)else
  } //if(_bThermoOn)
  else{
    //String szLogString= "Handle(): ThermostatData.bThermoOn is false, Thermostat is off";
    //LogToSerial(szLogString);
  } //if(_bThermoOn)else
  if(bStateChanged || (millis() >= ulNextThermPrintMsec)){
    bStateChanged= false;
    ulNextThermPrintMsec= millis() + ulThermPrintPeriodMsec;
    if(ThermostatData.bThermoOn) {
      LogThermostatData(ThermostatData.fCurrentDegF);
    } //if(_bThermoOn)
    else {
      //String szLogString= "Handle(): ThermostatData.bThermoOn is false, Thermostat is off";
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
  if (ThermostatData.bHeatOn != bLastHeatOn){
    bLastHeatOn= ThermostatData.bHeatOn;
    if (ThermostatData.bHeatOn){
      asSwitchState[sHeatSwitchNum]= sOn;
      Serial << LOG0 << "ThermostatClass::HandleHeatSwitch(): ThermostatData.bHeatOn is now TRUE, Call SetSwitch(" <<
          sHeatSwitchNum << ", " << sOff << ")" << endl;
      SetSwitch(sHeatSwitchNum, sOn);
    } //if(ThermostatData.bHeatOn)
    else{
      asSwitchState[sHeatSwitchNum]= sOff;
      Serial << LOG0 << "ThermostatClass::HandleHeatSwitch(): ThermostatData.bHeatOn is now FALSE, Call SetSwitch(" <<
          sHeatSwitchNum << ", " << sOff << ")" << endl;
      SetSwitch(sHeatSwitchNum, sOff);
    } //if(_bHeatOn)else
  } //if (ThermostatData.bHeatOn != bLastHeatOn)
  //Serial << LOG0 << "ThermostatClass::HandleHeatSwitch(): End, bLastHeatOn= " << bLastHeatOn << endl;
  return;
} //HandleHeatSwitch


void ThermostatClass::LogThermostatData(float fCurrentDegF){
  static char    sz100CharBuffer[100];
  sprintf(sz100CharBuffer, " %d %d %4.2f %4.2f %4.2f",
    ThermostatData.bHeatOn, sThermoTimesCount, ThermostatData.fCurrentDegF, ThermostatData.fSetpoint, fThermoOffDeg);
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
  float fOriginalSetpoint= ThermostatData.fSetpoint;
  if( (fNewSetpoint >= ThermostatData.fMinSetpoint) && (fNewSetpoint <= ThermostatData.fMaxSetpoint)){
    if(fNewSetpoint != fOriginalSetpoint){
      ThermostatData.fSetpoint      = fNewSetpoint;
      fThermoOffDeg = ThermostatData.fSetpoint + ThermostatData.fMaxHeatRange;
      Serial << LOG0 << "ThermostatClass::SetSetpoint(): Set fSetpoint to " << ThermostatData.fSetpoint << endl;
    } //if(fSetpoint!=_fSetpoint)
  } //if((fSetpoint>=...
  if(ThermostatData.fSetpoint == fOriginalSetpoint){
    Serial << LOG0 << "ThermostatClass::SetSetpoint(): fSetpoint remains at " << ThermostatData.fSetpoint << endl;
  } //if((_fSetpoint==fLastSetpoint)
  return;
} //SetSetpoint(float)


float ThermostatClass::GetSetpoint(){
  return ThermostatData.fSetpoint;
}


float ThermostatClass::GetCurrentDegF(){
  //This routine reads the sensor and returns the temperature.
  BiotaTempSensor.requestTemperatures(); // Send the command to get temperatures
  ThermostatData.fCurrentDegF= BiotaTempSensor.getTempFByIndex(0);
  Serial << LOG0 << "ThermostatClass::GetCurrentDegF(): ThermostatData.fCurrentDegF= " <<
      ThermostatData.fCurrentDegF << endl;
  return ThermostatData.fCurrentDegF;
}


void ThermostatClass::SetMaxHeatRange(float NewMaxHeatRange){
  ThermostatData.fMaxHeatRange= NewMaxHeatRange;
  return;
}


float ThermostatClass::GetMaxHeatRange(){
  return ThermostatData.fMaxHeatRange;
}


void ThermostatClass::SetMinSetpoint(float NewMinSetpoint){
  ThermostatData.fMinSetpoint= NewMinSetpoint;
  return;
}

float ThermostatClass::GetMinSetpoint(void){
  return ThermostatData.fMinSetpoint;
}


void ThermostatClass::SetMaxSetpoint(float NewMaxSetpoint){
  ThermostatData.fMaxSetpoint= NewMaxSetpoint;
  return;
}

float ThermostatClass::GetMaxSetpoint(void){
  return ThermostatData.fMaxSetpoint;
}


void ThermostatClass::SetThermostatOn(bool bNewThermoOn){
  ThermostatData.bThermoOn= bNewThermoOn;
  return;
}


bool ThermostatClass::GetThermostatOn(){
  return ThermostatData.bThermoOn;
}  //GetThermostatOn


bool ThermostatClass::GetHeatOn(){
  return ThermostatData.bHeatOn;
}


void ThermostatClass::TurnHeatOn(bool bTurnOn){
  if (bTurnOn){
    String szLogString= "ThermostatClass::TurnHeatOn(): ON";
    LogToSerial(szLogString);
    ThermostatData.bHeatOn= true;
    SetHeatSwitch(sSwitchClosed);
    sThermoTimesCount= 0;
  } //if(bTurnOn)
  else{
    String szLogString= "ThermostatClass::TurnHeatOn(): OFF";
    LogToSerial(szLogString);
    ThermostatData.bHeatOn= false;
    SetHeatSwitch(sSwitchOpen);
    sThermoTimesCount= 0;
  } //if(bTurnOn)else
  return;
} //TurnHeatOn
//Last line.
