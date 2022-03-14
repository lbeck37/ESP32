const char szBeckTireTempDataClassFileName[]  = "BeckSampleDataClass.cpp";
const char szBeckTireTempDataClassFileDate[]  = "3/14/22a";

#include <BeckSampleDataClass.h>
#include <BeckE32_Defines.h>
#include <Streaming.h>

#include <ctime>
#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

BeckSampleDataClass     ProbeReadingData;
SampleDataStruct        _astSampleData[_wNumProbes + 1];

BeckSampleDataClass::BeckSampleDataClass() {
  //Serial << "BeckSampleDataClass(): CTR"<< "\n";
} //constructor

BeckSampleDataClass::BeckSampleDataClass(int8_t cProbeID) {
  //Serial << "BeckSampleDataClass(ProbePositionEnum, ProbeSetLocationEnum): CTR"<< "\n";
  _cProbeID     = cProbeID;
  return;
} //constructor

BeckSampleDataClass::~BeckSampleDataClass() {
  Serial << "~BeckSampleDataClass(): Destructor" << "\n";
} //destructor

/*
void BeckSampleDataClass::FillSampleData(SampleDataStruct& stSampleData) {
  SetSampleTime     (stSampleData.uwSampleTime);
  SetLastDegF       (fGetDegF());
  SetDegF           (stSampleData.fDegF);
  _bDegFChanged=    !(fGetLastDegF() == fGetDegF());
  _stSampleData     = stSampleData;
  return;
} //FillSampleData
*/

void BeckSampleDataClass::SetSampleTime(uint32_t uwSampleTime){
  _uwSampleTime= uwSampleTime;
  return;
} //SetSampleTime


uint32_t BeckSampleDataClass::uwGetSampleTime(void){
  return _uwSampleTime;
} //ulGetSampleTime


void BeckSampleDataClass::SetDegF(float fNewDegFValue){
  _fDegF= fNewDegFValue;
  return;
}	//SetDegF

float BeckSampleDataClass::fGetDegF(){
  return _fDegF;
}	//wGetDegF

bool BeckSampleDataClass::bDegFChanged(void){
  bool  bChanged= false;
  if ((fGetLastDegF() != fGetDegF()) || _bDegF_FirstTime){
    bChanged         = true;
    _bDegF_FirstTime = false;
  }
  return bChanged;
} //bDegFChanged

void BeckSampleDataClass::SetLastDegF(float fLastDegFValue){
  _fLastDegF= fLastDegFValue;
  return;
}

float BeckSampleDataClass::fGetLastDegF(){
  return _fLastDegF;
}
//Last line.
