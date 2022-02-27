// BeckProbeSetClass.h, 2/27/22c
#pragma once
#include <BeckBiotaDefines.h>
#include <BeckProbeClass.h>

class BeckProbeSetClass{
public:
  BeckProbeSetClass();
  //BeckProbeSetClass::BeckProbeSetClass(int wNumProbes, BeckProbeClass aoProbes[]);
  //BeckProbeSetClass(int wNumProbes, BeckProbeClass aoProbes[]);
  //BeckProbeSetClass(byte cSPI_MISO_Pin, byte cSPI_CLK_Pin, int wNumProbes, BeckProbeClass* aoProbes);
  BeckProbeSetClass(byte cSPI_MISO_Pin, byte cSPI_CLK_Pin, int wNumProbes, uint8_t acSPI_CS_Pins[]);

  virtual ~BeckProbeSetClass  ();
  void    Handle              (void);

protected:
  int                     _wNumProbes;
  //BeckProbeClass*       _aoProbes;
  BeckProbeClass          _aoProbes[];
  //byte                    _acSPI_CS_Pins[_wNumProbes + 1];
};  //BeckProbeSetClass

//extern BeckProbeSetClass          ProbeSet;       //This is so every module can use the same object

//Last line.
