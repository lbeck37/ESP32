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

BeckProbeClass::BeckProbeClass(int wProbeID, int wI2CAddress) {
  //Serial << "BeckProbeClass(): CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
//  Serial << "BeckProbeClass(): CTR, wProbeID= " << wProbeID << ", wI2CAddress= " << wI2CAddress << endl;
//  Serial << "BeckProbeClass(: CTR, new BeckTCoupleReaderClass(_wI2CAddress) " << endl;
  _wProbeID         = wProbeID;
  _wI2CAddress     = wI2CAddress;
  _poTCoupleReader  = new BeckTCoupleReaderClass(_wI2CAddress);
  return;
} //constructor


BeckProbeClass::~BeckProbeClass() {
  Serial << "~BeckProbeClass(): Destructor, deleting _poTCoupleReader" << endl;
  delete _poTCoupleReader;
  _poTCoupleReader= nullptr;
  return;
} //destructor


void BeckProbeClass::Begin(){
//  Serial << "BeckProbeClass::Begin(): Call _poTCoupleReader->begin(" << _wI2CAddress << ")" << endl;
  _poTCoupleReader->begin(_wI2CAddress);
  return;
} //Begin


float BeckProbeClass::fReadProbe(uint32_t uwSampleTime, int wProbeID) {
  bool    bProbeOK;
  float   fDegF;

  fDegF= _poTCoupleReader->fReadProbe();
  bProbeOK= _poTCoupleReader->bGetProbeOK();

  if (!bProbeOK) {
    Serial << "BeckProbeClass::ReadProbe(): _poTCoupleReader reports FAIL for wProbeID= " << wProbeID << endl;
  } //ReadProbe

/*
  _astSampleData[wProbeID].fDegF          = _poTCoupleReader->fGetDegF();
  _astSampleData[wProbeID].wProbeID       = wProbeID;
  _astSampleData[wProbeID].uwSampleTime   = uwSampleTime;
  _astSampleData[wProbeID].bProbeOK       = _poTCoupleReader->bGetProbeOK();
*/
  return fDegF;
} //Handle


//float BeckProbeClass::fGetDegF() {
//  return _astSampleData[_wProbeID].fDegF;
//} //Handle
//Last line.
