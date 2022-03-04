const char szBeckTireTempDataClassFileName[]  = "BeckProbeReadingDataClass.cpp";
const char szBeckTireTempDataClassFileDate[]  = "3/4/22a";

#include <BeckProbeReadingDataClass.h>
#include <Streaming.h>

/*
#include <ctime>

import <iostream>;
import <chrono>;
import <iomanip>;

#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;
*/

BeckProbeReadingDataClass ProbeReadingData;

BeckProbeReadingDataClass::BeckProbeReadingDataClass() {
  Serial << "BeckProbeReadingDataClass(): Constructor"<< endl;
  //std::cout << "BeckProbeReadingDataClass(): Constructor"<< endl;
} //constructor

BeckProbeReadingDataClass::BeckProbeReadingDataClass(ProbePosition ePosition){
  Serial << "BeckProbeReadingDataClass(ProbePosition): Constructor, ePosition= " << (int)ePosition << endl;
  _ePosition= ePosition;
  return;
} //constructor


BeckProbeReadingDataClass::~BeckProbeReadingDataClass() {
  Serial << "~BeckProbeReadingDataClass(): Destructor" << endl;
} //destructor

ProbePosition BeckProbeReadingDataClass::eGetPosition(void){
  return _ePosition;
} //eGetPosition


void BeckProbeReadingDataClass::SetDegF_Value(int16_t NewDegFValue){
/*
  //Round NewDegFValue to (1) decimal place.
  //Display flashes if more decimal places than displayed are stored
  int     wNumDecPlaces= 1;
  float   fRoundedNewDegFValue;
  fRoundedNewDegFValue= ceil((NewDegFValue * pow(10, wNumDecPlaces)) - 0.49) / pow(10, wNumDecPlaces);
  DegF_Value= fRoundedNewDegFValue;
*/
  //Testing chrono, Sloeber fails, AIDE doesn't?
  //chrono::duration<long long, milli> d2;
  //duration<long long, milli> d2;
  //duration<long, ratio(60)>> d1 {123};
  return;
}

int16_t BeckProbeReadingDataClass::wGetDegF_Value(){
  return _wDegF_Value;
}

bool BeckProbeReadingDataClass::bDegFChanged(void){
  bool  bChanged= false;
  if ((wGetLastDegF_Value() != wGetDegF_Value()) || _bDegF_FirstTime){
    bChanged       = true;
    _bDegF_FirstTime = false;
  }
  return bChanged;
} //bDegFChanged

void BeckProbeReadingDataClass::SetLastDegF_Value(int16_t wLastDegFValue){
  _wLastDegF_Value= wLastDegFValue;
  return;
}

int16_t BeckProbeReadingDataClass::wGetLastDegF_Value(){
  return _wLastDegF_Value;
}
//Last line.
