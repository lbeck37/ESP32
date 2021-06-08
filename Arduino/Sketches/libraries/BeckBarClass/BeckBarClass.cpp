const char szBarClassFileName[]  = "BeckBarClass.cpp";
const char szBarClassFileDate[]  = "6/8/21a";

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
  _SegmentData= SegmentData;
} //constructor

BarSegment::~BarSegment() {
  Serial << "~BarSegment(): Destructing" << endl;
} //destructor


void BarSegment::Draw(float fNewValue, float fLastValue) {
  Serial << LOG0 << "BarSegment::Draw(" << fNewValue << ", " << fLastValue << "): Begin" << endl;
  Serial << LOG0 << "BarSegment::Draw(): fNewValue  = " << fNewValue << endl;
  Serial << LOG0 << "BarSegment::Draw(); BarName    = " << _SegmentData.BarName << endl;
  Serial << LOG0 << "BarSegment::Draw(); ColorName  = " << _SegmentData.ColorName << endl;
  Serial << LOG0 << "BarSegment::Draw(): fLastValue = " << fLastValue << endl;
  Serial << LOG0 << "BarSegment::Draw(): fStartValue= " << _SegmentData.fStartValue << endl;
  Serial << LOG0 << "BarSegment::Draw(): fEndValue  = " << _SegmentData.fEndValue << endl;
  if (fNewValue == fLastValue){
    Serial << "BarSegment::Draw(): fNewValue same as fLastValue), return"<< endl;
    return;
  } //if(fNewValue==_SegmentData.fLastValue)

  if ((fNewValue < _SegmentData.fStartValue) && (fLastValue < _SegmentData.fStartValue)){
    Serial << "BarSegment::Draw(): fNewValue and fLastValue are less than fStartValue"<< endl;
     return;
  } //if((fNewValue<fStartValue)&&(fLastValue<fStartValue))

  if (fNewValue >= _SegmentData.fEndValue){
    Serial << "BarSegment::Draw():(fNewValue >= fEndValue), Fill in the whole segment"<< endl;
    //Fill in the whole segment
    Serial << "BarSegment::Call DrawFilledRectangle()"<< endl;
/*
    DrawFilledRectangle(_SegmentData.XLeft, _SegmentData.YBottom,
                        _SegmentData.Thickness, _SegmentData.Length, _SegmentData.Color);
*/
    DrawFilledRectangle(_SegmentData.XLeft, _SegmentData.YBottom,
                        _SegmentData.Length, _SegmentData.Thickness, _SegmentData.Color);
    return;
  } //if(fNewValue>=fEndValue)

  //See if it's in the segment range
  if ((fNewValue > _SegmentData.fStartValue) && (fNewValue < _SegmentData.fEndValue)){
    Serial << "BarSegment::Draw():((fNewValue > fStartValue) && (fNewValue < fEndValue))"<< endl;
    if (fNewValue > fLastValue){
      Serial << "BarSegment::Draw():(fNewValue > fLastValue), Partial fill segment"<< endl;
      PUnit PartialLength= (PUnit)(((fNewValue- _SegmentData.fStartValue) / _SegmentData.fRange) * (float)_SegmentData.Length);
      Serial << "BarSegment::Call DrawFilledRectangle()"<< endl;
      //DrawFilledRectangle(_SegmentData.XLeft, _SegmentData.YBottom, _SegmentData.Thickness, PartialLength, _SegmentData.Color);
      DrawFilledRectangle(_SegmentData.XLeft, _SegmentData.YBottom, PartialLength, _SegmentData.Thickness, _SegmentData.Color);
      return;
    } //if(fNewValue>fLastValue)
    else{
      Serial << "BarSegment::Draw():(fNewValue less than fLastValue, Blank & partial fill segment"<< endl;
      //fLastValue is higher than new value
      //Blank whole segment and fill at lower amount than last time
      Serial << "BarSegment::Call DrawFilledRectangle() to blank old segment"<< endl;
      //DrawFilledRectangle(_SegmentData.XLeft, _SegmentData.YBottom, _SegmentData.Thickness, _SegmentData.Length, BackgroundColor);
      DrawFilledRectangle(_SegmentData.XLeft, _SegmentData.YBottom, _SegmentData.Length, _SegmentData.Thickness, BackgroundColor);

      //Draw the partial segment bar
      PUnit PartialLength= (PUnit)(((fNewValue- _SegmentData.fStartValue) / _SegmentData.fRange) * (float)_SegmentData.Length);
      Serial << "BarSegment::Call DrawFilledRectangle()" << endl;
      //DrawFilledRectangle(_SegmentData.XLeft, _SegmentData.YBottom, _SegmentData.Thickness, PartialLength, _SegmentData.Color);
      DrawFilledRectangle(_SegmentData.XLeft, PartialLength, _SegmentData.YBottom, _SegmentData.Thickness, _SegmentData.Color);
      return;
    } //if(fNewValue>fLastValue)else
  } //if((fNewValue>fStartValue)&&(fNewValue<fEndValue))
  else{
    Serial << "BarSegment::Draw(): Not in range from " << _SegmentData.fStartValue << " to " << _SegmentData.fEndValue << endl;
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


void BarClass::SetLowerLeftCorner(PUnit XLeft, PUnit YBottom){
  Serial << "BarClass::SetLowerLeftCorner(" << XLeft << ", " << YBottom << ")" << endl;
  _BarData.XLeft    = XLeft;
  _BarData.YBottom  = YBottom;
  return;
} //SetowerCorner


void BarClass::Draw(float fNewValue) {
  Serial << "BarClass::Draw("<< fNewValue << "): Begin" << endl;
  int SegNum;
  for (SegNum= 0; SegNum < 3; SegNum++){
    float fSegmentOffset= (_BarData.BarSegs[SegNum]._SegmentData.fStartValue - _BarData.fStartValue);
    float fSegmentStartRatio= (fSegmentOffset / _BarData.fRange);

    _BarData.BarSegs[SegNum]._SegmentData.XLeft  = (PUnit)((float)_BarData.Length * fSegmentStartRatio) + _BarData.XLeft;
    _BarData.BarSegs[SegNum]._SegmentData.YBottom= _BarData.YBottom;
    _BarData.BarSegs[SegNum]._SegmentData.Length = (PUnit)((_BarData.BarSegs[SegNum]._SegmentData.fRange / _BarData.fRange) * (float)_BarData.Length);

    Serial << "BarClass::Draw(): Call _BarData.BarSegs[" << SegNum << "].Draw(" << fNewValue << ", " << _fLastValue << ")" << endl;
    _BarData.BarSegs[SegNum].Draw(fNewValue, _fLastValue);
  } //for(Iterator=BarSegments.begin();...
  _fLastValue= fNewValue;
  Serial << "BarClass::Draw(float fNewValue): return"<< endl;
  return;
} //Draw
//Last line.
