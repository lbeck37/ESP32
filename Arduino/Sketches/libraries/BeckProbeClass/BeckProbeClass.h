// BeckProbeClass.h, 2/22/22b
#pragma once
#include <BeckBiotaDefines.h>

class BeckProbeClass{
public:
  BeckProbeClass();
  BeckProbeClass(byte cSPI_MISO_Pin, byte cSPI_CLK_Pin, uint8_t ucCS_Pin);
  virtual ~BeckProbeClass();

  void  Setup           (void);
  void  Handle          (void);
  //bool  ReadProbeTemp   (void);

protected:
  uint16_t          DegF_Value        = 0;

  //bool  SetupProbe    		(void);
  //void  triggerGetTemp		(void);
};  //BeckProbeClass

extern BeckProbeClass          ProbeSet;       //This is so every module can use the same object

//Last line.
