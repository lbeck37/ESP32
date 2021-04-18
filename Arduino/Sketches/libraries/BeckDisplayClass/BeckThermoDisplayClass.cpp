const char szThermoDisplayFileName[]  = "BeckThermoDisplayClass.cpp";
const char szThermoDisplayFileDate[]  = "4/17/21c";

//#include <BeckThermoDisplayClass.h>
#include <BeckDisplayClass.h>
#include <BeckSystemClass.h>
#include <Streaming.h>

//TTGO 1.4" display
PUnit     ScreenWidth           = 240;
PUnit     ScreenHeight          = 135;
char      sz100CharBuffer[100];           //For building strings for display


ThermoDisplayClass        BiotaDisplay;

ThermoDisplayClass::ThermoDisplayClass() {
  Serial << LOG0 << "ThermoDisplayClass::ThermoDisplayClass(): " << szThermoDisplayFileName << ", " << szThermoDisplayFileDate << endl;
  return;
} //constructor


ThermoDisplayClass::~ThermoDisplayClass() {
  Serial << LOG0 << "~ThermoDisplayClass(): Destructing" << endl;
} //destructor


void  Setup(void){
  return;
} //Setup


void  Handle(void){
  return;
} //Handle


void ThermoDisplayClass::DisplayCurrentTemperature(){
  //Serial << LOG0 << "ThermoDisplayClass::DisplayCurrentTemperature(): Begin" << endl;
  //Clear the rectangular area where the DegF is displayed
  if (millis() > ulNextCurrentDegFDisplay){
    SetFillColor(_BackgroundColor);

    PUnit YBottom= (ThermoOnBarBottom + ThermoOnBarHeight);
    DrawFilledRectangle( 0, YBottom, ScreenWidth, ScreenHeight);

    SetCursor     (DegF_XLeftSide, DegF_YBaseline);
    SetTextColor  (DegF_Color);
    SelectFont    (eDegF_Font, eDegF_PointSize);

    sprintf(sz100CharBuffer, "%04.1f", BiotaThermostat.GetCurrentDegF());
    Print(sz100CharBuffer);

    //Set time for Setpoint to display, it will do same for me
    ulNextSetpointDisplay= millis() + ulCurrentDegFOnTimeMsec;

    //Set next DegF does't fire before Setpoint
    ulNextCurrentDegFDisplay= millis() + ulVeryLargeExtraWaitMsec;
  }
  return;
} //DisplayCurrentTemperature


void ThermoDisplayClass::DisplayCurrentSetpoint(){
  //Serial << LOG0 << "ThermoDisplayClass::DisplayCurrentSetpoint(): Begin" << endl;
  //Clear the rectangular area where the Setpoint is displayed
  if(BiotaThermostat.GetThermostatOn() &&(bSetPointChanged || (millis() > ulNextSetpointDisplay))){
    SetFillColor(_BackgroundColor);

    PUnit YBottom= (ThermoOnBarBottom + ThermoOnBarHeight);
    DrawFilledRectangle( 0, YBottom, ScreenWidth, ScreenHeight);

    SetCursor     (DegF_XLeftSide, DegF_YBaseline);
    SetTextColor  (ThermoSetpoint_Color);
    SelectFont    (eDegF_Font, eDegF_PointSize);

    sprintf(sz100CharBuffer, "%04.1f", BiotaThermostat.GetSetpoint());
    Print(sz100CharBuffer);

    //Set next time the CurrentDegF is displayed, it will do same for me
    ulNextCurrentDegFDisplay= millis() + ulSetpointOnTimeMsec;

    //Set next Setpoint does't fire before next DegF
    ulNextSetpointDisplay= millis() + ulVeryLargeExtraWaitMsec;
  }
  return;
} //DisplayCurrentSetpoint

void ThermoDisplayClass::DisplayMainScreen(){
  //Serial << LOG0 << "ThermoDisplayClass::DisplayMainScreen(): Begin" << endl;
  DisplayCurrentSetpoint();
  DisplayCurrentTemperature();
  return;
} //DisplayMainScreen

void ThermoDisplayClass::DisplayThermoOnBar(){
  //Draw a fat bar, the ThermoOnBar, under the large current temperature display, present when thermostat is on.
  if (bThermoOnLast != BiotaThermostat.GetThermostatOn()){
    bThermoOnChanged= true;
    //if (stData.bThermoOn){
    if (BiotaThermostat.GetThermostatOn()){
      SetFillColor(ThermoOnBarColor);
      bThermoOnLast= true;
    } //if(stData.bThermoOn)
    else{
      SetFillColor(_BackgroundColor);
      bThermoOnLast= false;
    } //if(stData.bThermoOn)else
    DrawFilledRectangle(ThermoOnBarLeft, ThermoOnBarBottom, ThermoOnBarWidth, ThermoOnBarHeight);
  } //if(bThermoOnLast!=stData.bThermoOn)
  else{
    bThermoOnChanged= true;
  }
  return;
} //DisplayThermoOnBar

void ThermoDisplayClass::DisplaySetpointLine(){
  //Print a line with the string containing the Setpoint and Offpoint values, call it SetpointLine
  if (fSetpointLast != BiotaThermostat.GetSetpoint()){
    fSetpointLast= BiotaThermostat.GetSetpoint();
    bSetPointChanged= true;

    //Clear the Setpoint area
    SetFillColor(_BackgroundColor);
    DrawFilledRectangle(0, 0, ScreenWidth, ThermoOnBarBottom);

    //Display set-point and off-point at the bottom as in "Set= 87.0, Off= 87.1"
    SetCursor     (Setpoint_XLeft , Setpoint_YTop);
    SetTextColor  (Setpoint_Color);
    SelectFont    (eSetpoint_TextFace, eSetpoint_TextPointSize);

    sprintf(sz100CharBuffer, "Set= %4.1f       Off= %4.1f", BiotaThermostat.GetSetpoint(),
        (BiotaThermostat.GetSetpoint() + BiotaThermostat.GetMaxHeatRange()));
    Print(sz100CharBuffer);
  } //if(fSetpointLast!=stData.fSetpointDegF)
  return;
} //DisplaySetpointLine

void ThermoDisplayClass::DisplayHeatOnBox(){
  //Draw a box, the HeatOnBox, between the Setpoint and Offpoint text, present when heat is on.
  //Draws on top of SetpointText, position it to not overwrite text
  if (bThermoOnChanged || bSetPointChanged || (bHeatOnLast != BiotaThermostat.GetHeatOn())){
    if (BiotaThermostat.GetThermostatOn() && BiotaThermostat.GetHeatOn()){
      SetFillColor(HeatOnBoxColor);
      bHeatOnLast= true;
    } //if(stData.bThermoOn)
    else{
      SetFillColor(_BackgroundColor);
      bHeatOnLast= false;
    } //if(stData.bThermoOn)else
    DrawFilledRectangle( (HeatOnBoxCenter - HeatOnBoxWidth/2), HeatOnBoxBottom, HeatOnBoxWidth, HeatOnBoxHeight);
  } //if(stData.bThermoOn&&...
  return;
} //DisplayHeatOnBox

void ThermoDisplayClass::DrawScreen(){
  //Serial << LOG0 << "ThermoDisplayClass::DrawScreen(): Begin" << endl;
  DisplayThermoOnBar    ();
  DisplaySetpointLine   ();
  DisplayHeatOnBox      ();
  DisplayMainScreen     ();
  bSetPointChanged= false;    //All done with this, used for getting Setpoint up quickly and drawing Heat On box.
  return;
} //DrawScreen
//Last line.
