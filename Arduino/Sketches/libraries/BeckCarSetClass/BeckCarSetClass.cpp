const char szSystemFileName[]  = "BeckCarSetClass.cpp";
const char szSystemFileDate[]  = "3/29/22e";

#include <BeckCarSetClass.h>
#include <BeckE32_Defines.h>
#include <BeckDataMgrClass.h>
#include <BeckSensorClass.h>
#include <BeckTireTempNTPClass.h>
#include <Streaming.h>

BeckCarSetClass::BeckCarSetClass() {
  Serial << "BeckCarSetClass(): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;

  Serial << "BeckCarSetClass(): Default CTR, Do _poDataMgr= new BeckDataMgrClass()" << endl;
  _poDataMgr  = new BeckDataMgrClass();

  Serial << "BeckCarSetClass(): Default CTR, Do _poNTP    = new BeckTireTempNTPClass()" << endl;
  _poNTP= new BeckTireTempNTPClass();
  _poNTP->SetupNTP();
  _poNTP->PrintCurrentTime();

  Serial << "BeckCarSetClass(): Default CTR, Call BuildObjectData()" << endl;
  BuildObjectData();

  Serial << "\nBeckCarSetClass(): Default CTR, Do _poButtons  = new BeckButtonsClass()" << endl;
  _poButtons= new BeckButtonsClass();

  Serial << "BeckCarSetClass(): Default CTR, Do _poDisplay= new BeckTireTempDisplayClass()" << endl;
  _poDisplay= new BeckTireTempDisplayClass();
  _poDisplay->DisplayBegin();

  Serial << "BeckCarSetClass(): Default CTR, Done" << endl;
  return;
} //constructor

void BeckCarSetClass::BuildObjectData(){
  Serial << "BuildObjectData(): Build " << (_wNumSensorSets + 1) << " _apoSensorSet[] objects using new" << endl;
  Serial << "    ";
  int w_apoSensorSetCount= 1;
  for (int wSensorSetID= 0; wSensorSetID <= _wNumSensorSets; wSensorSetID++){
    Serial << "*" << w_apoSensorSetCount++;
    _apoSensorSet[wSensorSetID]= new BeckSensorSetClass(_poDisplay, _poDataMgr, wSensorSetID);
  } //for(int wSensorSetID=0
  Serial << ".*" << endl;
  return;
} //BuildObjectData

void BeckCarSetClass::Begin(){
  // Call one probe set since all (4) probe-sets use the same type of probe
  _apoSensorSet[1]->bBegin();
  return;
} //Begin

void BeckCarSetClass::HandleLoop(){
  int wChangedSection =  -1;
  //Read and save log temperatures
  ReadLogTemps();

  //Check the buttons and sample and record the (3) sensor values
  int wPressedButton= _poButtons->wHandleLoop();
  if (wPressedButton > 0){
    ReadSensorSet(wPressedButton);
    _poDisplay->DisplaySensorSet(wPressedButton);
  } //if(wPressedButton>0)

  if (wChangedSection >= 0){
    _poDisplay->DisplaySensorSet(wChangedSection);
  } //if(wChangedSection>=0)

  PrintLogData();
  return;
} //HandleLoop


void BeckCarSetClass::ReadSensorSet(int wSensorSetID) {
  //Data is read and written to DataMgr
  _poNTP->HandleNTP();
  _uwEpochTime= _poNTP->uwGetEpochTime();
  _apoSensorSet[wSensorSetID]->ReadSensorSet(_uwEpochTime);
  return;
} //ReadSensorSet


void BeckCarSetClass::ReadLogTemps(){
  if (millis() > _ulNextReadLogMsec){
    _ulNextReadLogMsec= millis() + _ulReadLogPeriodMsec;
    ReadSensorSet(_wLogSensorSetID);
  } //if (millis()>_ulNextReadLogMsec)
  return;
} //ReadLogTemps


void BeckCarSetClass::DisplayLogData(){
  if (millis() > _ulNextPrintLogMsec){
    _ulNextPrintLogMsec= millis() + _ulPrintLogPeriodMsec;
    _apoSensorSet[_wLogSensorSetID]->PrintSensorSetData();
  } //if (millis()>_ulNextPrintLogMsec)

  return;
} //DisplayLogData


void BeckCarSetClass::PrintLogData(){
  if (millis() > _ulNextPrintLogMsec){
    _ulNextPrintLogMsec= millis() + _ulPrintLogPeriodMsec;
    _apoSensorSet[_wLogSensorSetID]->PrintSensorSetData();
  } //if (millis()>_ulNextPrintLogMsec)

  return;
} //PrintLogData


BeckCarSetClass::~BeckCarSetClass() {
  Serial << "~BeckCarSetClass(): Destructor, Deleting sensors" << endl;
  for (int wSensorSetID= 1; wSensorSetID <= _wNumSensorSets; wSensorSetID++){
    Serial << "~BeckCarSetClass(): Destructor, call delete _apoSensor[" << wSensorSetID << "]" << endl;
    delete _apoSensorSet[wSensorSetID];
    _apoSensorSet[wSensorSetID]= nullptr;
  }   //for
  if (_poDataMgr != nullptr) {
    Serial << "~BeckCarSetClass(): Destructor, delete _poDataMgr" << endl;
    delete _poDataMgr;
    _poDataMgr= nullptr;
  }
  if (_poDisplay != nullptr) {
    Serial << "~BeckCarSetClass(): Destructor, delete _poDisplay" << endl;
    delete _poDisplay;
    _poDisplay= nullptr;
  }
  if (_poNTP != nullptr) {
    Serial << "~BeckCarSetClass(): Destructor, delete _poNTP" << endl;
    delete _poNTP;
    _poNTP= nullptr;
  }
  if (_poButtons != nullptr) {
    Serial << "~BeckCarSetClass(): Destructor, delete _poButtons" << endl;
    delete _poButtons;
    _poButtons= nullptr;
  }
  return;
} //destructor
//Last line.
