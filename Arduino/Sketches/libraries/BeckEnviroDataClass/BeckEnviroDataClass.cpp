const char szGasSensorDataClassFileName[]  = "BeckEnviroDataClass.cpp";
const char szGasSensorDataClassFileDate[]  = "6/13/21b";

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
  //if (bCO2FirstTime || (LastCO2_Value != CO2_Value)){
  if ((GetLastCO2_Value() != GetCO2_Value()) || bCO2FirstTime){
    bChanged      = true;
    bCO2FirstTime = false;
    //LastCO2_Value = CO2_Value;
  }
  return bChanged;
} //bCO2Changed

void EnviroDataClass::SetLastCO2_Value(uint16_t LastCO2Value){
  LastCO2_Value= LastCO2Value;
  return;
}

uint16_t EnviroDataClass::GetLastCO2_Value(){
  return LastCO2_Value;
}

void EnviroDataClass::SetVOC_Value(uint16_t NewVOCValue){
	VOC_Value= NewVOCValue;
  return;
}

uint16_t EnviroDataClass::GetVOC_Value(){
  return VOC_Value;
}

bool EnviroDataClass::bVOCChanged(void){
  bool  bChanged= false;
  if ((GetLastVOC_Value() != GetVOC_Value()) || bVOCFirstTime){
    bChanged      = true;
    bVOCFirstTime = false;
    //LastVOC_Value = VOC_Value;
  }
  return bChanged;
} //bVOCChanged

void EnviroDataClass::SetLastVOC_Value(uint16_t LastVOCValue){
  LastVOC_Value= LastVOCValue;
  return;
}

uint16_t EnviroDataClass::GetLastVOC_Value(){
  return LastVOC_Value;
}


void EnviroDataClass::SetDegF_Value(float NewDegFValue){
  //Round NewDegFValue to (1) decimal place.
  //Display flashes if more decimal places than displayed are stored
  int     wNumDecPlaces= 1;
  float   fRoundedNewDegFValue;
  fRoundedNewDegFValue= ceil((NewDegFValue * pow(10, wNumDecPlaces)) - 0.49) / pow(10, wNumDecPlaces);
  DegF_Value= fRoundedNewDegFValue;
  return;
}

float EnviroDataClass::GetDegF_Value(){
  return DegF_Value;
}

bool EnviroDataClass::bDegFChanged(void){
  bool  bChanged= false;
  if ((GetLastDegF_Value() != GetDegF_Value()) || bDegFFirstTime){
    bChanged       = true;
    bDegFFirstTime = false;
    //LastDegF_Value = DegF_Value;
  }
  return bChanged;
} //bDegFChanged

void EnviroDataClass::SetLastDegF_Value(float LastDegFValue){
  LastDegF_Value= LastDegFValue;
  return;
}

float EnviroDataClass::GetLastDegF_Value(){
  return LastDegF_Value;
}


void EnviroDataClass::SetRH_Value(uint16_t NewRHValue){
  RH_Value= NewRHValue;
  return;
}

uint16_t EnviroDataClass::GetRH_Value(){
  return RH_Value;
}

bool EnviroDataClass::bRHChanged(void){
  bool  bChanged= false;
  if ((GetLastRH_Value() != GetRH_Value()) || bRHFirstTime){
    bChanged     = true;
    bRHFirstTime = false;
    //LastRH_Value = RH_Value;
  }
  return bChanged;
} //bRHChanged

void EnviroDataClass::SetLastRH_Value(uint16_t LastRHValue){
  LastRH_Value= LastRHValue;
  return;
}

uint16_t EnviroDataClass::GetLastRH_Value(){
  return LastRH_Value;
}
//Last line.
