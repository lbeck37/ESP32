const char szSketchName[]  = "BeckE32_RoverEnviroDisplay.ino";
const char szFileDate[]    = "6/8/21d";
#include <BeckBarClass.h>
#include <BeckBiotaDefines.h>
#include <BeckEnviroDataClass.h>
#include <BeckI2cClass.h>
#include <BeckGasSensorClass.h>
#include <BeckLogLib.h>
#include <BeckMiniLib.h>
#include <BeckTempAndHumidityClass.h>

#include <Adafruit_GFX.h>
#include <WROVER_KIT_LCD.h>
#include <Wire.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansOblique18pt7b.h>
#include <Streaming.h>

#define min(X, Y)     (((X) < (Y)) ? (X) : (Y))

static const UINT16     usVOC_CursorY           =  90;
static const UINT16     usDegF_CursorY          = 150;
static const UINT16     usRH_CursorY            = 210;

static char             sz100CharString[101];

BarClass              CO2Bar;
BarData               CO2BarData;

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

  Serial << LOG0 << "setup(): Call DisplayBegin()" << endl;
  DisplayBegin();

  Serial << LOG0 << "setup(): Call CreateBarData() and initialize CO2Bar" << endl;
  CO2BarData  = CreateBarData(eCO2Bar);
  CO2Bar      = BarClass(CO2BarData);

  Serial << LOG0 << "setup(): return" << endl;
  return;
}  //setup


void loop() {
  GasSensor.Handle();
  TempAndHumiditySensor.Handle();
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


const SegmentData& CreateSegmentData(BarType eBarType, SegmentPosition eSegmentPosition){
  SegmentData*          pSegmentData        = new SegmentData;
  SegmentData           &SegData     = *pSegmentData;

  switch(eBarType) {
  case eCO2Bar:
    switch(eSegmentPosition){
    case eFirstSegment:
      strcpy(SegData.BarName  , "CO2");
      strcpy(SegData.ColorName, "Green");
      SegData.StartPercent     = 0;
      SegData.Color            = BECK_GREEN;
      SegData.fStartValue      =   0.0;
      SegData.fEndValue        = 600.0;
      SegData.fRange           = SegData.fEndValue - SegData.fStartValue;
      SegData.XLeft            = CO2_XLEFT + ((SegData.StartPercent * BAR_LENGTH) / 100);
      SegData.YBottom          = CO2_YBOTTOM;
      SegData.Length           = (SegData.fRange / CO2_RANGE) * BAR_LENGTH;
      break;
    case eSecondSegment:
      strcpy(SegData.BarName  , "CO2");
      strcpy(SegData.ColorName, "Yellow");
      SegData.StartPercent     = 33;
      SegData.Color            = BECK_YELLOW;
      SegData.fStartValue      =  600.0;
      SegData.fEndValue        = 1000.0;
      SegData.fRange           = SegData.fEndValue - SegData.fStartValue;
      SegData.XLeft            = CO2_XLEFT + ((SegData.StartPercent * BAR_LENGTH) / 100);
      SegData.YBottom          = CO2_YBOTTOM;
      SegData.Length           = (SegData.fRange / CO2_RANGE) * BAR_LENGTH;
      break;
    case eThirdSegment:
      strcpy(SegData.BarName  , "CO2");
      strcpy(SegData.ColorName, "Red");
      SegData.StartPercent     = 66;
      SegData.Color            = BECK_RED;
      SegData.fStartValue      = 1000.0;
      SegData.fEndValue        = 2000.0;
      SegData.fRange           = SegData.fEndValue - SegData.fStartValue;
      SegData.XLeft            = CO2_XLEFT + ((SegData.StartPercent * BAR_LENGTH) / 100);
      SegData.YBottom          = CO2_YBOTTOM;
      SegData.Length           = (SegData.fRange / CO2_RANGE) * BAR_LENGTH;
      break;
    default:
      Serial << LOG0 << "CreateSegmentData(): Bad switch, eSegmentPosition= " << eSegmentPosition << endl;
      break;
    } //switch(eSegmentPosition)
    break;
  default:
    Serial << LOG0 << "CreateSegmentData(): Bad switch, eBarType= " << eBarType << endl;
    break;
  } //switch(eBarType)

  return SegData;
} //CreateSegmentData


const BarData& CreateBarData(BarType eBarType){
  BarData*          pBarData              = new BarData;
  BarData           &NewBarData           = *pBarData;

  NewBarData.eBarType= eCO2Bar;
  NewBarData.Orientation            = eHorizontal;
  NewBarData.XLeft                  = CO2_XLEFT;
  NewBarData.YBottom                = CO2_YBOTTOM;
  NewBarData.Thickness              = BAR_THICKNESS;
  NewBarData.Length                 = BAR_LENGTH;
  NewBarData.fStartValue            = CO2_START_VALUE;
  NewBarData.fEndValue              = CO2_END_VALUE;
  NewBarData.fRange                 = NewBarData.fEndValue - NewBarData.fStartValue;

  SegmentData   FirstSegmentData    = CreateSegmentData(eBarType, eFirstSegment);
  SegmentData   SecondSegmentData   = CreateSegmentData(eBarType, eSecondSegment);
  SegmentData   ThirdSegmentData    = CreateSegmentData(eBarType, eThirdSegment);

  Serial << LOG0 << "CreateBarData(): Save BarSegments in BarSegs array" << endl;
  NewBarData.BarSegs[0]= BarSegment(FirstSegmentData);
  NewBarData.BarSegs[1]= BarSegment(SecondSegmentData);
  NewBarData.BarSegs[2]= BarSegment(ThirdSegmentData);

  return NewBarData;
} //CreateBarData


void DisplayUpdate(void) {
  DisplayCO2();
  DisplayVOC();
  DisplayTemperature();
  DisplayHumidity();
  //DisplayLowerBanner();
  return;
}  //DisplayUpdate


void DisplayClear() {
  FillScreen(BackgroundColor);
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
  RoverLCD.fillRect(sUpperLeftX, sUpperLeftY, usWidth, usHeight, BackgroundColor);
  return;
} //ClearTextBackground


void DisplayLine(const GFXfont stFont, UINT16 usColor, UINT16 usCursorX, UINT16 usCursorY,
                  UINT16 usClearWidth, UINT16 usClearHeight,
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

  if(EnviroData.bCO2Changed()) {
    UINT16 CO2Value= EnviroData.GetCO2_Value();
    sprintf(sz100CharString, "%6d", CO2Value);
    //Calculate width to clear based on number of characters + 2, use that unless last width was bigger
    //usClearWidth= (strlen(sz100CharString) + 2) * usCharWidth;
    usClearWidth= strlen(sz100CharString) * usCharWidth;
    usClearWidth= std::max(usClearWidth, usLastClearWidth);
    usLastClearWidth= usClearWidth;
    Serial << LOG0 << "DisplayCO2(): Call ClearTextBackground(" << sClearLeftX << ", " << sClearTopY <<
        ", " << usClearWidth << ", " << usClearHeight << ")" << endl;
    ClearTextBackground(sClearLeftX, sClearTopY, usClearWidth, usClearHeight);
    Serial << LOG0 << "DisplayCO2(): Call DisplayLine for: " << sz100CharString << endl;
    DisplayLine(FreeMonoBold24pt7b, usColor, usCursorX, usCursorY, usClearWidth, usClearHeight,
                 sz100CharString, false, ucSize);

    //Draw the CO2 bar
    //CO2Bar.SetLowerLeftCorner((usCursorX + usClearWidth), usCursorY);
    CO2Bar.SetLowerLeftCorner(CO2_XLEFT, CO2_YBOTTOM);
    Serial << LOG0 << "DisplayCO2(): Call CO2Bar.Draw(" << CO2Value << ")" << endl;
    CO2Bar.Draw(CO2Value);

    usCursorX= 50;
    usCursorY += 20;
    sprintf(sz100CharString, "CO2 ppm");
    DisplayLine(FreeSans9pt7b, usColor, usCursorX, usCursorY, usClearWidth, usClearHeight, sz100CharString, false);
  } //if(EnviroData.bCO2Changed())
  return;
}  //DisplayCO2


void DisplayVOC() {
  UINT16          usCharWidth     = 25;
  UINT16          usCursorX       = 0;
  UINT16          usCursorY       = usVOC_CursorY;   //GFX fonts Y is bottom 90
  UINT8           ucSize          = 1;
  UINT16          usColor         = WROVER_WHITE;
  INT16           sClearLeftX     = usCursorX;
  INT16           sClearTopY      = usCursorY - 32;
  UINT16          usClearWidth    = 120;
  UINT16          usClearHeight   = 40;
  static UINT16   usLastClearWidth= 0;

  if(EnviroData.bVOCChanged()) {
    UINT16  VOCValue_ppm      = EnviroData.GetVOC_Value();
    float   VOC_to_mg_per_m3  = 3.23;
    int16_t   VOC_mgPerM3     = (int16_t)((float)VOCValue_ppm * VOC_to_mg_per_m3);

    sprintf(sz100CharString, "%6d", VOC_mgPerM3);
    //Calculate width to clear based on number of characters + 2, use that unless last width was bigger
    usClearWidth= (strlen(sz100CharString) + 2) * usCharWidth;
    usClearWidth= std::max(usClearWidth, usLastClearWidth);
    usLastClearWidth= usClearWidth;
    Serial << LOG0 << "DisplayVOC(): Call ClearTextBackground(" << sClearLeftX << ", " << sClearTopY <<
        ", " << usClearWidth << ", " << usClearHeight << ")" << endl;
    ClearTextBackground(sClearLeftX, sClearTopY, usClearWidth, usClearHeight);
    Serial << LOG0 << "DisplayVOC(): Call DisplayLine for: " << sz100CharString << endl;
    DisplayLine(FreeMonoBold24pt7b, usColor, usCursorX, usCursorY, usClearWidth, usClearHeight,
                 sz100CharString, false, ucSize);

    usCursorX= 50;
    usCursorY += 20;
    sprintf(sz100CharString, "VOC mg/m^3");
    DisplayLine(FreeSans9pt7b, usColor, usCursorX, usCursorY, usClearWidth, usClearHeight, sz100CharString, false);
  } //if(EnviroData.bVOCChanged())
  return;
}  //DisplayVOC


void DisplayTemperature() {
  UINT16          usCharWidth     = 25;
  UINT16          usCursorX       = 0;
  UINT16          usCursorY       = usDegF_CursorY;   //GFX fonts Y is bottom
  UINT8           ucSize          = 1;
  UINT16          usColor         = WROVER_WHITE;
  INT16           sClearLeftX     = usCursorX;
  //INT16           sClearTopY      = 0;
  INT16           sClearTopY      = usCursorY - 32;
  UINT16          usClearWidth    = 120;
  UINT16          usClearHeight   = 35;
  static UINT16   usLastClearWidth= 0;

  if(EnviroData.bDegFChanged()) {
    Serial << LOG0 << "DisplayTemperature(): Call EnviroData.GetDegF_Value()" << endl;
    float DegFValue= EnviroData.GetDegF_Value();
    sprintf(sz100CharString, "%6.1f", DegFValue);
    //Calculate width to clear based on number of characters + 2, use that unless last width was bigger
    usClearWidth= (strlen(sz100CharString) + 2) * usCharWidth;
    usClearWidth= std::max(usClearWidth, usLastClearWidth);
    usLastClearWidth= usClearWidth;
    Serial << LOG0 << "DisplayTemperature(): Call ClearTextBackground(" << sClearLeftX << ", " << sClearTopY <<
        ", " << usClearWidth << ", " << usClearHeight << ")" << endl;
    ClearTextBackground(sClearLeftX, sClearTopY, usClearWidth, usClearHeight);
    Serial << LOG0 << "DisplayTemperature(): Call DisplayLine for: " << sz100CharString << endl;
    DisplayLine(FreeMonoBold24pt7b, usColor, usCursorX, usCursorY, usClearWidth, usClearHeight,
                 sz100CharString, false, ucSize);
    usCursorX= 50;
    usCursorY += 20;
    sprintf(sz100CharString, "Temperature");
    DisplayLine(FreeSans9pt7b, usColor, usCursorX, usCursorY, usClearWidth, usClearHeight, sz100CharString, false);
  } //if(EnviroData.bDegFChanged())
  return;
}  //DisplayTemperature


void DisplayHumidity() {
  UINT16          usCharWidth     = 25;
  UINT16          usCursorX       = 0;
  UINT16          usCursorY       = usRH_CursorY;   //GFX fonts Y is bottom
  UINT8           ucSize          = 1;
  UINT16          usColor         = WROVER_WHITE;
  INT16           sClearLeftX     = usCursorX;
  //INT16           sClearTopY      = 0;
  INT16           sClearTopY      = usCursorY - 32;
  UINT16          usClearWidth    = 120;
  UINT16          usClearHeight   = 35;
  static UINT16   usLastClearWidth= 0;

  if(EnviroData.bRHChanged()) {
    Serial << LOG0 << "DisplayHumidity(): Call EnviroData.GetRH_Value()" << endl;
    UINT16 RHValue= EnviroData.GetRH_Value();
    sprintf(sz100CharString, "%5d%%", RHValue);
    //Calculate width to clear based on number of characters + 2, use that unless last width was bigger
    usClearWidth= (strlen(sz100CharString) + 2) * usCharWidth;
    usClearWidth= std::max(usClearWidth, usLastClearWidth);
    usLastClearWidth= usClearWidth;
    Serial << LOG0 << "DisplayHumidity(): Call ClearTextBackground(" << sClearLeftX << ", " << sClearTopY <<
        ", " << usClearWidth << ", " << usClearHeight << ")" << endl;
    ClearTextBackground(sClearLeftX, sClearTopY, usClearWidth, usClearHeight);
    Serial << LOG0 << "DisplayHumidity(): Call DisplayLine for: " << sz100CharString << endl;
    DisplayLine(FreeMonoBold24pt7b, usColor, usCursorX, usCursorY, usClearWidth, usClearHeight,
                 sz100CharString, false, ucSize);
    usCursorX= 50;
    usCursorY += 20;
    sprintf(sz100CharString, "Humidity");
    DisplayLine(FreeSans9pt7b, usColor, usCursorX, usCursorY, usClearWidth, usClearHeight, sz100CharString, false);
  } //if(EnviroData.bRHChanged())
  return;
}  //DisplayHumidity
//Last line
