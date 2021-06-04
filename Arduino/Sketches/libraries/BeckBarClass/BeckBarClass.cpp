const char szBarClassFileName[]  = "BeckBarClass.cpp";
const char szBarClassFileDate[]  = "6/3/21d";

//#include <BeckEnviroDataClass.h>
#include <BeckBarClass.h>
#include <BeckLogLib.h>
#include <Streaming.h>

/*
PUnit     EnviroBarWidth   =  35;
PUnit     EnviroBarLength  = 120;
*/

//BarSegmentClass methods
BarSegmentClass::BarSegmentClass() {
  Serial << "BarSegmentClass::BarSegmentClass(void): " << szBarClassFileName << ", " << szBarClassFileDate << endl;
} //constructor

BarSegmentClass::~BarSegmentClass() {
  Serial << "~BarSegmentClass(): Destructing" << endl;
} //destructor

void BarSegmentClass::Draw() {
  Serial << "BarSegmentClass::Draw(XLeft, YBottom): Begin"<< endl;

  return;
} //Draw


//BarDataClass methods
BarDataClass::BarDataClass() {
  Serial << "BarDataClass::BarDataClass(void): " << szBarClassFileName << ", " << szBarClassFileDate << endl;
} //constructor

BarDataClass::~BarDataClass() {
  Serial << "~BarDataClass(): Destructing" << endl;
} //destructor

//BarClass methods
BarClass::BarClass() {
  Serial << "BarClass::BarClass(void): " << szBarClassFileName << ", " << szBarClassFileDate << endl;
} //constructor

BarClass::~BarClass() {
  Serial << "~BarClass(): Destructing" << endl;
} //destructor

//BarClass::BarClass(BarType eBar, PUnit XLeft, PUnit YBottom) {
BarClass::BarClass(BarDataClass BarData) {
  Serial <<"BarClass::BarClass(BarDataClass): "<< szBarClassFileName << ", "<< szBarClassFileDate << endl;
  Serial << LOG0 << "BarClass::BarClass(): Set BarType to: " << BarData.eBarType << endl;
  switch(BarData.eBarType){
    case eCO2Bar:
      GreenSegment.StartPercent   = 0;
      GreenSegment.SegmentColor   = BECK_GREEN;
      GreenSegment.fStartValue    =   0.0;
      GreenSegment.fEndValue      = 600.0;
       BarSegments.push_back(GreenSegment);

      YellowSegment.StartPercent   = 33;
      YellowSegment.SegmentColor   = BECK_YELLOW;
      YellowSegment.fStartValue    =  600.0;
      YellowSegment.fEndValue      = 1000.0;
      BarSegments.push_back(YellowSegment);

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


void BarClass::Draw(void) {
  Serial << "BarClass::Draw(XLeft, YBottom): Begin"<< endl;
  for (Iterator= BarSegments.begin(); Iterator != BarSegments.end(); Iterator++){
    //Compute segment XLeft, Length and YBottom
    float fSegmentOffset= (Iterator->fStartValue - _BarData.fStartValue);
    float fSegmentStartRatio= (fSegmentOffset / _BarData.fRange);
    Iterator->XLeft= (PUnit)((float)_BarData.Length * fSegmentStartRatio) + _BarData.XLeft;
    Iterator->Length= (PUnit)((Iterator->fRange / _BarData.fRange) * (float)_BarData.Length);
    Iterator->YBottom= _BarData.YBottom;
    Iterator->Draw();
  } //for

  return;
} //Draw

//Last line.
