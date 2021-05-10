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

    SetTextColor  (Gas_FontColor);
    SelectFont    (eGas_Font, eGas_PointSize);

    FillScreen(Gas_BackgroundColor);
    Gas_YBaseline= (ScreenHeight *80)/100;
    SetCursor(Gas_LeftSide, Gas_YBaseline);
    sprintf(sz100CharDisplayBuffer, "CO2 %4dppm", GasSensorData.GetCO2_Value());
    Print(sz100CharDisplayBuffer);

    Gas_YBaseline= (ScreenHeight * 30)/100;
    SetCursor(Gas_LeftSide, Gas_YBaseline);
    sprintf(sz100CharDisplayBuffer, "TVOC%4dppb", GasSensorData.GetTVOC_Value());
    Print(sz100CharDisplayBuffer);

  return;
} //DisplayCO2andTVOC
//Last line.
