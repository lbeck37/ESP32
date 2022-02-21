// BeckTempProbeClass.h, 2/21/22a
#pragma once
#include <BeckBiotaDefines.h>

class BeckTempProbeClass{
public:
BeckTempProbeClass();
  virtual ~BeckTempProbeClass();

  void  Setup           (void);
  void  Handle          (void);
  bool  ReadProbeTemp   (void);

protected:
  bool  SetupProbe   (void);
  uint16_t          DegF_Value        = 0;
  //uint16_t          RH_Value          = 0;
/*
  unsigned long     ulNextPrintMsec   = 0;
  unsigned long     ulPrintPeriodMsec = 1000; //mSec between printing current CO2 and TVOC vales
*/

  void  triggerGetTemp        (void);
  void  ReadDHT_Task          (void *pvParameters);
};  //BeckTempProbeClass

extern BeckTempProbeClass          TempAndHumiditySensor;       //This is so every module can use the same object

//Last line.
