const char szGasSensorDisplayClassFileName[]  = "BeckGasSensorDisplayClass.cpp";
const char szGasSensorDisplayClassFileDate[]  = "6/16/21b";

#include <BeckGasSensorDisplayClass.h>
#include <BeckEnviroDataClass.h>
#include "Free_Fonts.h"
#include <Streaming.h>

GasSensorDisplayClass GasSensorDisplay;                   //So every module can use the same object

GasSensorDisplayClass::GasSensorDisplayClass() {
  Serial << "GasSensorDisplayClass::GasSensorDisplayClass(): Do nothing."  << endl;
} //constructor


GasSensorDisplayClass::~GasSensorDisplayClass() {
  Serial << "~GasSensorDisplayClass(): Destructing" << endl;
} //destructor


void GasSensorDisplayClass::Setup(void){
  FillScreen(Gas_BackgroundColor);    //Minimize this, later.
  Serial << "GasSensorDisplayClass::Setup(): Call Handle()" << endl;
  Handle();
  return;
} //Setup

void GasSensorDisplayClass::Handle(){
   if(millis() >= ulNextGasSensorDisplayMsec){
    ulNextGasSensorDisplayMsec= millis() + ulGasSensorDisplayPeriodMsec;
    Serial << "GasSensorDisplayClass::Handle(): ulNextGasSensorDisplayMsec= " << ulNextGasSensorDisplayMsec << endl;
    //DrawCO2andTVOC();
/*
    int32_t   CO2_Value= GasSensorData.GetCO2_Value();
    int32_t   VOC_Value= GasSensorData.GetVOC_Value();
*/
    int32_t   CO2_Value= EnviroData.GetCO2_Value();
    int32_t   VOC_Value= EnviroData.GetVOC_Value();

    DrawCO2andTVOC_text(CO2_Value, VOC_Value);
    DrawBar(eCO2Gas, CO2_Value);
    DrawBar(eVOCGas, VOC_Value);
    VOC_LastValue= CO2_Value;
  }
  return;
} //Handle


void GasSensorDisplayClass::DrawCO2andTVOC_text(int32_t CO2_Value, int32_t VOC_Value){
  Serial << "GasSensorDisplayClass::DrawCO2andTVOC_text(" << CO2_Value << ", " << VOC_Value << "): Begin" << endl;
  SetTextColor  (Gas_FontColor);
  SelectFont    (eGas_Font, eGas_PointSize);

  //If the new value is different than last value, clear the changed area and display the new value.
  if (CO2_Value != CO2_LastValue){
    Serial << "GasSensorDisplayClass::DrawCO2andTVOC_text():(CO2_Value!=CO2_LastValue)"<< endl;
    SetFillColor(Gas_BackgroundColor);
    DrawFilledRectangle(BlankTextLeftDots, BlankTextCO2BottomDots, BlankTextWidthDots, BlankTextHeightDots);

    Serial << "GasSensorDisplayClass::DrawCO2andTVOC_text(): CO2: Call SetCursor("<< CO2_TextLeftDots <<", "<<
        CO2_TextBottomDots <<")"<<endl;
    SetCursor(CO2_TextLeftDots, CO2_TextBottomDots);
    sprintf(sz100CharDisplayBuffer, "CO2:%4dppm", CO2_Value);
    Print(sz100CharDisplayBuffer);
  } //if(CO2Value!=CO2_LastValue)

  if (VOC_Value != VOC_LastValue){
    Serial << "DrawCO2andTVOC_text():(VOC_Value!=VOC_LastValue)"<< endl;
    SetFillColor(Gas_BackgroundColor);
    DrawFilledRectangle(BlankTextLeftDots, BlankTextVOCBottomDots, BlankTextWidthDots, BlankTextHeightDots);

    Serial << "GasSensorDisplayClass::DrawCO2andTVOC_text(): VOC:Call SetCursor("<< VOC_TextLeftDots <<", "<<
        VOC_TextBottomDots <<")"<<endl;
    SetCursor(VOC_TextLeftDots, VOC_TextBottomDots);
    sprintf(sz100CharDisplayBuffer, "VOC:%4dppb", VOC_Value);
    Print(sz100CharDisplayBuffer);
  } //if(CO2Value!=CO2_LastValue)

  return;
}   //DrawCO2andTVOC_text


void GasSensorDisplayClass::DrawBar(GasType eGasType, int32_t wValue){
  Serial << "GasSensorDisplayClass::DrawBar(): Begin"<< endl;
  int32_t   XLeftDots;
  //int32_t   XRightDots;
  int32_t   YBottomDots;
  int32_t   XWidthDots;
  int32_t   YHeightDots;
  float     fValueRatio;
  int       XStartDot;
  int       BarWidth;

  switch(eGasType) {
    case eCO2Gas :
      //Only clear the bar if the new value is less than the old value,
      if (wValue < CO2_LastValue){
        SetFillColor(Gas_BackgroundColor);
        if (wValue < CO2_YellowStartValue){
          XStartDot= CO2_GreenStartDots;
        } //if(wValue<CO2_YellowStartValue)
        else{
          if (wValue < CO2_RedStartValue){
            XStartDot= CO2_YellowStartDots;
          } //if(wValue<CO2_RedStartValue)
          else{
            if (wValue < CO2_RedEndValue){
              XStartDot= CO2_RedStartDots;
            }
          } //if(wValue<CO2_RedStartValue)else
        } //if(wValue<CO2_YellowStartValue)else
        BarWidth= ScreenWidth - XStartDot;
        DrawFilledRectangle(XStartDot, CO2_BarBottomDots, BarWidth, CO2_BarHeightDots);
      } //if(wValue < CO2_LastValue)
      CO2_LastValue= wValue;
      YBottomDots = CO2_BarBottomDots;
      YHeightDots = CO2_BarHeightDots;
      if (wValue < CO2_YellowStartValue){
        //Draw partial Green segment
        XLeftDots= CO2_GreenStartDots;
        fValueRatio= ((float)(wValue - CO2_GreenStartValue)) / ((float)(CO2_YellowStartValue - CO2_GreenStartValue));
        XWidthDots= fValueRatio * (CO2_YellowStartDots - CO2_GreenStartDots);
        SetFillColor(TFT_GREEN);
        DrawFilledRectangle(XLeftDots, YBottomDots, XWidthDots, YHeightDots);
      } //if(wValue<CO2_YellowStartValue)
      else{
        //Draw full Green segment
        XLeftDots = CO2_GreenStartDots;
        XWidthDots= CO2_YellowStartDots - CO2_GreenStartDots;
        SetFillColor(TFT_GREEN);
        DrawFilledRectangle(XLeftDots, YBottomDots, XWidthDots, YHeightDots);
        if (wValue <= CO2_RedStartValue){
          //Draw partial Yellow segment
          XLeftDots= CO2_YellowStartDots;
          fValueRatio= ((float)(wValue - CO2_YellowStartValue)) / ((float)(CO2_RedStartValue - CO2_YellowStartValue));
          XWidthDots= fValueRatio * (CO2_RedStartDots - CO2_YellowStartDots);
          SetFillColor(TFT_YELLOW);
          DrawFilledRectangle(XLeftDots, YBottomDots, XWidthDots, YHeightDots);
        } //if(CO2_Value<=CO2_RedStart)
        else{
          //Draw full Yellow segment
          XLeftDots= CO2_YellowStartDots;
          XWidthDots= CO2_RedStartDots - CO2_YellowStartDots;
          SetFillColor(TFT_YELLOW);
          DrawFilledRectangle(XLeftDots, YBottomDots, XWidthDots, YHeightDots);
          XLeftDots= CO2_RedStartDots;
          fValueRatio= ((float)(wValue - CO2_RedStartValue)) / ((float)(CO2_RedEndValue - CO2_RedStartValue));
          XWidthDots= fValueRatio * (CO2_RedEndValue - CO2_RedStartValue);
          SetFillColor(TFT_RED);
          DrawFilledRectangle(XLeftDots, YBottomDots, XWidthDots, YHeightDots);
        } // //if(CO2_Value<=CO2_RedStart)
      } //if(wValue<CO2_YellowStartValue)else
      break;

    case eVOCGas:
      if (wValue < VOC_LastValue){
        Serial << "GasSensorDisplayClass::DrawBar(): Clearing VOC bar, VOC_LastValue= " << VOC_LastValue << ", wValue= " << wValue << endl;
        SetFillColor(Gas_BackgroundColor);
        if (wValue < VOC_YellowStartValue){
          XStartDot= VOC_GreenStartDots;
        } //if(wValue<VOC_YellowStartValue)
        else{
          if (wValue < VOC_RedStartValue){
            XStartDot= VOC_YellowStartDots;
          } //if(wValue<VOC_RedStartValue)
          else{
            if (wValue < VOC_RedEndValue){
              XStartDot= VOC_RedStartDots;
            }
          } //if(wValue<VOC_RedStartValue)else
        } //if(wValue<VOC_YellowStartValue)else
        BarWidth= ScreenWidth - XStartDot;
        DrawFilledRectangle(XStartDot, VOC_BarBottomDots, BarWidth, VOC_BarHeightDots);
      } //if(wValue < VOC_LastValue)
      VOC_LastValue= wValue;
      YBottomDots = VOC_BarBottomDots;
      YHeightDots = VOC_BarHeightDots;
      if (wValue < VOC_YellowStartValue){
        //Draw partial Green segment
        XLeftDots= VOC_GreenStartDots;
        fValueRatio= ((float)(wValue - VOC_GreenStartValue)) / ((float)(VOC_YellowStartValue - VOC_GreenStartValue));
        XWidthDots= fValueRatio * (VOC_YellowStartDots - VOC_GreenStartDots);
        SetFillColor(TFT_GREEN);
        DrawFilledRectangle(XLeftDots, YBottomDots, XWidthDots, YHeightDots);
      } //if(wValue<VOC_YellowStartValue)
      else{
        //Draw full Green segment
        XLeftDots = VOC_GreenStartDots;
        XWidthDots= VOC_YellowStartDots - VOC_GreenStartDots;
        SetFillColor(TFT_GREEN);
        DrawFilledRectangle(XLeftDots, YBottomDots, XWidthDots, YHeightDots);
        if (wValue <= VOC_RedStartValue){
          //Draw partial Yellow segment
          XLeftDots= VOC_YellowStartDots;
          fValueRatio= ((float)(wValue - VOC_YellowStartValue)) / ((float)(VOC_RedStartValue - VOC_YellowStartValue));
          XWidthDots= fValueRatio * (VOC_RedStartDots - VOC_YellowStartDots);
          SetFillColor(TFT_YELLOW);
          DrawFilledRectangle(XLeftDots, YBottomDots, XWidthDots, YHeightDots);
        } //if(VOC_Value<=VOC_RedStart)
        else{
          //Draw full Yellow segment
          XLeftDots= VOC_YellowStartDots;
          XWidthDots= VOC_RedStartDots - VOC_YellowStartDots;
          SetFillColor(TFT_YELLOW);
          DrawFilledRectangle(XLeftDots, YBottomDots, XWidthDots, YHeightDots);
          XLeftDots= VOC_RedStartDots;
          fValueRatio= ((float)(wValue - VOC_RedStartValue)) / ((float)(VOC_RedEndValue - VOC_RedStartValue));
          XWidthDots= fValueRatio * (VOC_RedEndValue - VOC_RedStartValue);
          SetFillColor(TFT_RED);
          DrawFilledRectangle(XLeftDots, YBottomDots, XWidthDots, YHeightDots);
        } // //if(VOC_Value<=VOC_RedStart)
      } //if(wValue<VOC_YellowStartValue)else
      break;
    default :
      Serial << "GasSensorDisplayClass::DrawBar: Bad Switch, eGasType= " << eGasType << endl;
      break;
  } //switch
  return;
}
//Last line.
