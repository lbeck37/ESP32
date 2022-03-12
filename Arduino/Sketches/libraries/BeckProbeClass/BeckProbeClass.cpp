const char szSystemFileName[]  = "BeckProbeClass.cpp";
const char szSystemFileDate[]  = "3/11/22a";

#include <BeckProbeClass.h>
#include <BeckSampleDataClass.h>
#include <NTPClient.h>
#include <Streaming.h>

extern NTPClient        _oNTPClient;
//BeckSampleDataClass     oSampleData{};
//BeckSampleDataClass*     _poSampleData;

//BeckProbeClass::BeckProbeClass(): _oTCoupleReader()
BeckProbeClass::BeckProbeClass(void) {
  _poTCoupleReader= new BeckTCoupleReaderClass;
  Serial << "BeckProbeClass(void): Default constructor, " << szSystemFileName << ", " << szSystemFileDate << endl;
  return;
} //constructor

/*
BeckProbeClass::BeckProbeClass(uint8_t ucI2CAddress) {
  _ucI2CAddress= ucI2CAddress;
  //BeckTCoupleReaderClass* poLocalTCoupleReader { new BeckTCoupleReaderClass {_ucI2CAddress} };
  _poTCoupleReader= new BeckTCoupleReaderClass(_ucI2CAddress);

  Serial << "BeckProbeClass::BeckProbeClass(uint8_t): Constructor, " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t): Constructor, ucI2CAddress= " << ucI2CAddress << endl;
} //constructor
*/

/*
BeckProbeClass::BeckProbeClass(uint8_t ucI2CAddress, ProbePositionEnum eProbePosition) {
  _ucI2CAddress     = ucI2CAddress;
  _eProbePosition   = eProbePosition;
  _poTCoupleReader  = new BeckTCoupleReaderClass(_ucI2CAddress);
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t,ProbePositionEnum): Constructor, " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t,ProbePositionEnum):  Constructor, ucI2CAddress= " << ucI2CAddress << endl;
} //constructor
*/
BeckProbeClass::BeckProbeClass(int8_t cProbeID, uint8_t ucI2CAddress) {
  _cProbeID         = cProbeID;
  _ucI2CAddress     = ucI2CAddress;
  Serial << "BeckProbeClass(cProbeID,ucI2CAddress): Constructor, " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckProbeClass(cProbeID,ucI2CAddress): Constructor, _cProbeID= " << _cProbeID << ", ucI2CAddress= " << ucI2CAddress << endl;
  Serial << "BeckProbeClass(cProbeID,ucI2CAddress): Constructor, new BeckTCoupleReaderClass(_ucI2CAddress) " << endl;
  _poTCoupleReader= new BeckTCoupleReaderClass(_ucI2CAddress);

  Serial << "BeckProbeClass(cProbeID,ucI2CAddress): Constructor, Call _poSampleData= new BeckSampleDataClass()" << endl;
//  _poSampleData= new BeckSampleDataClass();
  return;
} //constructor


BeckProbeClass::~BeckProbeClass() {
  Serial << "~BeckProbeClass(): Destructor, deleting _poTCoupleReader" << endl;
  delete _poTCoupleReader;
  _poTCoupleReader= nullptr;

/*
  Serial << "~BeckProbeClass(): Destructor, deleting _poSampleData" << endl;
  delete _poSampleData;
  _poSampleData= nullptr;
*/
  return;
} //destructor


void BeckProbeClass::Begin(){
  Serial << "BeckProbeClass::Begin(): Call _poTCoupleReader->begin(" << _ucI2CAddress << ")" << endl;
  _poTCoupleReader->begin(_ucI2CAddress);
  return;
} //Begin


double BeckProbeClass::Handle(){
  Serial << "BeckProbeClass::Handle(): Call _dfDegF= _poTCoupleReader->Handle()" << endl;
  _dfDegF= _poTCoupleReader->Handle();

  //oSampleData.SetDegF_Value(_dfDegF);

  unsigned long ulCurrentEpochSeconds= _oNTPClient.getEpochTime();
/*
  Serial << "BeckProbeClass::Handle(): oSampleData.SetSampleTime(" << ulCurrentEpochSeconds << ")" << endl;
  oSampleData.SetSampleTime(ulCurrentEpochSeconds);
*/

  return _dfDegF;
} //Handle
//Last line.
