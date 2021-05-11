// BeckGasSensorDisplayClass.h, 5/10/21d
#pragma once
//Initially used for TTGO ESP32 module. 135 x 240, 1.14", 240dpi display

#include <BeckDisplayClass.h>
#include <TFT_eSPI.h>

class GasSensorDisplayClass : public TTGO_DisplayClass {
public:
  GasSensorDisplayClass();
  virtual ~GasSensorDisplayClass();

  void  Setup             (void);
  void  Handle            (void);

protected:
  uint32_t          ulNextGasSensorDisplayMsec      = 0;
  uint32_t          ulGasSensorDisplayPeriodMsec    = 1000; //mSec between updating display

  int               CO2_TextBottomPercent           = 80;
  int               VOC_TextBottomPercent           = 30;

  int               CO2_BarHeightPercent            = 20;
  int               VOC_BarHeightPercent            = 20;

  int               CO2_BarBottomPercent            = 55;
  int               VOC_BarBottomPercent            =  5;

  int               CO2_BarLeftPercent              =  0;
  int               VOC_BarLeftPercent              =  0;

  PUnit             CO2_TextLeft                    = 0;
  PUnit             VOC_TextLeft                    = 0;

  PUnit             CO2_TextBottomDots              = (ScreenHeight * CO2_TextBottomPercent)/100;
  PUnit             VOC_TextBottomDots              = (ScreenHeight * VOC_TextBottomPercent)/100;

  PUnit             CO2_BarHeightDots               = (ScreenHeight * CO2_BarHeightPercent) /100;
  PUnit             VOC_BarHeightDots               = (ScreenHeight * VOC_BarHeightPercent) /100;

  PUnit             CO2_BarBottomDots               = (ScreenHeight * CO2_BarBottomPercent) /100;
  PUnit             VOC_BarBottomDots               = (ScreenHeight * VOC_BarBottomPercent) /100;

  PUnit             CO2_BarLeftDots                 = (ScreenWidth * CO2_BarLeftPercent) /100;
  PUnit             VOC_BarLeftDots                 = (ScreenWidth * VOC_BarLeftPercent) /100;

  int32_t           CO2_YellowStart                 =  600;   // parts/million
  int32_t           CO2_RedStart                    = 1000;   // parts/million

  int32_t           CO2_YellowStartPercent          =  33;
  int32_t           CO2_RedStartPercent             =  66;

  int               VOC_YellowStart                 =  200;   // parts/billion
  int               VOC_RedStart                    =  600;   // parts/billion

  int32_t           VOC_YellowStartPercent          =  33;
  int32_t           VOC_RedStartPercent             =  66;

  Colortype         Gas_BackgroundColor             = TFT_WHITE;
  Colortype         Gas_FontColor                   = TFT_BLACK;

  FontFaceType      eGas_Font                       = eMonospacedBold;
  FontPointType     eGas_PointSize                  = e30point;

  void  DisplayCO2andTVOC       (void);
  void  DisplayCO2andTVOC_text  (void);
  void  DisplayCO2andTVOC_bars  (void);
  void  DisplayCO2_bar          (void);
  void  DisplayVOC_bar          (void);
};  //GasSensorDisplayClass

extern GasSensorDisplayClass    GasSensorDisplay;       //This is so every module can use the same object

//Last line.
