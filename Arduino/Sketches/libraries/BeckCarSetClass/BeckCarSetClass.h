// BeckCarSetClass.h, 3/14/22a
#pragma once
#include <BeckProbeSetClass.h>
#include <BeckE32_Defines.h>

const int    _wNumProbeSets =  4;    //A car has 4 tires

class BeckCarSetClass{
public:
  BeckCarSetClass             ();
  virtual ~BeckCarSetClass    ();

  void  BuildProbeSets        ();
  void  Handle                (uint32_t uwSampleTime, int8_t cProbeID);
  void  PrintLogData          ();
  //void  PrintProbeSetData   ();

private:
 BeckProbeSetClass*           _apoProbeSet[_wNumProbeSets + 1];
 // _apoProbeSet[_cLogProbeSetID] is used for logging, _cLogProbeSetID is the [0] element
};  //BeckCarSetClass
//Last line.
