// BeckProbeSetClass.h, 2/22/22d
#pragma once
#include <BeckBiotaDefines.h>
#include <BeckProbeClass.h>

class BeckProbeSetClass{
public:
  BeckProbeSetClass();
  //BeckProbeSetClass::BeckProbeSetClass(int wNumProbes, BeckProbeClass aoProbes[]);
  //BeckProbeSetClass(int wNumProbes, BeckProbeClass aoProbes[]);
  BeckProbeSetClass(int wNumProbes, BeckProbeClass* aoProbes);

  virtual ~BeckProbeSetClass  ();
  void    Handle              (void);

protected:
  int               _wNumProbes;
  BeckProbeClass*   _aoProbes;
};  //BeckProbeSetClass

//extern BeckProbeSetClass          ProbeSet;       //This is so every module can use the same object

//Last line.
