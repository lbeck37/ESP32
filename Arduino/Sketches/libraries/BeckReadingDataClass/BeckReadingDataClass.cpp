static const char szSystemFileName[]  = "BeckReadingDataClass.cpp";
static const char szSystemFileDate[]  = "3/17/22b3";

#include <BeckReadingDataClass.h>
#include <BeckE32_Defines.h>
#include <Streaming.h>

/*
#include <ctime>
#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;
*/

//BeckSampleDataClass     CarSampleSetData;
//SampleDataStruct        _astSampleData[_wNumSensorSets + 1] [_wNumSensors + 1];

/*
BeckReadingDataClass::BeckReadingDataClass() {
  Serial << "BeckReadingDataClass(): Default CTR"<< "\n";
} //constructor

BeckReadingDataClass::BeckReadingDataClass(int wSensorSetID, int wSensorID) {
  Serial << "BeckReadingDataClass(wSensorSetID, wSensorID): CTR"<< "\n";
  _wSensorSetID  = wSensorSetID;
  _wSensorID     = wSensorID;
  return;
} //constructor

BeckReadingDataClass::~BeckReadingDataClass() {
  Serial << "~BeckReadingDataClass(): Destructor" << "\n";
} //destructor


void BeckReadingDataClass::SetReadingTime(int wSensorSetID, int wSensorID, uint32_t uwSampleTime){
  _uwSampleTime= uwSampleTime;
  return;
} //SetSampleTime


uint32_t BeckSampleDataClass::uwGetSampleTime(int wSensorSetID, int wSensorID){
  return _uwSampleTime;
} //ulGetSampleTime


void BeckSampleDataClass::SetDegF(int wSensorSetID, int wSensorID, float fNewDegFValue){
  SetLastDegF(wSensorSetID, wSensorID, _fDegF);
  _fDegF= fNewDegFValue;
  return;
}	//SetDegF

float BeckSampleDataClass::fGetDegF(int wSensorSetID, int wSensorID){
  return _fDegF;
}	//wGetDegF

void BeckSampleDataClass::SetDegFChanged(int wSensorSetID, int wSensorID){
  bool  bChanged= false;
  if ((fGetLastDegF(wSensorSetID, wSensorID) != fGetDegF(wSensorSetID, wSensorID)) || _bDegF_FirstTime){
    _bDegFChanged     = true;
    _bDegF_FirstTime  = false;
  }
  return;
} //bDegFChanged

bool BeckSampleDataClass::bGetDegFChanged(int wSensorSetID, int wSensorID){
  bool  bChanged= false;
  if ((fGetLastDegF(wSensorSetID, wSensorID) != fGetDegF(wSensorSetID, wSensorID)) || _bDegF_FirstTime){
    bChanged         = true;
    _bDegF_FirstTime = false;
  }
  return bChanged;
} //bDegFChanged

void BeckSampleDataClass::SetLastDegF(int wSensorSetID, int wSensorID, float fLastDegFValue){
  _fLastDegF= fLastDegFValue;
  return;
}

float BeckSampleDataClass::fGetLastDegF(int wSensorSetID, int wSensorID){
  return _fLastDegF;
}
*/

BeckReadingDataClass::BeckReadingDataClass() {
  Serial << "BeckReadingDataClass(): Default CTR"<< "\n";
} //constructor

BeckReadingDataClass::BeckReadingDataClass(int wSensorSetID, int wSensorID) {
  Serial << "BeckReadingDataClass(wSensorSetID, wSensorID): CTR"<< "\n";

  _wSensorSetID  = wSensorSetID;
  _wSensorID     = wSensorID;

  return;
} //constructor

BeckReadingDataClass::~BeckReadingDataClass() {
  Serial << "~BeckReadingDataClass(): Destructor" << "\n";
} //destructor


void BeckReadingDataClass::SetReadingTime(uint32_t uwReadingTime){
  _uwReadingTime= uwReadingTime;
  return;
} //SetReadingTime


uint32_t BeckReadingDataClass::uwGetReadingTime(){
  return _uwReadingTime;
} //ulGetReadingTime


void BeckReadingDataClass::SetDegF(float fNewDegFValue){
  SetLastDegF(_fDegF);
  _fDegF= fNewDegFValue;
  return;
} //SetDegF

float BeckReadingDataClass::fGetDegF(){
  return _fDegF;
} //wGetDegF

void BeckReadingDataClass::SetDegFChanged(){
  bool  bChanged= false;
  if ((fGetLastDegF() != fGetDegF()) || _bDegF_FirstTime){
    _bDegFChanged     = true;
    _bDegF_FirstTime  = false;
  }
  return;
} //bDegFChanged

bool BeckReadingDataClass::bGetDegFChanged(){
  bool  bChanged= false;
  if ((fGetLastDegF() != fGetDegF()) || _bDegF_FirstTime){
    bChanged         = true;
    _bDegF_FirstTime = false;
  }
  return bChanged;
} //bDegFChanged

void BeckReadingDataClass::SetLastDegF(float fLastDegFValue){
  _fLastDegF= fLastDegFValue;
  return;
}

float BeckReadingDataClass::fGetLastDegF(){
  return _fLastDegF;
}
//Last line.
