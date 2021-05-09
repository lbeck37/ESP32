// BeckGasSensorDataClass.h, 5/9/21b
#pragma once
#include <BeckBiotaDefines.h>

class GasSensorDataClass{
public:
  GasSensorDataClass();
  virtual ~GasSensorDataClass();

  void    	SetCO2_Value               (uint16_t NewCO2Value);
  uint16_t  GetCO2_Value               (void);
  void    	SetTVOC_Value              (uint16_t NewTVOCValue);
  uint16_t  GetTVOC_Value              (void);

protected:
  uint16_t   CO2_Value        = 0;
  uint16_t   TVOC_Value       = 0;
};  //GasSensorDataClass

extern GasSensorDataClass GasSensorData;
//Last line.
