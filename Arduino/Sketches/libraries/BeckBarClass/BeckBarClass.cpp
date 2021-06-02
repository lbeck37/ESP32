const char szSystemFileName[]  = "BeckBarClass.cpp";
const char szSystemFileDate[]  = "6/2/21a";

//#include <BeckEnviroDataClass.h>
#include <BeckBarClass.h>
#include <BeckLogLib.h>
#include <Streaming.h>

BarClass::BarClass(BarType eBar) {
  Serial << "BarClass::BarClass(): " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << LOG0 << "BarClass::BarClass(): Set BarType to: " << eNewBarType << endl;
  eBarType= eBar;
  switch(eBarType){
  case eCO2Bar:
    break;
  case eVOCBar:
    break;
  case eDegFBar:
    break;
  case eRHBar:
    break;
    default:
      Serial << LOG0 << "BarClass::BarClass(): Bad Switch= " << eBarType << endl;
      break;
  } //switch
  return;
} //constructor


BarClass::~BarClass() {
  Serial << "~BarClass(): Destructing" << endl;
  return;
} //destructor


//Last line.
