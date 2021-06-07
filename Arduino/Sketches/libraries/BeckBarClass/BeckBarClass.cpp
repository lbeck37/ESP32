const char szBarClassFileName[]  = "BeckBarClass.cpp";
const char szBarClassFileDate[]  = "6/6/21a";

//#include <BeckEnviroDataClass.h>
#include <BeckBarClass.h>
#include <BeckLogLib.h>
#include <Streaming.h>

WROVER_KIT_LCD    RoverLCD;
ColorType         BackgroundColor= WROVER_BLACK;

BarSegmentClass   GreenSegment  = BarSegmentClass();
BarSegmentClass   YellowSegment = BarSegmentClass();
BarSegmentClass   RedSegment    = BarSegmentClass();

//BarSegmentClass methods
BarSegmentClass::BarSegmentClass() {
  Serial << "BarSegmentClass::BarSegmentClass(void): " << szBarClassFileName << ", " << szBarClassFileDate << endl;
} //constructor

BarSegmentClass::~BarSegmentClass() {
  Serial << "~BarSegmentClass(): Destructing" << endl;
} //destructor

void BarSegmentClass::Draw(float fNewValue) {
  Serial << "BarSegmentClass::Draw(" << fNewValue << "): Begin" << endl;
  Serial << "BarSegmentClass::Draw(): fNewValue= "  << fNewValue << endl;
  Serial << "BarSegmentClass::Draw(): fLastValue= " << fLastValue << endl;

  Serial << LOG0 << "BarSegmentClass::Draw(); BarName= " << BarName << endl;
  Serial << LOG0 << "BarSegmentClass::Draw(); ColorName= " << ColorName << endl;
  if (fNewValue == fLastValue){
    Serial << "BarSegmentClass::Draw(): (fNewValue == fLastValue), return"<< endl;
    return;
  } //if(fNewValue==fLastValue

  if ((fNewValue < fStartValue) && (fLastValue < fStartValue)){
    fLastValue= fNewValue;
    Serial << "BarSegmentClass::Draw():((fNewValue<fStartValue)&&(fLastValue<fStartValue)), return"<< endl;
    return;
  } //if((fNewValue<fStartValue)&&(fLastValue<fStartValue))

  if (fNewValue >= fEndValue){
    Serial << "BarSegmentClass::Draw():(fNewValue >= fEndValue), Fill in the whole segment"<< endl;
    //Fill in the whole segment
    fLastValue= fNewValue;
    Serial << "BarSegmentClass::Call DrawFilledRectangle()"<< endl;
    DrawFilledRectangle(XLeft, YBottom, Width, Length, Color);
    return;
  } //if(fNewValue>=fEndValue)

  //See if it's in the segment range
  if ((fNewValue > fStartValue) && (fNewValue < fEndValue)){
    Serial << "BarSegmentClass::Draw():((fNewValue > fStartValue) && (fNewValue < fEndValue))"<< endl;
    if (fNewValue > fLastValue){
      Serial << "BarSegmentClass::Draw():(fNewValue > fLastValue), Partial fill segment"<< endl;
      fLastValue= fNewValue;
      PUnit PartialLength= (PUnit)(((fNewValue- fStartValue) / fRange) * (float)Length);
      Serial << "BarSegmentClass::Call DrawFilledRectangle()"<< endl;
      DrawFilledRectangle(XLeft, YBottom, Width, PartialLength, Color);
      return;
    } //if(fNewValue>fLastValue)
    else{
      Serial << "BarSegmentClass::Draw():(fNewValue > fLastValue)else,Blank&partial fill segment"<< endl;
      fLastValue= fNewValue;
      //fLastValue is higher than new value
      //Blank whole segment and fill at lower amount than last time
      Serial << "BarSegmentClass::Call DrawFilledRectangle() to blank old segment"<< endl;
      DrawFilledRectangle(XLeft, YBottom, Width, Length, BackgroundColor);

      //Draw the partial segment bar
      PUnit PartialLength= (PUnit)(((fNewValue- fStartValue) / fRange) * (float)Length);
      Serial << "BarSegmentClass::Call DrawFilledRectangle()" << endl;
      DrawFilledRectangle(XLeft, YBottom, Width, PartialLength, Color);
      return;
    } //if(fNewValue>fLastValue)else
  } //if((fNewValue>fStartValue)&&(fNewValue<fEndValue))
  else{
    Serial << "BarSegmentClass::Draw(): Not in range from " << fStartValue << " to " << fEndValue << endl;
  } //if((fNewValue>fStartValue)&&(fNewValue<fEndValue))else
  return;
} //Draw


void BarSegmentClass::DrawFilledRectangle(PUnit NewXLeft, PUnit NewYBottom,
                                            PUnit NewWidth, PUnit NewLength, ColorType NewColor){
  Serial << "BarSegmentClass::DrawFilledRectangle(): Call RoverLCD.fillRect()"<< endl;
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
BarClass::BarClass(BarDataClass BarData) {
  Serial <<"BarClass::BarClass(BarDataClass): "<< szBarClassFileName << ", "<< szBarClassFileDate << endl;
  Serial << LOG0 << "BarClass::BarClass(): Set BarType to: " << BarData.eBarType << endl;
  switch(BarData.eBarType){
    case eCO2Bar:
      strcpy(GreenSegment.BarName,    "CO2");
      strcpy(YellowSegment.BarName,   "CO2");
      strcpy(RedSegment.BarName,      "CO2");

      strcpy(GreenSegment.ColorName,  "Green");
      strcpy(YellowSegment.ColorName, "Yellow");
      strcpy(RedSegment.ColorName,    "Red");

      GreenSegment.StartPercent   = 0;
      GreenSegment.Color          = BECK_GREEN;
      GreenSegment.fStartValue    =   0.0;
      GreenSegment.fEndValue      = 600.0;
      //BarSegments.push_back(GreenSegment);
      BarSegmentArray[0]= GreenSegment;

      YellowSegment.StartPercent   = 33;
      YellowSegment.Color          = BECK_YELLOW;
      YellowSegment.fStartValue    =  600.0;
      YellowSegment.fEndValue      = 1000.0;
      //BarSegments.push_back(YellowSegment);
      BarSegmentArray[1]= YellowSegment;

      RedSegment.StartPercent   = 66;
      RedSegment.Color          = BECK_RED;
      RedSegment.fStartValue    = 1000.0;
      RedSegment.fEndValue      = 2000.0;
      //BarSegments.push_back(RedSegment);
      BarSegmentArray[2]= RedSegment;
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
/*

void BarClass::Draw(float fNewValue) {
  Serial << "BarClass::Draw(XLeft, YBottom): Begin"<< endl;
  for (Iterator= BarSegments.begin(); Iterator != BarSegments.end(); Iterator++){
    //Compute segment XLeft, Length and YBottom
    float fSegmentOffset= (Iterator->fStartValue - _BarData.fStartValue);
    float fSegmentStartRatio= (fSegmentOffset / _BarData.fRange);
    Iterator->XLeft= (PUnit)((float)_BarData.Length * fSegmentStartRatio) + _BarData.XLeft;
    Iterator->Length= (PUnit)((Iterator->fRange / _BarData.fRange) * (float)_BarData.Length);
    Iterator->YBottom= _BarData.YBottom;
    Serial << "BarClass::Draw(): Call Iterator->Draw(" << fNewValue << ")" << endl;
    Iterator->Draw(fNewValue);
  } //for(Iterator=BarSegments.begin();...
  Serial << "BarClass::Draw(XLeft, YBottom): return"<< endl;
  return;
} //Draw
*/

void BarClass::Draw(float fNewValue) {
  Serial << "BarClass::Draw("<< fNewValue << "): Begin" << endl;
  int SegmentCount;
  BarSegmentClass   CurrentSegment= BarSegmentClass();
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
