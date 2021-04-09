// 4/9/21a, BeckThermoDisplayClass.h
#include <BeckDisplayClass.h>

class ThermoDisplay : public ColorDisplay {
protected:
  //Show the current temperature in very large font as in "89.4"
  PUnit           DegF_XLeftSide    =  5;
  PUnit           DegF_YBaseline    = 97;
  Colortype       DegF_Color        = TFT_BLACK;
  FontFaceType    eDegF_Font        = eRobotoCondensedFace;
  FontPointType   eDegF_PointSize   = e130point;

  //Fat bar under the large current temperature display
  //Is present when thermostat (not just the heat) is on.
  PUnit     BarLeft     =   0;
  PUnit     BarTop      = 102;
  PUnit     BarWidth    = 240;
  PUnit     BarHeight   =  10;
  Colortype BarColor    = TFT_RED;

  //Display setpoint and offpoint at the bottom as in "Set= 87.0, Off= 87.1"
  PUnit           Setpoint_XLeft            = 10;
  PUnit           Setpoint_YTop             = 113;
  Colortype       Setpoint_Color            = TFT_BLACK;
  FontFaceType    eSetpoint_TextFace        = eTextFace;
  FontPointType   eSetpoint_TextPointSize   = eText26px;

public:
  ThermoDisplay();
  virtual ~ThermoDisplay();

  void  Update        (ThermoStruct stData);
  //bool  bIsDataNew    (ThermoStruct stData);
};  //ThermoDisplay class
//Last line.
