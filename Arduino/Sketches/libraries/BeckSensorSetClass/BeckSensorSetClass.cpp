const char szSystemFileName[]  = "BeckSensorSetClass.cpp";		//Copied from BeckSensorSetClass.cpp
const char szSystemFileDate[]  = "3/17/22h";

#include <BeckSensorClass.h>
#if DO_DATA
  #include <BeckSensorDataMgrClass.h>
#endif
#include <BeckSensorSetClass.h>
#include <BeckCarSetClass.h>
//#include <BeckSampleDataClass.h>
#include <BeckE32_Defines.h>
#include <Streaming.h>

//BeckSensorSetClass::BeckSensorSetClass() : _aucI2CAdresses{0, _ucI2CAddress1, _ucI2CAddress2, _ucI2CAddress3} {
//wSensorSetI //constructor

BeckSensorSetClass::BeckSensorSetClass(int wSensorSetID){
  Serial << "BeckSensorSetClass(cSensorSetID): CTR, wSensorSetID= " << wSensorSetID  << endl;
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
    Serial << "BeckSensorSetClass::BuildSensors(): _apoSensor[" << wSensorID << "]= new BeckSensorClass()" << endl;
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

#if DO_DATA
    Serial << "BeckSensorSetClass::ReadSensorSet(uwSampleTime): Call _oSensorDataMgr.SetDegF()"  << endl;
    _oSensorDataMgr.SetDegF       (_wSensorSetID, wSensorID, fDegF);
    _oSensorDataMgr.SetSampleTime (_wSensorSetID, wSensorID, uwSampleTime);
#endif
  } //for
  return;
} //ReadSensorSet


void BeckSensorSetClass::PrintSensorSetData() {
#if DO_DATA
  Serial << "BeckSensorSetClass::PrintSensorSetData(): Call _oSensorDataMgr.fGetDegF()"  << endl;
  float   fDegF1= _oSensorDataMgr.fGetDegF(_wSensorSetID, 1);
  float   fDegF2= _oSensorDataMgr.fGetDegF(_wSensorSetID, 2);
  float   fDegF3= _oSensorDataMgr.fGetDegF(_wSensorSetID, 3);

  Serial << "BeckSensorSetClass::PrintSensorSetData(): Thermo #1= " << fDegF1 << "F, #2= " << fDegF2 << "F, #3=" << fDegF3 << endl;
#endif
  return;
} //PrintSensorSetData
//Last line.
