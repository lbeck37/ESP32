const char szSketchName[]  = "BeckE32_TireTemp.ino";	//From BeckE32_EnviroDisplay.ino, 6/16/21c
const char szFileDate[]    = "2/21/22q";

#define DO_OTA          true
#define DO_ROVER        true

#include <BeckBiotaDefines.h>         //Set DO_ROVER to true to display to ROVER
#if DO_OTA
  #include <BeckE32_OTALib.h>
#endif
#include <BeckEnviroDataClass.h>
#include <BeckLogLib.h>
#include <BeckMiniLib.h>
#include <BeckTempProbeClass.h>

#include <Adafruit_GFX.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansOblique18pt7b.h>
#include <WiFi.h>
#include <Streaming.h>

const char* szWebHostName = "TireTemp";

#define min(X, Y)       (((X) < (Y)) ? (X) : (Y))
#if DO_ROVER
  const UINT16     usTopText_CursorY       =  35;
#else
  const UINT16     usTopText_CursorY       =  35;
#endif

static  UINT16     usTextSpacing           = 20;
static  UINT16     usCO2_CursorY           = usTopText_CursorY;
static  UINT16     usVOC_CursorY           = usCO2_CursorY   + usTextSpacing;
static  UINT16     usDegF_CursorY          = usVOC_CursorY   + usTextSpacing;
static  UINT16     usRH_CursorY            = usDegF_CursorY  + usTextSpacing;
const   ColorType  BackgroundColor         = WROVER_BLACK;

static char             sz100CharString[101];

unsigned long           ulNextDisplayMsec   =    0;
unsigned long           ulDisplayPeriodMsec = 2000; //mSec between output to display

void              DisplayTemperature  (void);

const char* szRouterName  = "Aspot24b";
const char* szRouterPW    = "Qazqaz11";

extern WROVER_KIT_LCD     RoverLCD;

void setup()   {
  Serial.begin(115200);
  Serial << endl<< LOG0 << "setup(): Begin " << szSketchName << ", " << szFileDate << endl;

  // Start WiFi and wait for connection to the network
  WiFi.begin(szRouterName, szRouterPW);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial << endl << "setup(): Connected to " << szRouterName << ", IP address to connect to is " << WiFi.localIP() << endl;

  Serial << LOG0 << "setup(): Call TempAndHumidSensor.Setup()" << endl;
  TempProbe.Setup();

  Serial << LOG0 << "setup(): Call DisplayBegin()" << endl;
  DisplayBegin();

#if DO_OTA
  Serial << "setup(): Call SetupWebServer(" << szWebHostName << ")" << endl;
  SetupWebserver(szWebHostName);
#endif

  Serial << LOG0 << "setup(): return" << endl;
  return;
}  //setup


void loop() {
  TempProbe.Handle();
  DisplayUpdate();
#if DO_OTA
  HandleOTAWebserver();
#endif
  delay(1000);
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
  if (millis() > ulNextDisplayMsec){
    ulNextDisplayMsec= millis() + ulDisplayPeriodMsec;
    DisplayTemperature();
  } //if (millis()>ulNextDisplayMsec)
  DisplayLowerBanner();
  return;
}  //DisplayUpdate


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
#if DO_ROVER
  RoverLCD.fillRect(sUpperLeftX, sUpperLeftY, usWidth, usHeight, BackgroundColor);
#else
#endif
  return;
} //ClearTextBackground


void DisplayLowerBanner(){
  const GFXfont   *pFont          = &FreeSansOblique18pt7b;
  UINT16          usCursorX       = 7;
  UINT16          usCursorY       = 232;    //Was 72
  UINT8           ucSize          = 1;
  //UINT16          usColor         = WROVER_CYAN;
  ColorType       usColor         = WROVER_CYAN;

  DisplayText( usCursorX, usCursorY, "      Air Quality", pFont, ucSize, usColor);
  return;
} //DisplayLowerBanner


void DisplayTemperature() {
  UINT16          usCursorX       = 0;
  UINT16          usCursorY       = usDegF_CursorY;   //GFX fonts Y is bottom
  UINT8           ucSize          = 1;
  ColorType       usColor         = WROVER_WHITE;
  float           fDegFValue       = 0.0;

  if(EnviroData.bDegFChanged()) {
    //Erase the currently displayed value by overwriting it with the background color
    float fLastDegFValue= EnviroData.GetLastDegF_Value();
    sprintf(sz100CharString, "%6.1f", fLastDegFValue);
    DisplayText( usCursorX, usCursorY, sz100CharString, &FreeMonoBold24pt7b, ucSize, BackgroundColor);

    //Display the new value
    fDegFValue= EnviroData.GetDegF_Value();
    sprintf(sz100CharString, "%6.1f", fDegFValue);
    DisplayText( usCursorX, usCursorY, sz100CharString, &FreeMonoBold24pt7b, ucSize, usColor);

    usCursorX= 50;
    usCursorY += 20;
    sprintf(sz100CharString, "Temperature");
    DisplayText( usCursorX, usCursorY, sz100CharString, &FreeSans9pt7b, ucSize, usColor);

/*
    //Draw the bar
    DegFBar.Draw(fDegFValue, fLastDegFValue);
*/

    //Set the last value to be the displayed value
    EnviroData.SetLastDegF_Value(fDegFValue);
  } //if(EnviroData.bDegFChanged())
  return;
}  //DisplayTemperature
//Last line
