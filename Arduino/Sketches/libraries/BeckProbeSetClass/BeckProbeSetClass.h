// BeckProbeSetClass.h, 2/28/22d
#pragma once
#include <BeckProbeClass.h>
#include <BeckTireTempDefines.h>

class BeckProbeSetClass{
public:
  BeckProbeSetClass           ();
  virtual ~BeckProbeSetClass  ();

  //Copy constructor
  BeckProbeSetClass& operator=(const BeckProbeSetClass& t){
    return *this;
  }

  void    Handle              (void);

protected:
  BeckProbeClass          _aoProbes[_wNumProbes + 1];
};  //BeckProbeSetClass
//Last line.
