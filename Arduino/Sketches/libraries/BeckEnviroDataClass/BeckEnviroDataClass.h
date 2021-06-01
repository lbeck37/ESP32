// BeckEnviroDataClass.h, 5/31/21e
#pragma once
#include <BeckBiotaDefines.h>

class EnviroDataClass{
public:
  EnviroDataClass();
  virtual ~EnviroDataClass();

  void      SetCO2_Value    (uint16_t NewCO2Value);
  uint16_t  GetCO2_Value    (void);
  bool      bCO2Changed     (void);

  void      SetVOC_Value    (uint16_t NewVOCValue);
  uint16_t  GetVOC_Value    (void);
  bool      bVOCChanged     (void);

  void      SetDegF_Value   (float NewDegFValue);
  float     GetDegF_Value   (void);
  bool      bDegFChanged    (void);

  void      SetRH_Value     (uint16_t NewDegFValue);
  uint16_t  GetRH_Value     (void);
  bool      bRHChanged      (void);

protected:
  uint16_t    CO2_Value         = 0;
  uint16_t    VOC_Value         = 0;
  float       DegF_Value        = 0.0;
  uint16_t    RH_Value          = 0;

  uint16_t    LastCO2_Value     = 0;
  uint16_t    LastVOC_Value     = 0;
  float       LastDegF_Value    = 0.0;
  uint16_t    LastRH_Value      = 0;

  bool        bCO2FirstTime     = true;
  bool        bVOCFirstTime     = true;
  bool        bDegFFirstTime    = true;
  bool        bRHFirstTime      = true;
};  //EnviroDataClass

extern EnviroDataClass EnviroData;
//Last line.
