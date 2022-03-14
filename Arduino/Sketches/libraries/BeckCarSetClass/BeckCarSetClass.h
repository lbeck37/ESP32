// BeckCarSetClass.h, 3/14/22b
#pragma once
#include <BeckProbeSetClass.h>
#include <BeckE32_Defines.h>

class BeckCarSetClass{
public:
  BeckCarSetClass             ();
  virtual ~BeckCarSetClass    ();

  void  Handle                (uint32_t uwSampleTime, int8_t cProbeID);
  void  PrintLogData          ();

private:
  void  BuildProbeSets        ();

  BeckProbeSetClass*    _apoProbeSet[_wNumProbeSets + 1];
};  //BeckCarSetClass
//Last line.
