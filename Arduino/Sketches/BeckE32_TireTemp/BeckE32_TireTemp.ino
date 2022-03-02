const char szSketchName[]  = "BeckE32_TireTemp.ino";
const char szFileDate[]    = "3/1/22e";

#include <BeckTireTempDefines.h>
#if DO_OTA
  #include <BeckE32_OTALib.h>
#endif
#include <BeckTireTempDataClass.h>
#include <BeckLogLib.h>
#include <BeckMiniLib.h>
#include <BeckProbeSetClass.h>

#include <Adafruit_GFX.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansOblique18pt7b.h>
#include <WiFi.h>
#include <Streaming.h>

const char* szWebHostName = "TireTemp";

#define min(X, Y)       (((X) < (Y)) ? (X) : (Y))
const UINT16       usTopText_CursorY       =  35;

static  UINT16     usTextSpacing           = 20;
static  UINT16     usDegF_CursorY          = usTopText_CursorY;

static char             sz100CharString[101];

unsigned long           ulNextDisplayMsec   =    0;
unsigned long           ulDisplayPeriodMsec = 2000; //mSec between output to display

const char* szRouterName  = "Aspot24b";
const char* szRouterPW    = "Qazqaz11";

#if DO_ROVER
  WROVER_KIT_LCD     RoverLCD;

  const   ColorType  BackgroundColor         = WROVER_BLACK;
#endif

//Protos
void  setup               (void);
void  loop                (void);
#if DO_ROVER
  void  DisplayBegin        (void);
  void  DisplayClear        (void);
  void  FillScreen          (UINT16 usColor);
  void  DisplayUpdate       (void);
  void  DisplayTemperature  (void);
  void  DisplayLowerBanner  (void);
  void  DisplayText         (UINT16 usCursorX, UINT16 usCursorY, char *pcText,
                             const GFXfont *pFont, UINT8 ucSize, UINT16 usColor);
  void  ClearTextBackground (INT16 sUpperLeftX, INT16 sUpperLeftY, UINT16 usWidth, UINT16 usHeight);
#endif

//Create ProbeSet object
static BeckProbeSetClass _oProbeSet;

void setup(){
  Serial.begin(115200);
  Serial << endl<< LOG0 << "setup(): Begin " << szSketchName << ", " << szFileDate << endl;


#if DO_ROVER
  Serial << LOG0 << "setup(): Call DisplayBegin()" << endl;
  DisplayBegin();
#endif

  // Start WiFi and wait for connection to the network
  WiFi.begin(szRouterName, szRouterPW);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial << endl << "setup(): Connected to " << szRouterName << ", IP address to connect to is " << WiFi.localIP() << endl;

#if DO_OTA
  Serial << "setup(): Call SetupWebServer(" << szWebHostName << ")" << endl;
  SetupWebserver(szWebHostName);
#endif

  Serial << LOG0 << "setup(): Call BuildProbes()" << endl;
  _oProbeSet.BuildProbes();

  Serial << LOG0 << "setup(): return" << endl;
  return;
}  //setup


void loop() {
  _oProbeSet.Handle();
#if DO_ROVER
  DisplayUpdate();
#endif
#if DO_OTA
  HandleOTAWebserver();
#endif
  delay(5000);
  return;
}  //loop()


#if DO_ROVER
void DisplayBegin() {
  Serial << LOG0 << "DisplayBegin(): Call RoverLCD.begin()" << endl;
  RoverLCD.begin();
  RoverLCD.setRotation(1);
  DisplayClear();
  return;
}  //DisplayBegin


void DisplayClear() {
  FillScreen(BackgroundColor);
  return;
}  //DisplayClear


void FillScreen(UINT16 usColor) {
#if DO_ROVER
  RoverLCD.fillScreen(usColor);
#else
#endif
  return;
}  //FillScreen


void DisplayUpdate(void) {
if (millis() > ulNextDisplayMsec){
  ulNextDisplayMsec= millis() + ulDisplayPeriodMsec;
  DisplayTemperature();
} //if (millis()>ulNextDisplayMsec)
DisplayLowerBanner();
return;
}  //DisplayUpdate


void DisplayTemperature() {
  UINT16          usTextCursorX   =  100;
  UINT16          usTextCursorY   =  15;  //Zero for font is lower-left
  UINT16          usTempCursorX   =   0;
  UINT16          usTempCursorY   = 100;
  UINT8           ucSize          =   1;
  ColorType       usColor         = WROVER_WHITE;
  float           fDegFValue      = 0.0;

  if(true || TireTempData.bDegFChanged()) {
    //Erase the currently displayed value by overwriting it with the background color
    float fLastDegFValue= TireTempData.GetLastDegF_Value();
    sprintf(sz100CharString, "%6.1f", fLastDegFValue);
    DisplayText( usTempCursorX, usTempCursorY, sz100CharString, &FreeMonoBold24pt7b, ucSize, BackgroundColor);

    //Display the new value
    fDegFValue= TireTempData.GetDegF_Value();
    sprintf(sz100CharString, "%6.1f", fDegFValue);
    DisplayText( usTempCursorX, usTempCursorY, sz100CharString, &FreeMonoBold24pt7b, ucSize, usColor);

    sprintf(sz100CharString, "Front Tires");
    DisplayText( usTextCursorX, usTextCursorY, sz100CharString, &FreeSans9pt7b, ucSize, usColor);

    usTextCursorX  =  0;
    usTextCursorY += 20;
    sprintf(sz100CharString, "179  167  159    209  104  178");
    DisplayText( usTextCursorX, usTextCursorY, sz100CharString, &FreeSans9pt7b, ucSize, usColor);

    //Set the last value to be the displayed value
    TireTempData.SetLastDegF_Value(fDegFValue);
  } //if(TireTempData.bDegFChanged())
  return;
}  //DisplayTemperature


void DisplayLowerBanner(){
  const GFXfont   *pFont          = &FreeSansOblique18pt7b;
  UINT16          usCursorX       = 45;
  UINT16          usCursorY       = 232;    //Was 72
  UINT8           ucSize          = 1;
  ColorType       usColor         = WROVER_CYAN;

  DisplayText( usCursorX, usCursorY, "Tire Degrees F", pFont, ucSize, usColor);
  return;
} //DisplayLowerBanner


void DisplayText(UINT16 usCursorX, UINT16 usCursorY, char *pcText,
                 const GFXfont *pFont, UINT8 ucSize, UINT16 usColor) {
  //240x320 3.2", 10 lines => 24 pixels/line
#if DO_ROVER
  RoverLCD.setFont(pFont);
  RoverLCD.setTextColor(usColor);
  RoverLCD.setTextSize(ucSize);
  RoverLCD.setTextWrap(false);
  RoverLCD.setCursor(usCursorX, usCursorY);
  RoverLCD.print(pcText);
#else
#endif
  return;
}  //DisplayText


void ClearTextBackground(INT16 sUpperLeftX, INT16 sUpperLeftY, UINT16 usWidth, UINT16 usHeight){
  RoverLCD.fillRect(sUpperLeftX, sUpperLeftY, usWidth, usHeight, BackgroundColor);
  return;
} //ClearTextBackground
#endif
//Last line
