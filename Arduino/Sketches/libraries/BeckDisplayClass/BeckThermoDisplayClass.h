#pragma once
// 4/10/21b, BeckThermoDisplayClass.h
#include <BeckDisplayClass.h>

class ThermoDisplay : public ColorDisplay {
protected:
  //uint32_t    ulUpdatePeriodSeconds     = 5;
  uint32_t    ulCurrentDegFOnTimeSeconds  = 4;
  uint32_t    ulSetpointOnTimeSeconds     = 2;

  uint32_t    ulCurrentDegFOnTimeMsec   = ulCurrentDegFOnTimeSeconds   * lMsecPerSec;
  uint32_t    ulSetpointOnTimeMsec      = ulSetpointOnTimeSeconds      * lMsecPerSec;

  uint32_t    ulNextCurrentDegFDisplay  = 0;
  uint32_t    ulNextSetpointDisplay     = 0;

  uint32_t    ulVeryLargeExtraWaitMsec  = 1000 * lMsecPerSec;   //Time to do next display needs this.

  //uint32_t    ulThermDisplayPeriodMsec    = ulUpdatePeriodSeconds     * lMsecPerSec; //mSec between updating the display
  //uint32_t    ulSetpointOnTimeMsec        = ulSetpointOnTimeSeconds   * lMsecPerSec;
  //uint32_t    ulNextThermDisplayMsec      = 0;

  bool bFirstTimeDrawn  = true;
  bool bThermoOnLast    = false;    //Used to check if thermo on bar should be changed.
  bool bHeatOnLast      = false;    //Used to check if ThermoOnBar bar should be changed.

  //Current temperature or Setpoint in very large font as in "89.4"
  PUnit           DegF_XLeftSide          =  5;
  PUnit           DegF_YBaseline          = 38;         //ScreenHeight - 97
  Colortype       DegF_Color              = TFT_BLACK;
  Colortype       ThermoSetpoint_Color    = TFT_RED;
  //Colortype       Setpoint_Color    = TFT_ORANGE;
  FontFaceType    eDegF_Font              = eRobotoCondensedFace;
  FontPointType   eDegF_PointSize         = e130point;

  //Fat bar under the large current temperature display
  //Is present when thermostat (not just the heat) is on.
  PUnit     ThermoOnBarLeft     =  0;
  PUnit     ThermoOnBarBottom   = 23;
  PUnit     ThermoOnBarWidth    = ScreenWidth;
  PUnit     ThermoOnBarHeight   = 10 + 2;
  Colortype ThermoOnBarColor    = TFT_RED;

  PUnit     HeatOnBoxCenter   = (ScreenWidth / 2);
  PUnit     HeatOnBoxBottom   = 0;
  PUnit     HeatOnBoxWidth    = 24;
  PUnit     HeatOnBoxHeight   = ThermoOnBarBottom - HeatOnBoxBottom;
  Colortype HeatOnBoxColor    = TFT_RED;

  //Display setpoint and offpoint at the bottom as in "Set= 87.0, Off= 87.1"
  PUnit           Setpoint_XLeft            =  0;
  PUnit           Setpoint_YTop             = 22;            //ScreenHeight - 102
  Colortype       Setpoint_Color            = TFT_BLACK;
  FontFaceType    eSetpoint_TextFace        = eTextFace;
  FontPointType   eSetpoint_TextPointSize   = eText26px;

  void  DisplayCurrentTemperature   (ThermoStruct stData);
  void  DisplayCurrentSetpoint      (ThermoStruct stData);
  void  UpdateDisplay               (ThermoStruct stData);

public:
  ThermoDisplay();
  virtual ~ThermoDisplay();

  void  DrawScreen        (ThermoStruct stData);
};  //ThermoDisplay class
//Last line.
