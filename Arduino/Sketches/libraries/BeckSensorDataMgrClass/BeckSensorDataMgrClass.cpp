static const char szSystemFileName[]  = "BeckSensorDataMgrClass.cpp";
static const char szSystemFileDate[]  = "3/16/22c";

#include <BeckSensorDataMgrClass.h>
#include <Streaming.h>

BeckSensorDataMgrClass      _oSensorDataMgr;

BeckSensorDataMgrClass::BeckSensorDataMgrClass() {
  Serial << "BeckSensorDataMgrClass(): Default CTR"<< "\n";
} //constructor

/*
BeckSensorDataMgrClass::BeckSensorDataMgrClass(int wSensorSetID, int wSensorID) {
  //Serial << "BeckSensorDataMgrClass(wSensorSetID, wSensorID): CTR"<< "\n";
  _wSensorSetID  = wSensorSetID;
  _wSensorID     = wSensorID;
  return;
} //constructor
*/

BeckSensorDataMgrClass::~BeckSensorDataMgrClass() {
  Serial << "~BeckSensorDataMgrClass(): Destructor" << "\n";
} //destructor


void BeckSensorDataMgrClass::BuildSensorData(){
//  Serial << "BeckCarSetClass::BuildSensorData(): Begin\n" <<
  int w_apoCarSamplesCount= 1;
  int wTotalSensorSets = _wNumSensorSets + 1;
  int wTotalSensors    = _wNumSensors    + 1;
  int wGrandTotal     = (wTotalSensorSets * wTotalSensors);
  Serial << "BuildSensorData(): Build " << wTotalSensorSets << " X " << wTotalSensors << " = " << wGrandTotal << " _apoCarSamples[][]" << endl;
  Serial << "    ";

  for (int wSensorSetID= 0; wSensorSetID <= _wNumSensorSets; wSensorSetID++){
    for (int wSensorID= 0; wSensorID <= _wNumSensors; wSensorID++){
      Serial << "." << w_apoCarSamplesCount++;
      _apoCarSamples[wSensorSetID][wSensorID]= new BeckSampleDataClass(wSensorSetID, wSensorID);
    } //for(int wSensorID=0...
    Serial << ".*";
  } //for(int wSensorSetID=0...
  Serial << endl;

  return;
} //BuildSensorData


void BeckSensorDataMgrClass::SetSampleTime(int wSensorSetID, int wSensorID, uint32_t uwSampleTime){
  _apoCarSamples[wSensorSetID][wSensorID]->SetSampleTime(uwSampleTime);
  return;
} //SetSampleTime

uint32_t BeckSensorDataMgrClass::uwGetSampleTime(int wSensorSetID, int wSensorID){
  return (_apoCarSamples[wSensorSetID][wSensorID]->uwGetSampleTime());
} //ulGetSampleTime

void BeckSensorDataMgrClass::SetDegF(int wSensorSetID, int wSensorID, float fNewDegFValue){
  _apoCarSamples[wSensorSetID][wSensorID]->SetDegF(fNewDegFValue);
  return;
}	//SetDegF

float BeckSensorDataMgrClass::fGetDegF(int wSensorSetID, int wSensorID){
  return (_apoCarSamples[wSensorSetID][wSensorID]->fGetDegF());
}	//wGetDegF

void BeckSensorDataMgrClass::SetDegFChanged(int wSensorSetID, int wSensorID){
  _apoCarSamples[wSensorSetID][wSensorID]->SetDegFChanged();
  return;
} //bDegFChanged

bool BeckSensorDataMgrClass::bGetDegFChanged(int wSensorSetID, int wSensorID){
  return (_apoCarSamples[wSensorSetID][wSensorID]->bGetDegFChanged());
} //bDegFChanged

float BeckSensorDataMgrClass::fGetLastDegF(int wSensorSetID, int wSensorID){
  return (_apoCarSamples[wSensorSetID][wSensorID]->fGetLastDegF());
} //fGetLastDegF
//Last line.
