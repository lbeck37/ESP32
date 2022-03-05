const char szSystemFileName[]  = "BeckProbeClass.cpp";
const char szSystemFileDate[]  = "3/4/22c";

#include <BeckProbeClass.h>
#include <BeckSampleDataClass.h>
#include <NTPClient.h>
#include <Streaming.h>

extern NTPClient oNTPClient;
BeckSampleDataClass    oSampleData{};

BeckProbeClass::BeckProbeClass(): _oTCoupleReader(2)
{
  //_oTCoupleReader= BeckTCoupleReaderClass(2);
  Serial << "BeckProbeClass::BeckProbeClass(): Default constructor, " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor

BeckProbeClass::BeckProbeClass(uint8_t ucCS_Pin) : _ucCS_Pin{ucCS_Pin}, _oTCoupleReader{ucCS_Pin}
{
  //_oTCoupleReader= BeckTCoupleReaderClass(_ucCS_Pin);
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t): " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t): ucCS_Pin= " << ucCS_Pin << endl;
} //constructor


BeckProbeClass::BeckProbeClass(uint8_t ucCS_Pin, ProbePosition eProbePosition) : _ucCS_Pin{ucCS_Pin}, _oTCoupleReader{ucCS_Pin}, _eProbePosition{eProbePosition}
{
  //_oTCoupleReader= BeckTCoupleReaderClass(_ucCS_Pin);
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t): " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckProbeClass::BeckProbeClass(uint8_t): ucCS_Pin= " << ucCS_Pin << endl;
} //constructor


BeckProbeClass::~BeckProbeClass() {
  Serial << "~BeckProbeClass(): Destructing" << endl;
} //destructor


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
