const char szGasSensorDisplayClassFileName[]  = "BeckGasSensorDisplayClass.cpp";
const char szGasSensorDisplayClassFileDate[]  = "5/11/21a";

//#include <BeckDisplayClass.h>
#include <BeckGasSensorDisplayClass.h>
#include <BeckGasSensorDataClass.h>
#include "Free_Fonts.h"
#include <Streaming.h>

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
  DrawBar(eCO2Gas, GasSensorData.GetCO2_Value());
  DrawBar(eVOCGas, GasSensorData.GetVOC_Value());
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


void GasSensorDisplayClass::DrawBar(GasType eGasType, int32_t wValue){
  int32_t   XLeftDots;
  //int32_t   XRightDots;
  int32_t   YBottomDots;
  int32_t   XWidthDots;
  int32_t   YHeightDots;
  float     fValueRatio;

  switch(eGasType) {
    case eCO2Gas :
      YBottomDots = CO2_BarBottomDots;
      YHeightDots = CO2_BarHeightDots;
      if (wValue < CO2_YellowStartValue){
        //Draw partial Green segment
        XLeftDots= CO2_GreenStartDots;
        //fValueRatio= (wValue - CO2_GreenStartValue) / (CO2_YellowStartValue - CO2_GreenStartValue);
        fValueRatio= ((float)(wValue - CO2_GreenStartValue)) / ((float)(CO2_YellowStartValue - CO2_GreenStartValue));
        XWidthDots= fValueRatio * (CO2_YellowStartDots - CO2_GreenStartDots);
        Serial << "GasSensorDisplayClass::DrawBar():  wValue= " << wValue << ", fValueRatio= " << fValueRatio << endl;
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
      YBottomDots = VOC_BarBottomDots;
      YHeightDots = VOC_BarHeightDots;
      if (wValue < VOC_YellowStartValue){
        //Draw partial Green segment
        XLeftDots= VOC_GreenStartDots;
        fValueRatio= ((float)(wValue - VOC_GreenStartValue)) / ((float)(VOC_YellowStartValue - VOC_GreenStartValue));
        XWidthDots= fValueRatio * (VOC_YellowStartDots - VOC_GreenStartDots);
        Serial << "GasSensorDisplayClass::DrawBar():  wValue= " << wValue << ", fValueRatio= " << fValueRatio << endl;
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
