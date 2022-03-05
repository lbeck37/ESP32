const char szBeckTireTempDataClassFileName[]  = "BeckProbeDataClass.cpp";
const char szBeckTireTempDataClassFileDate[]  = "3/4/22b";

#include <BeckProbeDataClass.h>
#include <Streaming.h>

#include <ctime>
#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

/*
//Define a "rational real-time constant" representing 1/60 of a second (just for testing compiler)
using r1= ratio<1, 60>;

//More testing
duration    <long long, milli>  d2;
duration    <long, ratio<60>>   d1 {123};
time_point  <steady_clock>      oSteadyClock;   //time_pont never decreases
time_point  <system_clock>      oSystemClock;   //Wall clock time
*/

BeckProbeDataClass ProbeReadingData;

BeckProbeDataClass::BeckProbeDataClass() {
  Serial << "BeckProbeDataClass(): Constructor"<< "\n";
} //constructor

BeckProbeDataClass::BeckProbeDataClass(ProbePosition eProbePosition){
  Serial << "BeckProbeDataClass(ProbePosition): Constructor, eProbePosition= " << (int)eProbePosition << "\n";
  _eProbePosition= eProbePosition;
  return;
} //constructor


BeckProbeDataClass::~BeckProbeDataClass() {
  Serial << "~BeckProbeDataClass(): Destructor" << "\n";
} //destructor

void BeckProbeDataClass::SetProbePosition(ProbePosition eProbePosition){
  _eProbePosition= eProbePosition;
  return;
} //SetProbePosition


ProbePosition BeckProbeDataClass::eGetProbePosition(void){
  return _eProbePosition;
} //eGetProbePosition


uint32_t BeckProbeDataClass::uwGetSampleTime(void){
  return _uwSampleTime;
} //uwGetSampleTime


void BeckProbeDataClass::SetSampleTime(uint32_t uwSampleTime){
  _uwSampleTime= uwSampleTime;
  return;
} //SetSampleTime


void BeckProbeDataClass::SetDegF_Value(int16_t NewDegFValue){
/*
  //Round NewDegFValue to (1) decimal place.
  //Display flashes if more decimal places than displayed are stored
  int     wNumDecPlaces= 1;
  float   fRoundedNewDegFValue;
  fRoundedNewDegFValue= ceil((NewDegFValue * pow(10, wNumDecPlaces)) - 0.49) / pow(10, wNumDecPlaces);
  DegF_Value= fRoundedNewDegFValue;
*/
/*
  //Get current time (Pro C++ pg 801)
  system_clock::time_point  oCurentTime{system_clock::now()};

  //Convert to a time_t
  time_t  oCurrentTime_time_t{system_clock::to_time_t(oCurentTime)};

  //Convert to local time
  tm*   pLocalTime{localtime(&oCurrentTime_time_t)};

  //Print the current time
  cout << "SetDegF_Value(): Current time is " << put_time(pLocalTime, "%H:%M:&S") << "\n";
*/

  return;
}

int16_t BeckProbeDataClass::wGetDegF_Value(){
  return _wDegF_Value;
  //system_clock::time_point tpoint { system_clock::now() );
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
