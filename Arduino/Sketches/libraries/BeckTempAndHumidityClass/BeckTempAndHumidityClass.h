// BeckTempAndHumidClass.h, 6/10/21a
#pragma once
#include <BeckBiotaDefines.h>

class TempAndHumidityClass{
public:
TempAndHumidityClass();
  virtual ~TempAndHumidityClass();

  void  Setup                 (void);
  void  Handle                (void);
  bool  ReadTempAndHumidity   (void);

protected:
  uint16_t          DegF_Value        = 0;
  uint16_t          RH_Value          = 0;
/*
  unsigned long     ulNextPrintMsec   = 0;
  unsigned long     ulPrintPeriodMsec = 1000; //mSec between printing current CO2 and TVOC vales
*/

  void  triggerGetTemp        (void);
  void  ReadDHT_Task          (void *pvParameters);
};  //TempAndHumidityClass

extern TempAndHumidityClass          TempAndHumiditySensor;       //This is so every module can use the same object

//Last line.
