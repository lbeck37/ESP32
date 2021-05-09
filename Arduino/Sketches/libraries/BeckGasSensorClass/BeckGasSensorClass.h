// BeckGasSensorClass.h, 5/9/21a
#pragma once
#include <BeckBiotaDefines.h>

class GasSensorClass{
public:
  GasSensorClass();
  virtual ~GasSensorClass();

  void          Setup                 (void);
  void          Handle                (void);

protected:
  uint16_t  	CO2_Value;
  uint16_t  	TVOC_Value;
};  //GasSensorClass

extern GasSensorClass          GasSensor;       //This is so every module can use the same object

//Last line.
