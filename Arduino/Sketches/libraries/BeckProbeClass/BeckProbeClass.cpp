const char szSystemFileName[]  = "BeckProbeClass.cpp";
const char szSystemFileDate[]  = "3/14/22b";

#include <BeckProbeClass.h>
#include <BeckSampleDataClass.h>
#include <NTPClient.h>
#include <Streaming.h>

extern NTPClient        _oNTPClient;

BeckProbeClass::BeckProbeClass(void) {
  //Serial << "BeckProbeClass(void): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
  _poTCoupleReader= new BeckTCoupleReaderClass;
  return;
} //constructor

BeckProbeClass::BeckProbeClass(int8_t cProbeID, uint8_t ucI2CAddress) {
  //Serial << "BeckProbeClass(): CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
//  Serial << "BeckProbeClass(): CTR, cProbeID= " << cProbeID << ", ucI2CAddress= " << ucI2CAddress << endl;
//  Serial << "BeckProbeClass(: CTR, new BeckTCoupleReaderClass(_ucI2CAddress) " << endl;
  _cProbeID         = cProbeID;
  _ucI2CAddress     = ucI2CAddress;
  _poTCoupleReader  = new BeckTCoupleReaderClass(_ucI2CAddress);
  return;
} //constructor


BeckProbeClass::~BeckProbeClass() {
  Serial << "~BeckProbeClass(): Destructor, deleting _poTCoupleReader" << endl;
  delete _poTCoupleReader;
  _poTCoupleReader= nullptr;
  return;
} //destructor


void BeckProbeClass::Begin(){
//  Serial << "BeckProbeClass::Begin(): Call _poTCoupleReader->begin(" << _ucI2CAddress << ")" << endl;
  _poTCoupleReader->begin(_ucI2CAddress);
  return;
} //Begin


void BeckProbeClass::Handle(uint32_t uwSampleTime, int8_t cProbeID) {
  _poTCoupleReader->Handle();
  bool  bProbeOK= _poTCoupleReader->bGetProbeOK();
  if (!bProbeOK) {
    Serial << "BeckProbeClass::Handle(): _poTCoupleReader reports FAIL for cProbeID= " << cProbeID << endl;
  }

  _astSampleData[cProbeID].fDegF          = _poTCoupleReader->fGetDegF();
  _astSampleData[cProbeID].cProbeID       = cProbeID;
  _astSampleData[cProbeID].uwSampleTime   = uwSampleTime;
  _astSampleData[cProbeID].bProbeOK       = _poTCoupleReader->bGetProbeOK();
  return;
} //Handle


//float BeckProbeClass::fGetDegF() {
//  return _astSampleData[_cProbeID].fDegF;
//} //Handle
//Last line.
