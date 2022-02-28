// BeckProbeSetClass.h, 2/28/22c
#pragma once
#include <BeckProbeClass.h>
#include <BeckTireTempDefines.h>

class BeckProbeSetClass{
public:
  BeckProbeSetClass           ();
  virtual ~BeckProbeSetClass  ();

  BeckProbeSetClass& operator=(const BeckProbeSetClass& t){
    return *this;
  }

  void    Handle              (void);

protected:
  BeckProbeClass          _aoProbes[_wNumProbes + 1];
};  //BeckProbeSetClass
//Last line.
