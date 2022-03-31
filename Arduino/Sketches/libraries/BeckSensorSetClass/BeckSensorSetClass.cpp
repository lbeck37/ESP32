const char szSystemFileName[]  = "BeckSensorSetClass.cpp";
const char szSystemFileDate[]  = "3/31/22a";

#include <BeckE32_Defines.h>
#include <BeckSensorSetClass.h>
#include <BeckCarSetClass.h>
#include <BeckDataMgrClass.h>
#include <BeckSensorClass.h>
#include <Streaming.h>

BeckSensorSetClass::BeckSensorSetClass() {
  Serial << "BeckSensorSetClass(): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
  return;
} //constructor


  BeckSensorSetClass::BeckSensorSetClass(BeckDisplayClass* poDisplay, BeckDataMgrClass* poDataMgr, int wSensorSetID){
  _wSensorSetID= wSensorSetID;
  _poDataMgr= poDataMgr;
  _poDisplay= poDisplay;
  BuildSensors();
  return;
} //constructor


BeckSensorSetClass::~BeckSensorSetClass() {
  Serial << "~BeckSensorSetClass(): Destructor, deleting probes" << endl;
  for (int wSensorID= 1; wSensorID <= _wNumSensors; wSensorID++){
    Serial << "~BeckSensorSetClass(): Destructor, call delete _apoSensor[" << wSensorID << "]" << endl;
    delete _apoSensor[wSensorID];
    _apoSensor[wSensorID]= nullptr;
  }   //for
  return;
} //destructor


void BeckSensorSetClass::BuildSensors(){
  for (int wSensorID= 0; wSensorID <= _wNumSensors; wSensorID++){
    _apoSensor[wSensorID]= new BeckSensorClass(wSensorID, _awI2CAdresses[wSensorID]);
   }
  return;
} //BuildSensors


bool BeckSensorSetClass::bBegin(){
  bool bOK= true;
  // Call bBegin() for each TC probe
  for (int wSensorID= 1; wSensorID <= _wNumSensors; wSensorID++){
    if (_apoSensor[wSensorID]->bBegin() != true) {
      Serial << "BeckSensorSetClass::bBegin(): Failed bBegin() for wSensorID= " << wSensorID << endl;
      bOK= false;
    } //if
  } //for
  return bOK;
} //bBegin


void BeckSensorSetClass::ReadSensorSet(uint32_t uwSampleTime) {
  float fDegF= 0.0;
  //Serial << "ReadSensorSet(): Read each sensor and save to _apoCarSamples[][]" << endl;
  //Read the DegF at each sensor and write that value and the time (passed in) to the data array.
  for (int wSensorID= 1; wSensorID <= _wNumSensors; wSensorID++){
    fDegF= _apoSensor[wSensorID]->fReadSensor();

    if (_poDataMgr != nullptr) {
      //Serial << "ReadSensorSet(): Use _poDataMgr->SetDegF and ->uwSampleTime" << endl;
      _poDataMgr->SetDegF           (_wSensorSetID, wSensorID, fDegF);
      _poDataMgr->SetReadingTime    (_wSensorSetID, wSensorID, uwSampleTime);
    } //if(_poDataMgr!=nullptr)
    else{
      Serial << "ReadSensorSet(): _poDataMgr is NULL, skip calls to SetDegF and uwSampleTime" << endl;
    }
  } //for
  return;
} //ReadSensorSet


void BeckSensorSetClass::DisplaySensorSet(int wSensorSetID) {
/*
 if (_poDataMgr != nullptr) {
    float   fDegF1= _poDataMgr->fGetDegF(_wSensorSetID, 1);
    float   fDegF2= _poDataMgr->fGetDegF(_wSensorSetID, 2);
    float   fDegF3= _poDataMgr->fGetDegF(_wSensorSetID, 3);
    Serial << "PrintSensorSetData()Using BeckDataMgrClass  : Thermo #1= " << fDegF1  << "F, #2= " << fDegF2  << "F, #3=" << fDegF3  << endl;
  } //if(_poDataMgr!=nullptr)
  else{
    Serial << "PrintSensorSetData(): _poDataMgr is NULL, skip calls to fGetDegF" << endl;
  }
*/
  _poDisplay->DisplaySensorSet(wSensorSetID);
  return;
} //DisplaySensorSet


void BeckSensorSetClass::PrintSensorSetData() {
 if (_poDataMgr != nullptr) {
    float   fDegF1= _poDataMgr->fGetDegF(_wSensorSetID, 1);
    float   fDegF2= _poDataMgr->fGetDegF(_wSensorSetID, 2);
    float   fDegF3= _poDataMgr->fGetDegF(_wSensorSetID, 3);
    Serial << "PrintSensorSetData()Using BeckDataMgrClass  : Thermo #1= " << fDegF1  << "F, #2= " << fDegF2  << "F, #3=" << fDegF3  << endl;
  } //if(_poDataMgr!=nullptr)
  else{
    Serial << "PrintSensorSetData(): _poDataMgr is NULL, skip calls to fGetDegF" << endl;
  }
  return;
} //PrintSensorSetData
//Last line.
