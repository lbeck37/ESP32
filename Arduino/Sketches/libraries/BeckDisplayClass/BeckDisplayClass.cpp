const char szSystemFileName[]  = "BeckDisplayClass.cpp";
const char szSystemFileDate[]  = "3/31/22c";

#include <BeckDisplayClass.h>
#include <BeckLogLib.h>
#include <Adafruit_GFX.h>
#include <Streaming.h>
#include <exception>
#include <stdexcept>

BeckDisplayClass::BeckDisplayClass() {
  Serial << "BeckDisplayClass(): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
  return;
} //constructor

BeckDisplayClass::BeckDisplayClass(BeckDataMgrClass* poDataMgr) {
  Serial << "BeckDisplayClass(poDataMgr): CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
  _poDataMgr= poDataMgr;
  return;
} //constructor

BeckDisplayClass::~BeckDisplayClass() {
  Serial << "~BeckDisplayClass(): Destructor, deleting _poTCoupleSensor" << endl;
  return;
} //destructor


void BeckDisplayClass::DisplayBegin() {
  Serial << LOG0 << "DisplayBegin(): Call RoverLCD.begin()\n";
  RoverLCD.begin();
  RoverLCD.setRotation(1);
  DisplayClear();
  return;
}  //DisplayBegin


void BeckDisplayClass::DisplaySensorSet(int wSensorSetID) {
  Serial << "BeckDisplayClass::DisplaySensorSet(): wSensorSetID= " << wSensorSetID << endl;
  if (wSensorSetID == _wLogSensorSetID){
    Serial << "BeckDisplayClass::DisplaySensorSet(): Call DisplayLogTemps()" << endl;
    //DisplayLogTemps(37.0, 38.0, 39.0);
    DisplayLogTemps("This is a test");
  } //if (wSensorSetID==_wLogSensorSetID)
  else{
    Serial << "BeckDisplayClass::DisplaySensorSet(): Call DisplayTemperature()" << endl;
    DisplayTemperature();
  } //if (wSensorSetID==_wLogSensorSetID)else
  Serial << "BeckDisplayClass::DisplaySensorSet(): Done" << endl;
  return;
}  //DisplaySensorSet


/*
void BeckDisplayClass::DisplayLogTemps(float fDegf1, float fDegf2, float fDegf3){
  Serial << "BeckDisplayClass::DisplayLogTemps(" << fDegf1 << ", " << fDegf2 << ", " << fDegf3 << "): Begin" << endl;
*/
void BeckDisplayClass::DisplayLogTemps(char* szLogString){
  Serial << "BeckDisplayClass::DisplayLogTemps(): Begin: szLogString= " << szLogString << endl;
  const GFXfont   *pFont        = &FreeSansOblique18pt7b;
  uint16_t        usCursorX     = 45;
  uint16_t        usCursorY     = 232;    //Was 72
  uint8_t         ucSize        = 1;
  ColorType       usColor       = WROVER_CYAN;

  //sprintf(sz100CharString, "%6.1f   %6.1f   %6.1f", fDegf1, fDegf2, fDegf3);
  Serial << "BeckDisplayClass::DisplayLogTemps(): Call DisplayText() String= " << szLogString << endl;
  //Serial << "BeckDisplayClass::DisplayLogTemps(): Call DisplayText() String= not printed"  << endl;
  Serial << "BeckDisplayClass::DisplayLogTemps(): I haven't crashed but I haven't called DisplayText() yet" << endl;

  //DisplayText( usCursorX, usCursorY, sz100CharString, pFont, ucSize, usColor);
  //DisplayText( usCursorX, usCursorY, szLogString, pFont, ucSize, usColor);

  Serial << "BeckDisplayClass::DisplayLogTemps(): After call to DisplayText()" << endl;

  return;
} //DisplayLogTemps(float,float,float)


void BeckDisplayClass::DisplayClear() {
  FillScreen(BackgroundColor);
  return;
}  //DisplayClear

void BeckDisplayClass::FillScreen(uint16_t usColor) {
  RoverLCD.fillScreen(usColor);
  return;
}  //FillScreen


void BeckDisplayClass::DisplayTemperature() {
  uint16_t          usTextCursorX   =  100;
  uint16_t          usTextCursorY   =  15;  //Zero for font is lower-left
  uint16_t          usTempCursorX   =   0;
  uint16_t          usTempCursorY   = 100;
  uint8_t           ucSize          =   1;
  ColorType       usColor         = WROVER_WHITE;
  float           fDegFValue      = 0.0;

  //if(true || TireTempData.bDegFChanged()) {
  if(true) {
    //Erase the currently displayed value by overwriting it with the background color
/*
    float fLastDegFValue= TireTempData.GetLastDegF_Value();
    sprintf(sz100CharString, "%6.1f", fLastDegFValue);
*/
    sprintf(sz100CharString, "%6.1f", 37.37);
    DisplayText( usTempCursorX, usTempCursorY, sz100CharString, &FreeMonoBold24pt7b, ucSize, BackgroundColor);

    //Display the new value
/*
    fDegFValue= TireTempData.GetDegF_Value();
    sprintf(sz100CharString, "%6.1f", fDegFValue);
    DisplayText( usTempCursorX, usTempCursorY, sz100CharString, &FreeMonoBold24pt7b, ucSize, usColor);
*/

    sprintf(sz100CharString, "Front Tires");
    DisplayText( usTextCursorX, usTextCursorY, sz100CharString, &FreeSans9pt7b, ucSize, usColor);

    usTextCursorX  =  0;
    usTextCursorY += 20;
    sprintf(sz100CharString, "179  167  159    209  104  178");
    DisplayText( usTextCursorX, usTextCursorY, sz100CharString, &FreeSans9pt7b, ucSize, usColor);

    //Set the last value to be the displayed value
    //TireTempData.SetLastDegF_Value(fDegFValue);
  } //if(TireTempData.bDegFChanged())
  return;
}  //DisplayTemperature


void BeckDisplayClass::DisplayText(uint16_t usCursorX, uint16_t usCursorY, char *pcText,
                 const GFXfont *pFont, uint8_t ucSize, uint16_t usColor) {
  //240x320 3.2", 10 lines => 24 pixels/line
  RoverLCD.setFont(pFont);
  RoverLCD.setTextColor(usColor);
  RoverLCD.setTextSize(ucSize);
  RoverLCD.setTextWrap(false);
  RoverLCD.setCursor(usCursorX, usCursorY);
  RoverLCD.print(pcText);
  return;
}  //DisplayText

void BeckDisplayClass::ClearTextBackground(INT16 sUpperLeftX, INT16 sUpperLeftY, uint16_t usWidth, uint16_t usHeight){
  RoverLCD.fillRect(sUpperLeftX, sUpperLeftY, usWidth, usHeight, BackgroundColor);
  return;
} //ClearTextBackground
//Last line.
