const char szSystemFileName[]  = "BeckProbeClass.cpp";
const char szSystemFileDate[]  = "3/6/22e";

#include <BeckProbeClass.h>
#include <BeckSampleDataClass.h>
#include <NTPClient.h>
#include <Streaming.h>

extern NTPClient        _oNTPClient;
BeckSampleDataClass     oSampleData{};

BeckProbeClass::BeckProbeClass(): _oTCoupleReader()
{
  Serial << "BeckProbeClass::BeckProbeClass(): Default constructor, " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor

BeckProbeClass::BeckProbeClass(uint8_t ucI2CAddress) : _ucI2CAddress{ucI2CAddress}
{
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t): " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t): ucI2CAddress= " << ucI2CAddress << endl;
} //constructor


BeckProbeClass::BeckProbeClass(uint8_t ucI2CAddress, ProbePositionEnum eProbePosition) : _ucI2CAddress{ucI2CAddress}, _oTCoupleReader{}, _eProbePosition{eProbePosition}
{
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t,ProbePositionEnum): " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t,ProbePositionEnum): ucI2CAddress= " << ucI2CAddress << endl;
} //constructor


BeckProbeClass::~BeckProbeClass() {
  Serial << "~BeckProbeClass(): Destructing" << endl;
} //destructor


void BeckProbeClass::Begin(){
  Serial << "BeckProbeClass::Begin(): Begin" << endl;
  _oTCoupleReader.begin(_ucI2CAddress);
  return;
} //Begin


double BeckProbeClass::Handle(){
  _dfDegF= _oTCoupleReader.Handle();

  oSampleData.SetDegF_Value(_dfDegF);

  unsigned long ulCurrentEpochSeconds= _oNTPClient.getEpochTime();
  oSampleData.SetSampleTime(ulCurrentEpochSeconds);

  //Serial << "BeckProbeClass::Handle(): dfDegF= " << dfDegF << endl;
  return _dfDegF;
} //Handle
//Last line.
