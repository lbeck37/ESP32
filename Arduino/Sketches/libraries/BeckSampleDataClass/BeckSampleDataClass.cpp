const char szBeckTireTempDataClassFileName[]  = "BeckSampleDataClass.cpp";
const char szBeckTireTempDataClassFileDate[]  = "3/6/22b";

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

BeckSampleDataClass::BeckSampleDataClass(ProbePositionEnum eProbePosition, ProbeSetLocationEnum eProbeSetLocation) {
  Serial << "BeckSampleDataClass(ProbePositionEnum, ProbeSetLocationEnum): Constructor"<< "\n";
  _eProbePosition     = eProbePosition;
  _eProbeSetLocation  = eProbeSetLocation;
  return;
} //constructor

BeckSampleDataClass::~BeckSampleDataClass() {
  Serial << "~BeckSampleDataClass(): Destructor" << "\n";
} //destructor

void BeckSampleDataClass::FillSampleData(uint32_t uwSampleTime, float fNewDegFValue) {
  SetSampleTime(uwSampleTime);
  SetDegF_Value(fNewDegFValue);
  SetLastDegF_Value(fNewDegFValue);
  _bDegFChanged= !(fGetLastDegF_Value() == fNewDegFValue);

  return;
}

uint32_t BeckSampleDataClass::uwGetSampleTime(void){
  return _uwSampleTime;
} //ulGetSampleTime


void BeckSampleDataClass::SetSampleTime(uint32_t uwSampleTime){
  _uwSampleTime= uwSampleTime;
  return;
} //SetSampleTime


void BeckSampleDataClass::SetDegF_Value(float fNewDegFValue){
  _fDegF_Value= fNewDegFValue;
  return;
}	//SetDegF_Value

float BeckSampleDataClass::fGetDegF_Value(){
  return _fDegF_Value;
}	//wGetDegF_Value

bool BeckSampleDataClass::bDegFChanged(void){
  bool  bChanged= false;
  if ((fGetLastDegF_Value() != fGetDegF_Value()) || _bDegF_FirstTime){
    bChanged       = true;
    _bDegF_FirstTime = false;
  }
  return bChanged;
} //bDegFChanged

void BeckSampleDataClass::SetLastDegF_Value(float fLastDegFValue){
  _fLastDegF_Value= fLastDegFValue;
  return;
}

float BeckSampleDataClass::fGetLastDegF_Value(){
  return _fLastDegF_Value;
}
//Last line.
