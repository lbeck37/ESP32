// BeckProbeSetClass.h, 2/22/22b
#pragma once
#include <BeckBiotaDefines.h>

class BeckProbeSetClass{
public:
BeckProbeSetClass();
BeckProbeSetClass::BeckProbeSetClass(BeckProbeClass aoProbe[]);

virtual ~BeckProbeSetClass();

  bool  Setup           (void);
  bool  Handle          (void);
  //bool  ReadProbeTemp   (void);

protected:
  uint16_t          DegF_Value        = 0;

  bool  SetupProbes   		(void);
  //void  triggerGetTemp		(void);
};  //BeckProbeSetClass

extern BeckProbeSetClass          ProbeSet;       //This is so every module can use the same object

//Last line.
