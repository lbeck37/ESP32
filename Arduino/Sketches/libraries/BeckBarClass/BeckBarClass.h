// BeckTempAndHumidClass.h, 6/1/21a
#pragma once
#include <BeckBiotaDefines.h>

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
  eBarType
};


class BarClass{
public:
  BarClass            (BarType eNewBarType);
  virtual ~BarClass   ();

  void  Setup         (void);
  void  Handle        (void);
  bool  DrawBar       (void);

protected:
  float             fLastValue            = 0.0;
  OrientationType   Orientation           = eHorizontal;
  PUnit             XLeft                 = 0;
  PUnit             YBottom               = 0;
  PUnit             Width                 = 10;
  PUnit             Length                = 100;
  float             fLowValue             = 0.0;
  float             fHighValue            = 1000.0;
  float             fLastDisplayedValue   = 0.0;
  BarType           eBarType              = eCO2Bar;


  //unsigned long     ulNextPrintMsec   = 0;
  //unsigned long     ulPrintPeriodMsec = 1000; //mSec between printing current CO2 and TVOC vales
};  //TempAndHumidityClass
//Last line.
