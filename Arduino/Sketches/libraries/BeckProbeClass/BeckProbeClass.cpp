const char szSystemFileName[]  = "BeckProbeClass.cpp";
const char szSystemFileDate[]  = "2/27/22d";  //From 5/31/21e

#include <BeckProbeClass.h>
#include <Streaming.h>

BeckProbeClass::BeckProbeClass() {
  Serial << "BeckProbeClass::BeckProbeClass(): " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor


BeckProbeClass::BeckProbeClass(uint8_t ucSPI_CS_Pin){

  BeckTCoupleReaderClass _oTCoupleReader(ucSPI_CS_Pin);

  Serial << "BeckProbeClass::BeckProbeClass(): " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor


BeckProbeClass::~BeckProbeClass() {
  Serial << "~BeckProbeClass(): Destructing" << endl;
} //destructor


double BeckProbeClass::Handle(){
  double dfDegF= 0.00;

  Serial << "BeckProbeClass::Handle(): Call _poMAX6675_Thermocouple->readFahrenheit()" << dfDegF << endl;
  dfDegF= _oTCoupleReader.Handle();
  Serial << "BeckProbeClass::Handle(): dfDegF= " << dfDegF << endl;
  return dfDegF;
} //Handle
//Last line.
