// BeckProbesClass.h, 2/21/22c
#pragma once
#include <BeckBiotaDefines.h>

class BeckProbesClass{
public:
BeckProbesClass();
  virtual ~BeckProbesClass();

  void  Setup           (void);
  void  Handle          (void);
  bool  ReadProbeTemp   (void);

protected:
  uint16_t          DegF_Value        = 0;

  bool  SetupProbe   		(void);
  void  triggerGetTemp		(void);
};  //BeckProbesClass

extern BeckProbesClass          Probes;       //This is so every module can use the same object

//Last line.
