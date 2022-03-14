const char szBeckTireTempDataClassFileName[]  = "BeckSampleDataClass.cpp";
const char szBeckTireTempDataClassFileDate[]  = "3/13/22c";

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

BeckSampleDataClass::BeckSampleDataClass(int8_t cProbeID) {
  Serial << "BeckSampleDataClass(ProbePositionEnum, ProbeSetLocationEnum): Constructor"<< "\n";
  _cProbeID     = cProbeID;
  return;
} //constructor

BeckSampleDataClass::~BeckSampleDataClass() {
  Serial << "~BeckSampleDataClass(): Destructor" << "\n";
} //destructor

void BeckSampleDataClass::FillSampleData(SampleDataStruct& stSampleData) {
  SetSampleTime     (stSampleData.uwSampleTime);
  SetLastDegF_Value (fGetDegF_Value());
  SetDegF_Value     (stSampleData.fDegF);
  _bDegFChanged=    !(fGetLastDegF_Value() == fGetDegF_Value());
  _stSampleData     = stSampleData;
  return;
} //FillSampleData

void BeckSampleDataClass::SetSampleTime(uint32_t uwSampleTime){
  _uwSampleTime= uwSampleTime;
  return;
} //SetSampleTime


uint32_t BeckSampleDataClass::uwGetSampleTime(void){
  return _uwSampleTime;
} //ulGetSampleTime


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
