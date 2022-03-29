const char szSystemFileName[]  = "BeckTireTempDisplayClass.cpp";
const char szSystemFileDate[]  = "3/19/22b";

#include <BeckTireTempDisplayClass.h>
#include <BeckLogLib.h>
#include <Adafruit_GFX.h>
//#include <WROVER_KIT_LCD.h>
#include <Streaming.h>

BeckTireTempDisplayClass::BeckTireTempDisplayClass(void) {
  Serial << "BeckTireTempDisplayClass(void): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
  return;
} //constructor

BeckTireTempDisplayClass::~BeckTireTempDisplayClass() {
  Serial << "~BeckTireTempDisplayClass(): Destructor, deleting _poTCoupleSensor" << endl;
  return;
} //destructor


void BeckTireTempDisplayClass::DisplayBegin() {
  Serial << LOG0 << "DisplayBegin(): Call RoverLCD.begin()\n";
  RoverLCD.begin();
  RoverLCD.setRotation(1);
  DisplayClear();
  return;
}  //DisplayBegin


void BeckTireTempDisplayClass::DisplayUpdate(int wSensorID) {
/*
if (millis() > ulNextDisplayMsec){
  ulNextDisplayMsec= millis() + ulDisplayPeriodMsec;
  DisplayTemperature();
  DisplayLowerBanner();
} //if (millis()>ulNextDisplayMsec)
*/
return;
}  //DisplayUpdate


void BeckTireTempDisplayClass::DisplayClear() {
  FillScreen(BackgroundColor);
  return;
}  //DisplayClear


void BeckTireTempDisplayClass::FillScreen(uint16_t usColor) {
  RoverLCD.fillScreen(usColor);
  return;
}  //FillScreen


void BeckTireTempDisplayClass::DisplayTemperature() {
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


void BeckTireTempDisplayClass::DisplayLowerBanner(){
  const GFXfont   *pFont          = &FreeSansOblique18pt7b;
  uint16_t          usCursorX       = 45;
  uint16_t          usCursorY       = 232;    //Was 72
  uint8_t           ucSize          = 1;
  ColorType       usColor         = WROVER_CYAN;

/*
  sprintf(sz100CharString, "%6.1f", 37.37);
  DisplayText( usCursorX, usCursorY, "Tire Degrees F", pFont, ucSize, usColor);
*/
  sprintf(sz100CharString, "%s", "Tire Degrees F");
  DisplayText( usCursorX, usCursorY, sz100CharString, pFont, ucSize, usColor);
  return;
} //DisplayLowerBanner


void BeckTireTempDisplayClass::DisplayText(uint16_t usCursorX, uint16_t usCursorY, char *pcText,
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


void BeckTireTempDisplayClass::ClearTextBackground(INT16 sUpperLeftX, INT16 sUpperLeftY, uint16_t usWidth, uint16_t usHeight){
  RoverLCD.fillRect(sUpperLeftX, sUpperLeftY, usWidth, usHeight, BackgroundColor);
  return;
} //ClearTextBackground

//Last line.
