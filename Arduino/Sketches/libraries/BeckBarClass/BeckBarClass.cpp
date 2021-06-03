const char szBarClassFileName[]  = "BeckBarClass.cpp";
const char szBarClassFileDate[]  = "6/3/21b";

//#include <BeckEnviroDataClass.h>
#include <BeckBarClass.h>
#include <BeckLogLib.h>
#include <Streaming.h>

/*
PUnit     EnviroBarWidth   =  35;
PUnit     EnviroBarLength  = 120;
*/

BarSegmentClass::BarSegmentClass() {
  Serial << "BarSegmentClass::BarSegmentClass(void): " << szBarClassFileName << ", " << szBarClassFileDate << endl;
} //constructor

BarSegmentClass::~BarSegmentClass() {
  Serial << "~BarSegmentClass(): Destructing" << endl;
} //destructor

BarDataClass::BarDataClass() {
  Serial << "BarDataClass::BarDataClass(void): " << szBarClassFileName << ", " << szBarClassFileDate << endl;
} //constructor

BarDataClass::~BarDataClass() {
  Serial << "~BarDataClass(): Destructing" << endl;
} //destructor

BarClass::BarClass() {
  Serial << "BarClass::BarClass(void): " << szBarClassFileName << ", " << szBarClassFileDate << endl;
} //constructor

BarClass::~BarClass() {
  Serial << "~BarClass(): Destructing" << endl;
} //destructor

//BarClass::BarClass(BarType eBar, PUnit XLeft, PUnit YBottom) {
BarClass::BarClass(BarDataClass BarData) {
  Serial << "BarClass::BarClass(BarDataClass): " << szBarClassFileName << ", " << szBarClassFileDate << endl;
  Serial << LOG0 << "BarClass::BarClass(): Set BarType to: " << BarData.eBarType << endl;
  BarData.eBarType= eCO2Bar;
  //switch(BarData.eBarType){
  switch(BarData.eBarType){
  case eCO2Bar:
    //BarSegmentClass   GreenSegment= BarSegmentClass();
    GreenSegment.StartPercent   = 0;
    GreenSegment.SegmentColor   = BECK_GREEN;
    GreenSegment.fStartValue    =   0.0;
    GreenSegment.fEndValue      = 600.0;
    //BarSegments.push_back(GreenSegment);
    BarSegments.push_back(GreenSegment);

    //BarSegmentClass   YellowSegment= BarSegmentClass();
    YellowSegment.StartPercent   = 33;
    YellowSegment.SegmentColor   = BECK_YELLOW;
    YellowSegment.fStartValue    =  600.0;
    YellowSegment.fEndValue      = 1000.0;
    BarSegments.push_back(YellowSegment);

    //BarSegmentClass   RedSegment= BarSegmentClass();
    RedSegment.StartPercent   = 66;
    RedSegment.SegmentColor   = BECK_RED;
    RedSegment.fStartValue    = 1000.0;
    RedSegment.fEndValue      = 2000.0;
    BarSegments.push_back(RedSegment);
    break;
  case eVOCBar:
    break;
  case eDegFBar:
    break;
  case eRHBar:
    break;
  case eNoBar:
  case eLastBarType:
  default:
    Serial << LOG0 << "BarClass::BarClass(): Bad Switch= " << BarData.eBarType << endl;
    break;
  } //switch
} //constructor


void BarClass::DrawBar(void) {
  Serial << "BarClass::BarClass(void): " << szBarClassFileName << ", " << szBarClassFileDate << endl;
} //constructor

//Last line.
