const char szSystemFileName[]  = "BeckProbeClass.cpp";
const char szSystemFileDate[]  = "2/28/22b";

#include <BeckProbeClass.h>
#include <Streaming.h>

BeckProbeClass::BeckProbeClass() {
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
