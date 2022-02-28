// BeckProbeSetClass.h, 2/27/22c
#pragma once
#include <BeckProbeClass.h>

class BeckProbeSetClass{
public:
  BeckProbeSetClass           ();
  BeckProbeSetClass           (MAX6675 _aoMAX6675[]);
  virtual ~BeckProbeSetClass  ();

  void    Handle              (void);

protected:
  static BeckProbeClass          _aoProbes[];
};  //BeckProbeSetClass
//Last line.
