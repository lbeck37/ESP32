const char szFileName[]  = "BeckThermoDisplayClass.cpp";
const char szFileDate[]  = "4/10/21d";

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
  if(millis() > ulNextSetpointDisplay){
    SetFillColor(_BackgroundColor);

    PUnit YBottom= (ThermoOnBarBottom + ThermoOnBarHeight);
    DrawFilledRectangle( 0, YBottom, ScreenWidth, ScreenHeight);

    SetCursor     (DegF_XLeftSide, DegF_YBaseline);
    SetTextColor  (ThermoSetpoint_Color);
    SelectFont    (eDegF_Font, eDegF_PointSize);

    sprintf(sz100CharBuffer, "%04.1f", stData.fSetpointDegF);
    Print(sz100CharBuffer);

    //Set time for CurrentDegF to display, it will do same for me
    ulNextCurrentDegFDisplay= millis() + ulSetpointOnTimeMsec;

    //Set next Setpoint does't fire before next DegF
    ulNextSetpointDisplay= millis() + ulVeryLargeExtraWaitMsec;
  }
  return;
} //DisplayCurrentSetpoint


void ThermoDisplay::UpdateScreen(ThermoStruct stData){
  DisplayCurrentTemperature   (stData);
  DisplayCurrentSetpoint      (stData);
  return;
} //UpdateScreen


  void ThermoDisplay::DrawScreen(ThermoStruct stData){
/* Old debug line
  PUnit MsecUntilNextDegF       = ulNextCurrentDegFDisplay  - millis();
  PUnit MsecUntilNextSetpoint   = ulNextSetpointDisplay     - millis();
  Serial << endl << LOG0 << "ThermoDisplay::DrawScreen(): Before UpdateDisplay(), Msec until next firing: DegF= " << MsecUntilNextDegF << ", Set= " << MsecUntilNextSetpoint << endl;
*/
  //Display the current temperature and setpoint temperatures, cycling though selected on times
  UpdateScreen(stData);

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
  if (bFirstTimeDrawn){
    //Only draw the Setpoint and Offpoint since they currently don't change.
    //Display setpoint and offpoint at the bottom as in "Set= 87.0, Off= 87.1"
    SetCursor     (Setpoint_XLeft , Setpoint_YTop);
    SetTextColor  (Setpoint_Color);
    SelectFont    (eSetpoint_TextFace, eSetpoint_TextPointSize);

    sprintf(sz100CharBuffer, "Set= %4.1f       Off= %4.1f", stData.fSetpointDegF, (stData.fSetpointDegF + stData.fMaxHeatRangeF));
    Print(sz100CharBuffer);
    bFirstTimeDrawn= false;
  } //if(bFirstTimeDrawn)

  //Draw a box, the HeatOnBox, between the Setpoint and Offpoint text, present when heat is on.
  //Draws on top of SetpointText, position it to not overwrite text
  if (bHeatOnLast != stData.bHeatOn){
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

  return;
} //DrawScreen
//Last line.
