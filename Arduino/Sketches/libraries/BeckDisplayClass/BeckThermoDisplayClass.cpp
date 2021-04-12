const char szFileName[]  = "BeckThermoDisplayClass.cpp";
const char szFileDate[]  = "4/10/21b";

#include <BeckThermoDisplayClass.h>

ThermoDisplay::ThermoDisplay() {
  Serial << LOG0 << "ThermoDisplay::ThermoDisplay(): " << szFileName << ", " << szFileDate << endl;
  return;
} //constructor


ThermoDisplay::~ThermoDisplay() {
  Serial << LOG0 << "~ThermoDisplay(): Destructing" << endl;
} //destructor


void ThermoDisplay::DisplayCurrentTemperature(ThermoStruct stData){
  Serial << LOG0 << "ThermoDisplay::DisplayCurrentTemperature(): Begin" << endl;
  //Clear the rectangular area where the DegF is displayed
  SetFillColor(_BackgroundColor);
  DrawFilledRectangle( 0, (ThermoOnBarBottom + ThermoOnBarHeight), ScreenWidth, ScreenHeight);

  SetCursor     (DegF_XLeftSide, DegF_YBaseline);
  SetTextColor  (DegF_Color);
  SelectFont    (eDegF_Font, eDegF_PointSize);

  sprintf(sz100CharBuffer, "%04.1f", stData.fCurrentDegF);
  Print(sz100CharBuffer);
  return;
}

void ThermoDisplay::DisplayCurrentSetpoint(ThermoStruct stData){
  //Serial << LOG0 << "ThermoDisplay::DisplayCurrentSetpoint(): Begin" << endl;
  //Clear the rectangular area where the Setpoint is displayed
  SetFillColor(_BackgroundColor);

  PUnit YBottom= (ThermoOnBarBottom + ThermoOnBarHeight);
  //DrawFilledRectangle( 0, (ThermoOnBarBottom + ThermoOnBarHeight), ScreenWidth, ScreenHeight);
  DrawFilledRectangle( 0, YBottom, ScreenWidth, ScreenHeight);

  SetCursor     (DegF_XLeftSide, DegF_YBaseline);
  //SetTextColor  (Setpoint_Color);
  SetTextColor  (ThermoSetpoint_Color);
  SelectFont    (eDegF_Font, eDegF_PointSize);

  sprintf(sz100CharBuffer, "%04.1f", stData.fSetpointDegF);
  Print(sz100CharBuffer);
  return;
}

void ThermoDisplay::UpdateDisplay(ThermoStruct stData){
  if (millis() > ulNextCurrentDegFDisplay){
    DisplayCurrentTemperature(stData);

    //Set time for Setpoint to display, it will do same for me
    ulNextSetpointDisplay= millis() + ulCurrentDegFOnTimeMsec;

    //Set next DegF does't fire before Setpoint
    ulNextCurrentDegFDisplay= millis() + ulVeryLargeExtraWaitMsec;
  }

  if(millis() > ulNextSetpointDisplay){
    DisplayCurrentSetpoint(stData);

    //Serial << LOG0 << "ThermoDisplay::UpdateDisplay(): Set ulNextCurrentDegFDisplay, ulSetpointOnTimeMsec= " << ulSetpointOnTimeMsec << endl;
    //Set time for CurrentDegF to display, it will do same for me
    ulNextCurrentDegFDisplay= millis() + ulSetpointOnTimeMsec;

    //Set next Setpoint does't fire before next DegF
    ulNextSetpointDisplay= millis() + ulVeryLargeExtraWaitMsec;
  }
  return;
} //UpdateDisplay

  void ThermoDisplay::DrawScreen(ThermoStruct stData){
  //Serial << LOG0 << "DrawScreen(): _szLastDegF= " << _szLastDegF << ", _wDisplayCount= " << _wDisplayCount << endl;

/*
  //Screen is currently (4/10/21) redrawn every 5 seconds.
  if (millis() < ulNextThermDisplayMsec){
    return;
  } //if(millis()<ulNextThermDisplayMsec)
*/
  //See if it's time for DegF display to start and if not, check if it's time for Setpoint.

  //DisplayCurrentTemperature(stData);

/*
  if (millis() > ulNextCurrentDegFDisplay){
    DisplayCurrentTemperature(stData);

    //Set time for Setpoint to display, it will do same for me
    ulNextSetpointDisplay= millis() + ulCurrentDegFOnTimeMsec;

    //Set next DegF does't fire before Setpoint
    ulNextCurrentDegFDisplay= millis() + ulVeryLargeExtraWaitMsec;
  }

  if(millis() < ulNextSetpointDisplay){
    DisplayCurrentSetpoint(stData);

    //Set time for CurrentDegF to display, it will do same for me
    ulNextCurrentDegFDisplay= millis() + ulSetpointOnTimeMsec;

    //Set next Setpoint does't fire before next DegF
    ulNextSetpointDisplay= millis() + ulVeryLargeExtraWaitMsec;
  }
*/
/*
  //Set the next time to update display.
  //ulNextThermDisplayMsec= millis() + ulThermDisplayPeriodMsec;

  //Format the string to display.
  //sprintf(sz100CharBuffer, "%04.1f", stData.fCurrentDegF);


  if (strcmp(sz100CharBuffer, _szLastDegF) == 0){
      //Strings are  the same, so return without updating the display.
      Serial << LOG0 << "ThermoDisplay::DrawScreen(): DegF hasn't changed: " << _szLastDegF << " = " << sz100CharBuffer << endl;
      return;
   }  //if(strcmp(sz100CharBuffer, _szLastDegF)

  //Remember the current value to check for having changed on next screen draw
  strcpy(_szLastDegF, sz100CharBuffer);



  //Clear the rectangular area where the DegF is displayed
  SetFillColor(_BackgroundColor);
  DrawFilledRectangle( 0, (ThermoOnBarBottom + ThermoOnBarHeight), ScreenWidth, ScreenHeight);


  //Show the current temperature in very large font as in "89.4"

  SetCursor     (DegF_XLeftSide, DegF_YBaseline);
  SetTextColor  (DegF_Color);
  SelectFont    (eDegF_Font, eDegF_PointSize);
  Print(_szLastDegF);


  //delay(ulSetpointOnTimeMsec);


    ulNextCurrentDegFDisplay= millis() + ulSetpointOnTimeMsec;

    //Set next Setpoint does't fire before next DegF
    ulNextSetpointDisplay= millis() + ulVeryLargeExtraWaitMsec;
*/

  PUnit MsecUntilNextDegF;
  PUnit MsecUntilNextSetpoint;

  MsecUntilNextDegF       = ulNextCurrentDegFDisplay  - millis();
  MsecUntilNextSetpoint   = ulNextSetpointDisplay     - millis();
  Serial << endl << LOG0 << "ThermoDisplay::DrawScreen(): Before UpdateDisplay(), Msec until next firing: DegF= " << MsecUntilNextDegF << ", Set= " << MsecUntilNextSetpoint << endl;

  //Display the current temperature and setpoint temperatures, cycling though selected on times
  UpdateDisplay(stData);

  MsecUntilNextDegF       = ulNextCurrentDegFDisplay  - millis();
  MsecUntilNextSetpoint   = ulNextSetpointDisplay     - millis();
  Serial << LOG0 << "ThermoDisplay::DrawScreen(): After UpdateDisplay(), Msec until next firing: DegF= " << MsecUntilNextDegF << ", Set= " << MsecUntilNextSetpoint << endl;

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
