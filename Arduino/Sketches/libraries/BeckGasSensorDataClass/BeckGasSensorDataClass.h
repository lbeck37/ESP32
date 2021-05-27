// BeckGasSensorDataClass.h, 5/26/21a
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

protected:
  uint16_t   CO2_Value        = 0;
  uint16_t   VOC_Value        = 0;
};  //GasSensorDataClass

extern GasSensorDataClass GasSensorData;
//Last line.
