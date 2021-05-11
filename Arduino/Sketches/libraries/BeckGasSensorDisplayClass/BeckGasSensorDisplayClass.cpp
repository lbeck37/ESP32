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
      YHeightDots  = CO2_BarHeightDots;
      if (wValue < CO2_YellowStartValue){
        //Draw partial Green segment
        XLeftDots= CO2_GreenStartDots;
        //fValueRatio= (wValue - CO2_GreenStartValue) / (CO2_YellowStartValue - CO2_GreenStartValue);
        fValueRatio= ((float)(wValue - CO2_GreenStartValue)) / ((float)(CO2_YellowStartValue - CO2_GreenStartValue));
        XWidthDots= fValueRatio * (CO2_YellowStartDots - CO2_GreenStartDots);
        Serial << "GasSensorDisplayClass::DrawBar():  wValue= " << wValue << ", fValueRatio= " << fValueRatio << endl;
        SetFillColor(TFT_GREEN);
        Serial << "GasSensorDisplayClass::DrawBar(): TFT_GREEN: XLeftDots= " << XLeftDots << ", YBottomDots= " << YBottomDots <<
            ", XWidthDots= " << XWidthDots << ", YHeightDots= " << YHeightDots << endl;
        DrawFilledRectangle(XLeftDots, YBottomDots, XWidthDots, YHeightDots);
      } //if(wValue<CO2_YellowStartValue)
      else{
        //Draw full Green segment
        XLeftDots= CO2_GreenStartDots;
        XWidthDots= CO2_YellowStartDots - CO2_GreenStartDots;
        SetFillColor(TFT_GREEN);
        Serial << "GasSensorDisplayClass::DrawBar(): TFT_GREEN: XLeftDots= " << XLeftDots << ", YBottomDots= " << YBottomDots <<
            ", XWidthDots= " << XWidthDots << ", YHeightDots= " << YHeightDots << endl;
        DrawFilledRectangle(XLeftDots, YBottomDots, XWidthDots, YHeightDots);
        if (wValue <= CO2_RedStartValue){
          //Draw partial Yellow segment
          XLeftDots= CO2_YellowStartDots;
          //fValueRatio= (wValue - CO2_YellowStartValue) / (CO2_RedStartValue - CO2_YellowStartValue);
          fValueRatio= ((float)(wValue - CO2_YellowStartValue)) / ((float)(CO2_RedStartValue - CO2_YellowStartValue));
          XWidthDots= fValueRatio * (CO2_RedStartDots - CO2_YellowStartDots);
          SetFillColor(TFT_YELLOW);
          Serial << "GasSensorDisplayClass::DrawBar(): TFT_YELLOW: XLeftDots= " << XLeftDots << ", YBottomDots= " << YBottomDots <<
              ", XWidthDots= " << XWidthDots << ", YHeightDots= " << YHeightDots << endl;
          DrawFilledRectangle(XLeftDots, YBottomDots, XWidthDots, YHeightDots);
        } //if(CO2_Value<=CO2_RedStart)
        else{
          //Draw full Yellow segment
          XLeftDots= CO2_YellowStartDots;
          XWidthDots= CO2_RedStartDots - CO2_YellowStartDots;
          SetFillColor(TFT_YELLOW);
          Serial << "GasSensorDisplayClass::DrawBar(): TFT_YELLOW: XLeftDots= " << XLeftDots << ", YBottomDots= " << YBottomDots <<
              ", XWidthDots= " << XWidthDots << ", YHeightDots= " << YHeightDots << endl;
          DrawFilledRectangle(XLeftDots, YBottomDots, XWidthDots, YHeightDots);
          XLeftDots= CO2_RedStartDots;
          fValueRatio= ((float)(wValue - CO2_RedStartValue)) / ((float)(CO2_RedEndValue - CO2_RedStartValue));
          XWidthDots= fValueRatio * (CO2_RedEndValue - CO2_RedStartValue);
          SetFillColor(TFT_RED);
          Serial << "GasSensorDisplayClass::DrawBar(): TFT_RED: XLeftDots= " << XLeftDots << ", YBottomDots= " << YBottomDots <<
              ", XWidthDots= " << XWidthDots << ", YHeightDots= " << YHeightDots << endl;
          DrawFilledRectangle(XLeftDots, YBottomDots, XWidthDots, YHeightDots);
        } // //if(CO2_Value<=CO2_RedStart)
      } //if(wValue<CO2_YellowStartValue)else
      break;
    case eVOCGas:
      YBottomDots= CO2_BarBottomDots;
      break;
    default :
      Serial << "GasSensorDisplayClass::DrawBar: Bad Switch, eGasType= " << eGasType << endl;
      break;
  } //switch
  return;
}
//Last line.
