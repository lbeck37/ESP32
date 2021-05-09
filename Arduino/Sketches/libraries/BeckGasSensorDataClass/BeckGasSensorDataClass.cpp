const char szGasSensorDataClassFileName[]  = "BeckGasSensorDataClass.cpp";
const char szGasSensorDataClassFileDate[]  = "5/9/21a";

#include <BeckGasSensorDataClass.h>
#include <Streaming.h>

GasSensorDataClass GasSensorData;

GasSensorDataClass::GasSensorDataClass() {
} //constructor


GasSensorDataClass::~GasSensorDataClass() {
  Serial << "~SystemClass(): Destructing" << endl;
} //destructor


void GasSensorDataClass::Setup(){
  Serial << "GasSensorDataClass::Setup(): " <<
		  szGasSensorDataClassFileName << ", " << szGasSensorDataClassFileDate << endl;
  return;
} //Setup


void GasSensorDataClass::Handle(){
  return;
} //Handle

void GasSensorDataClass::SetCO2_Value(uint16_t NewCO2Value){
	CO2_Value= NewCO2Value;
  return;
}

uint16_t GasSensorDataClass::GetCO2_Value(){
  return CO2_Value;
}


void GasSensorDataClass::SetVOC_Value(uint16_t NewVOCValue){
	VOC_Value= NewVOCValue;
  return;
}

uint16_t GasSensorDataClass::GetVOC_Value(){
  return VOC_Value;
}


//Last line.
