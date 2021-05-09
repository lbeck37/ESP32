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


void GasSensorDataClass::SetCO2_Value(uint16_t NewCO2Value){
	CO2_Value= NewCO2Value;
  return;
}

uint16_t GasSensorDataClass::GetCO2_Value(){
  return CO2_Value;
}


void GasSensorDataClass::SetTVOC_Value(uint16_t NewTVOCValue){
	TVOC_Value= NewTVOCValue;
  return;
}

uint16_t GasSensorDataClass::GetTVOC_Value(){
  return TVOC_Value;
}
//Last line.
