const char szGasSensorDataClassFileName[]  = "BeckTireTempDataClass.cpp";
const char szGasSensorDataClassFileDate[]  = "2/21/22b";

#include <BeckTireTempDataClass.h>
#include <Streaming.h>

TireTempDataClass TireTempData;

TireTempDataClass::TireTempDataClass() {
} //constructor


TireTempDataClass::~TireTempDataClass() {
  Serial << "~SystemClass(): Destructing" << endl;
} //destructor


void TireTempDataClass::SetDegF_Value(float NewDegFValue){
  //Round NewDegFValue to (1) decimal place.
  //Display flashes if more decimal places than displayed are stored
  int     wNumDecPlaces= 1;
  float   fRoundedNewDegFValue;
  fRoundedNewDegFValue= ceil((NewDegFValue * pow(10, wNumDecPlaces)) - 0.49) / pow(10, wNumDecPlaces);
  DegF_Value= fRoundedNewDegFValue;
  return;
}

float TireTempDataClass::GetDegF_Value(){
  return DegF_Value;
}

bool TireTempDataClass::bDegFChanged(void){
  bool  bChanged= false;
  if ((GetLastDegF_Value() != GetDegF_Value()) || bDegFFirstTime){
    bChanged       = true;
    bDegFFirstTime = false;
  }
  return bChanged;
} //bDegFChanged

void TireTempDataClass::SetLastDegF_Value(float LastDegFValue){
  LastDegF_Value= LastDegFValue;
  return;
}

float TireTempDataClass::GetLastDegF_Value(){
  return LastDegF_Value;
}
//Last line.
