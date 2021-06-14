// BeckEnviroDisplayClass.h, 6/14/21a
#pragma once

/*
#include <BeckBiotaDefines.h>
#if DO_TTGO
  #include <BeckTTGODisplayClass.h>
#endif
#if DO_ROVER
  #include <BeckRoverDisplayClass.h>
#endif
#include <TFT_eSPI.h>
*/
#include <BeckBiotaDefines.h>
#include <BeckMiniLib.h>
//#include <BeckRoverDisplayClass.h>
#if DO_ROVER
  #include <BeckRoverDisplayClass.h>
#endif
#if DO_TTGO
  #include <BeckTTGODisplayClass.h>
#endif

enum GasType{
  eNoGasType= -1,
  eCO2Gas,
  eVOCGas,
  eLastGasType
};

enum BarSegmentType{
  eNoBarSegmentType= -1,
  eGreenBarSegment,
  eYellowBarSegment,
  eRedBarSegment,
  eLastBarSegmentType
};

class EnviroDisplayClass : public RoverDisplayClass {
public:
  EnviroDisplayClass();
  virtual ~EnviroDisplayClass();

  void  Setup               (void);
  void  Handle              (void);

protected:
  void  DisplayClear        (void);
  bool  bScreenChanged      (void);
  void  DisplayCO2          (int32_t CO2_Value);
  void  DisplayVOC          (void);
  void  DisplayLowerBanner  (void);

  ColorType         Gas_BackgroundColor             = BECK_BLACK;
  ColorType         Gas_FontColor                   = BECK_CYAN;

  FontFaceType      eGas_Font                       = eMonospacedBold;
  FontPointType     eGas_PointSize                  = e30point;

  PUnit             BlankTextLeftDots               =  72;     //Area of screen to clear before writing text values
  PUnit             BlankTextWidthDots              =  84;
  PUnit             BlankTextHeightDots             =  30;
  PUnit             BlankTextCO2BottomDots          = 108;
  PUnit             BlankTextVOCBottomDots          =  40;

  uint32_t          ulNextGasSensorDisplayMsec      = 0;
  uint32_t          ulGasSensorDisplayPeriodMsec    = 1000; //mSec between updating display

  int32_t           CO2_LastValue                   = -1;
  int32_t           VOC_LastValue                   = -1;

  int32_t           CO2_GreenStartValue             =    0;   // parts/million
  int32_t           CO2_YellowStartValue            =  600;
  int32_t           CO2_RedStartValue               = 1000;
  int32_t           CO2_RedEndValue                 = 2000;

  int32_t           VOC_GreenStartValue             =    0;   // parts/billion
  int32_t           VOC_YellowStartValue            =  200;
  int32_t           VOC_RedStartValue               =  600;
  int32_t           VOC_RedEndValue                 = 1000;

  int32_t           CO2_GreenStartPercent           =   0;    // Percent of screen width
  int32_t           CO2_YellowStartPercent          =  33;
  int32_t           CO2_RedStartPercent             =  66;

  int32_t           VOC_GreenStartPercent           =   0;
  int32_t           VOC_YellowStartPercent          =  33;
  int32_t           VOC_RedStartPercent             =  66;

  PUnit             CO2_TextLeftDots                = 0;
  PUnit             VOC_TextLeftDots                = 0;

  int               CO2_TextBottomPercent           = 80;    // Percent of screen height
  int               VOC_TextBottomPercent           = 30;

  int               CO2_BarHeightPercent            = 20;
  int               VOC_BarHeightPercent            = 20;

  int               CO2_BarBottomPercent            = 55;
  int               VOC_BarBottomPercent            =  5;

  PUnit             CO2_TextBottomDots              = (ScreenHeight * CO2_TextBottomPercent)/100;
  PUnit             VOC_TextBottomDots              = (ScreenHeight * VOC_TextBottomPercent)/100;

  PUnit             CO2_BarHeightDots               = (ScreenHeight * CO2_BarHeightPercent) /100;
  PUnit             VOC_BarHeightDots               = (ScreenHeight * VOC_BarHeightPercent) /100;

  PUnit             CO2_BarBottomDots               = (ScreenHeight * CO2_BarBottomPercent) /100;
  PUnit             VOC_BarBottomDots               = (ScreenHeight * VOC_BarBottomPercent) /100;

  PUnit             CO2_GreenStartDots              = (ScreenWidth * CO2_GreenStartPercent)  /100;
  PUnit             CO2_YellowStartDots             = (ScreenWidth * CO2_YellowStartPercent) /100;
  PUnit             CO2_RedStartDots                = (ScreenWidth * CO2_RedStartPercent)    /100;

  PUnit             VOC_GreenStartDots              = (ScreenWidth * VOC_GreenStartPercent)  /100;
  PUnit             VOC_YellowStartDots             = (ScreenWidth * VOC_YellowStartPercent) /100;
  PUnit             VOC_RedStartDots                = (ScreenWidth * VOC_RedStartPercent)    /100;
};  //EnviroDisplayClass

extern EnviroDisplayClass    EnviroDisplay;       //This is so every module can use the same object

//Last line.
