const char szBeckTireTempDataClassFileName[]  = "BeckTireTempDataClass.cpp";
const char szBeckTireTempDataClassFileDate[]  = "2/27/22b";

#include <BeckTireTempDataClass.h>
#include <Streaming.h>

BeckTireTempDataClass TireTempData;

BeckTireTempDataClass::BeckTireTempDataClass() {
} //constructor


BeckTireTempDataClass::~BeckTireTempDataClass() {
  Serial << "~SystemClass(): Destructing" << endl;
} //destructor


void BeckTireTempDataClass::SetDegF_Value(float NewDegFValue){
  //Round NewDegFValue to (1) decimal place.
  //Display flashes if more decimal places than displayed are stored
  int     wNumDecPlaces= 1;
  float   fRoundedNewDegFValue;
  fRoundedNewDegFValue= ceil((NewDegFValue * pow(10, wNumDecPlaces)) - 0.49) / pow(10, wNumDecPlaces);
  DegF_Value= fRoundedNewDegFValue;
  return;
}

float BeckTireTempDataClass::GetDegF_Value(){
  return DegF_Value;
}

bool BeckTireTempDataClass::bDegFChanged(void){
  bool  bChanged= false;
  if ((GetLastDegF_Value() != GetDegF_Value()) || bDegFFirstTime){
    bChanged       = true;
    bDegFFirstTime = false;
  }
  return bChanged;
} //bDegFChanged

void BeckTireTempDataClass::SetLastDegF_Value(float LastDegFValue){
  LastDegF_Value= LastDegFValue;
  return;
}

float BeckTireTempDataClass::GetLastDegF_Value(){
  return LastDegF_Value;
}
//Last line.
