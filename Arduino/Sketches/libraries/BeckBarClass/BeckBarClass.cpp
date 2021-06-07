const char szBarClassFileName[]  = "BeckBarClass.cpp";
const char szBarClassFileDate[]  = "6/7/21d";

//#include <BeckEnviroDataClass.h>
#include <BeckBarClass.h>
#include <BeckLogLib.h>
#include <Streaming.h>

WROVER_KIT_LCD    RoverLCD;
ColorType         BackgroundColor= WROVER_BLACK;

//SegmentData methods
SegmentData::SegmentData() {
  Serial << "SegmentData::SegmentData(void): " << szBarClassFileName << ", " << szBarClassFileDate << endl;
} //constructor

SegmentData::~SegmentData() {
  Serial << "~SegmentData(): Destructing" << endl;
} //destructor


//BarData methods
BarData::BarData() {
  Serial << "BarData::BarData(void): " << szBarClassFileName << ", " << szBarClassFileDate << endl;
} //constructor

BarData::~BarData() {
  Serial << "~BarData(): Destructing" << endl;
} //destructor


//BarSegment methods
BarSegment::BarSegment() {
  Serial << "BarSegment::BarSegment(void): " << szBarClassFileName << ", " << szBarClassFileDate << endl;
} //constructor

BarSegment::BarSegment(SegmentData& SegmentData) {
  Serial << "BarSegment::BarSegment(SegmentData&): " << szBarClassFileName << ", " << szBarClassFileDate << endl;
} //constructor

BarSegment::~BarSegment() {
  Serial << "~BarSegment(): Destructing" << endl;
} //destructor

void BarSegment::Draw(float fNewValue) {
  Serial << "BarSegment::Draw(" << fNewValue << "): Begin" << endl;
  Serial << "BarSegment::Draw(): fNewValue= "  << fNewValue << endl;
  Serial << "BarSegment::Draw(): fLastValue= " << fLastValue << endl;

  Serial << LOG0 << "BarSegment::Draw(); BarName= " << BarName << endl;
  Serial << LOG0 << "BarSegment::Draw(); ColorName= " << ColorName << endl;
  if (fNewValue == fLastValue){
    Serial << "BarSegment::Draw(): (fNewValue == fLastValue), return"<< endl;
    return;
  } //if(fNewValue==fLastValue

  if ((fNewValue < fStartValue) && (fLastValue < fStartValue)){
    fLastValue= fNewValue;
    Serial << "BarSegment::Draw():((fNewValue<fStartValue)&&(fLastValue<fStartValue)), return"<< endl;
    return;
  } //if((fNewValue<fStartValue)&&(fLastValue<fStartValue))

  if (fNewValue >= fEndValue){
    Serial << "BarSegment::Draw():(fNewValue >= fEndValue), Fill in the whole segment"<< endl;
    //Fill in the whole segment
    fLastValue= fNewValue;
    Serial << "BarSegment::Call DrawFilledRectangle()"<< endl;
    DrawFilledRectangle(XLeft, YBottom, Width, Length, Color);
    return;
  } //if(fNewValue>=fEndValue)

  //See if it's in the segment range
  if ((fNewValue > fStartValue) && (fNewValue < fEndValue)){
    Serial << "BarSegment::Draw():((fNewValue > fStartValue) && (fNewValue < fEndValue))"<< endl;
    if (fNewValue > fLastValue){
      Serial << "BarSegment::Draw():(fNewValue > fLastValue), Partial fill segment"<< endl;
      fLastValue= fNewValue;
      PUnit PartialLength= (PUnit)(((fNewValue- fStartValue) / fRange) * (float)Length);
      Serial << "BarSegment::Call DrawFilledRectangle()"<< endl;
      DrawFilledRectangle(XLeft, YBottom, Width, PartialLength, Color);
      return;
    } //if(fNewValue>fLastValue)
    else{
      Serial << "BarSegment::Draw():(fNewValue > fLastValue)else,Blank&partial fill segment"<< endl;
      fLastValue= fNewValue;
      //fLastValue is higher than new value
      //Blank whole segment and fill at lower amount than last time
      Serial << "BarSegment::Call DrawFilledRectangle() to blank old segment"<< endl;
      DrawFilledRectangle(XLeft, YBottom, Width, Length, BackgroundColor);

      //Draw the partial segment bar
      PUnit PartialLength= (PUnit)(((fNewValue- fStartValue) / fRange) * (float)Length);
      Serial << "BarSegment::Call DrawFilledRectangle()" << endl;
      DrawFilledRectangle(XLeft, YBottom, Width, PartialLength, Color);
      return;
    } //if(fNewValue>fLastValue)else
  } //if((fNewValue>fStartValue)&&(fNewValue<fEndValue))
  else{
    Serial << "BarSegment::Draw(): Not in range from " << fStartValue << " to " << fEndValue << endl;
  } //if((fNewValue>fStartValue)&&(fNewValue<fEndValue))else
  return;
} //Draw

void BarSegment::DrawFilledRectangle(PUnit NewXLeft, PUnit NewYBottom,
                                          PUnit NewWidth, PUnit NewLength, ColorType NewColor){
  Serial << "BarSegment::DrawFilledRectangle(): Call RoverLCD.fillRect()"<< endl;
  RoverLCD.fillRect(NewXLeft, NewYBottom, NewWidth, NewLength, NewColor);
  return;
} //DrawFilledRectangle


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
BarClass::BarClass(BarData& BarData) {
  Serial <<"BarClass::BarClass(BarData&): "<< szBarClassFileName << ", "<< szBarClassFileDate << endl;
  //Serial << LOG0 << "BarClass::BarClass(): Set BarType to: " << BarData.eBarType << endl;
  _BarData= BarData;
} //constructor

void BarClass::Draw(float fNewValue) {
  Serial << "BarClass::Draw("<< fNewValue << "): Begin" << endl;
  int SegmentCount;
  BarSegment   CurrentSegment= BarSegment();
  for (SegmentCount= 0; SegmentCount < 3; SegmentCount++){
    //Compute segment XLeft, Length and YBottom
    CurrentSegment= BarSegmentArray[SegmentCount];

    float fSegmentOffset= (CurrentSegment.fStartValue - _BarData.fStartValue);
    float fSegmentStartRatio= (fSegmentOffset / _BarData.fRange);
    CurrentSegment.XLeft= (PUnit)((float)_BarData.Length * fSegmentStartRatio) + _BarData.XLeft;
    CurrentSegment.Length= (PUnit)((CurrentSegment.fRange / _BarData.fRange) * (float)_BarData.Length);
    CurrentSegment.YBottom= _BarData.YBottom;
    Serial << "BarClass::Draw(): Call CurrentSegment.Draw(" << fNewValue << ")" << endl;
    CurrentSegment.Draw(fNewValue);
  } //for(Iterator=BarSegments.begin();...
  Serial << "BarClass::Draw(XLeft, YBottom): return"<< endl;
  return;
} //Draw
//Last line.
