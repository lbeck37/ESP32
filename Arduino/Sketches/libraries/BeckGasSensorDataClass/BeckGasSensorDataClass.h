// BeckGasSensorDataClass.h, 5/9/21b
#pragma once
#include <cstdint>
class GasSensorDataClass{
public:
  GasSensorDataClass();
  virtual ~GasSensorDataClass();

  void    	Setup                      (void);
  void    	Handle                     (void);

  void    	SetCO2_Value               (uint16_t NewCO2Value);
  uint16_t  GetCO2_Value               (void);
  void    	SetVOC_Value               (uint16_t NewVOCValue);
  uint16_t  GetVOC_Value               (void);

protected:
  uint16_t   CO2_Value        = 0;
  uint16_t   VOC_Value        = 0;
};  //GasSensorDataClass

extern GasSensorDataClass GasSensorData;
//Last line.
