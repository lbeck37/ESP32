const char szGasSensorDataClassFileName[]  = "BeckEnviroDataClass.cpp";
const char szGasSensorDataClassFileDate[]  = "5/31/21d";

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


bool EnviroDataClass::bCO2Changed(void){
  bool  bChanged= false;
  if (bCO2FirstTime || (LastCO2_Value != CO2_Value)){
    bChanged      = true;
    bCO2FirstTime = false;
    LastCO2_Value = CO2_Value;
  }
  return bChanged;
} //bCO2Changed


void EnviroDataClass::SetVOC_Value(uint16_t NewVOCValue){
	VOC_Value= NewVOCValue;
  return;
}


uint16_t EnviroDataClass::GetVOC_Value(){
  return VOC_Value;
}


bool EnviroDataClass::bVOCChanged(void){
  bool  bChanged= false;
  if (bVOCFirstTime || (LastVOC_Value != VOC_Value)){
    bChanged      = true;
    bVOCFirstTime = false;
    LastVOC_Value = VOC_Value;
  }
  return bChanged;
} //bVOCChanged


void EnviroDataClass::SetDegF_Value(float NewDegFValue){
  DegF_Value= NewDegFValue;
  return;
}


float EnviroDataClass::GetDegF_Value(){
  return DegF_Value;
}


bool EnviroDataClass::bDegFChanged(void){
  bool  bChanged= false;
  if (bDegFFirstTime || (LastDegF_Value != DegF_Value)){
    bChanged       = true;
    bDegFFirstTime = false;
    LastDegF_Value = DegF_Value;
  }
  return bChanged;
} //bDegFChanged


void EnviroDataClass::SetRH_Value(uint16_t NewRHValue){
  RH_Value= NewRHValue;
  return;
}


uint16_t EnviroDataClass::GetRH_Value(){
  return RH_Value;
}


bool EnviroDataClass::bRHChanged(void){
  bool  bChanged= false;
  if (bRHFirstTime || (LastRH_Value != RH_Value)){
    bChanged     = true;
    bRHFirstTime = false;
    LastRH_Value = RH_Value;
  }
  return bChanged;
} //bRHChanged
//Last line.
