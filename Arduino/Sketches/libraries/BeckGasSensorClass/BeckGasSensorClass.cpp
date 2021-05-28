const char szSystemFileName[]  = "BeckGasSensorClass.cpp";
const char szSystemFileDate[]  = "5/27/21a";

#include <BeckGasSensorClass.h>
#include <BeckGasSensorDataClass.h>
#include <Adafruit_CCS811.h>
#include <Streaming.h>
#include <Wire.h>

Adafruit_CCS811     CCS811_GasSensor;
GasSensorClass      GasSensor;       //This is so every module can use the same object

GasSensorClass::GasSensorClass() {
  Serial << "GasSensorClass::GasSensorClass(): " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor


GasSensorClass::~GasSensorClass() {
  Serial << "~GasSensorClass(): Destructing" << endl;
} //destructor


void GasSensorClass::Setup(void){
  Serial << "GasSensorClass::setup(): Begin" << endl;
  if (!CCS811_GasSensor.begin()){
	  Serial << "GasSensorClass::setup(): Failed to start sensor, please check the wiring." << endl;
	  while(1);
  } //if(!GasSensor.begin())

  // Wait for CCS811_GasSensor.available()
  Serial << "GasSensorClass::setup(): Wait for CCS811_GasSensor.available()" << endl;
  while(!CCS811_GasSensor.available());
  Serial << "GasSensorClass::setup(): Return" << endl;
return;
} //Setup


void GasSensorClass::Handle(){
  if (CCS811_GasSensor.available()){
    if (!CCS811_GasSensor.readData()){
      CO2_Value= CCS811_GasSensor.geteCO2();
      VOC_Value= CCS811_GasSensor.getTVOC();
      GasSensorData.SetCO2_Value(CO2_Value);
      GasSensorData.SetVOC_Value(VOC_Value);

      if(false || (millis() >= ulNextPrintMsec)){
        ulNextPrintMsec= millis() + ulPrintPeriodMsec;
        Serial << "GasSensorClass::Handle(): CO2= " << CO2_Value << "ppm, VOC= " << VOC_Value << endl;
      }	//if(millis()>=ulNextPrintMsec)
    } //if(!CCS811_GasSensor.readData())
    else{
      Serial.println("ERROR!");
      Serial << "GasSensorClass::Handle(): CCS811_GasSensor.readData() returned error" << endl;
      while(1);
    } //if(!CCS811_GasSensor.readData())else
  } //if(CCS811_GasSensor.available())
  return;
} //Handle
/*
bool GasSensorClass::bCO2Changed(void){
  bool  bChanged= false;
  if (LastCO2_Value != CO2_Value){
    bChanged= true;
    LastCO2_Value= CO2_Value;
  }
  return bChanged;
} //bCO2Changed


bool GasSensorClass::bVOCChanged(void){
  bool  bChanged= false;
  if (LastVOC_Value != VOC_Value){
    bChanged= true;
    LastVOC_Value= VOC_Value;
  }
  return bChanged;
} //bVOCChanged
*/
//Last line.
