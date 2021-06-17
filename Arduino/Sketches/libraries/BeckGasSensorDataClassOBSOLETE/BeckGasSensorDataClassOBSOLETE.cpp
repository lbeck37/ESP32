const char szGasSensorDataClassFileName[]  = "BeckGasSensorDataClass.cpp";
const char szGasSensorDataClassFileDate[]  = "5/27/21a";

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


void GasSensorDataClass::SetVOC_Value(uint16_t NewVOCValue){
	VOC_Value= NewVOCValue;
  return;
}

uint16_t GasSensorDataClass::GetVOC_Value(){
  return VOC_Value;
}


bool GasSensorDataClass::bCO2Changed(void){
  bool  bChanged= false;
  if (bCO2FirstTime || (LastCO2_Value != CO2_Value)){
    bChanged      = true;
    bCO2FirstTime = false;
    LastCO2_Value = CO2_Value;
  }
  return bChanged;
} //bCO2Changed


bool GasSensorDataClass::bVOCChanged(void){
  bool  bChanged= false;
  if (bVOCFirstTime || (LastVOC_Value != VOC_Value)){
    bChanged      = true;
    bVOCFirstTime = false;
    LastVOC_Value = VOC_Value;
  }
  return bChanged;
} //bVOCChanged
//Last line.
