const char szSystemFileName[]  = "BeckCarSetClass.cpp";
const char szSystemFileDate[]  = "3/18/22d";

#include <BeckCarSetClass.h>
#include <BeckE32_Defines.h>
#include <BeckDataMgrClass.h>
#if USE_OLD_DATA_ARRAY
  #include <BeckSampleDataClass.h>
#endif
#include <BeckSensorClass.h>
#include <Streaming.h>

BeckCarSetClass::BeckCarSetClass()  {
  Serial << "BeckCarSetClass(): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;

  //Build the DataMgr and set _poDataMgr to that
  Serial << "BeckCarSetClass(): Default CTR, Do _poDataMgr= new BeckDataMgrClass()" << endl;
  _poDataMgr= new BeckDataMgrClass();

  if (_poDataMgr != nullptr) {
    Serial << "BeckCarSetClass(): Default CTR, _poDataMgr is NON_NULL" << endl;
    Serial << "BeckCarSetClass(): Default CTR, Call fDegf= _poDataMgr->fGetDegF(0,0)" << endl;
    float fDegF= _poDataMgr->fGetDegF(0,0);
    Serial << "BeckCarSetClass(): Default CTR, _poDataMgr->fGetDegF(0,0) returned fDegF=" << fDegF << endl;
  }
  else{
    Serial << "BeckCarSetClass(): Default CTR,new returned a NULL pointer for _poDataMgr" << endl;
  }

  Serial << "BeckCarSetClass(): Default CTR, Call BuildObjectData()" << endl;
  BuildObjectData();

  //Serial << "BeckCarSetClass(): Default CTR, Done" << endl;
  return;
} //constructor

BeckCarSetClass::~BeckCarSetClass() {
  Serial << "~BeckCarSetClass(): Destructor, Deleting probes" << endl;
  for (int wSensorSetID= 1; wSensorSetID <= _wNumSensorSets; wSensorSetID++){
    Serial << "~BeckCarSetClass(): Destructor, call delete _apoSensor[" << wSensorSetID << "]" << endl;
    delete _apoSensorSet[wSensorSetID];
    _apoSensorSet[wSensorSetID]= nullptr;
  }   //for
  return;
} //destructor


void BeckCarSetClass::BuildObjectData(){
//  Serial << "BeckCarSetClass::BuildObjectData(): Begin\n" <<

#if USE_OLD_DATA_ARRAY
  int w_apoCarSamplesCount= 1;
  int wTotalSensorSets = _wNumSensorSets + 1;
  int wTotalSensors    = _wNumSensors    + 1;
  int wGrandTotal     = (wTotalSensorSets * wTotalSensors);
  Serial << "BuildObjectData(): Build " << wTotalSensorSets << " X " << wTotalSensors << " = " << wGrandTotal << " _apoCarSamples[][]" << endl;
  Serial << "    ";
  for (int wSensorSetID= 0; wSensorSetID <= _wNumSensorSets; wSensorSetID++){
    for (int wSensorID= 0; wSensorID <= _wNumSensors; wSensorID++){
      Serial << "." << w_apoCarSamplesCount++;
      _apoCarSamples[wSensorSetID][wSensorID]= new BeckSampleDataClass(wSensorSetID, wSensorID);
    } //for(int wSensorID=0...
    Serial << ".*";
  } //for(int wSensorSetID=0...
  Serial << endl;
#endif
  Serial << "BuildObjectData(): Build " << (_wNumSensorSets + 1) << " _apoSensorSet[] objects using new" << endl;
  Serial << "    ";
  int w_apoSensorSetCount= 1;
  for (int wSensorSetID= 0; wSensorSetID <= _wNumSensorSets; wSensorSetID++){
    Serial << "*" << w_apoSensorSetCount++;
    //_apoSensorSet[wSensorSetID]= new BeckSensorSetClass(_apoCarSamples, wSensorSetID);
#if USE_OLD_DATA_ARRAY
    _apoSensorSet[wSensorSetID]= new BeckSensorSetClass(_poDataMgr, _apoCarSamples, wSensorSetID);
#else
    _apoSensorSet[wSensorSetID]= new BeckSensorSetClass(_poDataMgr, wSensorSetID);
#endif
  } //for(int wSensorSetID=0
  Serial << ".*" << endl;

  return;
} //BuildObjectData


bool BeckCarSetClass::bBegin(){
  // Call one probe set since all (4) probe-sets use the same (3) probes
  return _apoSensorSet[1]->bBegin();
} //bBegin


void BeckCarSetClass::PrintLogData(){
  _apoSensorSet[_wLoggingSensorSetID]->PrintSensorSetData();
  return;
} //PrintLogData


void BeckCarSetClass::ReadSensorSet(uint32_t uwSampleTime, int wSensorSetID) {
  //Have the SensorSet handle itself, like have each of its Sensors read its TCouple
  //_apoSensorSet[wSensorSetID]->ReadSensorSet(uwSampleTime, wSensorSetID); //
  //_apoSensorSet[wSensorSetID]->ReadSensorSet(uwSampleTime);
  _apoSensorSet[wSensorSetID]->ReadSensorSet(uwSampleTime);
  return;
} //ReadSensorSet
//Last line.
