const char szDisplayClassFileName[]  = "BeckDisplayClass.cpp";
const char szDisplayClassFileDate[]  = "5/9/21c";

//#include <BeckDisplayClass.h>
#include <BeckThermostatDisplayClass.h>
#include <BeckThermostatDataClass.h>
#include "Free_Fonts.h"
#include <Streaming.h>

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

char  	sz100CharDisplayBuffer[100];    //For building strings for display

ThermostatDisplayClass	ThermostatDisplay;                   //So every module can use the same object


//**********************************************************************************************//
//***** Was in ThermoDisplayClass **************************************************************//
//**********************************************************************************************//
ThermostatDisplayClass::ThermostatDisplayClass() {
  Serial << "ThermostatDisplayClass::ThermostatDisplayClass(): Do nothing."  << endl;
} //constructor


ThermostatDisplayClass::~ThermostatDisplayClass() {
  Serial << "~ThermostatDisplayClass(): Destructing" << endl;
} //destructor


void ThermostatDisplayClass::Setup(void){
  Serial << "ThermostatDisplayClass::Setup(): Call Handle()" << endl;
  Handle();
  return;
} //Setup

//void TTGO_DisplayClass::Handle(DisplayThermoStruct ThermoData){
void ThermostatDisplayClass::Handle(){
  //Serial << "ThermostatDisplayClass::Handle(): Begin" << endl;
  DisplayThermoOnBar        ();
  DisplaySetpointText       ();
  DisplayOffpointText       ();
  DisplayHeatOnBox          ();
  DisplayMainScreen         ();
  return;
} //Handle

void ThermostatDisplayClass::DisplayMainScreen(void){
  if (millis() > ulNextDisplayChange){
    //Change to next display
    if (!ThermostatData.GetThermostatOn()){
      CurrentScreen= eDegFScreen;
      ForceScreenUpdate= true;
    } //if(!ThermostatData.GetThermostatOn())
    else{
      if (CurrentScreen == eDegFScreen){
        CurrentScreen= eSetpointScreen;
      }
      else{
        CurrentScreen= eDegFScreen;
      }
      ForceScreenUpdate= true;
    } //if(!ThermostatData.GetThermostatOn())else
    ulNextDisplayChange= millis() + OnTimeMsec[CurrentScreen];
  }
  switch(CurrentScreen) {
    case eDegFScreen :
      DisplayCurrentTemperature(ForceScreenUpdate);
      break;
    case eSetpointScreen:
      DisplayCurrentSetpoint(ForceScreenUpdate);
      break;
    default :
      Serial << "DisplayMainScreen(): Bad Switch, CurrentScreen= " << CurrentScreen << endl;
      break;
  } //switch
  ForceScreenUpdate= false;
  return;
} //DisplayMainScreen

void ThermostatDisplayClass::DisplayCurrentTemperature(bool ForceUpdate){
  float   SingleDigitDegF= (int)(10 * ThermostatData.GetCurrentTemperature())/10.0;

  if (ForceUpdate || (fCurrentDegFLast != SingleDigitDegF)){
    fCurrentDegFLast= SingleDigitDegF;
    //Clear the rectangular area where the DegF is displayed
    SetFillColor(_BackgroundColor);
    PUnit YBottom= (ThermoOnBarBottom + ThermoOnBarHeight);
    DrawFilledRectangle( 0, YBottom, ScreenWidth, ScreenHeight);

    SetCursor     (DegF_XLeftSide, DegF_YBaseline);
    SetTextColor  (DegF_Color);
    SelectFont    (eDegF_Font, eDegF_PointSize);

    sprintf(sz100CharDisplayBuffer, "%04.1f", fCurrentDegFLast);
    //Serial << "ThermostatDisplayClass::DisplayCurrentTemperature(): Writing " << sz100CharDisplayBuffer << " to the display" << endl;
    Print(sz100CharDisplayBuffer);
  }
  return;
} //DisplayCurrentTemperature


void ThermostatDisplayClass::DisplayCurrentSetpoint(bool ForceUpdate){
  float   SingleDigitSetpoint= (int)(10 * ThermostatData.GetSetpoint())/10.0;

  if (ForceUpdate || (fSetpointLast != SingleDigitSetpoint)){
    fSetpointLast= SingleDigitSetpoint;
    //Clear the rectangular area where the Set-point is displayed
    SetFillColor(_BackgroundColor);
    PUnit YBottom= (ThermoOnBarBottom + ThermoOnBarHeight);
    DrawFilledRectangle( 0, YBottom, ScreenWidth, ScreenHeight);

    //Display the set-point
    SetCursor     (DegF_XLeftSide, DegF_YBaseline);
    SetTextColor  (ThermoSetpoint_Color);
    SelectFont    (eDegF_Font, eDegF_PointSize);

    sprintf(sz100CharDisplayBuffer, "%04.1f", fSetpointLast);
    //Serial << "ThermostatDisplayClass::DisplayCurrentSetpoint(): Writing " << sz100CharDisplayBuffer << " to the display" << endl;
    Print(sz100CharDisplayBuffer);
  }
  return;
} //DisplayCurrentSetpoint

void ThermostatDisplayClass::DisplayThermoOnBar(){
  //Draw a fat bar, the ThermoOnBar, under the large current temperature display, present when thermostat is on.
  if (bThermoOnLast != ThermostatData.GetThermostatOn()){
    bThermoOnLast= ThermostatData.GetThermostatOn();
    if (ThermostatData.GetThermostatOn()){
      SetFillColor(ThermoOnBarColor);
      bThermoOnLast= true;
    } //if(stData.GetThermostatOn())
    else{
      SetFillColor(_BackgroundColor);
      bThermoOnLast= false;
    } //if(stData.GetThermostatOn())else
    DrawFilledRectangle(ThermoOnBarLeft, ThermoOnBarBottom, ThermoOnBarWidth, ThermoOnBarHeight);
  } //if(bThermoOnLast!=stData.GetThermostatOn())
  return;
} //DisplayThermoOnBar

void ThermostatDisplayClass::DisplaySetpointText(){
  if (fSetpointLast != ThermostatData.GetSetpoint()){
    fSetpointLast= ThermostatData.GetSetpoint();

    //Clear the Setpoint area
    SetFillColor(_BackgroundColor);

    //DrawFilledRectangle(0, 0, ScreenWidth, ThermoOnBarBottom);
    DrawFilledRectangle(SetpointLeft, SetpointBottom, SetpointWidth, SetpointHeight);

    //Display set-point and off-point at the bottom as in "Set= 87.0, Off= 87.1"
    SetCursor     (SetpointLeft + 2, SetpointTop - 2);
    SetTextColor  (SetpointColor);
    SelectFont    (eSetpointTextFace, eSetpointTextPointSize);

    sprintf(sz100CharDisplayBuffer, "Set= %4.1f", fSetpointLast);
    Print(sz100CharDisplayBuffer);
  } //if(fSetpointLast!=stData.fSetpointDegF)
  return;
} //DisplaySetpointText

void ThermostatDisplayClass::DisplayOffpointText(){
  //float OffPoint= ThermostatData.GetSetpoint() + ThermostatData.GetMaxHeatRange();
  float OffPoint= ThermostatData.GetThermostatOffDeg();
  if (fOffpointLast != OffPoint){
    fOffpointLast= OffPoint;

    //Clear the Offpoint area
    SetFillColor(_BackgroundColor);
    DrawFilledRectangle(OffpointLeft, OffpointBottom, OffpointWidth, OffpointHeight);

    //Display off-point at the bottom as in "Off= 87.1"
    SetCursor     (OffpointLeft + 2, OffpointTop - 2);
    SetTextColor  (OffpointColor);
    SelectFont    (eOffpointTextFace, eOffpointTextPointSize);

    sprintf(sz100CharDisplayBuffer, "Off= %4.1f", fOffpointLast);
    Print(sz100CharDisplayBuffer);
  } //if(fSetpointLast!=stData.fSetpointDegF)
  return;
} //DisplayOffpointText

void ThermostatDisplayClass::DisplayHeatOnBox(){
  //Draw a box, the HeatOnBox, between the Setpoint and Offpoint text, present when heat is on.
  //Draws on top of SetpointText, position it to not overwrite text
  bool  bHeatIsOn         = ThermostatData.GetHeatOn();
  bool  bThermostatIsOn   = ThermostatData.GetThermostatOn();
  bool  bDrawHeatBox      = false;

  if (bHeatIsOn && bThermostatIsOn){
    bDrawHeatBox= true;
  }

  if (bDrawHeatBox != bLastDrawHeatBox){
    bLastDrawHeatBox= bDrawHeatBox;
    Serial << "ThermostatDisplayClass::DisplayHeatOnBox(): Changing bDrawHeatBox to " << bDrawHeatBox << endl;
    //Only turn on the HeatOn box if the thermostat is also on.
    if (bDrawHeatBox){
      SetFillColor(HeatOnBoxColor);
    }
    else{
      SetFillColor(_BackgroundColor);
    }
    DrawFilledRectangle(HeatOnBoxLeft, HeatOnBoxBottom, HeatOnBoxWidth, HeatOnBoxHeight);
  } //if (bDrawHeatBox!=bLastDrawHeatBox)
  return;
} //DisplayHeatOnBox
//Last line.
