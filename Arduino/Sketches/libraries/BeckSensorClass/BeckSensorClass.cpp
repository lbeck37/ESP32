const char szSystemFileName[]  = "BeckSensorClass.cpp";		//Copied from BeckProbeClass.cpp
const char szSystemFileDate[]  = "3/16/22a";

#include <BeckSensorClass.h>
#include <BeckSampleDataClass.h>
#include <NTPClient.h>
#include <Streaming.h>

extern NTPClient        _oNTPClient;

BeckSensorClass::BeckSensorClass(void) {
  Serial << "BeckSensorClass(void): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
  _poTCoupleSensor= new BeckTCoupleSensorClass;
  return;
} //constructor

BeckSensorClass::BeckSensorClass(int wSensorID, int wI2CAddress) {
// Serial << "BeckSensorClass(): CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
// Serial << "BeckSensorClass(): CTR, wSensorID= " << wSensorID << ", wI2CAddress= " << wI2CAddress << endl;
// Serial << "BeckSensorClass(: CTR, new BeckTCoupleSensorClass(_wI2CAddress) " << endl;
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


float BeckSensorClass::fReadSensor(uint32_t uwSampleTime, int wSensorID) {
  bool    bSensorOK;
  float   fDegF;

  fDegF= _poTCoupleSensor->fReadProbe();
  bSensorOK= _poTCoupleSensor->bGetProbeOK();

  if (!bSensorOK) {
    Serial << "BeckSensorClass::ReadSensor(): _poTCoupleSensor reports FAIL for wSensorID= " << wSensorID << endl;
  } //ReadSensor

  return fDegF;
} //fReadSensor
//Last line.
