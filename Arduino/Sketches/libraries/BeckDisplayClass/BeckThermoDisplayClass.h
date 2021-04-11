#pragma once
// 4/10/21b, BeckThermoDisplayClass.h
#include <BeckDisplayClass.h>

class ThermoDisplay : public ColorDisplay {
protected:
  const  uint32_t    ulThermDisplayrPeriodMsec    = 5 * lMsecPerSec; //mSec between updating the display
         uint32_t    ulNextThermDisplayMsec       = 0;

  bool bFirstTimeDrawn  = true;
  bool bThermoOnLast    = false;    //Used to check if thermo on bar should be changed.
  bool bHeatOnLast      = false;    //Used to check if ThermoOnBar bar should be changed.

  //Show the current temperature in very large font as in "89.4"
  PUnit           DegF_XLeftSide    =  5;
  PUnit           DegF_YBaseline    = 38;         //ScreenHeight - 97
  Colortype       DegF_Color        = TFT_BLACK;
  FontFaceType    eDegF_Font        = eRobotoCondensedFace;
  FontPointType   eDegF_PointSize   = e130point;

  //Fat bar under the large current temperature display
  //Is present when thermostat (not just the heat) is on.
  PUnit     ThermoOnBarLeft     =  0;
  PUnit     ThermoOnBarBottom   = 23;
  PUnit     ThermoOnBarWidth    = ScreenWidth;
  PUnit     ThermoOnBarHeight   = 10;
  Colortype ThermoOnBarColor    = TFT_RED;

  PUnit     HeatOnBoxCenter   = (ScreenWidth / 2);
  PUnit     HeatOnBoxBottom   = 0;
  PUnit     HeatOnBoxWidth    = 24;
  PUnit     HeatOnBoxHeight   = ThermoOnBarBottom - HeatOnBoxBottom;
  Colortype HeatOnBoxColor    = TFT_RED;

  //Display setpoint and offpoint at the bottom as in "Set= 87.0, Off= 87.1"
  PUnit           Setpoint_XLeft            =  0;
  //PUnit           Setpoint_YTop             = 113;
  PUnit           Setpoint_YTop             = 22;            //ScreenHeight - 102
  Colortype       Setpoint_Color            = TFT_BLACK;
  FontFaceType    eSetpoint_TextFace        = eTextFace;
  FontPointType   eSetpoint_TextPointSize   = eText26px;

public:
  ThermoDisplay();
  virtual ~ThermoDisplay();

  void  DrawScreen        (ThermoStruct stData);
};  //ThermoDisplay class
//Last line.
