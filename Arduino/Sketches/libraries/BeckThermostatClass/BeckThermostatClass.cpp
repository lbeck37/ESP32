const char szThermostatFileName[]  = "BeckThermostatClass.cpp";
const char szThermostatFileDate[]  = "4/25/21b";

#include <BeckThermostatClass.h>
#include <BeckLogLib.h>
#include <BeckPinNumbers.h>
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
  ReadCurrentDegF();
  float fCurrentDegF      = ThermostatData.GetCurrentTemperature();
  float fSetpoint         = ThermostatData.GetSetpoint();
  float fThermoOffDeg     = ThermostatData.GetThermostatOffDeg();
  bool  bThermostatIsOn   = ThermostatData.GetThermostatOn();
  bool  bHeatIsOn         = ThermostatData.GetHeatOn();

  //If Thermostat is OFF, make sure the heat switch is OFF, and then return.
  if (!bThermostatIsOn){
    ThermostatData.SetHeatOn(false);
    return;
  } //if(!bThermostatIsOn)

  //If the heat is OFF and the temperature is BELOW the set-point, turn the heat ON
  //if (!bHeatIsOn && (fCurrentDegF < fSetpoint)){
  //If the temperature is BELOW the setpoint, turn the heat ON.
  if (fCurrentDegF < fSetpoint){
    ThermostatData.SetHeatOn(true);
  }

  //If the heat is ON and the temperature is ABOVE the off-point, then turn the heat OFF
  //if (bHeatIsOn && (fCurrentDegF > fThermoOffDeg)){
  //If the temperature is ABOVE the off-point, then turn the heat OFF
  if (fCurrentDegF > fThermoOffDeg){
      ThermostatData.SetHeatOn(false);
  }

  if(millis() >= ulNextPrintMsec){
    ulNextPrintMsec= millis() + ulPrintPeriodMsec;
    LogThermostatData(ThermostatData.GetCurrentTemperature());
  } //if(millis()>=ulNextPrintMsec)
  return;
} //Handle


float ThermostatClass::ReadCurrentDegF(){
  //This routine reads the Dallas One-wire temperature sensor
  //It sets this value into the ThermostatData object.
  //It returns the newly read value.
  float fCurrentDegF= ThermostatData.GetCurrentTemperature();

  if(millis() >= ulNextSensorReadMsec){
    ulNextSensorReadMsec= millis() + ulSensorReadPeriodMsec;

    //Read the Dallas One-wire temperature sensor
    BiotaTempSensor.requestTemperatures(); // Send the command to get temperatures
    fCurrentDegF= BiotaTempSensor.getTempFByIndex(0);

    ThermostatData.SetCurrentTemperature(fCurrentDegF);
  } //if(millis() >= ulNextSensorReadMsec)
  return fCurrentDegF;
} //ReadCurrentDegF


void ThermostatClass::LogThermostatData(float fCurrentDegF){
  static char    sz100CharBuffer[100];

  sprintf(sz100CharBuffer, "HeatOn= %d, DegF= %4.2f, Setpoint= %4.2f, ThermoOffDegF= %4.2f",
    ThermostatData.GetHeatOn(), ThermostatData.GetCurrentTemperature(),
    ThermostatData.GetSetpoint(), ThermostatData.GetThermostatOffDeg());
  LogToSerial(sz100CharBuffer);
  return;
} //LogThermostatData
//Last line.
