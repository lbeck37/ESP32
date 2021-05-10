// BeckGasSensorDisplayClass.h, 5/10/21a
#pragma once
//Initially used for TTGO ESP32 module. 135 x 240, 1.14", 240dpi display

#include <BeckDisplayClass.h>
#include <TFT_eSPI.h>

class GasSensorDisplayClass : public TTGO_DisplayClass {
public:
  GasSensorDisplayClass();
  virtual ~GasSensorDisplayClass();

  void  Setup         		(void);
  void  Handle        		(void);

protected:
  unsigned long     ulNextGasSensorDisplayMsec    	= 0;
  unsigned long     ulGasSensorDisplayPeriodMsec  	= 1000; //mSec between updating display
  PUnit           	Gas_LeftSide          			= 0;
  //PUnit           	Gas_YBaseline         			= (ScreenHeight * 70)/100;
  PUnit           	Gas_YBaseline         			= 0;
/*
  Colortype       	Gas_BackgroundColor             = TFT_BLACK;
  Colortype       	Gas_FontColor             		= TFT_WHITE;
  FontFaceType    	eGas_Font             			= eRobotoCondensedFace;
  FontFaceType    	eGas_Font             			= eRobotoMediumFace;
  FontPointType   	eGas_PointSize        			= e40point;
  FontFaceType    	eGas_Font             			= eLatoBlack;
  FontFaceType    	eGas_Font             			= eMonospacedBold;
  FontPointType   	eGas_PointSize        			= e60point;
*/
  Colortype       	Gas_BackgroundColor             = TFT_WHITE;
  Colortype       	Gas_FontColor             		= TFT_BLACK;
  FontFaceType    	eGas_Font             			= eMonospacedBold;
  FontPointType   	eGas_PointSize        			= e30point;

  void  DisplayCO2andTVOC	(void);
};  //GasSensorDisplayClass

extern GasSensorDisplayClass    GasSensorDisplay;       //This is so every module can use the same object

//Last line.
