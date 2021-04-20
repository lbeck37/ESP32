const char szThermostatFileName[]  = "BeckThermostatClass.cpp";
const char szThermostatFileDate[]  = "4/19/21b";

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
//ThermostatDataStruct    ThermostatData;


float ReadCurrentDegF(){
  //This routine reads the sensor and returns the temperature.
  BiotaTempSensor.requestTemperatures(); // Send the command to get temperatures
  float fCurrentDegF= BiotaTempSensor.getTempFByIndex(0);

  ThermostatData.SetCurrentDegF(fCurrentDegF);
  Serial << "ThermostatClass::ReadCurrentDegF(): ThermostatData.GetCurrentDegF()= " <<
      ThermostatData.GetCurrentDegF() << endl;
  return ThermostatData.GetCurrentDegF();
}


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
  static bool     bStateChanged= false;
  //unsigned long   ulStartTime;

  //Read the Dallas One-wire temperature sensor
  Serial << "ThermostatClass::Handle(): Call GetCurrentDegF()" << endl;
  float   fCurrentDegF= ReadCurrentDegF();
  ThermostatData.SetCurrentDegF(fCurrentDegF);

  //Update Setpoint after qualifying
  float fProposedSetpoint= ThermostatData.GetProposedSetpoint();
  ThermostatData.SetSetpoint(fProposedSetpoint);

  if (ThermostatData.GetThermostatOn()){
    if (ThermostatData.GetHeatOn()){
      if (ThermostatData.GetCurrentDegF() >= fThermoOffDeg){
        //bStateChanged= true;
        if (++sThermoTimesCount >= sThermoTimesInRow){
          TurnHeatOn(false);
          //DidHeatOnChange= true;
          sThermoTimesCount= 0;
        } //if(sThermoTimesCount>=sThermoTimesInRow)
      } //if(GetCurrentDegF()>=_fThermoOffDegF)
      else{
        sThermoTimesCount= 0;
      } //if(GetCurrentDegF()>=_fThermoOffDegF)else
    } //if(_ThermostatData.GetHeatOn())
    else{
      if (ThermostatData.GetCurrentDegF() <= ThermostatData.GetSetpoint()){
        bStateChanged= true;
        if (++sThermoTimesCount >= sThermoTimesInRow){
          TurnHeatOn(true);
          //DidHeatOnChange= true;
          sThermoTimesCount= 0;
        } //if(sThermoTimesCount>=sThermoTimesInRow)
      } //if(GetCurrentDegF()<_fSetpoint)
      else{
        sThermoTimesCount= 0;
      } //if(GetCurrentDegF()<_fSetpoint)else
    } //if(_ThermostatData.GetHeatOn())else
  } //if(_bThermoOn)
  else{
    //String szLogString= "Handle(): ThermostatData.GetThermostatOn() is false, Thermostat is off";
    //LogToSerial(szLogString);
  } //if(_bThermoOn)else
  if(bStateChanged || (millis() >= ulNextThermPrintMsec)){
    bStateChanged= false;
    ulNextThermPrintMsec= millis() + ulThermPrintPeriodMsec;
    if(ThermostatData.GetThermostatOn()) {
      LogThermostatData(ThermostatData.GetCurrentDegF());
    } //if(_bThermoOn)
    else {
      //String szLogString= "Handle(): ThermostatData.GetThermostatOn() is false, Thermostat is off";
      //LogToSerial(szLogString);
    } //if(_bThermoOn)else
  }
  //Serial << "ThermostatClass::Handle(): Call HandleHeatSwitch()" << endl;
  HandleHeatSwitch();
  return;
} //Handle


void ThermostatClass::HandleHeatSwitch(){
  static bool   bLastHeatOn= false;
  //Serial << "ThermostatClass::HandleHeatSwitch(): Begin, bLastHeatOn= " << bLastHeatOn << endl;
  if (ThermostatData.GetHeatOn() != bLastHeatOn){
    bLastHeatOn= ThermostatData.GetHeatOn();
    if (ThermostatData.GetHeatOn()){
      asSwitchState[sHeatSwitchNum]= sOn;
      Serial << "ThermostatClass::HandleHeatSwitch(): ThermostatData.GetHeatOn() is now TRUE, Call SetSwitch(" <<
          sHeatSwitchNum << ", " << sOff << ")" << endl;
      SetSwitch(sHeatSwitchNum, sOn);
    } //if(ThermostatData.GetHeatOn())
    else{
      asSwitchState[sHeatSwitchNum]= sOff;
      Serial << "ThermostatClass::HandleHeatSwitch(): ThermostatData.GetHeatOn() is now FALSE, Call SetSwitch(" <<
          sHeatSwitchNum << ", " << sOff << ")" << endl;
      SetSwitch(sHeatSwitchNum, sOff);
    } //if(_bHeatOn)else
  } //if (ThermostatData.GetHeatOn() != bLastHeatOn)
  //Serial << "ThermostatClass::HandleHeatSwitch(): End, bLastHeatOn= " << bLastHeatOn << endl;
  return;
} //HandleHeatSwitch


void ThermostatClass::LogThermostatData(float fCurrentDegF){
  static char    sz100CharBuffer[100];
  float fThermostatOffDeg= ThermostatData.GetSetpoint() + ThermostatData.GetMaxHeatRange();
  sprintf(sz100CharBuffer, " %d %d %4.2f %4.2f %4.2f",
    ThermostatData.GetHeatOn(), sThermoTimesCount, ThermostatData.GetCurrentDegF(),
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
    sThermoTimesCount= 0;
  } //if(bTurnOn)
  else{
    String szLogString= "ThermostatClass::TurnHeatOn(): OFF";
    LogToSerial(szLogString);
    ThermostatData.SetHeatOn(false);
    SetHeatSwitch(sSwitchOpen);
    sThermoTimesCount= 0;
  } //if(bTurnOn)else
  return;
} //TurnHeatOn


/*void ThermostatClass::SetSetpoint(float fNewSetpoint){
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
*/
//Last line.
