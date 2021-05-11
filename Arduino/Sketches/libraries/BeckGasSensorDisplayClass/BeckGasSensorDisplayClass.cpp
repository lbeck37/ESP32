const char szGasSensorDisplayClassFileName[]  = "BeckGasSensorDisplayClass.cpp";
const char szGasSensorDisplayClassFileDate[]  = "5/10/21a";

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
    DisplayCO2andTVOC();
  }
  return;
} //Handle


void GasSensorDisplayClass::DisplayCO2andTVOC(void){
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
  DisplayCO2andTVOC_text();
  //DisplayCO2andTVOC_bars();
  return;
} //DisplayCO2andTVOC


void GasSensorDisplayClass::DisplayCO2andTVOC_text(void){
  SetTextColor  (Gas_FontColor);
  SelectFont    (eGas_Font, eGas_PointSize);

  FillScreen(Gas_BackgroundColor);    //Minimize this, later.

  SetCursor(CO2_TextLeft, CO2_TextBottomDots);
  sprintf(sz100CharDisplayBuffer, "CO2:%4dppm", GasSensorData.GetCO2_Value());
  Print(sz100CharDisplayBuffer);

  SetCursor(VOC_TextLeft, VOC_TextBottomDots);
  sprintf(sz100CharDisplayBuffer, "VOC:%4dppb", GasSensorData.GetVOC_Value());
  Print(sz100CharDisplayBuffer);
  return;
}   //DisplayCO2andTVOC_text


void GasSensorDisplayClass::DisplayCO2andTVOC_bars(void){
  int CO2_Value= GasSensorData.GetCO2_Value();
  int VOC_Value= GasSensorData.GetVOC_Value();


  //DrawFilledRectangle(CO2_BarLeftDots, VOC_BarBottomDots, ThermoOnBarWidth, ThermoOnBarHeight);

  return;
}   //DisplayCO2andTVOC_bars

void GasSensorDisplayClass::DisplayCO2_bar(void){
    int CO2_Value= GasSensorData.GetCO2_Value();

    if (CO2_Value <= CO2_YellowStart){
      SetFillColor(TFT_GREEN);
    } //if(CO2_Value<=CO2_YellowStart)
    else{
      if (CO2_Value <= CO2_RedStart){
        SetFillColor(TFT_YELLOW);
      } //if(CO2_Value<=CO2_RedStart)
      else{
        SetFillColor(TFT_RED);
      } // //if(CO2_Value<=CO2_RedStart)
    } //if(CO2_Value<=CO2_YellowStart)else

    //DrawFilledRectangle(CO2_BarLeftDots, VOC_BarBottomDots, ThermoOnBarWidth, ThermoOnBarHeight);

    return;
  }   //DisplayCO2andTVOC_bars
//Last line.
