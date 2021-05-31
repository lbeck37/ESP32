// BeckTempAndHumidClass.h, 5/31/21a
#pragma once
#include <BeckBiotaDefines.h>

class TempAndHumidClass{
public:
  TempAndHumidClass();
  virtual ~TempAndHumidClass();

  void          Setup                 (void);
  void          Handle                (void);

protected:
  uint16_t          DegF_Value        = 0;
  uint16_t          RH_Value          = 0;
  unsigned long     ulNextPrintMsec   = 0;
  unsigned long     ulPrintPeriodMsec = 1000; //mSec between printing current CO2 and TVOC vales

  bool  SetupDHT    (void);
  void triggerGetTemp();
  void ReadDHT_Task(void *pvParameters);
  bool ReadTempAndHumidity();
};  //TempAndHumidClass

extern TempAndHumidClass          TempAndHumidSensor;       //This is so every module can use the same object

//Last line.
