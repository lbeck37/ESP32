const char szSystemFileName[]  = "BeckGasSensorClass.cpp";
const char szSystemFileDate[]  = "5/21/21b";

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


#if false
void GasSensorClass::Setup(void){
  if (!CCS811_GasSensor.begin()){
	  Serial << "GasSensorClass::setup(): Failed to start sensor, please check the wiring." << endl;
	  while(1);
  } //if(!GasSensor.begin())

  // Wait for the sensor to be ready
  while(!CCS811_GasSensor.available());
return;
} //Setup

void GasSensorClass::Handle(){
  if (CCS811_GasSensor.available()){
    if (!CCS811_GasSensor.readData()){
      CO2_Value= CCS811_GasSensor.geteCO2();
      TVOC_Value= CCS811_GasSensor.getTVOC();
      GasSensorData.SetCO2_Value(CO2_Value);
      GasSensorData.SetVOC_Value(TVOC_Value);

      if(false || (millis() >= ulNextPrintMsec)){
        ulNextPrintMsec= millis() + ulPrintPeriodMsec;
        Serial << "GasSensorClass::Handle(): CO2= " << CO2_Value << "ppm, TVOC= " << TVOC_Value << endl;
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
#else
//These versions of Setup() and Handle are for debugging w/o a CO2 sensor
void GasSensorClass::Setup(void){
  CO2_Value= 400;
  TVOC_Value= 0;
return;
} //Setup

void GasSensorClass::Handle(){
  if(false || (millis() >= ulNextPrintMsec)){
    ulNextPrintMsec= millis() + ulPrintPeriodMsec;
    CO2_Value++;
    TVOC_Value++;
    GasSensorData.SetCO2_Value(CO2_Value);
    GasSensorData.SetVOC_Value(TVOC_Value);
    Serial << "GasSensorClass::Handle(): CO2= " << CO2_Value << "ppm, TVOC= " << TVOC_Value << endl;
  } //if(millis()>=ulNextPrintMsec)
  return;
} //Handle
#endif
//Last line.
