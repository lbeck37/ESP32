const char szSystemFileName[]  = "BeckCarSetClass.cpp";
const char szSystemFileDate[]  = "3/15/22g";

#include <BeckCarSetClass.h>
#include <BeckSensorClass.h>
#include <BeckSampleDataClass.h>
#include <BeckE32_Defines.h>
#include <Streaming.h>

BeckCarSetClass::BeckCarSetClass()  {
  Serial << "BeckCarSetClass(): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckCarSetClass(): Default CTR, Call BuildSensorSets()" << endl;
  //BuildSensorSets();
  BuildObjectData();
  Serial << "BeckCarSetClass(): Default CTR, Done" << endl;
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

//  BeckSampleDataClass*    _apoCarSample [_wNumSensorSets + 1] [_wNumSensors + 1];


void BeckCarSetClass::BuildObjectData(){
//  Serial << "BeckCarSetClass::BuildObjectData(): Begin\n" <<

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

  Serial << "BuildObjectData(): Build " << (_wNumSensorSets + 1) << " _apoSensorSet[] objects using new" << endl;
  Serial << "    ";
  int w_apoSensorSetCount= 1;
  for (int wSensorSetID= 0; wSensorSetID <= _wNumSensorSets; wSensorSetID++){
    Serial << "*" << w_apoSensorSetCount++;
    _apoSensorSet[wSensorSetID]= new BeckSensorSetClass(wSensorSetID);
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


void BeckCarSetClass::ReadSensorSet(uint32_t uwSampleTime, int wSensorID) {
  //Have the SensorSet handle itself, like have each of its Sensors read its TCouple
  _apoSensorSet[wSensorID]->ReadSensorSet(uwSampleTime, wSensorID);
  return;
} //ReadSensorSet
//Last line.
