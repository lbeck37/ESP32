// BeckGasSensorClass.h, 5/20/21a
#pragma once
#include <BeckBiotaDefines.h>

class GasSensorClass{
public:
  GasSensorClass();
  virtual ~GasSensorClass();

  void          Setup                 (void);
  void          Handle                (void);

protected:
  uint16_t  		    CO2_Value				  = 0;
  uint16_t  		    TVOC_Value				= 0;
  unsigned long     ulNextPrintMsec   = 0;
  unsigned long     ulPrintPeriodMsec = 1000; //mSec between printing current CO2 and TVOC vales
};  //GasSensorClass

extern GasSensorClass          GasSensor;       //This is so every module can use the same object

//Last line.
