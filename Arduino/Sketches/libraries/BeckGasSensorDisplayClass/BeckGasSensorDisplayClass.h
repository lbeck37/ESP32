// BeckGasSensorDisplayClass.h, 5/9/21d
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
  unsigned long     ulGasSensorDisplayPeriodMsec  	= 1000; //mSec between reading sensor
  PUnit           	CO2_LeftSide          			=  5;
  PUnit           	CO2_YBaseline         			= 10 + 40;         //ScreenHeight - 97
  Colortype       	CO2_Color             			= TFT_BLACK;
  FontFaceType    	eCO2_Font             			= eRobotoCondensedFace;
  FontPointType   	eCO2_PointSize        			= e30point;

  void  DisplayCO2andTVOC	(void);
};  //GasSensorDisplayClass

extern GasSensorDisplayClass    GasSensorDisplay;       //This is so every module can use the same object

//Last line.
