static const char szSystemFileName[]  = "BeckReadingDataClass.cpp";
static const char szSystemFileDate[]  = "3/17/22b5";

#include <BeckReadingDataClass.h>
#include <BeckE32_Defines.h>
#include <Streaming.h>


BeckReadingDataClass::BeckReadingDataClass() {
  Serial << "BeckReadingDataClass(): Default CTR"<< "\n";
} //constructor

BeckReadingDataClass::BeckReadingDataClass(int wSensorSetID, int wSensorID) {
  //Serial << "BeckReadingDataClass(wSensorSetID, wSensorID): CTR"<< "\n";

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


void BeckReadingDataClass::SetDegF(float fDegF){
  SetLastDegF(_fDegF);
  _fDegF= fDegF;
  return;
} //SetDegF

float BeckReadingDataClass::fGetDegF(){
  //Serial << "\BeckReadingDataClass::fGetDegF(), _wSensorSetID=" << _wSensorID << ", wSensorID=" << _wSensorID << endl;
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
} //SetLastDegF

float BeckReadingDataClass::fGetLastDegF(){
  return _fLastDegF;
} //fGetLastDegF
//Last line.
