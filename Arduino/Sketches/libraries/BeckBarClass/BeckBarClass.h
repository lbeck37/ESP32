// BeckBarClass.h, 6/10/21a
#pragma once
#include <BeckBiotaDefines.h>
#include <WROVER_KIT_LCD.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

//Dimensions are in pixels
#define NUMBER_OF_SEGMENTS      3
#define BAR_THICKNESS          20
#define BAR_LENGTH            120

#define CO2_XLEFT             190
#define CO2_YBOTTOM            10
#define CO2_GREEN_START         0       //The start pixels are evenly spaced over the BAR_LENGTH
#define CO2_YELLOW_START       40
#define CO2_RED_START          80

#define CO2_START_VALUE          0.0
#define CO2_END_VALUE         2000.0
#define CO2_RANGE             (CO2_END_VALUE - CO2_START_VALUE)

#define VOC_XLEFT             190
#define VOC_YBOTTOM            70         //Text on display is spaced 60 pixels going down
#define VOC_GREEN_START         0         //The start pixels are evenly spaced over the BAR_LENGTH
#define VOC_YELLOW_START       40
#define VOC_RED_START          80

#define VOC_START_VALUE          0.0
#define VOC_END_VALUE         3000.0
#define VOC_RANGE             (VOC_END_VALUE - VOC_START_VALUE)

#define DEGF_XLEFT             190
#define DEGF_YBOTTOM            70         //Text on display is spaced 60 pixels going down
#define DEGF_BLUE_START          0         //The start pixels are spaced over the BAR_LENGTH
#define DEGF_GREEN_START        32
#define DEGF_RED_START          80

#define DEGF_START_VALUE        60.0
#define DEGF_END_VALUE          90.0
#define DEGF_RANGE             (DEGF_END_VALUE - DEGF_START_VALUE)

#define RH_XLEFT                190
#define RH_YBOTTOM               70         //Text on display is spaced 60 pixels going down
#define RH_YELLOW_START           0         //The start pixels are spaced over the BAR_LENGTH
#define RH_GREEN_START           32
#define RH_RED_START             96

#define RH_START_VALUE          0.0
#define RH_END_VALUE          100.0
#define RH_RANGE             (RH_END_VALUE - RH_START_VALUE)

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

enum DataValueType{
  eNoDataValue  = -1,
  eCO2DataValue =  0,
  eVOCDataValue,
  eDegFDataValue,
  eRHDataValue,
  eLastDataValueType
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

/*
const PUnit     CO2Bar_XLeft     = 200;
const PUnit     CO2Bar_YBottom   = 30;
*/

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

  //void  SetLowerLeftCorner  (PUnit XLeft, PUnit YBottom);
  void  Draw                (float fNewValue);
protected:
  float        _fLastValue= 9999.9;
  BarData      _BarData;
};  //BarClass
//Last line.
