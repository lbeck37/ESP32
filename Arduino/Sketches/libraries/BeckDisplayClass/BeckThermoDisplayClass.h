#pragma once
// 4/14/21a, BeckThermoDisplayClass.h
#include <BeckDisplayClass.h>
//#include <BeckThermostatClass.h>

typedef int32_t       PUnit;        //Pixel Unit


class ThermoDisplayClass : public ColorDisplay {
//class ThermoDisplayClass : public ColorDisplay {
protected:
  uint32_t    ulCurrentDegFOnTimeSeconds  = 4;
  uint32_t    ulSetpointOnTimeSeconds     = 2;

  uint32_t    ulCurrentDegFOnTimeMsec   = ulCurrentDegFOnTimeSeconds   * lMsecPerSec;
  uint32_t    ulSetpointOnTimeMsec      = ulSetpointOnTimeSeconds      * lMsecPerSec;

  uint32_t    ulNextCurrentDegFDisplay  = 0;
  uint32_t    ulNextSetpointDisplay     = 0;

  uint32_t    ulVeryLargeExtraWaitMsec  = 1000 * lMsecPerSec;   //Time to do next display needs this.

  bool  bFirstTimeDrawn   = true;
  bool  bThermoOnLast     = false;    //Used to check if thermo on bar should be changed.
  bool  bHeatOnLast       = false;    //Used to check if ThermoOnBar bar should be changed.
  float fSetpointLast     = 0.00;     //Used to check if Setpoint text at bottom should be changed.
  bool  bSetPointChanged  = true;     //Used to force the Heat On box to redraw itself after Setpoint text is drawn
  bool  bThermoOnChanged  = true;     //Used to force the Heat On box to redraw itself after change in ThermoOn

  //Current temperature or Setpoint in very large font as in "89.4"
  PUnit           DegF_XLeftSide          =  5;
  PUnit           DegF_YBaseline          = 38;         //ScreenHeight - 97
  Colortype       DegF_Color              = TFT_BLACK;
  Colortype       ThermoSetpoint_Color    = TFT_RED;    //Trying to call it Setpoint_Color and it blew up TFT_eSPI.h
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

  ThermostatClass      BiotaThermostat;

  //Protected methods
  void  DisplayCurrentTemperature   (ThermoStruct stData);
  void  DisplayCurrentSetpoint      (ThermoStruct stData);
  void  DisplayMainScreen           (ThermoStruct stData);
  void  DisplayThermoOnBar          (ThermoStruct stData);
  void  DisplaySetpointLine         (ThermoStruct stData);
  void  DisplayHeatOnBox            (ThermoStruct stData);

public:
  ThermoDisplayClass();
  //ThermoDisplayClass(Thermostat &BiotaThermostatObject);
  virtual ~ThermoDisplayClass();

  void  Setup             (void){}
  void  Handle            (void){}
  void  DrawScreen        (ThermoStruct stData);
};  //ThermoDisplayClass

//extern ThermoDisplayClass        BiotaDisplay;       //This is so every module can use the same object

//Last line.
