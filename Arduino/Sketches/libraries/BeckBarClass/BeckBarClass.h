// BeckBarClass.h, 6/2/21a
#pragma once
#include <BeckBiotaDefines.h>
#include <stdlib.h>
#include <vector>

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

PUnit     StdBarWidth   =  35;
PUnit     StdBarLength  = 120;

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
  PUnit             Width           = StdBarWidth;
  PUnit             Length          = StdBarLength;
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
  PUnit             Width                 = StdBarWidth;
  PUnit             Length                = StdBarLength;
  float             fStartValue           = 0.0;
  float             fEndValue             = 0.0;
  std::vector<BarSegmentClass>  BarSegments;
protected:
};  //BarDataClass


class BarClass{
public:
  //BarClass            (BarType eBar, PUnit XLeft, PUnit YBottom);
  BarClass            (BarDataClass BarData);
  virtual ~BarClass   ();

  //void  Setup         (void);
  //void  Handle        (void);
  bool  DrawBar       (void);

protected:
  BarDataClass      _BarData;
  BarType           eBarType              = eNoBar;
/*
  int16_t           NumSegments           = 3;
  BarSegmentClass   BarSegments           [NumSegments];
*/
/*
  std::vector<BarSegmentClass>            BarSegments;
  OrientationType   Orientation           = eHorizontal;
  PUnit             XLeft                 = 0;
  PUnit             YBottom               = 0;
  PUnit             Width                 = StdBarWidth;
  PUnit             Length                = StdBarLength;
  float             fLowValue             = 0.0;
  float             fHighValue            = 0.0;
  float             fLastDisplayedValue   = 0.0;
*/
};  //BarClass
//Last line.
