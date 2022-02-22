// BeckTireTempDataClass.h, 2/21/22c
#pragma once
#include <BeckBiotaDefines.h>

class TireTempDataClass{
public:
  TireTempDataClass();
  virtual ~TireTempDataClass();

  void        SetDegF_Value       (float NewDegFValue);
  float       GetDegF_Value       (void);
  bool        bDegFChanged        (void);
  void        SetLastDegF_Value   (float LastDegFValue);
  float       GetLastDegF_Value   (void);
protected:
  float       DegF_Value          = 0.0;
  float       LastDegF_Value      = 0.0;
  bool        bDegFFirstTime      = true;
};  //TireTempDataClass

extern TireTempDataClass TireTempData;
//Last line.
