const char szSystemFileName[]  = "BeckCarSetClass.cpp";
const char szSystemFileDate[]  = "3/22/22b";

#include <BeckCarSetClass.h>
#include <BeckE32_Defines.h>
#include <BeckDataMgrClass.h>
#include <BeckSensorClass.h>
#include <BeckTireTempNTPClass.h>
#include <Streaming.h>

BeckCarSetClass::BeckCarSetClass() // : _TestButton(_cButton_Pin1)
{
  Serial << "BeckCarSetClass(): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;

  Serial << "BeckCarSetClass(): Default CTR, Do _poDataMgr= new BeckDataMgrClass()" << endl;
  _poDataMgr  = new BeckDataMgrClass();

  Serial << "BeckCarSetClass(): Default CTR, Do _poDisplay= new BeckTireTempDisplayClass()" << endl;
  _poDisplay  = new BeckTireTempDisplayClass();

  Serial << "BeckCarSetClass(): Default CTR, Do _poNTP    = new BeckTireTempNTPClass()" << endl;
  _poNTP      = new BeckTireTempNTPClass();
  _poNTP->SetupNTP();
  _poNTP->PrintCurrentTime();

  Serial << "BeckCarSetClass(): Default CTR, Call BuildObjectData()" << endl;
  BuildObjectData();

  Serial << "\nBeckCarSetClass(): Default CTR, Do _poButtons= new BeckButtonsClass()" << endl;
  _poButtons  = new BeckButtonsClass();

/*
  Serial << "BeckCarSetClass(): Default CTR, Call _poButtons->SetCallback( CarSetCallback )" << endl;
  //sprintf(_sz100Char, "BeckCarSetClass(): Default CTR, WhenPressedTest address= %x\n", CarSetCallback);
  //Serial << _sz100Char;
  _poButtons->SetCallback(CarSetCallback);
*/

  Serial << "BeckCarSetClass(): Call _poDisplay->DisplayBegin()" << endl;
  _poDisplay->DisplayBegin();

  Serial << "BeckCarSetClass(): Default CTR, Done" << endl;
  return;
} //constructor
//BeckTireTempButtonsClass*   _poButtons                {nullptr};

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
  //return _apoSensorSet[1]->bBegin();
  _apoSensorSet[1]->bBegin();
  return;
} //Begin


void BeckCarSetClass::ReadSensorSet(int wSensorSetID) {
  //Have the SensorSet handle itself, like have each of its Sensors read its TCouple
  _poNTP->HandleNTP();
  _uwEpochTime= _poNTP->uwGetEpochTime();
  _apoSensorSet[wSensorSetID]->ReadSensorSet(_uwEpochTime);
  return;
} //ReadSensorSet


void BeckCarSetClass::CarSetCallback(){
  int   wSensorSet= 1;
  Serial << "BeckCarSetClass::CarSetCallback(): I feel the need for speed!" << endl;
/*
  Serial << ": Set static variable _wButtonWasPressed to 37" << endl;
  BeckCarSetClass::_wButtonWasPressed= 37;
*/
  return;
} //CarSetCallback

/*
void BeckCarSetClass::CarSetCallback1(){
  int   wSensorSet= 1;
  Serial << "BeckCarSetClass::CarSetCallback1(): I feel the need for speed!" << endl;
  return;
} //CarSetCallback1

void BeckCarSetClass::CarSetCallback2(){
  int   wSensorSet= 1;
  Serial << "BeckCarSetClass::CarSetCallback2(): I feel the need for speed!" << endl;
  return;
} //CarSetCallback2

void BeckCarSetClass::CarSetCallback3(){
  int   wSensorSet= 1;
  Serial << "BeckCarSetClass::CarSetCallback3(): I feel the need for speed!" << endl;
  return;
} //CarSetCallback3

void BeckCarSetClass::CarSetCallback4(){
  int   wSensorSet= 1;
  Serial << "BeckCarSetClass::CarSetCallback4(): I feel the need for speed!" << endl;
  return;
} //CarSetCallback4
*/

void BeckCarSetClass::HandleLoop(){
  _poButtons->HandleLoop();
  UpdateDisplay();
  HandleLogging();
  return;
} //HandleLoop


void BeckCarSetClass::UpdateDisplay(){
  // Call one probe set since all (4) probe-sets use the same type of probe
  //return _apoSensorSet[1]->bBegin();
  _poDisplay->DisplayUpdate();
  return;
} //UpdateDisplay


void BeckCarSetClass::HandleLogging(){
  if (millis() > _ulNextHandleSensorsMsec){
    _ulNextHandleSensorsMsec= millis() + _ulHandleSensorsPeriodMsec;
    _poNTP->HandleNTP();

    ReadSensorSet(_wLoggingSensorSetID);
    PrintLogData();
  } //if (millis()>ulNextDisplayMsec)
  return;
} //HandleLogging


void BeckCarSetClass::PrintLogData(){
  _apoSensorSet[_wLoggingSensorSetID]->PrintSensorSetData();
  return;
} //PrintLogData
//Last line.
