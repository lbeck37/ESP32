const char szBarClassFileName[]  = "BeckBarClass.cpp";
const char szBarClassFileDate[]  = "6/7/21j";

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

void BarSegment::Draw(float fNewValue) {
  Serial << "BarSegment::Draw(" << fNewValue << "): Begin" << endl;
  Serial << "BarSegment::Draw(): fNewValue= "  << fNewValue << endl;
  Serial << "BarSegment::Draw(): fLastValue= " << _SegmentData.fLastValue << endl;

  Serial << LOG0 << "BarSegment::Draw(); BarName= " << _SegmentData.BarName << endl;
  Serial << LOG0 << "BarSegment::Draw(); ColorName= " << _SegmentData.ColorName << endl;
  if (fNewValue == _SegmentData.fLastValue){
    Serial << "BarSegment::Draw(): (fNewValue == fLastValue), return"<< endl;
    return;
  } //if(fNewValue==fLastValue

  if ((fNewValue < _SegmentData.fStartValue) && (_SegmentData.fLastValue < _SegmentData.fStartValue)){
    _SegmentData.fLastValue= fNewValue;
    Serial << "BarSegment::Draw():((fNewValue<fStartValue)&&(fLastValue<fStartValue)), return"<< endl;
    return;
  } //if((fNewValue<fStartValue)&&(fLastValue<fStartValue))

  if (fNewValue >= _SegmentData.fEndValue){
    Serial << "BarSegment::Draw():(fNewValue >= fEndValue), Fill in the whole segment"<< endl;
    //Fill in the whole segment
    _SegmentData.fLastValue= fNewValue;
    Serial << "BarSegment::Call DrawFilledRectangle()"<< endl;
    DrawFilledRectangle(_SegmentData.XLeft, _SegmentData.YBottom,
                        _SegmentData.Width, _SegmentData.Length, _SegmentData.Color);
    return;
  } //if(fNewValue>=fEndValue)

  //See if it's in the segment range
  if ((fNewValue > _SegmentData.fStartValue) && (fNewValue < _SegmentData.fEndValue)){
    Serial << "BarSegment::Draw():((fNewValue > fStartValue) && (fNewValue < fEndValue))"<< endl;
    if (fNewValue > _SegmentData.fLastValue){
      Serial << "BarSegment::Draw():(fNewValue > fLastValue), Partial fill segment"<< endl;
      _SegmentData.fLastValue= fNewValue;
      PUnit PartialLength= (PUnit)(((fNewValue- _SegmentData.fStartValue) / _SegmentData.fRange) * (float)_SegmentData.Length);
      Serial << "BarSegment::Call DrawFilledRectangle()"<< endl;
      DrawFilledRectangle(_SegmentData.XLeft, _SegmentData.YBottom, _SegmentData.Width, PartialLength, _SegmentData.Color);
      return;
    } //if(fNewValue>fLastValue)
    else{
      Serial << "BarSegment::Draw():(fNewValue > fLastValue)else,Blank&partial fill segment"<< endl;
      _SegmentData.fLastValue= fNewValue;
      //fLastValue is higher than new value
      //Blank whole segment and fill at lower amount than last time
      Serial << "BarSegment::Call DrawFilledRectangle() to blank old segment"<< endl;
      DrawFilledRectangle(_SegmentData.XLeft, _SegmentData.YBottom, _SegmentData.Width, _SegmentData.Length, BackgroundColor);

      //Draw the partial segment bar
      PUnit PartialLength= (PUnit)(((fNewValue- _SegmentData.fStartValue) / _SegmentData.fRange) * (float)_SegmentData.Length);
      Serial << "BarSegment::Call DrawFilledRectangle()" << endl;
      DrawFilledRectangle(_SegmentData.XLeft, _SegmentData.YBottom, _SegmentData.Width, PartialLength, _SegmentData.Color);
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

//BarClass::BarClass(BarType eBar, PUnit XLeft, PUnit YBottom) {
BarClass::BarClass(BarData& BarData) {
  Serial <<"BarClass::BarClass(BarData&): "<< szBarClassFileName << ", "<< szBarClassFileDate << endl;
  //Serial << LOG0 << "BarClass::BarClass(): Set BarType to: " << BarData.eBarType << endl;
  _BarData= BarData;
} //constructor


void BarClass::SetLowerLeftCorner(PUnit XLeft, PUnit YBottom){
  _BarData.XLeft    = XLeft;
  _BarData.YBottom  = YBottom;
  return;
} //SetowerCorner

void BarClass::Draw(float fNewValue) {
  Serial << "BarClass::Draw("<< fNewValue << "): Begin" << endl;
  int SegmentCount;
  //BarSegment   CurrentSegment= BarSegment();
  BarSegment   CurrentSegment;
  for (SegmentCount= 0; SegmentCount < 3; SegmentCount++){
    CurrentSegment= _BarData.BarSegmentArray[SegmentCount];

    float fSegmentOffset= (CurrentSegment._SegmentData.fStartValue - _BarData.fStartValue);
    float fSegmentStartRatio= (fSegmentOffset / _BarData.fRange);

    CurrentSegment._SegmentData.XLeft  = (PUnit)((float)_BarData.Length * fSegmentStartRatio) + _BarData.XLeft;
    CurrentSegment._SegmentData.YBottom= _BarData.YBottom;
    CurrentSegment._SegmentData.Length = (PUnit)((CurrentSegment._SegmentData.fRange / _BarData.fRange) * (float)_BarData.Length);

    Serial << "BarClass::Draw(): Call CurrentSegment.Draw(" << fNewValue << ")" << endl;
    CurrentSegment.Draw(fNewValue);
  } //for(Iterator=BarSegments.begin();...
  Serial << "BarClass::Draw(XLeft, YBottom): return"<< endl;
  return;
} //Draw
//Last line.
