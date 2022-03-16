static const char szSystemFileName[]  = "BeckSampleDataClass.cpp";
static const char szSystemFileDate[]  = "3/15/22a";

#include <BeckSampleDataClass.h>
#include <BeckE32_Defines.h>
#include <Streaming.h>

#include <ctime>
#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

//BeckSampleDataClass     CarSampleSetData;
//SampleDataStruct        _astSampleData[_wNumProbeSets + 1] [_wNumProbes + 1];

BeckSampleDataClass::BeckSampleDataClass() {
  Serial << "BeckSampleDataClass(): Default CTR"<< "\n";
} //constructor

BeckSampleDataClass::BeckSampleDataClass(int wProbeSetID, int wProbeID) {
  //Serial << "BeckSampleDataClass(ProbePositionEnum, ProbeSetLocationEnum): CTR"<< "\n";
  _wProbeSetID  = wProbeSetID;
  _wProbeID     = wProbeID;
  return;
} //constructor

BeckSampleDataClass::~BeckSampleDataClass() {
  Serial << "~BeckSampleDataClass(): Destructor" << "\n";
} //destructor


void BeckSampleDataClass::SetSampleTime(int wProbeSetID, int wProbeID, uint32_t uwSampleTime){
  _uwSampleTime= uwSampleTime;
  return;
} //SetSampleTime


uint32_t BeckSampleDataClass::uwGetSampleTime(int wProbeSetID, int wProbeID){
  return _uwSampleTime;
} //ulGetSampleTime


void BeckSampleDataClass::SetDegF(int wProbeSetID, int wProbeID, float fNewDegFValue){
  _fDegF= fNewDegFValue;
  return;
}	//SetDegF

float BeckSampleDataClass::fGetDegF(int wProbeSetID, int wProbeID){
  return _fDegF;
}	//wGetDegF

void BeckSampleDataClass::SetDegFChanged(int wProbeSetID, int wProbeID){
  bool  bChanged= false;
  if ((fGetLastDegF(wProbeSetID, wProbeID) != fGetDegF(wProbeSetID, wProbeID)) || _bDegF_FirstTime){
    _bDegFChanged     = true;
    _bDegF_FirstTime  = false;
  }
  return;
} //bDegFChanged

bool BeckSampleDataClass::bGetDegFChanged(int wProbeSetID, int wProbeID){
  bool  bChanged= false;
  if ((fGetLastDegF(wProbeSetID, wProbeID) != fGetDegF(wProbeSetID, wProbeID)) || _bDegF_FirstTime){
    bChanged         = true;
    _bDegF_FirstTime = false;
  }
  return bChanged;
} //bDegFChanged

void BeckSampleDataClass::SetLastDegF(int wProbeSetID, int wProbeID, float fLastDegFValue){
  _fLastDegF= fLastDegFValue;
  return;
}

float BeckSampleDataClass::fGetLastDegF(int wProbeSetID, int wProbeID){
  return _fLastDegF;
}
//Last line.
