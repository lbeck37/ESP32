const char szFileName[]  = "BeckThermoDisplayClass.cpp";
const char szFileDate[]  = "4/9/21a";

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

  ulNextThermDisplayMsec= millis() + ulThermDisplayrPeriodMsec;

  //Format the string to display.
  sprintf(sz100CharBuffer, "%04.1f", stData.fCurrentDegF);

  if (strcmp(sz100CharBuffer, _szLastDegF) == 0){
      //Strings are  the same, so return without updating the display.
      Serial << LOG0 << "ThermoDisplay::DrawScreen(): DegF hasn't changed: " << _szLastDegF << " = " << sz100CharBuffer << endl;
      return;
   }  //if(strcmp(sz100CharBuffer, _szLastDegF)

  strcpy(_szLastDegF, sz100CharBuffer);

  FillScreen(_BackgroundColor);

  //Show the current temperature in very large font as in "89.4"
  SetCursor     (DegF_XLeftSide, DegF_YBaseline);
  SetTextColor  (DegF_Color);
  SelectFont    (eDegF_Font, eDegF_PointSize);

  Print(_szLastDegF);

  //Fat bar under the large current temperature display, present when thermostat is on.
  if (stData.bThermoOn){
    SetFillColor(BarColor);
  } //if(stData.bThermoOn)
  else{
    SetFillColor(_BackgroundColor);
  } //if(stData.bThermoOn)else

  DrawFilledRectangle( BarLeft, BarTop, BarWidth, BarHeight);

  //Display setpoint and offpoint at the bottom as in "Set= 87.0, Off= 87.1"
  SetCursor     (Setpoint_XLeft , Setpoint_YTop);
  SetTextColor  (Setpoint_Color);
  SelectFont    (eSetpoint_TextFace, eSetpoint_TextPointSize);

  sprintf(sz100CharBuffer, "Set= %4.1f    Off= %4.1f", stData.fSetpointDegF, (stData.fSetpointDegF + stData.fMaxHeatRangeF));
  Print(sz100CharBuffer);

  return;
} //DrawScreen
//Last line.
