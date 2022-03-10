const char szSystemFileName[]  = "BeckProbeClass.cpp";
const char szSystemFileDate[]  = "3/10/22a";

#include <BeckProbeClass.h>
#include <BeckSampleDataClass.h>
#include <NTPClient.h>
#include <Streaming.h>

extern NTPClient        _oNTPClient;
BeckSampleDataClass     oSampleData{};

//BeckProbeClass::BeckProbeClass(): _oTCoupleReader()
BeckProbeClass::BeckProbeClass(void) {
  //_ucI2CAddress= 0;
  _poTCoupleReader= new BeckTCoupleReaderClass;
  Serial << "BeckProbeClass::BeckProbeClass(void): Default constructor, " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor

BeckProbeClass::BeckProbeClass(uint8_t ucI2CAddress) {
  _ucI2CAddress= ucI2CAddress;
  //BeckTCoupleReaderClass* poLocalTCoupleReader { new BeckTCoupleReaderClass {_ucI2CAddress} };
  _poTCoupleReader= new BeckTCoupleReaderClass(_ucI2CAddress);

  Serial << "BeckProbeClass::BeckProbeClass(uint8_t): Constructor, " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t): Constructor, ucI2CAddress= " << ucI2CAddress << endl;
} //constructor


BeckProbeClass::BeckProbeClass(uint8_t ucI2CAddress, ProbePositionEnum eProbePosition) : _ucI2CAddress{ucI2CAddress}, _oTCoupleReader{}, _eProbePosition{eProbePosition}
{
  _ucI2CAddress= ucI2CAddress;
  _poTCoupleReader= new BeckTCoupleReaderClass(_ucI2CAddress);
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t,ProbePositionEnum): Constructor, " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t,ProbePositionEnum):  Constructor, ucI2CAddress= " << ucI2CAddress << endl;
} //constructor


BeckProbeClass::~BeckProbeClass() {
  Serial << "~BeckProbeClass(): Destructing" << endl;
} //destructor


void BeckProbeClass::Begin(){
  Serial << "BeckProbeClass::Begin(): Call _oTCoupleReader.begin(" << _ucI2CAddress << ")" << endl;
  _oTCoupleReader.begin(_ucI2CAddress);
  return;
} //Begin


double BeckProbeClass::Handle(){
  Serial << "BeckProbeClass::Handle(): Call _dfDegF= _oTCoupleReader.Handle()" << endl;
  _dfDegF= _oTCoupleReader.Handle();

  oSampleData.SetDegF_Value(_dfDegF);

  unsigned long ulCurrentEpochSeconds= _oNTPClient.getEpochTime();
  Serial << "BeckProbeClass::Handle(): oSampleData.SetSampleTime(" << ulCurrentEpochSeconds << ")" << endl;
  oSampleData.SetSampleTime(ulCurrentEpochSeconds);

  return _dfDegF;
} //Handle
//Last line.
