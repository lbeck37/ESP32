const char szSystemFileName[]  = "BeckBarClass.cpp";
const char szSystemFileDate[]  = "6/1/21";

//#include <BeckEnviroDataClass.h>
#include <BeckBarClass.h>
#include <BeckLogLib.h>
#include <Streaming.h>

BarClass::BarClass() {
  Serial << "BarClass::BarClass(): " << szSystemFileName << ", " << szSystemFileDate << endl;
/*
  Serial << LOG0 << "BarClass::BarClass(): Set BarType to: " << eNewBarType << endl;
  eBarType= eNewBarType;
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
*/
  return;
} //constructor


BarClass::~BarClass() {
  Serial << "~BarClass(): Destructing" << endl;
  return;
} //destructor


//Last line.
