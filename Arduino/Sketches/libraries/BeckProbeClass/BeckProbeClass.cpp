const char szSystemFileName[]  = "BeckProbeClass.cpp";
const char szSystemFileDate[]  = "3/13/22f";

#include <BeckProbeClass.h>
#include <BeckSampleDataClass.h>
#include <NTPClient.h>
#include <Streaming.h>

extern NTPClient        _oNTPClient;

BeckProbeClass::BeckProbeClass(void) {
  _poTCoupleReader= new BeckTCoupleReaderClass;
  Serial << "BeckProbeClass(void): Default constructor, " << szSystemFileName << ", " << szSystemFileDate << endl;
  return;
} //constructor

BeckProbeClass::BeckProbeClass(int8_t cProbeID, uint8_t ucI2CAddress) {
  _stSampleData.cProbeID  = cProbeID;
  _ucI2CAddress           = ucI2CAddress;
  Serial << "BeckProbeClass(cProbeID,ucI2CAddress): Constructor, " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckProbeClass(cProbeID,ucI2CAddress): Constructor, fGetLastDegF_Value= " << cProbeID << ", ucI2CAddress= " << ucI2CAddress << endl;
  Serial << "BeckProbeClass(cProbeID,ucI2CAddress): Constructor, new BeckTCoupleReaderClass(_ucI2CAddress) " << endl;
  _poTCoupleReader= new BeckTCoupleReaderClass(_ucI2CAddress);
  return;
} //constructor


BeckProbeClass::~BeckProbeClass() {
  Serial << "~BeckProbeClass(): Destructor, deleting _poTCoupleReader" << endl;
  delete _poTCoupleReader;
  _poTCoupleReader= nullptr;
  return;
} //destructor


void BeckProbeClass::Begin(){
  Serial << "BeckProbeClass::Begin(): Call _poTCoupleReader->begin(" << _ucI2CAddress << ")" << endl;
  _poTCoupleReader->begin(_ucI2CAddress);
  return;
} //Begin


void BeckProbeClass::Handle(uint32_t uwSampleTime) {
  _stSampleData.uwSampleTime  = uwSampleTime;
  _stSampleData.fDegF         = _poTCoupleReader->fHandle();
  _stSampleData.bProbeOK      = _poTCoupleReader->bGetProbeOK();
  return;
} //Handle


float BeckProbeClass::fGetDegF() {
  return _stSampleData.fDegF;
} //Handle
//Last line.
