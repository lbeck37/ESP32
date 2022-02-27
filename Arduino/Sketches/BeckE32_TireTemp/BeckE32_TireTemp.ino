const char szSketchName[]  = "BeckE32_TireTemp.ino";	//From BeckE32_EnviroDisplay.ino, 6/16/21c
const char szFileDate[]    = "2/27/22c";

#define DO_OTA          true
#define DO_ROVER        true

#include <BeckBiotaDefines.h>         //Set DO_ROVER to true to display to ROVER
#if DO_OTA
  #include <BeckE32_OTALib.h>
#endif
#include <BeckTireTempDataClass.h>
#include <BeckLogLib.h>
#include <BeckMiniLib.h>
#include <BeckProbeClass.h>
#include <BeckProbeSetClass.h>

#include <Adafruit_GFX.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansOblique18pt7b.h>
#include <WiFi.h>
#include <Streaming.h>

//ESP32
// https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
//static const byte    cSPI_MOSI_Pin    = 23;     // MasterOutSlaveIn is not used, chips are read only
static const byte      cSPI_MISO_Pin    = 19;
static const byte      cSPI_CLK_Pin     = 18;
static const int       _wNumProbes      =  3;

uint8_t   acSPI_CS_Pin[] {0, 2, 4, 5};

//BeckProbeClass(byte cSPI_MISO_Pin, byte cSPI_CLK_Pin, uint8_t ucCS_Pin);

//Create the Probes, with a dummy one for a non existant probe 0.
BeckProbeClass   oProbe0(cSPI_MISO_Pin, cSPI_CLK_Pin, acSPI_CS_Pin[0]);
BeckProbeClass   oProbe1(cSPI_MISO_Pin, cSPI_CLK_Pin, acSPI_CS_Pin[1]);
BeckProbeClass   oProbe2(cSPI_MISO_Pin, cSPI_CLK_Pin, acSPI_CS_Pin[2]);
BeckProbeClass   oProbe3(cSPI_MISO_Pin, cSPI_CLK_Pin, acSPI_CS_Pin[3]);

//Create array of Probe objects to pass to the ProbeSet constructor
BeckProbeClass  aoProbes[] {oProbe0, oProbe1, oProbe2, oProbe3};

//Create ProbeSet object
BeckProbeSetClass oProbeSet(_wNumProbes, aoProbes);

const char* szWebHostName = "TireTemp";

#define min(X, Y)       (((X) < (Y)) ? (X) : (Y))
const UINT16     usTopText_CursorY       =  35;

static  UINT16     usTextSpacing           = 20;
static  UINT16     usDegF_CursorY          = usTopText_CursorY;
const   ColorType  BackgroundColor         = WROVER_BLACK;

static char             sz100CharString[101];

unsigned long           ulNextDisplayMsec   =    0;
unsigned long           ulDisplayPeriodMsec = 2000; //mSec between output to display

const char* szRouterName  = "Aspot24b";
const char* szRouterPW    = "Qazqaz11";

//extern WROVER_KIT_LCD     RoverLCD;
WROVER_KIT_LCD     RoverLCD;

//Protos
void  setup               (void);
void  loop                (void);
void  DisplayBegin        (void);
void  DisplayClear        (void);
void  FillScreen          (UINT16 usColor);
void  DisplayUpdate       (void);
void  DisplayTemperature  (void);
void  DisplayLowerBanner  (void);
void  DisplayText         (UINT16 usCursorX, UINT16 usCursorY, char *pcText,
                           const GFXfont *pFont, UINT8 ucSize, UINT16 usColor);
void  ClearTextBackground (INT16 sUpperLeftX, INT16 sUpperLeftY, UINT16 usWidth, UINT16 usHeight);


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


void setup(){
  Serial.begin(115200);
  Serial << endl<< LOG0 << "setup(): Begin " << szSketchName << ", " << szFileDate << endl;

  // Start WiFi and wait for connection to the network
  WiFi.begin(szRouterName, szRouterPW);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial << endl << "setup(): Connected to " << szRouterName << ", IP address to connect to is " << WiFi.localIP() << endl;

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
  oProbeSet.Handle();
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
  RoverLCD.fillRect(sUpperLeftX, sUpperLeftY, usWidth, usHeight, BackgroundColor);
  return;
} //ClearTextBackground
//Last line
