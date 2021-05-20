const char szSystemFileName[]  = "BeckGasSensorClass.cpp";
const char szSystemFileDate[]  = "5/20/21b";

#include <BeckGasSensorClass.h>
#include <BeckGasSensorDataClass.h>
#include <Adafruit_CCS811.h>
#include <Streaming.h>

Adafruit_CCS811     CS811_GasSensor;
GasSensorClass      GasSensor;       //This is so every module can use the same object

GasSensorClass::GasSensorClass() {
  Serial << "GasSensorClass::GasSensorClass(): " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor


GasSensorClass::~GasSensorClass() {
  Serial << "~GasSensorClass(): Destructing" << endl;
} //destructor


//These versions of Setup() and Handle are for debugging w/o a CO2 sensor
void GasSensorClass::Setup(void){
  CO2_Value= 400;
  TVOC_Value= 0;
return;
} //Setup


void GasSensorClass::Handle(){
  if(true || (millis() >= ulNextPrintMsec)){
    ulNextPrintMsec= millis() + ulPrintPeriodMsec;
    CO2_Value++;
    TVOC_Value++;
    GasSensorData.SetCO2_Value(CO2_Value);
    GasSensorData.SetVOC_Value(TVOC_Value);
    Serial << "GasSensorClass::Handle(): CO2= " << CO2_Value << "ppm, TVOC= " << TVOC_Value << endl;
  } //if(millis()>=ulNextPrintMsec)
  return;
} //Handle

/*
void GasSensorClass::Setup(void){
  if (!CS811_GasSensor.begin()){
	  Serial << "GasSensorClass::setup(): Failed to start sensor, please check the wiring." << endl;
	  while(1);
  } //if(!GasSensor.begin())

  // Wait for the sensor to be ready
  while(!CS811_GasSensor.available());
return;
} //Setup


void GasSensorClass::Handle(){
  if (CS811_GasSensor.available()){
    if (!CS811_GasSensor.readData()){
      CO2_Value= CS811_GasSensor.geteCO2();
      TVOC_Value= CS811_GasSensor.getTVOC();

      //Are these calls needed?
      GasSensorData.SetCO2_Value(CO2_Value);
      GasSensorData.SetVOC_Value(TVOC_Value);

      if(true || (millis() >= ulNextPrintMsec)){
        ulNextPrintMsec= millis() + ulPrintPeriodMsec;
        Serial << "GasSensorClass::Handle(): CO2= " << CO2_Value << "ppm, TVOC= " << TVOC_Value << endl;
      }	//if(millis()>=ulNextPrintMsec)
    } //if(!CS811_GasSensor.readData())
    else{
      Serial.println("ERROR!");
      Serial << "GasSensorClass::Handle(): CS811_GasSensor.readData() returned error" << endl;
      while(1);
    } //if(!CS811_GasSensor.readData())else
  } //if(CS811_GasSensor.available())
  return;
} //Handle
*/
//Last line.
