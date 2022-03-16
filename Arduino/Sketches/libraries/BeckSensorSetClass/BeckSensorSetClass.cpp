const char szSystemFileName[]  = "BeckSensorSetClass.cpp";		//Copied from BeckSensorSetClass.cpp
const char szSystemFileDate[]  = "3/16/22c";

#include <BeckSensorClass.h>
#include <BeckSensorSetClass.h>
#include <BeckCarSetClass.h>
#include <BeckSampleDataClass.h>
#include <BeckE32_Defines.h>
#include <Streaming.h>

//BeckSensorSetClass::BeckSensorSetClass() : _aucI2CAdresses{0, _ucI2CAddress1, _ucI2CAddress2, _ucI2CAddress3} {
BeckSensorSetClass::BeckSensorSetClass() {
  Serial << "BeckSensorSetClass(): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
  return;
} //constructor

//    BeckSensorSetClass       (BeckSampleDataClass* apoCarSamples, int wSensorSetID);
//BeckSensorSetClass           (BeckSampleDataClass* apoCarSamples[_wNumSensorSets + 1][_wNumSensors + 1], int wSensorSetID);
//BeckSensorSetClass::BeckSensorSetClass(BeckSampleDataClass* apoCarSamples, int wSensorSetID){
BeckSensorSetClass::BeckSensorSetClass(BeckSampleDataClass* apoCarSamples[_wNumSensorSets + 1][_wNumSensors + 1], int wSensorSetID){
  //Serial << "BeckSensorSetClass(cSensorSetID): CTR, _aucI2CAdresses{} filled with I2CAddresses" << endl;
  //_apoCarSamples= apoCarSamples;
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


//void BeckSensorSetClass::ReadSensorSet(uint32_t uwSampleTime, int wSensorID) {
void BeckSensorSetClass::ReadSensorSet(uint32_t uwSampleTime) {
  //_uwSampleTime= uwSampleTime;
  //Have each Sensor handle itself, like read the tcouple
/*
  for (int wSensor= 1; cSensor <= _wNumSensors; cSensor++){
    _apoSensor[cSensor]->Handle(uwSampleTime);
   }
  Serial << "    Thermo #1= " << _apoSensor[1]->fGetDegF() << "F, #2= " << _apoSensor[2]->fGetDegF() << "F, #3=" << _apoSensor[3]->fGetDegF() << endl;
*/
  float fDegF= 0.0;
  for (int wSensorID= 1; wSensorID <= _wNumSensors; wSensorID++){
    //_apoSensor[wSensorID]->fReadSensor(uwSampleTime, wSensorID);
    fDegF= _apoSensor[wSensorID]->fReadSensor();
  } //for
  return;
} //ReadSensorSet


void BeckSensorSetClass::PrintSensorSetData(void) {
/*
  for (int wSensor= 1; cSensor <= _wNumSensors; cSensor++){
    //Serial << "BeckSensorSetClass::PrintSensorSetData(): Printing data for Sensor #" << cSensor << endl;
   }
*/
  //Serial << "    Thermo #1= " << _apoSensor[1]->fGetDegF() << "F, #2= " << _apoSensor[2]->fGetDegF() << "F, #3=" << _apoSensor[3]->fGetDegF() << endl;
/*
  float   fDegF1, fDegF2, fDeg3;
  float   fDeg1= fGetDegF(1, 1);

  Serial << "    Thermo #1= " << _astSampleData[1][1].fDegF << "F, #2= " << _astSampleData[1][2].fDegF << "F, #3=" << _astSampleData[1][3].fDegF << endl;
*/
  return;
} //PrintSensorSetData
//Last line.
