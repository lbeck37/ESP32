// BeckCarSetClass.h, 3/13/22a
#pragma once
#include <BeckProbeSetClass.h>
#include <BeckE32_Defines.h>

const int    _wNumProbeSets =   4;

class BeckCarSetClass{
public:
  BeckCarSetClass             ();
  virtual ~BeckCarSetClass    ();

  void  BuildProbeSets        ();
  //void  Handle                ();
  //void  PrintProbeSetData   ();

private:
 BeckProbeSetClass*       _apoProbeSet[_wNumProbeSets + 1];
};  //BeckCarSetClass
//Last line.
