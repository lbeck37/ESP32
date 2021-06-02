const char szSystemFileName[]  = "BeckBarClass.cpp";
const char szSystemFileDate[]  = "6/2/21b";

//#include <BeckEnviroDataClass.h>
#include <BeckBarClass.h>
#include <BeckLogLib.h>
#include <Streaming.h>

//BarClass::BarClass(BarType eBar, PUnit XLeft, PUnit YBottom) {
BarClass::BarClass(BarDataClass BarData) {
  Serial << "BarClass::BarClass(): " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << LOG0 << "BarClass::BarClass(): Set BarType to: " << BarData.eBarType << endl;
  eBarType= BarData.eBarType;
  switch(eBarType){
  case eCO2Bar:
    BarSegmentClass   GreenSegment= BarSegmentClass();
    GreenSegment.StartPercent   = 0;
    GreenSegment.SegmentColor   = BECK_GREEN;
    GreenSegment.fStartValue    =   0.0;
    GreenSegment.fEndValue      = 600.0;
    //BarSegments.push_back(GreenSegment);
    BarData.BarSegments.push_back(GreenSegment);

    BarSegmentClass   YellowSegment= BarSegmentClass();
    GreenSegment.StartPercent   = 33;
    GreenSegment.SegmentColor   = BECK_YELLOW;
    GreenSegment.fStartValue    =  600.0;
    GreenSegment.fEndValue      = 1000.0;
    BarData.BarSegments.push_back(YellowSegment);

    BarSegmentClass   RedSegment= BarSegmentClass();
    GreenSegment.StartPercent   = 66;
    GreenSegment.SegmentColor   = BECK_RED;
    GreenSegment.fStartValue    = 1000.0;
    GreenSegment.fEndValue      = 2000.0;
    BarData.BarSegments.push_back(YellowSegment);
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
