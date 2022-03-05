// BeckProbeSetClass.h, 2/28/22f
#pragma once
#include <BeckProbeClass.h>
#include <BeckE32_Defines.h>

class BeckProbeSetClass{
public:
  BeckProbeSetClass           ();
  virtual ~BeckProbeSetClass  ();

  void  BuildProbes   ();

  void    Handle              (void);

protected:
  BeckProbeClass          _aoProbes[_wNumProbes + 1];
};  //BeckProbeSetClass
//Last line.
