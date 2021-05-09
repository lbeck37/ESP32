const char szSystemFileName[]  = "BeckGasSensorClass.cpp";
const char szSystemFileDate[]  = "5/9/21a";

#include <BeckGasSensorClass.h>
#include <BeckGasSensorDataClass.h>
#include <Adafruit_CCS811.h>
#include <Streaming.h>

Adafruit_CCS811 		CS811_GasSensor;
GasSensorClass          GasSensor;       //This is so every module can use the same object

GasSensorClass::GasSensorClass() {
  Serial << "GasSensorClass::GasSensorClass(): " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor


GasSensorClass::~GasSensorClass() {
  Serial << "~GasSensorClass(): Destructing" << endl;
} //destructor


void GasSensorClass::Setup(void){
  if (!CS811_GasSensor.begin()){
	Serial << "GasSensorClass::setup(): Failed to start sensor, please check the wiring." << endl;
	while(1);
  }	//if(!GasSensor.begin())

  // Wait for the sensor to be ready
  while(!CS811_GasSensor.available());
return;
} //Setup


void GasSensorClass::Handle(){
  if (CS811_GasSensor.available()){
	if (!CS811_GasSensor.readData()){
	  CO2_Value= CS811_GasSensor.geteCO2();
	  TVOC_Value= CS811_GasSensor.getTVOC();

	  GasSensorData.SetCO2_Value(CO2_Value);
	  GasSensorData.SetCO2_Value(CO2_Value);
	  Serial << "loop(): CO2= " << CO2_Value << "ppm, TVOC= " << TVOC_Value << endl;
	}	//if(!CS811_GasSensor.readData())
	else{
	  Serial.println("ERROR!");
	  Serial << "loop: readData() returned error" << endl;
	  while(1);
	}	//if(!CS811_GasSensor.readData())else
  }	//if(CS811_GasSensor.available())
  return;
} //Handle
//Last line.
