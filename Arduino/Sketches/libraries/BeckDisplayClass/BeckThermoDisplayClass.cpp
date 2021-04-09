const char szFileName[]  = "BeckThermoDisplayClass.cpp";
const char szFileDate[]  = "4/9/21a";

#include <BeckThermoDisplayClass.h>

ThermoDisplay::ThermoDisplay() {
  Serial << "ThermoDisplay::ThermoDisplay(): Constructing" << endl;
  return;
} //constructor


ThermoDisplay::~ThermoDisplay() {
  Serial << LOG0 << "~ThermoDisplay(): Destructing" << endl;
} //destructor


void ThermoDisplay::Update(ThermoStruct stData){
  Serial << LOG0 << "Update(): _szLastDegF= " << _szLastDegF << ", _wDisplayCount= " << _wDisplayCount << endl;
  //Format the string to display.
  sprintf(sz100CharBuffer, "%04.1f", stData.fCurrentDegF);

  //Potentially update the display every _wFrequency times that Update() is called
  bool  bUpdateDisplay= false;
  if ((_wDisplayCount++ % _wFrequency) != 0){
    if (strcmp(sz100CharBuffer, _szLastDegF) != 0){
      //Strings are not the same, so we will update the display
      bUpdateDisplay= true;
    }
    else{
      Serial << LOG0 << "Update(): DegF hasn't changed: " << _szLastDegF << " = " << sz100CharBuffer << endl;
      bUpdateDisplay= false;
    }
  }
  else{
    Serial << LOG0 << "Update(): Not MOD _Frequincy, _wDisplayCount= " << _wDisplayCount << endl;
    bUpdateDisplay= false;
  }

  if (true && !bUpdateDisplay){
    //Don't update the display.
    return;
  }

  //_wDisplayCount++;
  //Remember this string to compare to.
  strcpy(_szLastDegF, sz100CharBuffer);

  FillScreen(_BackgroundColor);
  //cDisplay.DrawGrid();

  //Show the current temperature in very large font as in "89.4"
  SetCursor     (DegF_XLeftSide, DegF_YBaseline);
  SetTextColor  (DegF_Color);
  SelectFont    (eDegF_Font, eDegF_PointSize);

  //sprintf(sz100CharBuffer, "%04.1f", stData.fCurrentDegF);
  //Print(sz100CharBuffer);

  Print(_szLastDegF);

  //Fat bar under the large current temperature display, present when thermostat is on.
  if (stData.bThermoOn){
    SetFillColor(BarColor);
  }
  else{
    SetFillColor(_BackgroundColor);
  }

  DrawFilledRectangle( BarLeft, BarTop, BarWidth, BarHeight);

  //Display setpoint and offpoint at the bottom as in "Set= 87.0, Off= 87.1"
  SetCursor(Setpoint_XLeft , Setpoint_YTop);
  SetTextColor(Setpoint_Color);
  SelectFont(eSetpoint_TextFace, eSetpoint_TextPointSize);

  sprintf(sz100CharBuffer, "Set= %4.1f    Off= %4.1f", stData.fSetpointDegF, (stData.fSetpointDegF + stData.fMaxHeatRangeF));
  Print(sz100CharBuffer);

  return;
} //Update
//Last line.
