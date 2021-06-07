// BeckBarClass.h, 6/7/21e
#pragma once
#include <BeckBiotaDefines.h>
#include <WROVER_KIT_LCD.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
//#include <string>
//using std::string;
//using std::vector;

#define BAR_WIDTH              35
#define BAR_LENGTH            120
#define NUMBER_OF_SEGMENTS    3

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
  SegmentData             ();
  virtual ~SegmentData    ();

  void  Draw                  (float fNewValue);
  void  DrawFilledRectangle   (PUnit XLeft, PUnit YBottom, PUnit Width, PUnit Length, ColorType Color);

  char              BarName[20]     = "No bar";
  ColorType         Color           = BECK_YELLOW;
  char              ColorName[20]   = "No color";
  int               StartPercent    = 33;
  PUnit             XLeft           = 0;
  PUnit             YBottom         = 0;
  PUnit             Width           = BAR_WIDTH;
  PUnit             Length          = BAR_LENGTH;
  float             fStartValue     = 777.0;
  float             fEndValue       = 888.0;
  float             fRange          = fEndValue - fStartValue;
  float             fLastValue      = 999.0;

protected:
};  //SegmentData

class BarSegment{
public:
BarSegment             ();
BarSegment             (SegmentData& SegmentData);
virtual ~BarSegment    ();

  void  Draw                  (float fNewValue);
  void  DrawFilledRectangle   (PUnit XLeft, PUnit YBottom, PUnit Width, PUnit Length, ColorType Color);

  uint16_t          StartPercent    = 33;
  ColorType         Color           = BECK_YELLOW;
  char              ColorName[20]   = "No color";
  char              BarName[20]     = "No bar";
  PUnit             XLeft           = 0;
  PUnit             YBottom         = 0;
  PUnit             Width           = BAR_WIDTH;
  PUnit             Length          = BAR_LENGTH;
  float             fStartValue     = 777.0;
  float             fEndValue       = 888.0;
  float             fRange          = fEndValue - fStartValue;
  //float             fLastValue      = fStartValue;
  float             fLastValue      = 999.0;

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
  PUnit             Width                 = BAR_WIDTH;
  PUnit             Length                = BAR_LENGTH;
  float             fStartValue           = 0.0;
  float             fEndValue             = 0.0;
  float             fRange                = fEndValue - fStartValue;
  BarSegment   FirstSegment;
  BarSegment   SecondSegment;
  BarSegment   ThirdSegment;
  //int               NumberOfSegments      = 3;      //Doesn't work
  //SegmentData       SegmentArray          [NUMBER_OF_SEGMENTS];

protected:
};  //BarData

class BarDataClass{
public:
  BarDataClass            ();
  virtual ~BarDataClass   ();

  BarType           eBarType              = eNoBar;
  OrientationType   Orientation           = eHorizontal;
  PUnit             XLeft                 = 0;
  PUnit             YBottom               = 0;
  PUnit             Width                 = BAR_WIDTH;
  PUnit             Length                = BAR_LENGTH;
  float             fStartValue           = 0.0;
  float             fEndValue             = 0.0;
  float             fRange                = fEndValue - fStartValue;

protected:
};  //BarDataClass

class BarClass{
public:
  BarClass            ();
  BarClass            (BarData& BarData);
  virtual ~BarClass   ();

  //void  Draw          (PUnit XLeft, PUnit YBottom);
  void  Draw          (float fNewValue);
/*
  BarSegmentClass   GreenSegment  = BarSegmentClass();
  BarSegmentClass   YellowSegment = BarSegmentClass();
  BarSegmentClass   RedSegment    = BarSegmentClass();
*/
protected:
  BarData      _BarData;
/*
  std::vector<BarSegmentClass>              BarSegments;
  std::vector<BarSegmentClass>::iterator    Iterator;
*/
  BarSegment     BarSegmentArray[3];
};  //BarClass
//Last line.
