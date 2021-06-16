const char szBarClassFileName[]  = "BeckBarClass.cpp";
const char szBarClassFileDate[]  = "6/15/21a";

#include <BeckEnviroDataClass.h>
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
  _SegData= SegmentData;
} //constructor

BarSegment::~BarSegment() {
  Serial << "~BarSegment(): Destructing" << endl;
} //destructor


void BarSegment::Draw(float fNewValue, float fLastValue) {
  Serial << LOG0 << "BarSegment::Draw(" << fNewValue << ", " << fLastValue << "): Begin" << endl;
  Serial << LOG0 << "BarSegment::Draw(): fNewValue  = " << fNewValue << endl;
  Serial << LOG0 << "BarSegment::Draw(); BarName    = " << _SegData.BarName << endl;
  Serial << LOG0 << "BarSegment::Draw(); ColorName  = " << _SegData.ColorName << endl;
  Serial << LOG0 << "BarSegment::Draw(): fLastValue = " << fLastValue << endl;
  Serial << LOG0 << "BarSegment::Draw(): fStartValue= " << _SegData.fStartValue << endl;
  Serial << LOG0 << "BarSegment::Draw(): fEndValue  = " << _SegData.fEndValue << endl;
  PUnit PartialLength= 0;

  if (fNewValue == fLastValue){
    Serial << "BarSegment::Draw(): fNewValue same as fLastValue), return"<< endl;
    return;
  } //if(fNewValue==_SegData.fLastValue)

  if ((fNewValue < _SegData.fStartValue) && (fLastValue < _SegData.fStartValue)){
    Serial << "BarSegment::Draw(): fNewValue and fLastValue are less than fStartValue"<< endl;
    Serial << "BarSegment::Draw(): Blank the segment for good measure."<< endl;
    DrawFilledRectangle(_SegData.XLeft, _SegData.YBottom,
                        _SegData.Length, _SegData.Thickness, BackgroundColor);
    return;
  } //if((fNewValue<fStartValue)&&(fLastValue<fStartValue))

  if (fNewValue >= _SegData.fEndValue){
    Serial << "BarSegment::Draw():(fNewValue >= fEndValue), Fill in the whole segment"<< endl;
    //Fill in the whole segment
    DrawFilledRectangle(_SegData.XLeft, _SegData.YBottom,
                        _SegData.Length, _SegData.Thickness, _SegData.Color);
    return;
  } //if(fNewValue>=fEndValue)

  //See if it's in the segment range
  if ((fNewValue > _SegData.fStartValue) && (fNewValue < _SegData.fEndValue)){
    Serial << "BarSegment::Draw():((fNewValue > fStartValue) && (fNewValue < fEndValue))"<< endl;
    if (fNewValue > fLastValue){
      Serial << "BarSegment::Draw():(fNewValue > fLastValue), Partial fill segment"<< endl;
      PUnit PartialLength=
          (PUnit)(((fNewValue- _SegData.fStartValue) / _SegData.fRange) * (float)_SegData.Length);
      Serial << "BarSegment::Call DrawFilledRectangle()"<< endl;
      DrawFilledRectangle(_SegData.XLeft, _SegData.YBottom,
                          PartialLength , _SegData.Thickness, _SegData.Color);
      return;
    } //if(fNewValue>fLastValue)
    else{
      Serial << "BarSegment::Draw():(fNewValue less than fLastValue, Blank & partial fill segment"<< endl;
      //fLastValue is higher than new value
/*
      //Blank whole segment and fill at lower amount than last time
      Serial << "BarSegment::Call DrawFilledRectangle() to blank old segment"<< endl;
      DrawFilledRectangle(_SegData.XLeft , _SegData.YBottom,
                          _SegData.Length, _SegData.Thickness, BackgroundColor);
*/
      //Blank the area between current value and the last value
      PartialLength=
          (PUnit)(((fLastValue - fNewValue) / _SegData.fRange) * (float)_SegData.Length);
      Serial << "BarSegment::Call DrawFilledRectangle() to blank old segment"<< endl;
      DrawFilledRectangle(_SegData.XLeft , _SegData.YBottom,
                          _SegData.Length, _SegData.Thickness, BackgroundColor);

      //Draw the partial segment bar
      PartialLength=
          (PUnit)(((fNewValue- _SegData.fStartValue) / _SegData.fRange) * (float)_SegData.Length);
      Serial << "BarSegment::Call DrawFilledRectangle()" << endl;
      DrawFilledRectangle(_SegData.XLeft, _SegData.YBottom,
                          PartialLength , _SegData.Thickness, _SegData.Color);
      return;
    } //if(fNewValue>fLastValue)else
  } //if((fNewValue>fStartValue)&&(fNewValue<fEndValue))
  else{
    Serial << "BarSegment::Draw(): Not in range from " << _SegData.fStartValue << " to " << _SegData.fEndValue << endl;
  } //if((fNewValue>fStartValue)&&(fNewValue<fEndValue))else
  return;
} //Draw


void BarSegment::DrawFilledRectangle(PUnit NewXLeft, PUnit NewYBottom,
                                     PUnit NewWidth, PUnit NewLength, ColorType NewColor){
  Serial << "BarSegment::DrawFilledRectangle(" << NewXLeft << ", " << NewYBottom << ", " <<
      NewWidth << ", " << NewLength << ", " << NewColor << ")" << endl;
  Serial << "BarSegment::DrawFilledRectangle(): Call RoverLCD.fillRect()"<< endl;
  RoverLCD.fillRect(NewXLeft, NewYBottom, NewWidth, NewLength, NewColor);
  return;
} //DrawFilledRectangle


//BarClass methods
BarClass::BarClass() {
  Serial << "BarClass::BarClass(void): " << szBarClassFileName << ", " << szBarClassFileDate << endl;
} //constructor

BarClass::~BarClass() {
  Serial << "~BarClass(): Destructing" << endl;
} //destructor

BarClass::BarClass(BarData& BarData) {
  Serial << "BarClass::BarClass(BarData&): "<< szBarClassFileName << ", "<< szBarClassFileDate << endl;
  _BarData= BarData;
} //constructor


void BarClass::Draw(float fNewValue, float fLastValue) {
  Serial << "BarClass::Draw("<< fNewValue << ", " << fLastValue << "): Begin" << endl;
  int SegNum;
  //Going from left to right is attempt to remove line on left that remains until next draw
  //for (SegNum= 0; SegNum < 3; SegNum++){
  for (SegNum= 2; SegNum >= 0; SegNum--){
    Serial << "BarClass::Draw(): Call _BarData.BarSegs[" << SegNum << "].Draw(" << fNewValue << ", " << fLastValue << ")" << endl;
    _BarData.BarSegs[SegNum].Draw(fNewValue, fLastValue);
  } //for(SegNum= ...
  Serial << "BarClass::Draw(float fNewValue): return"<< endl;
  return;
} //Draw
//Last line.
