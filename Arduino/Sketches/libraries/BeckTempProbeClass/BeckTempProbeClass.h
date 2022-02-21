// BeckTempProbeClass.h, 2/21/22c
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
  uint16_t          DegF_Value        = 0;

  bool  SetupProbe   		(void);
  void  triggerGetTemp		(void);
};  //BeckTempProbeClass

extern BeckTempProbeClass          TempProbe;       //This is so every module can use the same object

//Last line.
