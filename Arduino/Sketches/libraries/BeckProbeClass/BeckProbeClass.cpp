const char szSystemFileName[]  = "BeckProbeClass.cpp";
const char szSystemFileDate[]  = "3/5/22c";

#include <BeckProbeClass.h>
#include <BeckSampleDataClass.h>
#include <NTPClient.h>
#include <Streaming.h>

extern NTPClient oNTPClient;
BeckSampleDataClass    oSampleData{};

#if DO_MAX6675
BeckProbeClass::BeckProbeClass(): _oTCoupleReader(_cSPI_CS_Pin1)
{
  Serial << "BeckProbeClass::BeckProbeClass(): Default constructor, " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor

BeckProbeClass::BeckProbeClass(int8_t cCS_Pin) : _cCS_Pin{cCS_Pin}, _oTCoupleReader{cCS_Pin}
{
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t): " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t): cCS_Pin= " << cCS_Pin << endl;
} //constructor


BeckProbeClass::BeckProbeClass(int8_t cCS_Pin, ProbePosition eProbePosition) : _cCS_Pin{cCS_Pin}, _oTCoupleReader{cCS_Pin}, _eProbePosition{eProbePosition}
{
  Serial << "BeckProbeClass::BeckProbeClass(int8_t,ProbePosition): " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckProbeClass::BeckProbeClass(int8_t,ProbePosition): cCS_Pin= " << cCS_Pin << endl;
} //constructor

BeckProbeClass::BeckProbeClass(uint8_t ucI2CAddress) : _ucI2CAddress{ucI2CAddress}
{
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t): " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t): ucI2CAddress= " << ucI2CAddress << endl;
} //constructor


BeckProbeClass::BeckProbeClass(uint8_t ucI2CAddress, ProbePosition eProbePosition) : _ucI2CAddress{ucI2CAddress}, _oTCoupleReader{}, _eProbePosition{eProbePosition}
{
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t,ProbePosition): " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t,ProbePosition): ucI2CAddress= " << ucI2CAddress << endl;
} //constructor

#else
BeckProbeClass::BeckProbeClass(): _oTCoupleReader()
{
  Serial << "BeckProbeClass::BeckProbeClass(): Default constructor, " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor

BeckProbeClass::BeckProbeClass(int8_t cCS_Pin) : _cCS_Pin{cCS_Pin}
{
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t): " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t): cCS_Pin= " << cCS_Pin << endl;
} //constructor


BeckProbeClass::BeckProbeClass(int8_t cCS_Pin, ProbePosition eProbePosition) : _cCS_Pin{cCS_Pin}, _oTCoupleReader{}, _eProbePosition{eProbePosition}
{
  Serial << "BeckProbeClass::BeckProbeClass(int8_t,ProbePosition): " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckProbeClass::BeckProbeClass(int8_t,ProbePosition): cCS_Pin= " << cCS_Pin << endl;
} //constructor

BeckProbeClass::BeckProbeClass(uint8_t ucI2CAddress) : _ucI2CAddress{ucI2CAddress}
{
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t): " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t): ucI2CAddress= " << ucI2CAddress << endl;
} //constructor


BeckProbeClass::BeckProbeClass(uint8_t ucI2CAddress, ProbePosition eProbePosition) : _ucI2CAddress{ucI2CAddress}, _oTCoupleReader{}, _eProbePosition{eProbePosition}
{
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t,ProbePosition): " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t,ProbePosition): ucI2CAddress= " << ucI2CAddress << endl;
} //constructor
#endif

BeckProbeClass::~BeckProbeClass() {
  Serial << "~BeckProbeClass(): Destructing" << endl;
} //destructor


void BeckProbeClass::Begin(){
  Serial << "BeckProbeClass::Begin(): Begin" << endl;
  _oTCoupleReader.begin(_ucI2CAddress);
  return;
} //Begin


double BeckProbeClass::Handle(){
  double dfDegF= 0.00;

  //Serial << "BeckProbeClass::Handle(): _ucCS_Pin= " << _ucCS_Pin << endl;
  //Serial << "BeckProbeClass::Handle(): Call _oTCoupleReader.Handle()" << endl;

  dfDegF= _oTCoupleReader.Handle();

  oSampleData.SetDegF_Value(dfDegF);

  unsigned long ulCurrentEpochSeconds= oNTPClient.getEpochTime();
  oSampleData.SetSampleTime(ulCurrentEpochSeconds);

  //Serial << "BeckProbeClass::Handle(): dfDegF= " << dfDegF << endl;
  return dfDegF;
} //Handle
//Last line.
