// BeckBarClass.h, 6/8/21a
#pragma once
#include <BeckBiotaDefines.h>
#include <WROVER_KIT_LCD.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#define NUMBER_OF_SEGMENTS      3
//Dimensions are in pixels
#define BAR_THICKNESS          35
#define BAR_LENGTH            120
#define CO2_XLEFT             190
#define CO2_YBOTTOM            12

#define CO2_START_VALUE          0.00
#define CO2_END_VALUE         2000.00
#define CO2_RANGE             (CO2_END_VALUE - CO2_START_VALUE)

enum OrientationType{
  eNoOrientation  = 0,
  eHorizontal,
  eVertical,
  eLastOrientationType
};

enum BarType{
  eNoBar  = 0,
  eCO2Bar,
  eVOCBar,
  eDegFBar,
  eRHBar,
  eLastBarType
};

enum SegmentPosition{
  eNoPosition  = 0,
  eFirstSegment,
  eSecondSegment,
  eThirdSegment,
  eLastSegmentPosition
};

extern WROVER_KIT_LCD     RoverLCD;
extern ColorType          BackgroundColor;

const PUnit     CO2Bar_XLeft     = 200;
const PUnit     CO2Bar_YBottom   = 30;

class SegmentData{
public:
  SegmentData                 ();
  virtual ~SegmentData        ();

  char              BarName[20]     = "No bar";
  ColorType         Color           = BECK_YELLOW;
  char              ColorName[20]   = "No color";
  int               StartPercent    = 33;
  PUnit             XLeft           = 0;
  PUnit             YBottom         = 0;
  PUnit             Thickness       = BAR_THICKNESS;
  PUnit             Length          = BAR_LENGTH;
  float             fStartValue     = 777.0;
  float             fEndValue       = 888.0;
  float             fRange          = fEndValue - fStartValue;
protected:
};  //SegmentData


class BarSegment{
public:
BarSegment             ();
BarSegment             (SegmentData& SegmentData);
virtual ~BarSegment    ();

/*
  void  SetLastValue          (float fNewLastValue);
  float GetLastValue          ();
*/
  void  Draw                  (float fNewValue, float fLastValue);
  void  DrawFilledRectangle   (PUnit XLeft, PUnit YBottom, PUnit Thickness, PUnit Length, ColorType Color);

  SegmentData _SegData;
protected:
};  //BarSegment


class BarData{
public:
  BarData            ();
  virtual ~BarData   ();

  BarType           eBarType              = eNoBar;
  OrientationType   Orientation           = eHorizontal;
  PUnit             XLeft                 = 0;
  PUnit             YBottom               = 0;
  PUnit             Thickness             = BAR_THICKNESS;
  PUnit             Length                = BAR_LENGTH;
  float             fStartValue           = 0.0;
  float             fEndValue             = 0.0;
  float             fRange                = fEndValue - fStartValue;
  float             fLastValue            = 999.0;
  BarSegment        BarSegs               [NUMBER_OF_SEGMENTS];
protected:
};  //BarData


class BarClass{
public:
  BarClass                  ();
  BarClass                  (BarData& BarData);
  virtual ~BarClass         ();

  void  SetLowerLeftCorner  (PUnit XLeft, PUnit YBottom);
  void  Draw                (float fNewValue);
protected:
  float        _fLastValue= 9999.9;
  BarData      _BarData;
};  //BarClass
//Last line.
