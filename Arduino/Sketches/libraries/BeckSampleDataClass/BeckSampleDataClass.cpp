const char szBeckTireTempDataClassFileName[]  = "BeckSampleDataClass.cpp";
const char szBeckTireTempDataClassFileDate[]  = "3/4/22f";

#include <BeckSampleDataClass.h>
#include <Streaming.h>

#include <ctime>
#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

BeckSampleDataClass ProbeReadingData;

BeckSampleDataClass::BeckSampleDataClass() {
  Serial << "BeckSampleDataClass(): Constructor"<< "\n";
} //constructor

BeckSampleDataClass::~BeckSampleDataClass() {
  Serial << "~BeckSampleDataClass(): Destructor" << "\n";
} //destructor

unsigned long BeckSampleDataClass::ulGetSampleTime(void){
  return _ulSampleTime;
} //ulGetSampleTime


void BeckSampleDataClass::SetSampleTime(unsigned long ulSampleTime){
  _ulSampleTime= ulSampleTime;
  return;
} //SetSampleTime


void BeckSampleDataClass::SetDegF_Value(int16_t NewDegFValue){
  _wDegF_Value= NewDegFValue;
  return;
}	//SetDegF_Value

int16_t BeckSampleDataClass::wGetDegF_Value(){
  return _wDegF_Value;
}	//wGetDegF_Value

bool BeckSampleDataClass::bDegFChanged(void){
  bool  bChanged= false;
  if ((wGetLastDegF_Value() != wGetDegF_Value()) || _bDegF_FirstTime){
    bChanged       = true;
    _bDegF_FirstTime = false;
  }
  return bChanged;
} //bDegFChanged

void BeckSampleDataClass::SetLastDegF_Value(int16_t wLastDegFValue){
  _wLastDegF_Value= wLastDegFValue;
  return;
}

int16_t BeckSampleDataClass::wGetLastDegF_Value(){
  return _wLastDegF_Value;
}
//Last line.
