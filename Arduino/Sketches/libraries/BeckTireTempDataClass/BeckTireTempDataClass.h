// BeckTireTempDataClass.h, 3/3/22a
#pragma once
#include <BeckE32_Defines.h>

class BeckTireTempDataClass{
public:
  BeckTireTempDataClass();
  virtual ~BeckTireTempDataClass();

/*
  void        SetDegF_Value       (double dfNewDegFValue);
  void        SetDegF_Value       (int16_t wNewDegFValue);
  int16_t     wGetDegF_Value       (void);
  bool        bDegFChanged        (void);
  //void        SetLastDegF_Value   (float LastDegFValue);
  void        SetLastDegF_Value   (int16_t wLastDegFValue);
  float       GetLastDegF_Value   (void);
*/

protected:
  int16_t     _wDegF_Value          = 0;
  int16_t     _wLastDegF_Value      = 0;
  bool        _bDegFFirstTime       = true;
};  //BeckTireTempDataClass

extern BeckTireTempDataClass TireTempData;
//Last line.
