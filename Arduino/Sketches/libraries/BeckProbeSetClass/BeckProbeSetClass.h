// BeckProbeSetClass.h, 2/27/22c
#pragma once
#include <BeckProbeClass.h>

class BeckProbeSetClass{
public:
  BeckProbeSetClass           ();
  virtual ~BeckProbeSetClass  ();

  void    Handle              (void);

protected:
  BeckProbeClass          _aoProbes[];
};  //BeckProbeSetClass
//Last line.
