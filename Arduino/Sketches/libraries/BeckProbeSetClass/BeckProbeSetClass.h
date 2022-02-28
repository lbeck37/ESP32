// BeckProbeSetClass.h, 2/28/22b
#pragma once
#include <BeckProbeClass.h>
#include <BeckTireTempDefines.h>

class BeckProbeSetClass{
public:
  BeckProbeSetClass           ();
  virtual ~BeckProbeSetClass  ();

  void    Handle              (void);

protected:
  BeckProbeClass          _aoProbes[_wNumProbes + 1];
};  //BeckProbeSetClass
//Last line.
