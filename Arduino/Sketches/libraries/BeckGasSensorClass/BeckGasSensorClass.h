// BeckGasSensorClass.h, 5/26/21a
#pragma once
#include <BeckBiotaDefines.h>

class GasSensorClass{
public:
  GasSensorClass();
  virtual ~GasSensorClass();

  void          Setup                 (void);
  void          Handle                (void);
  bool          bCO2Changed           (void);
  bool          bVOCChanged           (void);

protected:
  uint16_t          CO2_Value         = 0;
  uint16_t          VOC_Value         = 0;
  uint16_t          LastCO2_Value     = 0;
  uint16_t          LastVOC_Value     = 0;
  unsigned long     ulNextPrintMsec   = 0;
  unsigned long     ulPrintPeriodMsec = 1000; //mSec between printing current CO2 and TVOC vales
};  //GasSensorClass

extern GasSensorClass          GasSensor;       //This is so every module can use the same object

//Last line.
