const char szSketchName[]  = "BeckE32_EnviroDisplay.ino";
const char szFileDate[]    = "6/16/21c";

#include <BeckBarClass.h>
#include <BeckBiotaDefines.h>         //Set DO_ROVER to true to display to ROVER
#include <BeckCreateDisplayData.h>
#include <BeckEnviroDataClass.h>
#include <BeckI2cClass.h>
#include <BeckGasSensorClass.h>
#include <BeckLogLib.h>
#include <BeckMiniLib.h>
#include <BeckTempAndHumidityClass.h>

#include <Adafruit_GFX.h>
#include <Wire.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansOblique18pt7b.h>
#include <Streaming.h>

#define min(X, Y)       (((X) < (Y)) ? (X) : (Y))
#if DO_ROVER
  const UINT16     usTopText_CursorY       =  35;
#else
  const UINT16     usTopText_CursorY       =  35;
#endif

static  UINT16     usTextSpacing           = BAR_SPACING;
static  UINT16     usCO2_CursorY           = usTopText_CursorY;
static  UINT16     usVOC_CursorY           = usCO2_CursorY   + usTextSpacing;
static  UINT16     usDegF_CursorY          = usVOC_CursorY   + usTextSpacing;
static  UINT16     usRH_CursorY            = usDegF_CursorY  + usTextSpacing;

static char             sz100CharString[101];

unsigned long           ulNextDisplayMsec   =    0;
unsigned long           ulDisplayPeriodMsec = 2000; //mSec between output to display

BarClass                CO2Bar;
BarData                 CO2BarData;

BarClass                VOCBar;
BarData                 VOCBarData;

BarClass                DegFBar;
BarData                 DegFBarData;

BarClass                RHBar;
BarData                 RHBarData;

void(* ResetESP32)(void)= 0;        //Hopefully system crashes and reset when this is called.

//Function prototypes
const BarData&    CreateBarData       (BarType eBarType);
void              DisplayCO2          (void);
void              DisplayVOC          (void);
void              DisplayTemperature  (void);
void              DisplayHumidity     (void);

void setup()   {
  Serial.begin(115200);
  Serial << endl<< LOG0 << "setup(): Begin " << szSketchName << ", " << szFileDate << endl;

  Serial << LOG0 << "setup(): Call I2C_Object.Setup()" << endl;
  I2C_Object.Setup();

  Serial << LOG0 << "setup(): Call TempAndHumidSensor.Setup()" << endl;
  TempAndHumiditySensor.Setup();

  Serial << LOG0 << "setup(): Call GasSensor.Setup()" << endl;
  GasSensor.Setup();

  //if (bDoRover){
#if DO_ROVER
    Serial << LOG0 << "setup(): Call DisplayBegin()" << endl;
    DisplayBegin();
#else
    GasSensorDisplay.Setup();
#endif

  Serial << LOG0 << "setup(): Call CreateBarData() and initialize CO2Bar" << endl;
  CO2BarData  = CreateBarData(eCO2Bar);
  CO2Bar      = BarClass(CO2BarData);

  Serial << LOG0 << "setup(): Call CreateBarData() and initialize VOCBar" << endl;
  VOCBarData  = CreateBarData(eVOCBar);
  VOCBar      = BarClass(VOCBarData);

  Serial << LOG0 << "setup(): Call CreateBarData() and initialize DegFBar" << endl;
  DegFBarData  = CreateBarData(eDegFBar);
  DegFBar      = BarClass(DegFBarData);

  Serial << LOG0 << "setup(): Call CreateBarData() and initialize RHBar" << endl;
  RHBarData  = CreateBarData(eRHBar);
  RHBar      = BarClass(RHBarData);

  Serial << LOG0 << "setup(): return" << endl;
  return;
}  //setup


void loop() {
  GasSensor.Handle();
  TempAndHumiditySensor.Handle();
#if DO_ROVER
  DisplayUpdate();
#else
  GasSensorDisplay.Handle();
#endif
}  //loop()


void DisplayBegin() {
#if DO_ROVER
  Serial << LOG0 << "DisplayBegin(): Call RoverLCD.begin()" << endl;
  RoverLCD.begin();
  RoverLCD.setRotation(1);
  DisplayClear();
#else
  // TTGODisplayClass::TTGODisplay() constructor handles setup, GasSensorDisplay inherits it
  // class GasSensorDisplay: public TTGO_DisplayClass
#endif
  return;
}  //DisplayBegin


void DisplayUpdate(void) {
  if (millis() > ulNextDisplayMsec){
    ulNextDisplayMsec= millis() + ulDisplayPeriodMsec;
    DisplayCO2();
    DisplayVOC();
    DisplayTemperature();
    DisplayHumidity();
  } //if (millis()>ulNextDisplayMsec)
  //DisplayLowerBanner();
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


void DisplayCO2() {
  UINT16          usCursorX       = 0;
  UINT16          usCursorY       = usCO2_CursorY;   //GFX fonts Y is bottom 90
  UINT8           ucSize          = 1;
  UINT16          usColor         = WROVER_WHITE;

  if (EnviroData.bCO2Changed()) {
    //Erase the currently displayed value by overwriting it with the background color
    UINT16 LastCO2Value= EnviroData.GetLastCO2_Value();
    sprintf(sz100CharString, "%6d", LastCO2Value);
    DisplayText( usCursorX, usCursorY, sz100CharString, &FreeMonoBold24pt7b, ucSize, BackgroundColor);

    //Display the new value
    UINT16 CO2Value= EnviroData.GetCO2_Value();
    sprintf(sz100CharString, "%6d", CO2Value);
    DisplayText( usCursorX, usCursorY, sz100CharString, &FreeMonoBold24pt7b, ucSize, usColor);

    //Put the label underneath
    usCursorX= 50;
    usCursorY += 20;
    sprintf(sz100CharString, "CO2 ppm");
    DisplayText( usCursorX, usCursorY, sz100CharString, &FreeSans9pt7b, ucSize, usColor);

    //Draw the bar
    CO2Bar.Draw(CO2Value, LastCO2Value);

    //Set the last value to be the displayed value
    EnviroData.SetLastCO2_Value(CO2Value);
  } //if(EnviroData.bCO2Changed())
  return;
}  //DisplayCO2


void DisplayVOC() {
  UINT16          usCursorX       = 0;
  UINT16          usCursorY       = usVOC_CursorY;   //GFX fonts Y is bottom 90
  UINT8           ucSize          = 1;
  UINT16          usColor         = WROVER_WHITE;
  int16_t         VOC_mgPerM3     = 0;

  if(EnviroData.bVOCChanged()) {
    //Erase the currently displayed value by overwriting it with the background color
    UINT16 LastVOCValue= EnviroData.GetLastVOC_Value();
    sprintf(sz100CharString, "%6d", LastVOCValue);
    DisplayText( usCursorX, usCursorY, sz100CharString, &FreeMonoBold24pt7b, ucSize, BackgroundColor);

    UINT16  VOCValue_ppm      = EnviroData.GetVOC_Value();
    float   VOC_to_mg_per_m3  = 3.23;
    VOC_mgPerM3               = (int16_t)((float)VOCValue_ppm * VOC_to_mg_per_m3);

    sprintf(sz100CharString, "%6d", VOC_mgPerM3);
    DisplayText( usCursorX, usCursorY, sz100CharString, &FreeMonoBold24pt7b, ucSize, usColor);

    usCursorX= 50;
    usCursorY += 20;
    sprintf(sz100CharString, "VOC mg/m^3");
    DisplayText( usCursorX, usCursorY, sz100CharString, &FreeSans9pt7b, ucSize, usColor);

    //Draw the bar
    VOCBar.Draw(VOC_mgPerM3, LastVOCValue);

    //Set the last value to be the displayed value
    EnviroData.SetLastVOC_Value(VOC_mgPerM3);
  } //if(EnviroData.bVOCChanged())
  return;
}  //DisplayVOC


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

    //Draw the bar
    DegFBar.Draw(fDegFValue, fLastDegFValue);

    //Set the last value to be the displayed value
    EnviroData.SetLastDegF_Value(fDegFValue);
  } //if(EnviroData.bDegFChanged())
  return;
}  //DisplayTemperature


void DisplayHumidity() {
  UINT16          usCursorX       = 0;
  UINT16          usCursorY       = usRH_CursorY;   //GFX fonts Y is bottom
  UINT8           ucSize          = 1;
  UINT16          usColor         = WROVER_WHITE;
  UINT16          RHValue         = 0;

  if(EnviroData.bRHChanged()) {
    //Erase the currently displayed value by overwriting it with the background color
    UINT16 LastRHValue= EnviroData.GetLastRH_Value();
    sprintf(sz100CharString, "%5d%%", LastRHValue);
    DisplayText( usCursorX, usCursorY, sz100CharString, &FreeMonoBold24pt7b, ucSize, BackgroundColor);

    //Display the new value
    RHValue= EnviroData.GetRH_Value();
    sprintf(sz100CharString, "%5d%%", RHValue);
    DisplayText( usCursorX, usCursorY, sz100CharString, &FreeMonoBold24pt7b, ucSize, usColor);

    usCursorX= 50;
    usCursorY += 20;
    sprintf(sz100CharString, "Humidity");
    DisplayText( usCursorX, usCursorY, sz100CharString, &FreeSans9pt7b, ucSize, usColor);

    //Draw the bar
    RHBar.Draw(RHValue, LastRHValue);

    //Set the last value to be the displayed value
    EnviroData.SetLastRH_Value(RHValue);
  } //if(EnviroData.bRHChanged())
  return;
}  //DisplayHumidity
//Last line
