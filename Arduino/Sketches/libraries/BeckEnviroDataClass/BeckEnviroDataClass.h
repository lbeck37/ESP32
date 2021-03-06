// BeckEnviroDataClass.h, 6/13/21b
#pragma once
#include <BeckBiotaDefines.h>

class EnviroDataClass{
public:
  EnviroDataClass();
  virtual ~EnviroDataClass();

  void        SetCO2_Value        (uint16_t NewCO2Value);
  uint16_t    GetCO2_Value        (void);
  bool        bCO2Changed         (void);
  void        SetLastCO2_Value    (uint16_t LastCO2Value);
  uint16_t    GetLastCO2_Value    (void);
protected:
  uint16_t    CO2_Value           = 0;
  uint16_t    LastCO2_Value       = 0;
  bool        bCO2FirstTime       = true;

public:
  void        SetVOC_Value        (uint16_t NewVOCValue);
  uint16_t    GetVOC_Value        (void);
  bool        bVOCChanged         (void);
  void        SetLastVOC_Value    (uint16_t LastVOCValue);
  uint16_t    GetLastVOC_Value    (void);
protected:
  uint16_t    VOC_Value           = 0;
  uint16_t    LastVOC_Value       = 0;
  bool        bVOCFirstTime       = true;

public:
  void        SetDegF_Value       (float NewDegFValue);
  float       GetDegF_Value       (void);
  bool        bDegFChanged        (void);
  void        SetLastDegF_Value   (float LastDegFValue);
  float       GetLastDegF_Value   (void);
protected:
  float       DegF_Value          = 0.0;
  float       LastDegF_Value      = 0.0;
  bool        bDegFFirstTime      = true;

public:
  void        SetRH_Value         (uint16_t NewDegFValue);
  uint16_t    GetRH_Value         (void);
  bool        bRHChanged          (void);
  void        SetLastRH_Value     (uint16_t LastRHValue);
  uint16_t    GetLastRH_Value     (void);
protected:
  uint16_t    LastRH_Value        = 0;
  uint16_t    RH_Value            = 0;
  bool        bRHFirstTime        = true;
};  //EnviroDataClass

extern EnviroDataClass EnviroData;
//Last line.
