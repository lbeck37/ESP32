static const char szSystemFileName[]  = "BeckDataMgrClass.cpp";
static const char szSystemFileDate[]  = "3/28/22b";

#include <BeckDataMgrClass.h>
#include <Streaming.h>

BeckDataMgrClass::BeckDataMgrClass() {
  Serial << "BeckDataMgrClass(): Default CTR, Call BuildSensorData()" << endl;
  BuildSensorData();
} //constructor


void BeckDataMgrClass::BuildSensorData(){
//  Serial << "BeckCarSetClass::BuildSensorData(): Begin\n" <<
  int w_apoCarReadingsCount= 1;
  int wTotalSensorSets = _wNumSensorSets + 1;
  int wTotalSensors    = _wNumSensors    + 1;
  int wGrandTotal     = (wTotalSensorSets * wTotalSensors);
  Serial << "BuildSensorData(): Build " << wTotalSensorSets << " X " << wTotalSensors << " = " << wGrandTotal << " _apoCarReadings[][]" << endl;
  Serial << "    ";

  for (int wSensorSetID= 0; wSensorSetID <= _wNumSensorSets; wSensorSetID++){
    for (int wSensorID= 0; wSensorID <= _wNumSensors; wSensorID++){
      Serial << "." << w_apoCarReadingsCount++;
      _apoCarReadings[wSensorSetID][wSensorID]= new BeckReadingDataClass(wSensorSetID, wSensorID);
    } //for(int wSensorID=0...
    Serial << ".*";
  } //for(int wSensorSetID=0...
  Serial << endl;

  return;
} //BuildSensorData


void BeckDataMgrClass::SetReadingTime(int wSensorSetID, int wSensorID, uint32_t uwReadingTime){
  _apoCarReadings[wSensorSetID][wSensorID]->SetReadingTime(uwReadingTime);
  return;
} //SetReadingTime

uint32_t BeckDataMgrClass::uwGetReadingTime(int wSensorSetID, int wSensorID){
  return (_apoCarReadings[wSensorSetID][wSensorID]->uwGetReadingTime());
} //ulGetReadingTime


void BeckDataMgrClass::SetDegF(int wSensorSetID, int wSensorID, float fNewDegFValue){
  _apoCarReadings[wSensorSetID][wSensorID]->SetDegF(fNewDegFValue);
  return;
}	//SetDegF

float BeckDataMgrClass::fGetDegF(int wSensorSetID, int wSensorID){
  //Serial << "\BeckDataMgrClass::fGetDegF(" << wSensorID << ", " << wSensorID << ") call fGetDegF()" << endl;
  float fReturn;
  fReturn= _apoCarReadings[wSensorSetID][wSensorID]->fGetDegF();
  //return (_apoCarReadings[wSensorSetID][wSensorID]->fGetDegF());
  return fReturn;
}	//wGetDegF


void BeckDataMgrClass::SetDegFChanged(int wSensorSetID, int wSensorID){
  _apoCarReadings[wSensorSetID][wSensorID]->SetDegFChanged();
  return;
} //bDegFChanged

bool BeckDataMgrClass::bGetDegFChanged(int wSensorSetID, int wSensorID){
  return (_apoCarReadings[wSensorSetID][wSensorID]->bGetDegFChanged());
} //bDegFChanged


float BeckDataMgrClass::fGetLastDegF(int wSensorSetID, int wSensorID){
  return (_apoCarReadings[wSensorSetID][wSensorID]->fGetLastDegF());
} //fGetLastDegF


BeckDataMgrClass::~BeckDataMgrClass() {
  Serial << "~BeckDataMgrClass(): Destructor, call delete _apoCarReadings[][]" << endl;
  for (int wSensorSetID= 0; wSensorSetID <= _wNumSensorSets; wSensorSetID++){
    for (int wSensorID= 0; wSensorID <= _wNumSensors; wSensorID++){
      if(_apoCarReadings[wSensorSetID][wSensorID] != nullptr){
        delete _apoCarReadings[wSensorSetID][wSensorID];
        _apoCarReadings[wSensorSetID][wSensorID]= nullptr;
      } //if
    } //for(int wSensorID=0...
    Serial << ".*";
  } //for(int wSensorSetID=0...
} //destructor
//Last line.
