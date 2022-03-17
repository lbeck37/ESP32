const char szSystemFileName[]  = "BeckSensorClass.cpp";		//Copied from BeckProbeClass.cpp
const char szSystemFileDate[]  = "3/16/22b";

#include <BeckSensorClass.h>
#include <Streaming.h>

BeckSensorClass::BeckSensorClass() {
  Serial << "BeckSensorClass(void): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
  _poTCoupleSensor= new BeckTCoupleSensorClass;
  return;
} //constructor

BeckSensorClass::BeckSensorClass(int wSensorID, int wI2CAddress) {
// Serial << "BeckSensorClass(): CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
  _wSensorID         = wSensorID;
  _wI2CAddress     = wI2CAddress;
  _poTCoupleSensor  = new BeckTCoupleSensorClass(_wI2CAddress);
  return;
} //CTR

BeckSensorClass::~BeckSensorClass() {
  Serial << "~BeckSensorClass(): Destructor, deleting _poTCoupleSensor" << endl;
  delete _poTCoupleSensor;
  _poTCoupleSensor= nullptr;
  return;
} //destructor


bool BeckSensorClass::bBegin(){
  Serial << "BeckSensorClass::bBegin(): Call _poTCoupleSensor->SetupMCP9600() for _wSensorID= " << _wSensorID << endl;
  _poTCoupleSensor->SetupMCP9600();
  return true;
} //Begin


//float BeckSensorClass::fReadSensor(uint32_t uwSampleTime, int wSensorID) {
float BeckSensorClass::fReadSensor() {
  bool    bSensorOK;
  float   fDegF;

  fDegF       = _poTCoupleSensor->fReadProbe();
  bSensorOK   = _poTCoupleSensor->bGetProbeOK();

  if (!bSensorOK) {
    _bSensorOK= bSensorOK;
    Serial << "BeckSensorClass::ReadSensor(): _poTCoupleSensor reports FAIL for wSensorID= " << _wSensorID << endl;
  } //ReadSensor

  return fDegF;
} //fReadSensor
//Last line.
