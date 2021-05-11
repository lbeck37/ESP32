const char szGasSensorDisplayClassFileName[]  = "BeckGasSensorDisplayClass.cpp";
const char szGasSensorDisplayClassFileDate[]  = "5/11/21a";

//#include <BeckDisplayClass.h>
#include <BeckGasSensorDisplayClass.h>
#include <BeckGasSensorDataClass.h>
#include "Free_Fonts.h"
#include <Streaming.h>

/*
//Scalable fonts created by Font Creator, http://oleddisplay.squix.ch/#/home
#ifdef REDRESSED__REGULAR_20
  #include <Redressed_Regular_20.h>
#endif
#ifdef ROBOTO_CONDENSED_30
  #include <Roboto_Condensed_30.h>
#endif
#ifdef ROBOTO_MEDIUM_40
  #include <Roboto_Medium_40.h>
#endif
#ifdef ROBOTO_MEDIUM_100
  #include <Roboto_Medium_100.h>
#endif
#ifdef ROBOTO_CONDENSED_130
  #include <Roboto_Condensed_130.h>
#endif
#ifdef ROBOTO_CONDENSED_BOLD_130
  #include <Roboto_Condensed_Bold_130.h>
#endif
#ifdef ROBOTO_MEDIUM_150
  #include <Roboto_Medium_150.h>
#endif
*/

//char  	sz100CharDisplayBuffer[100];    //For building strings for display

GasSensorDisplayClass	GasSensorDisplay;                   //So every module can use the same object

GasSensorDisplayClass::GasSensorDisplayClass() {
  Serial << "GasSensorDisplayClass::GasSensorDisplayClass(): Do nothing."  << endl;
} //constructor


GasSensorDisplayClass::~GasSensorDisplayClass() {
  Serial << "~GasSensorDisplayClass(): Destructing" << endl;
} //destructor


void GasSensorDisplayClass::Setup(void){
  Serial << "GasSensorDisplayClass::Setup(): Call Handle()" << endl;
  Handle();
  return;
} //Setup

void GasSensorDisplayClass::Handle(){
  //Serial << "GasSensorDisplayClass::Handle(): Begin" << endl;
  if(millis() >= ulNextGasSensorDisplayMsec){
    ulNextGasSensorDisplayMsec= millis() + ulGasSensorDisplayPeriodMsec;
    DrawCO2andTVOC();
  }
  return;
} //Handle


void GasSensorDisplayClass::DrawCO2andTVOC(void){
  //float   SingleDigitDegF= (int)(10 * ThermostatData.GetCurrentTemperature())/10.0;

/*
  SetTextColor  (Gas_FontColor);
  SelectFont    (eGas_Font, eGas_PointSize);

  FillScreen(Gas_BackgroundColor);
  SetCursor(CO2_TextLeft, CO2_TextBottom);
  sprintf(sz100CharDisplayBuffer, "CO2:%4dppm", GasSensorData.GetCO2_Value());
  Print(sz100CharDisplayBuffer);

  SetCursor(VOC_TextLeft, VOC_TextBottom);
  sprintf(sz100CharDisplayBuffer, "VOC:%4dppb", GasSensorData.GetTVOC_Value());
  Print(sz100CharDisplayBuffer);
*/
  DrawCO2andTVOC_text();
  //DrawCO2andTVOC_bars();
  return;
} //DrawCO2andTVOC


void GasSensorDisplayClass::DrawCO2andTVOC_text(void){
  SetTextColor  (Gas_FontColor);
  SelectFont    (eGas_Font, eGas_PointSize);

  FillScreen(Gas_BackgroundColor);    //Minimize this, later.

  SetCursor(CO2_TextLeftDots, CO2_TextBottomDots);
  sprintf(sz100CharDisplayBuffer, "CO2:%4dppm", GasSensorData.GetCO2_Value());
  Print(sz100CharDisplayBuffer);

  SetCursor(VOC_TextLeftDots, VOC_TextBottomDots);
  sprintf(sz100CharDisplayBuffer, "VOC:%4dppb", GasSensorData.GetVOC_Value());
  Print(sz100CharDisplayBuffer);
  return;
}   //DrawCO2andTVOC_text


void GasSensorDisplayClass::DrawCO2andTVOC_bars(void){
  int CO2_Value= GasSensorData.GetCO2_Value();
  int VOC_Value= GasSensorData.GetVOC_Value();


  //DrawFilledRectangle(CO2_BarLeftDots, VOC_BarBottomDots, ThermoOnBarWidth, ThermoOnBarHeight);

  return;
}   //DrawCO2andTVOC_bars

/*
void GasSensorDisplayClass::DrawCO2_bar(void){
    int CO2_Value= GasSensorData.GetCO2_Value();

    if (CO2_Value <= CO2_YellowStartValue){
      SetFillColor(TFT_GREEN);
    } //if(CO2_Value<=CO2_YellowStartValue)
    else{
      if (CO2_Value <= CO2_RedStartValue){
        SetFillColor(TFT_YELLOW);
      } //if(CO2_Value<=CO2_RedStart)
      else{
        SetFillColor(TFT_RED);
      } // //if(CO2_Value<=CO2_RedStart)
    } //if(CO2_Value<=CO2_YellowStart)else

    //DrawFilledRectangle(CO2_BarLeftDots, VOC_BarBottomDots, ThermoOnBarWidth, ThermoOnBarHeight);

    return;
  }   //DrawCO2andTVOC_bars
*/


void GasSensorDisplayClass::DrawBar(BarType eBarType, int32_t wValue){
  int32_t   XLeftDots;
  //int32_t   XRightDots;
  int32_t   YBottomDots;
  int32_t   XWidthDots;
  int32_t   YHeightDots;
  int32_t   ValueRatio;

  switch(eBarType) {
    case eCO2Bar :
      YBottomDots = CO2_BarBottomDots;
      YHeightDots  = CO2_BarHeightDots;
      if (wValue < CO2_YellowStartValue){
        //Draw partial Green segment
        XLeftDots= CO2_GreenStartDots;
        ValueRatio= (wValue - CO2_GreenStartValue) / (CO2_YellowStartValue - CO2_GreenStartValue);
        XWidthDots= ValueRatio * (CO2_YellowStartDots - CO2_GreenStartDots);
        SetFillColor(TFT_GREEN);
        DrawFilledRectangle(XLeftDots, YBottomDots, XWidthDots, YHeightDots);
      } //if(wValue<CO2_YellowStartValue)
      else{
        //Draw full Green segment
        XLeftDots= CO2_GreenStartDots;
        XWidthDots= CO2_YellowStartDots - CO2_GreenStartDots;
        SetFillColor(TFT_GREEN);
        DrawFilledRectangle(XLeftDots, YBottomDots, XWidthDots, YHeightDots);
        if (wValue <= CO2_RedStartValue){
          //Draw partial Yellow segment
          XLeftDots= CO2_YellowStartDots;
          ValueRatio= (wValue - CO2_YellowStartValue) / (CO2_RedStartValue - CO2_YellowStartValue);
          XWidthDots= ValueRatio * (CO2_RedStartDots - CO2_YellowStartDots);
          SetFillColor(TFT_YELLOW);
          DrawFilledRectangle(XLeftDots, YBottomDots, XWidthDots, YHeightDots);
        } //if(CO2_Value<=CO2_RedStart)
        else{
          XLeftDots= CO2_RedStartDots;
          ValueRatio= (wValue - CO2_RedStartValue) / (CO2_RedEndValue - CO2_RedStartValue);
          XWidthDots= ValueRatio * (CO2_RedEndValue - CO2_RedStartValue);
          SetFillColor(TFT_RED);
          DrawFilledRectangle(XLeftDots, YBottomDots, XWidthDots, YHeightDots);
        } // //if(CO2_Value<=CO2_RedStart)
      } //if(wValue<CO2_YellowStartValue)else
      break;
    case eSVOCBar:
      YBottomDots= CO2_BarBottomDots;
      break;
    default :
      Serial << "GasSensorDisplayClass::DrawBar: Bad Switch, eBarType= " << eBarType << endl;
      break;
  } //switch
  return;
}

//Last line.
