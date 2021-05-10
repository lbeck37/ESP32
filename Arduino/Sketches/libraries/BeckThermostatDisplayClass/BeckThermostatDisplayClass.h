// BeckThermostatDisplayClass.h, 5/9/21a
#pragma once
//Initially used for TTGO ESP32 module. 135 x 240, 1.14", 240dpi display

#include <BeckDisplayClass.h>
#include <TFT_eSPI.h>

class ThermostatDisplayClass : public TTGO_DisplayClass {
public:
  ThermostatDisplayClass();
  virtual ~ThermostatDisplayClass();

  void  Setup         (void);
  void  Handle        (void);

protected:
  uint32_t      DegFOnTimeSeconds     = 4;
  uint32_t      SetpointOnTimeSeconds = 2;
  uint32_t      OnTimeMsec[NumberOfScreens]= {DegFOnTimeSeconds*1000, SetpointOnTimeSeconds*1000};

  uint32_t    ulNextDisplayChange       = 0;

  uint32_t    ulVeryLargeExtraWaitMsec  = 1000 * 1000;   //Time to do next display needs this.

  //bool  bFirstTimeDrawn   = true;
  float       fCurrentDegFLast  = 0.00;
  float       fSetpointLast     = 0.00;
  float       fOffpointLast     = 0.00;
  float       fMaxHeatRangeLast = 0.10;
  bool        bThermoOnLast     = false;
  bool        bLastDrawHeatBox  = false;
  bool        ForceScreenUpdate = true;
  ScreenType  CurrentScreen     = eDegFScreen;

  //Current temperature or Setpoint in very large font as in "89.4"
  PUnit           DegF_XLeftSide          =  5;
  PUnit           DegF_YBaseline          = 38;         //ScreenHeight - 97
  Colortype       DegF_Color              = TFT_BLACK;
  Colortype       ThermoSetpoint_Color    = TFT_RED;    //Call it Setpoint_Color and it blows up TFT_eSPI.h
  FontFaceType    eDegF_Font              = eRobotoCondensedFace;
  FontPointType   eDegF_PointSize         = e130point;

  //Fat bar under the large current temperature display
  //Is present when thermostat (not just the heat) is on.
  PUnit     ThermoOnBarLeft   = 0;
  PUnit     ThermoOnBarRight  = ScreenWidth;
  PUnit     ThermoOnBarBottom = 23;
  PUnit     ThermoOnBarTop    = ThermoOnBarBottom + ThermoOnBarHeight;
  PUnit     ThermoOnBarWidth  = ThermoOnBarRight - ThermoOnBarLeft;
  PUnit     ThermoOnBarHeight = 12;
  Colortype ThermoOnBarColor  = TFT_RED;

  PUnit     HeatOnBoxCenter   = (ScreenWidth / 2);
  PUnit     HeatOnBoxWidth    = 24;
  PUnit     HeatOnBoxLeft     = HeatOnBoxCenter   - (HeatOnBoxWidth / 2);
  PUnit     HeatOnBoxRight    = HeatOnBoxLeft     + HeatOnBoxWidth;
  PUnit     HeatOnBoxBottom   = 0;
  PUnit     HeatOnBoxTop      = ThermoOnBarBottom;
  PUnit     HeatOnBoxHeight   = HeatOnBoxTop - HeatOnBoxBottom;
  Colortype HeatOnBoxColor    = TFT_RED;

  PUnit     SetpointLeft      = 0;
  PUnit     SetpointRight     = HeatOnBoxLeft;
  PUnit     SetpointBottom    = 0;
  PUnit     SetpointTop       = ThermoOnBarBottom;
  PUnit     SetpointWidth     = SetpointRight - SetpointLeft;
  PUnit     SetpointHeight    = SetpointTop   - SetpointBottom;
  Colortype SetpointColor    = TFT_BLACK;

  PUnit     OffpointLeft      = HeatOnBoxRight;
  PUnit     OffpointRight     = ScreenWidth;
  PUnit     OffpointBottom    = 0;
  PUnit     OffpointTop       = ThermoOnBarBottom;
  PUnit     OffpointWidth     = OffpointRight - OffpointLeft;
  PUnit     OffpointHeight    = OffpointTop   - OffpointBottom;
  Colortype OffpointColor    = TFT_BLACK;

  FontFaceType    eSetpointTextFace        = eTextFace;
  FontPointType   eSetpointTextPointSize   = eText26px;

  FontFaceType    eOffpointTextFace        = eTextFace;
  FontPointType   eOffpointTextPointSize   = eText26px;

  //Protected methods
  void  DisplayMainScreen           (void);
  void  DisplayCurrentTemperature   (bool ForceUpdate);
  void  DisplayCurrentSetpoint      (bool ForceUpdate);
  void  DisplayThermoOnBar          (void);
  void  DisplaySetpointText         (void);
  void  DisplayOffpointText         (void);
  void  DisplayHeatOnBox            (void);
};  //ThermostatDisplayClass

extern ThermostatDisplayClass    ThermostatDisplay;       //This is so every module can use the same object

//Last line.
