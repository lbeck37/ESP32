const char szBeckTireTempDataClassFileName[]  = "BeckProbeDataClass.cpp";
const char szBeckTireTempDataClassFileDate[]  = "3/4/22c";

#include <BeckProbeDataClass.h>
#include <Streaming.h>

#include <ctime>
#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

//Define a "rational real-time constant" representing 1/60 of a second (just for testing compiler)
using r1= ratio<1, 60>;

//More testing
duration    <long long, milli>  d2;
duration    <long, ratio<60>>   d1 {123};
time_point  <steady_clock>      oSteadyClock;   //time_pont never decreases
time_point  <system_clock>      oSystemClock;   //Wall clock time

BeckProbeDataClass ProbeReadingData;

BeckProbeDataClass::BeckProbeDataClass() {
  Serial << "BeckProbeDataClass(): Constructor"<< "\n";
} //constructor

BeckProbeDataClass::BeckProbeDataClass(ProbePosition ePosition){
  Serial << "BeckProbeDataClass(ProbePosition): Constructor, ePosition= " << (int)ePosition << "\n";
  _ePosition= ePosition;
  return;
} //constructor


BeckProbeDataClass::~BeckProbeDataClass() {
  Serial << "~BeckProbeDataClass(): Destructor" << "\n";
} //destructor

void BeckProbeDataClass::SetProbePosition(ProbePosition ePosition){
  _ePosition= ePosition;
  return;
} //SetProbePosition


ProbePosition BeckProbeDataClass::eGetPosition(void){
  return _ePosition;
} //eGetPosition


uint32_t BeckProbeDataClass::uwGetSampleTime(void){
  return _uwSampleTime;
} //uwGetSampleTime


void BeckProbeDataClass::SetSampleTime(uint32_t uwSampleTime){
  _uwSampleTime= uwSampleTime;
  return;
} //SetSampleTime


void BeckProbeDataClass::SetDegF_Value(int16_t NewDegFValue){
  _wDegF_Value= NewDegFValue;
  return;
}

int16_t BeckProbeDataClass::wGetDegF_Value(){
  return _wDegF_Value;
}

bool BeckProbeDataClass::bDegFChanged(void){
  bool  bChanged= false;
  if ((wGetLastDegF_Value() != wGetDegF_Value()) || _bDegF_FirstTime){
    bChanged       = true;
    _bDegF_FirstTime = false;
  }
  return bChanged;
} //bDegFChanged

void BeckProbeDataClass::SetLastDegF_Value(int16_t wLastDegFValue){
  _wLastDegF_Value= wLastDegFValue;
  return;
}

int16_t BeckProbeDataClass::wGetLastDegF_Value(){
  return _wLastDegF_Value;
}
//Last line.
