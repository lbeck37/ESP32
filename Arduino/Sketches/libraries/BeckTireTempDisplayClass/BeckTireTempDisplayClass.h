// BeckTireTempDisplayClass.h, 3/31/22a
#pragma once
#include <BeckE32_Defines.h>
#include <BeckDataMgrClass.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansOblique18pt7b.h>
#include <WROVER_KIT_LCD.h>

class BeckTireTempDisplayClass{
public:
  BeckTireTempDisplayClass          ();
  BeckTireTempDisplayClass          (BeckDataMgrClass* poDataMgr);
  virtual ~BeckTireTempDisplayClass ();

  void  DisplayBegin        ();
  void  DisplaySensorSet    (int wSensorSetID);
  void  DisplayLogTemps     (float fDegf1, float fDegf2, float fDegf3);

private:
  void  DisplayClear        ();
  void  FillScreen          (uint16_t usColor);
  void  DisplayTemperature  ();
  void  DisplayLogTemps     ();
  void  DisplayText         (uint16_t usCursorX, uint16_t usCursorY, char *pcText,
                             const GFXfont *pFont, uint8_t ucSize, uint16_t usColor);
  void  ClearTextBackground (int16_t sUpperLeftX, int16_t sUpperLeftY, uint16_t usWidth, uint16_t usHeight);

  BeckDataMgrClass*   _poDataMgr                {};
  WROVER_KIT_LCD      RoverLCD;
  const ColorType     BackgroundColor           = WROVER_BLACK;
  char                sz100CharString[101];

  /*
  unsigned long       ulNextDisplayMsec         =   0;
  unsigned long       ulDisplayPeriodMsec       = 500; //mSec between output to display

  //unsigned long     ulNextHandleSensorsMsec   =    0;
  //unsigned long     ulHandleSensorsPeriodMsec = 5000; //mSec between handling probes
  */

  const uint16_t      usTopText_CursorY         = 35;
  const uint16_t      usTextSpacing             = 20;
  const uint16_t      usDegF_CursorY            = usTopText_CursorY;

};  //BeckTireTempDisplayClass
//Last line.
