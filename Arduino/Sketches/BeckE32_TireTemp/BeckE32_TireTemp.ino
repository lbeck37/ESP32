const char szSketchName[]  = "BeckE32_TireTemp.ino";
const char szFileDate[]    = "3/4/22c";

#include <BeckTireTempDefines.h>
#if DO_OTA
  #include <BeckE32_OTALib.h>
#endif
#include <BeckTireTempDataClass.h>
#include <BeckLogLib.h>
#include <BeckMiniLib.h>
#include <BeckProbeSetClass.h>

#if DO_ROVER
  #include <WROVER_KIT_LCD.h>
#endif

#include <Adafruit_GFX.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansOblique18pt7b.h>
#include <EasyButtonTouch.h>
#include <WiFi.h>
#include <Streaming.h>

#include <ctime>
#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

//Define a "rational real-time constant" representing 1/60 of a second
using r1= ratio<1, 60>;

const char* szWebHostName = "TireTemp";

#define min(X, Y)       (((X) < (Y)) ? (X) : (Y))
const UINT16       usTopText_CursorY              =  35;

UINT16            usTextSpacing                  = 20;
UINT16            usDegF_CursorY                 = usTopText_CursorY;

char              sz100CharString[101];

unsigned long     ulNextDisplayMsec         =    0;
unsigned long     ulDisplayPeriodMsec       = 2000; //mSec between output to display

unsigned long     ulNextHandleProbesMsec    =    0;
unsigned long     ulHandleProbesPeriodMsec  = 3000; //mSec between handling probes

const char*       szRouterName              = "Aspot24b";
const char*       szRouterPW                = "Qazqaz11";

#if DO_ROVER
  WROVER_KIT_LCD     RoverLCD;

  const   ColorType  BackgroundColor         = WROVER_BLACK;
#endif

//Protos
void  setup                 (void);
void  loop                  (void);
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
void  FlashRGB_LED          (void);

//Create ProbeSet object
BeckProbeSetClass _oProbeSet;

#if true
//EasyButtonTouch RF_Button(_cRF_Button);

#include <EasyButton.h>
uint8_t   ucButtonPin = 15;

EasyButton TestButton(ucButtonPin);    //Defaults: 35msec debounce, Pullup enabled, Returns true on button press

void onPressed(){
  cout << "onPressed(): You pressed the test button.\n";
  Serial << "onPressed(): You pressed the test button.\n";
  return;
} //onPressed
#endif

void setup(){
  Serial.begin(115200);
  Serial << "\n" << LOG0 << "setup(): Begin " << szSketchName << ", " << szFileDate << "\n";


#if DO_ROVER
  Serial << LOG0 << "setup(): Call DisplayBegin()\n";
  DisplayBegin();
#endif
  //FlashRGB_LED();

  // Start WiFi and wait for connection to the network
  WiFi.begin(szRouterName, szRouterPW);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //The following cout statement caused the WiFi.localIP() to not print 192.168.0.197 it was a single integer
  //cout << "\nsetup(): Connected to " << szRouterName << ", IP address to connect to is " << WiFi.localIP() << "\n" << std::endl;
  Serial << "\nsetup(): Connected to " << szRouterName << ", IP address to connect to is " << WiFi.localIP() << "\n";

#if DO_OTA
  Serial << "setup(): Call SetupWebServer(" << szWebHostName << ")\n";
  SetupWebserver(szWebHostName);
#endif

  Serial << LOG0 << "setup(): Call BuildProbes()\n";
  _oProbeSet.BuildProbes();

  Serial << "setup(): Call TestButton.begin()\n";
  TestButton.begin();

  Serial << "setup(): Setup Callback, call TestButton.onPressed(onPressed)\n";
  TestButton.onPressed(onPressed);

  Serial << LOG0 << "setup(): return\n";
  return;
}  //setup


void loop() {
  TestButton.read();   //This has to get called for onPressed() to get called back
  if (millis() > ulNextHandleProbesMsec){
    ulNextHandleProbesMsec= millis() + ulHandleProbesPeriodMsec;
    _oProbeSet.Handle();
  } //if (millis()>ulNextDisplayMsec)
#if DO_ROVER
  DisplayUpdate();
#endif
#if DO_OTA
  HandleOTAWebserver();
#endif
  return;
}  //loop()


#if DO_ROVER
void DisplayBegin() {
  Serial << LOG0 << "DisplayBegin(): Call RoverLCD.begin()\n";
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


void FlashRGB_LED() {
  Serial << LOG0 << "FlashRGB_LED(): Begin\n";
  pinMode(_cRGB_RedPin, OUTPUT);
  pinMode(_cRGB_GreenPin, OUTPUT);
  pinMode(_cRGB_BluePin, OUTPUT);

  //Turn them all off
  digitalWrite(_cRGB_RedPin,    LOW);
  digitalWrite(_cRGB_GreenPin,  LOW);
  digitalWrite(_cRGB_BluePin,   LOW);
  delay(1000);
  //Red on
  digitalWrite(_cRGB_RedPin,    HIGH);
  delay(1000);
  //Green on
  digitalWrite(_cRGB_RedPin,    LOW);
  digitalWrite(_cRGB_GreenPin,  HIGH);
  delay(1000);
  //Blue on
  digitalWrite(_cRGB_GreenPin,  LOW);
  digitalWrite(_cRGB_BluePin,   HIGH);
  delay(1000);
  //All off
  digitalWrite(_cRGB_RedPin,    LOW);
  digitalWrite(_cRGB_GreenPin,  LOW);
  digitalWrite(_cRGB_BluePin,   LOW);
  delay(1000);
  //All on (white)
  digitalWrite(_cRGB_RedPin,    HIGH);
  digitalWrite(_cRGB_GreenPin,  HIGH);
  digitalWrite(_cRGB_BluePin,   HIGH);
  delay(1000);
  //All off
  digitalWrite(_cRGB_RedPin,    LOW);
  digitalWrite(_cRGB_GreenPin,  LOW);
  digitalWrite(_cRGB_BluePin,   LOW);
  delay(1000);
  //Green on
  digitalWrite(_cRGB_GreenPin,  HIGH);

  return;
}  //FlashRGB_LED
//Last line
