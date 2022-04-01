// BeckDisplayClass.h, 4/1/22a
#pragma once
#include <BeckE32_Defines.h>
#include <BeckDataMgrClass.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansOblique18pt7b.h>
#include <WROVER_KIT_LCD.h>

class BeckDisplayClass{
public:
  BeckDisplayClass          ();
  BeckDisplayClass          (BeckDataMgrClass* poDataMgr);
  virtual ~BeckDisplayClass ();

  void  DisplayBegin        ();
  void  DisplaySensorSet    (int wSensorSetID);
  //void  DisplayLogTemps     (float fDegf1, float fDegf2, float fDegf3);
  void  DisplayLogTemps     (char* szLogString);

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
        char                sz100CharString[101];
  const ColorType           BackgroundColor           = WROVER_BLACK;
  const uint16_t            usTopText_CursorY         = 35;
  const uint16_t            usTextSpacing             = 20;
  const uint16_t            usDegF_CursorY            = usTopText_CursorY;

};  //BeckDisplayClass
//Last line.
