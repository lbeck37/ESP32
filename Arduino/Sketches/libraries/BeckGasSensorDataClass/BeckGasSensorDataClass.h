// BeckGasSensorDataClass.h, 5/27/21a
#pragma once
#include <BeckBiotaDefines.h>

class GasSensorDataClass{
public:
  GasSensorDataClass();
  virtual ~GasSensorDataClass();

  void    	SetCO2_Value    (uint16_t NewCO2Value);
  uint16_t  GetCO2_Value    (void);
  void    	SetVOC_Value    (uint16_t NewVOCValue);
  uint16_t  GetVOC_Value    (void);
  bool      bCO2Changed     (void);
  bool      bVOCChanged     (void);

protected:
  uint16_t    CO2_Value         = 0;
  uint16_t    VOC_Value         = 0;
  uint16_t    LastCO2_Value     = 0;
  uint16_t    LastVOC_Value     = 0;
  bool        bCO2FirstTime     = true;
  bool        bVOCFirstTime     = true;
};  //GasSensorDataClass

extern GasSensorDataClass GasSensorData;
//Last line.
