const char szBeckEnviroDisplayClassFileName[]  = "BeckEnviroDisplayClass.cpp";
const char szEnviroDisplayClassFileDate[]  = "5/24/21a";

#include <BeckEnviroDisplayClass.h>
#include <BeckGasSensorDataClass.h>
#include "Free_Fonts.h"
#include <Streaming.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansOblique18pt7b.h>

EnviroDisplayClass EnviroDisplay;                   //So every module can use the same object

EnviroDisplayClass::EnviroDisplayClass(void) {
  Serial << "EnviroDisplayClass::EnviroDisplayClass(): Do nothing."  << endl;
} //constructor


EnviroDisplayClass::~EnviroDisplayClass(void) {
  Serial << "~EnviroDisplayClass(): Destructing" << endl;
} //destructor


void EnviroDisplayClass::Setup(void){
  //FillScreen(Gas_BackgroundColor);    //Minimize this, later.
  Serial << "EnviroDisplayClass::Setup(): Call DisplayBegin()" << endl;
  DisplayBegin();
  uint16_t FillDelay= 2000;
  Serial << "EnviroDisplayClass::Setup(): Fill screen with red" << endl;
  FillScreen(BECK_RED);
  delay(FillDelay);
  return;
} //Setup


void EnviroDisplayClass::Handle(void){
  if(millis() >= ulNextGasSensorDisplayMsec){
    ulNextGasSensorDisplayMsec= millis() + ulGasSensorDisplayPeriodMsec;
    Serial << "EnviroDisplayClass::Handle(): Timer is up for next display update" << endl;
    int32_t   CO2_Value= GasSensorData.GetCO2_Value();
    int32_t   VOC_Value= GasSensorData.GetVOC_Value();

    DisplayCO2(CO2_Value);
  } //if(millis()>=ulNextGasSensorDisplayMsec)
  return;
} //Handle


void EnviroDisplayClass::DisplayCO2(int32_t CO2_Value){
  uint16_t          usCharWidth     = 25;
  uint16_t          usCursorX       = 0;
  uint16_t          usCursorY       = 30;   //GFX fonts Y is bottom
  uint8_t           ucSize          = 1;
  //uint16_t          usColor         = WROVER_WHITE;
  uint16_t          usColor         = BECK_WHITE;
  uint16_t          usRightInset    = 2;  //Number of pixels to right of justified text
  int16_t           sClearLeftX     = usCursorX;
  int16_t           sClearTopY      = 0;
  uint16_t          usClearWidth    = 120;
  uint16_t          usClearHeight   = 35;
  static uint16_t   usLastClearWidth= 0;

  if(CO2_Value != CO2_LastValue) {
    CO2_LastValue= CO2_Value;
    Serial << "EnviroDisplayClass::DisplayCO2(): CO2 value is different than last one displayed." << endl;
    sprintf(sz100CharDisplayBuffer, "%5d", CO2_Value);
    //sprintf(szTempBuffer, "%+4.1f %+03.0f", dPitchPercent, dPitchDeg);
    //Calculate width to clear based on number of characters + 2, use that unless last width was bigger
    usClearWidth= (strlen(sz100CharDisplayBuffer) + 2) * usCharWidth;
    usClearWidth= std::max(usClearWidth, usLastClearWidth);
    usLastClearWidth= usClearWidth;
    //ClearTextBackground(sClearLeftX, sClearTopY, usClearWidth, usClearHeight);
    DisplayLine(FreeMonoBold24pt7b, usColor, usCursorX, usCursorY, usClearWidth, usClearHeight, sz100CharDisplayBuffer, false, ucSize);

    usCursorX= 50;
    usCursorY += 20;
    sprintf(sz100CharDisplayBuffer, "CO2");
    DisplayLine(FreeSans9pt7b, usColor, usCursorX, usCursorY, usClearWidth, usClearHeight, sz100CharDisplayBuffer, false, ucSize);
  } //if(bPitchChanged)
  return;
} //DisplayCO2


void EnviroDisplayClass::DisplayVOC(void){
  return;
}

void EnviroDisplayClass::DisplayLowerBanner(){
  const GFXfont   *pFont          = &FreeSansOblique18pt7b;
  uint16_t          usCursorX       = 7;
  uint16_t          usCursorY       = 232;    //Was 72
  uint8_t           ucSize          = 1;
  uint16_t          usColor         = WROVER_CYAN;
  bool            bRightJustify   = false;

  //DisplayText( usCursorX, usCursorY, "PowerShift Coach", pFont, ucSize, usColor);
  DisplayLine( usCursorX, usCursorY, "PowerShift Coach", pFont, ucSize, usColor);
  return;
} //DisplayLowerBanner
//Last line.
