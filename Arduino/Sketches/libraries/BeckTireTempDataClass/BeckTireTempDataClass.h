// BeckTireTempDataClass.h, 2/27/22a
#pragma once
#include <BeckBiotaDefines.h>

class BeckTireTempDataClass{
public:
  BeckTireTempDataClass();
  virtual ~BeckTireTempDataClass();

  void        SetDegF_Value       (float NewDegFValue);
  float       GetDegF_Value       (void);
  bool        bDegFChanged        (void);
  void        SetLastDegF_Value   (float LastDegFValue);
  float       GetLastDegF_Value   (void);
protected:
  float       DegF_Value          = 0.0;
  float       LastDegF_Value      = 0.0;
  bool        bDegFFirstTime      = true;
};  //BeckTireTempDataClass

extern BeckTireTempDataClass TireTempData;
//Last line.
