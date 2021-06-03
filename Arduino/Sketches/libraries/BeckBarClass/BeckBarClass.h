// BeckBarClass.h, 6/3/21b
#pragma once
#include <BeckBiotaDefines.h>
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

const PUnit     CO2Bar_XLeft     = 200;
const PUnit     CO2Bar_YBottom   = 30;

class BarSegmentClass{
public:
  BarSegmentClass            ();
  virtual ~BarSegmentClass   ();

  uint16_t          StartPercent    = 33;
  ColorType         SegmentColor    = BECK_YELLOW;
  float             fStartValue     =  600.0;
  float             fEndValue       = 1000.0;
  PUnit             XLeft           = 0;
  PUnit             YBottom         = 0;
  PUnit             Width           = BAR_WIDTH;
  PUnit             Length          = BAR_LENGTH;

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
  //BarDataClass      CO2BarData;

protected:
};  //BarDataClass


class BarClass{
public:
BarSegmentClass   GreenSegment  = BarSegmentClass();
BarSegmentClass   YellowSegment = BarSegmentClass();
BarSegmentClass   RedSegment    = BarSegmentClass();

  //BarClass            (BarType eBar, PUnit XLeft, PUnit YBottom);
  BarClass            ();
  //BarClass            (BarDataClass BarData);
  BarClass            (BarDataClass BarData);
  virtual ~BarClass   ();

  //void  Setup         (void);
  //void  Handle        (void);
  void  DrawBar       (void);

protected:
  std::vector<BarSegmentClass>  BarSegments;
  BarDataClass      _BarData;
};  //BarClass
//Last line.
