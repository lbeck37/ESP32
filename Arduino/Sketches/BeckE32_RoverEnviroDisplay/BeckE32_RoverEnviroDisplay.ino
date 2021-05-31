const char szSketchName[]  = "BeckE32_RoverEnviroDisplay.ino";
const char szFileDate[]    = "5/31/21a";
// 5/26/21, Copied from BeckE32_RoverDisplayTest.ino to isolate white screen problem
#include <BeckI2cClass.h>
#include <BeckGasSensorClass.h>
#include <BeckGasSensorDataClass.h>
#include <BeckLogLib.h>
#include <BeckMiniLib.h>
#include <Adafruit_GFX.h>
#include <WROVER_KIT_LCD.h>
#include <Wire.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansOblique18pt7b.h>
#include <Streaming.h>

#define min(X, Y)     (((X) < (Y)) ? (X) : (Y))

//Digital Pins
static const int       sI2C_SDA              = 26;
static const int       sI2C_SCL              = 27;

static const uint16_t  usBackgroundColor    = WROVER_BLACK;
static const UINT16    usBoostTop           = 90;

WROVER_KIT_LCD    RoverLCD;
static char       sz100CharString[101];

void(* ResetESP32)(void)= 0;        //Hopefully system crashes and reset when this is called.

void setup()   {
  Serial.begin(115200);
  Serial << endl<< LOG0 << "setup(): Begin " << szSketchName << ", " << szFileDate << endl;
  //Serial << LOG0 << "setup(): Call Wire.begin(sI2C_SDA, sI2C_SCL) " << sI2C_SDA << ", " << sI2C_SCL << endl;
  I2C_Object.Setup();
  GasSensor.Setup();
  DisplayBegin();
  return;
}  //setup


void loop() {
  GasSensor.Handle();
  DisplayUpdate();
  return;
}  //loop()


void DisplayBegin() {
  Serial << LOG0 << "DisplayBegin(): Call RoverLCD.begin()" << endl;
  RoverLCD.begin();
  RoverLCD.setRotation(1);
  DisplayClear();
  return;
}  //DisplayBegin


void DisplayUpdate(void) {
  DisplayCO2();
  DisplayVOC();
  DisplayLowerBanner();
  return;
}  //DisplayUpdate


void DisplayClear() {
  FillScreen(usBackgroundColor);
  return;
}  //DisplayClear


void FillScreen(UINT16 usColor) {
  RoverLCD.fillScreen(usColor);
  return;
}  //FillScreen


void DisplayText(UINT16 usCursorX, UINT16 usCursorY, char *pcText,
                 const GFXfont *pFont, UINT8 ucSize, UINT16 usColor) {
  //240x320 3.2", 10 lines => 24 pixels/line
  RoverLCD.setFont(pFont);
  RoverLCD.setTextColor(usColor);
  RoverLCD.setTextSize(ucSize);
  RoverLCD.setTextWrap(false);
  RoverLCD.setCursor(usCursorX, usCursorY);
  RoverLCD.print(pcText);
  return;
}  //DisplayText


void ClearTextBackground(INT16 sUpperLeftX, INT16 sUpperLeftY, UINT16 usWidth, UINT16 usHeight){
  RoverLCD.fillRect(sUpperLeftX, sUpperLeftY, usWidth, usHeight, usBackgroundColor);
  return;
} //ClearTextBackground


void DisplayLine(const GFXfont stFont, UINT16 usColor, UINT16 usCursorX, UINT16 usCursorY, UINT16 usClearWidth, UINT16 usClearHeight,
                 char szText[], bool bClearText= true, UINT8 ucSize= 1) {
  INT16           sClearXstart    = usCursorX - 10;
  INT16           sClearYstart    = usCursorY - 18;

  if(bClearText){
    ClearTextBackground(sClearXstart, sClearYstart, usClearWidth, usClearHeight);
  }
  DisplayText( usCursorX, usCursorY, szText, &stFont, ucSize, usColor);
  return;
} //DisplayLine


void DisplayLowerBanner(){
  const GFXfont   *pFont          = &FreeSansOblique18pt7b;
  UINT16          usCursorX       = 7;
  UINT16          usCursorY       = 232;    //Was 72
  UINT8           ucSize          = 1;
  UINT16          usColor         = WROVER_CYAN;

  DisplayText( usCursorX, usCursorY, "      Air Quality", pFont, ucSize, usColor);
  return;
} //DisplayLowerBanner


void DisplayCO2() {
  UINT16          usCharWidth     = 25;
  UINT16          usCursorX       = 0;
  UINT16          usCursorY       = 30;   //GFX fonts Y is bottom
  UINT8           ucSize          = 1;
  UINT16          usColor         = WROVER_WHITE;
  INT16           sClearLeftX     = usCursorX;
  INT16           sClearTopY      = 0;
  UINT16          usClearWidth    = 120;
  UINT16          usClearHeight   = 35;
  static UINT16   usLastClearWidth= 0;

  if(GasSensorData.bCO2Changed()) {
    UINT16 CO2Value= GasSensorData.GetCO2_Value();
    sprintf(sz100CharString, "%6d", CO2Value);
    //Calculate width to clear based on number of characters + 2, use that unless last width was bigger
    usClearWidth= (strlen(sz100CharString) + 2) * usCharWidth;
    usClearWidth= std::max(usClearWidth, usLastClearWidth);
    usLastClearWidth= usClearWidth;
    ClearTextBackground(sClearLeftX, sClearTopY, usClearWidth, usClearHeight);
    DisplayLine(FreeMonoBold24pt7b, usColor, usCursorX, usCursorY, usClearWidth, usClearHeight, sz100CharString, false, ucSize);

    usCursorX= 50;
    usCursorY += 20;
    sprintf(sz100CharString, "CO2 ppm");
    DisplayLine(FreeSans9pt7b, usColor, usCursorX, usCursorY, usClearWidth, usClearHeight, sz100CharString, false);
  } //if(GasSensorData.bCO2Changed())
  return;
}  //DisplayCO2


void DisplayVOC() {
  UINT16          usCharWidth     = 25;
  UINT16          usCursorX       = 0;
  UINT16          usCursorY       = usBoostTop;   //GFX fonts Y is bottom 90
  UINT8           ucSize          = 1;
  UINT16          usColor         = WROVER_WHITE;
  INT16           sClearLeftX     = usCursorX;
  INT16           sClearTopY      = usCursorY - 32;
  UINT16          usClearWidth    = 120;
  UINT16          usClearHeight   = 40;
  static UINT16   usLastClearWidth= 0;

  if(GasSensorData.bVOCChanged()) {
    UINT16  VOCValue_ppm      = GasSensorData.GetVOC_Value();
    float   VOC_to_mg_per_m3  = 3.23;
    float   VOC_mgPerM3       = (float)VOCValue_ppm * VOC_to_mg_per_m3;
    sprintf(sz100CharString, "%6.1f", VOC_mgPerM3);
    //Calculate width to clear based on number of characters + 2, use that unless last width was bigger
    usClearWidth= (strlen(sz100CharString) + 2) * usCharWidth;
    usClearWidth= std::max(usClearWidth, usLastClearWidth);
    usLastClearWidth= usClearWidth;
    ClearTextBackground(sClearLeftX, sClearTopY, usClearWidth, usClearHeight);
    DisplayLine(FreeMonoBold24pt7b, usColor, usCursorX, usCursorY, usClearWidth, usClearHeight, sz100CharString, false, ucSize);

    usCursorX= 50;
    usCursorY += 20;
    sprintf(sz100CharString, "VOC mg/m^3");
    DisplayLine(FreeSans9pt7b, usColor, usCursorX, usCursorY, usClearWidth, usClearHeight, sz100CharString, false);
  } //if(GasSensorData.bVOCChanged())
  return;
}  //DisplayVOC
//Last line
