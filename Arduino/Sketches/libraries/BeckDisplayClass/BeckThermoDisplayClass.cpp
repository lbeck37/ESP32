const char szFileName[]  = "BeckThermoDisplayClass.cpp";
const char szFileDate[]  = "4/13/21a";

#include <BeckThermoDisplayClass.h>

ThermoDisplay::ThermoDisplay() {
  Serial << LOG0 << "ThermoDisplay::ThermoDisplay(): " << szFileName << ", " << szFileDate << endl;
  return;
} //constructor


ThermoDisplay::~ThermoDisplay() {
  Serial << LOG0 << "~ThermoDisplay(): Destructing" << endl;
} //destructor


void ThermoDisplay::DisplayCurrentTemperature(ThermoStruct stData){
  //Serial << LOG0 << "ThermoDisplay::DisplayCurrentTemperature(): Begin" << endl;
  //Clear the rectangular area where the DegF is displayed
  if (millis() > ulNextCurrentDegFDisplay){
    SetFillColor(_BackgroundColor);

    PUnit YBottom= (ThermoOnBarBottom + ThermoOnBarHeight);
    DrawFilledRectangle( 0, YBottom, ScreenWidth, ScreenHeight);

    SetCursor     (DegF_XLeftSide, DegF_YBaseline);
    SetTextColor  (DegF_Color);
    SelectFont    (eDegF_Font, eDegF_PointSize);

    sprintf(sz100CharBuffer, "%04.1f", stData.fCurrentDegF);
    Print(sz100CharBuffer);

    //Set time for Setpoint to display, it will do same for me
    ulNextSetpointDisplay= millis() + ulCurrentDegFOnTimeMsec;

    //Set next DegF does't fire before Setpoint
    ulNextCurrentDegFDisplay= millis() + ulVeryLargeExtraWaitMsec;
  }
  return;
} //DisplayCurrentTemperature


void ThermoDisplay::DisplayCurrentSetpoint(ThermoStruct stData){
  //Serial << LOG0 << "ThermoDisplay::DisplayCurrentSetpoint(): Begin" << endl;
  //Clear the rectangular area where the Setpoint is displayed
  if(bSetPointChanged || (millis() > ulNextSetpointDisplay)){
    SetFillColor(_BackgroundColor);

    PUnit YBottom= (ThermoOnBarBottom + ThermoOnBarHeight);
    DrawFilledRectangle( 0, YBottom, ScreenWidth, ScreenHeight);

    SetCursor     (DegF_XLeftSide, DegF_YBaseline);
    SetTextColor  (ThermoSetpoint_Color);
    SelectFont    (eDegF_Font, eDegF_PointSize);

    sprintf(sz100CharBuffer, "%04.1f", stData.fSetpointDegF);
    Print(sz100CharBuffer);

    //Set next time the CurrentDegF is displayed, it will do same for me
    ulNextCurrentDegFDisplay= millis() + ulSetpointOnTimeMsec;

    //Set next Setpoint does't fire before next DegF
    ulNextSetpointDisplay= millis() + ulVeryLargeExtraWaitMsec;
  }
  return;
} //DisplayCurrentSetpoint


void ThermoDisplay::UpdateMainScreen(ThermoStruct stData){
  DisplayCurrentSetpoint      (stData);
  DisplayCurrentTemperature   (stData);
  return;
} //UpdateMainScreen


  void ThermoDisplay::DrawScreen(ThermoStruct stData){
  //Draw a fat bar, the ThermoOnBar, under the large current temperature display, present when thermostat is on.
  if (bThermoOnLast != stData.bThermoOn){
    if (stData.bThermoOn){
      SetFillColor(ThermoOnBarColor);
      bThermoOnLast= true;
    } //if(stData.bThermoOn)
    else{
      SetFillColor(_BackgroundColor);
      bThermoOnLast= false;
    } //if(stData.bThermoOn)else
    DrawFilledRectangle(ThermoOnBarLeft, ThermoOnBarBottom, ThermoOnBarWidth, ThermoOnBarHeight);
  } //if(bThermoOnLast!=stData.bThermoOn)

  //Print a line with the string containing the Setpoint and Offpoint values, call it SetpointLine
  if (fSetpointLast != stData.fSetpointDegF){
    fSetpointLast= stData.fSetpointDegF;
    bSetPointChanged= true;

    //Clear the Setpoint area
    SetFillColor(_BackgroundColor);
    DrawFilledRectangle(0, 0, ScreenWidth, ThermoOnBarBottom);

    //Display set-point and off-point at the bottom as in "Set= 87.0, Off= 87.1"
    SetCursor     (Setpoint_XLeft , Setpoint_YTop);
    SetTextColor  (Setpoint_Color);
    SelectFont    (eSetpoint_TextFace, eSetpoint_TextPointSize);

    sprintf(sz100CharBuffer, "Set= %4.1f       Off= %4.1f", stData.fSetpointDegF, (stData.fSetpointDegF + stData.fMaxHeatRangeF));
    Print(sz100CharBuffer);
    //bFirstTimeDrawn= false;
  } //if(fSetpointLast!=stData.fSetpointDegF)

  //Draw a box, the HeatOnBox, between the Setpoint and Offpoint text, present when heat is on.
  //Draws on top of SetpointText, position it to not overwrite text
  if (bSetPointChanged || (bHeatOnLast != stData.bHeatOn)){
    if (stData.bHeatOn){
      SetFillColor(HeatOnBoxColor);
      bHeatOnLast= true;
    } //if(stData.bThermoOn)
    else{
      SetFillColor(_BackgroundColor);
      bHeatOnLast= false;
    } //if(stData.bThermoOn)else
    DrawFilledRectangle( (HeatOnBoxCenter - HeatOnBoxWidth/2), HeatOnBoxBottom, HeatOnBoxWidth, HeatOnBoxHeight);
  } //if(bHeatOnLast!=stData.bHeatOn)

  //Display the current temperature and setpoint temperatures, cycling though selected on times
  UpdateMainScreen(stData);
  bSetPointChanged= false;      //All done with this, used for getting Setpoint up quickly and drawing Heat On box.

  return;
} //DrawScreen
//Last line.
