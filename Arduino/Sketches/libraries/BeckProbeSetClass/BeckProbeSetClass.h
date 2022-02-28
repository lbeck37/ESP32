// BeckProbeSetClass.h, 2/28/22a
#pragma once
#include <BeckProbeClass.h>
#include <BeckTireTempDefines.h>

class BeckProbeSetClass{
public:
  BeckProbeSetClass           ();
  //BeckProbeSetClass           (MAX6675 _aoMAX6675[]);
  virtual ~BeckProbeSetClass  ();

  void    Handle              (void);

protected:
  //static BeckProbeClass          _aoProbes[_wNumProbes + 1];
  BeckProbeClass          _aoProbes[_wNumProbes + 1];
};  //BeckProbeSetClass
//Last line.
