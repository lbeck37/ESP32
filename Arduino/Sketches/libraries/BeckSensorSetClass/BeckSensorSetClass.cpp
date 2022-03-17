const char szSystemFileName[]  = "BeckSensorSetClass.cpp";		//Copied from BeckSensorSetClass.cpp
const char szSystemFileDate[]  = "3/16/22f";

#include <BeckSensorClass.h>
#include <BeckSensorDataMgrClass.h>
#include <BeckSensorSetClass.h>
#include <BeckCarSetClass.h>
//#include <BeckSampleDataClass.h>
#include <BeckE32_Defines.h>
#include <Streaming.h>

//BeckSensorSetClass::BeckSensorSetClass() : _aucI2CAdresses{0, _ucI2CAddress1, _ucI2CAddress2, _ucI2CAddress3} {
BeckSensorSetClass::BeckSensorSetClass() {
  Serial << "BeckSensorSetClass(): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
  return;
} //constructor

BeckSensorSetClass::BeckSensorSetClass(int wSensorSetID){
  //Serial << "BeckSensorSetClass(cSensorSetID): CTR, _aucI2CAdresses{} filled with I2CAddresses" << endl;
  _wSensorSetID= wSensorSetID;
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
  //Read the DegF at each senson and write that value and the time (passed in) to the data array.
  for (int wSensorID= 1; wSensorID <= _wNumSensors; wSensorID++){
    fDegF= _apoSensor[wSensorID]->fReadSensor();

    _oSensorDataMgr.SetDegF       (_wSensorSetID, wSensorID, fDegF);
    _oSensorDataMgr.SetSampleTime (_wSensorSetID, wSensorID, uwSampleTime);
  } //for
  return;
} //ReadSensorSet


void BeckSensorSetClass::PrintSensorSetData() {
  float   fDegF1= _oSensorDataMgr.fGetDegF(_wSensorSetID, 1);
  float   fDegF2= _oSensorDataMgr.fGetDegF(_wSensorSetID, 2);
  float   fDegF3= _oSensorDataMgr.fGetDegF(_wSensorSetID, 3);

  Serial << "BeckSensorSetClass::PrintSensorSetData(): Thermo #1= " << fDegF1 << "F, #2= " << fDegF2 << "F, #3=" << fDegF3 << endl;
  return;
} //PrintSensorSetData
//Last line.
