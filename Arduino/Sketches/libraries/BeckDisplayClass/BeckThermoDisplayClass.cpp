const char szFileName[]  = "BeckThermoDisplayClass.cpp";
const char szFileDate[]  = "4/9/21b";

#include <BeckThermoDisplayClass.h>

ThermoDisplay::ThermoDisplay() {
  Serial << "ThermoDisplay::ThermoDisplay(): " << szFileName << ", " << szFileDate << endl;
  return;
} //constructor


ThermoDisplay::~ThermoDisplay() {
  Serial << LOG0 << "~ThermoDisplay(): Destructing" << endl;
} //destructor


void ThermoDisplay::DrawScreen(ThermoStruct stData){
  //Serial << LOG0 << "DrawScreen(): _szLastDegF= " << _szLastDegF << ", _wDisplayCount= " << _wDisplayCount << endl;

  //Screen is potentially redrawn every 5(?) seconds.
  if (millis() < ulNextThermDisplayMsec){
    return;
  } //if(millis()<ulNextThermDisplayMsec)

  //Set the next time to update display.
  ulNextThermDisplayMsec= millis() + ulThermDisplayrPeriodMsec;

  //Format the string to display.
  sprintf(sz100CharBuffer, "%04.1f", stData.fCurrentDegF);

  if (strcmp(sz100CharBuffer, _szLastDegF) == 0){
      //Strings are  the same, so return without updating the display.
      Serial << LOG0 << "ThermoDisplay::DrawScreen(): DegF hasn't changed: " << _szLastDegF << " = " << sz100CharBuffer << endl;
      return;
   }  //if(strcmp(sz100CharBuffer, _szLastDegF)

  //Remember the current value to check for changed on next screen draw
  strcpy(_szLastDegF, sz100CharBuffer);

  //FillScreen(_BackgroundColor);
  SetFillColor(_BackgroundColor);
  DrawFilledRectangle( 0, 0, ScreenWidth, BarTop);

  //Show the current temperature in very large font as in "89.4"
  SetCursor     (DegF_XLeftSide, DegF_YBaseline);
  SetTextColor  (DegF_Color);
  SelectFont    (eDegF_Font, eDegF_PointSize);

  Print(_szLastDegF);

  bool bDebug= false;
  //Fat bar under the large current temperature display, present when thermostat is on.
  if (bDebug || (bThermoWasOn != stData.bThermoOn)){
    if (stData.bThermoOn){
      SetFillColor(BarColor);
      bThermoWasOn= true;
    } //if(stData.bThermoOn)
    else{
      SetFillColor(_BackgroundColor);
      bThermoWasOn= false;
    } //if(stData.bThermoOn)else
    DrawFilledRectangle( BarLeft, BarTop, BarWidth, BarHeight);
  } //if(bThermoWasOn!=stData.bThermoOn)

  if (bDebug || bFirstTimeDrawn){
    //Only draw the Setpoint and Offpoint since they currently don't change.
    //Display setpoint and offpoint at the bottom as in "Set= 87.0, Off= 87.1"
    SetCursor     (Setpoint_XLeft , Setpoint_YTop);
    SetTextColor  (Setpoint_Color);
    SelectFont    (eSetpoint_TextFace, eSetpoint_TextPointSize);

    sprintf(sz100CharBuffer, "Set= %4.1f    Off= %4.1f", stData.fSetpointDegF, (stData.fSetpointDegF + stData.fMaxHeatRangeF));
    Print(sz100CharBuffer);
    bFirstTimeDrawn= false;
  } //if(bFirstTimeDrawn)

  return;
} //DrawScreen
//Last line.
