// BeckBarClass.h, 6/3/21d
#pragma once
#include <BeckBiotaDefines.h>
#include <WROVER_KIT_LCD.h>
#include <stdlib.h>
#include <vector>

#define BAR_WIDTH      35
#define BAR_LENGTH    120

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

extern WROVER_KIT_LCD     RoverLCD;
extern ColorType          BackgroundColor;

const PUnit     CO2Bar_XLeft     = 200;
const PUnit     CO2Bar_YBottom   = 30;

class BarSegmentClass{
public:
  BarSegmentClass             ();
  virtual ~BarSegmentClass    ();

  void  Draw                  (float fNewValue);
  void  DrawFilledRectangle   (PUnit XLeft, PUnit YBottom, PUnit Width, PUnit Length, ColorType Color);
  uint16_t          StartPercent    = 33;
  ColorType         Color           = BECK_YELLOW;
  PUnit             XLeft           = 0;
  PUnit             YBottom         = 0;
  PUnit             Width           = BAR_WIDTH;
  PUnit             Length          = BAR_LENGTH;
  float             fStartValue     =  600.0;
  float             fEndValue       = 1000.0;
  float             fRange          = fEndValue - fStartValue;
  float             fLastValue      = fStartValue;

protected:
};  //BarSegmentClass


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
  BarClass            (BarDataClass BarData);
  virtual ~BarClass   ();

  //void  Draw          (PUnit XLeft, PUnit YBottom);
  void  Draw          (float fNewValue);

  BarSegmentClass   GreenSegment  = BarSegmentClass();
  BarSegmentClass   YellowSegment = BarSegmentClass();
  BarSegmentClass   RedSegment    = BarSegmentClass();

protected:
  BarDataClass      _BarData;
  std::vector<BarSegmentClass>              BarSegments;
  std::vector<BarSegmentClass>::iterator    Iterator;
};  //BarClass
//Last line.
