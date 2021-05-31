const char szGasSensorDataClassFileName[]  = "BeckEnviroDataClass.cpp";
const char szGasSensorDataClassFileDate[]  = "5/31/21a";

#include <BeckEnviroDataClass.h>
#include <Streaming.h>

EnviroDataClass EnviroData;

EnviroDataClass::EnviroDataClass() {
} //constructor


EnviroDataClass::~EnviroDataClass() {
  Serial << "~SystemClass(): Destructing" << endl;
} //destructor


void EnviroDataClass::SetCO2_Value(uint16_t NewCO2Value){
  CO2_Value= NewCO2Value;
  return;
}

uint16_t EnviroDataClass::GetCO2_Value(){
  return CO2_Value;
}


void EnviroDataClass::SetVOC_Value(uint16_t NewVOCValue){
	VOC_Value= NewVOCValue;
  return;
}

uint16_t EnviroDataClass::GetVOC_Value(){
  return VOC_Value;
}


bool EnviroDataClass::bCO2Changed(void){
  bool  bChanged= false;
  if (bCO2FirstTime || (LastCO2_Value != CO2_Value)){
    bChanged      = true;
    bCO2FirstTime = false;
    LastCO2_Value = CO2_Value;
  }
  return bChanged;
} //bCO2Changed


bool EnviroDataClass::bVOCChanged(void){
  bool  bChanged= false;
  if (bVOCFirstTime || (LastVOC_Value != VOC_Value)){
    bChanged      = true;
    bVOCFirstTime = false;
    LastVOC_Value = VOC_Value;
  }
  return bChanged;
} //bVOCChanged
//Last line.
