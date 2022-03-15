const char szSystemFileName[]  = "BeckCarSetClass.cpp";
const char szSystemFileDate[]  = "3/14/22e";

#include <BeckCarSetClass.h>
#include <BeckProbeClass.h>
#include <BeckSampleDataClass.h>
#include <BeckE32_Defines.h>
#include <Streaming.h>

BeckCarSetClass::BeckCarSetClass()  {
  Serial << "BeckCarSetClass(): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckCarSetClass(): Default CTR, call BuildProbeSets()" << endl;
  //BuildProbeSets();
  BuildObjectData();
  return;
} //constructor


BeckCarSetClass::~BeckCarSetClass() {
  Serial << "~BeckCarSetClass(): Destructor, deleting probes" << endl;
  for (int wProbeSetID= 1; wProbeSetID <= _wNumProbeSets; wProbeSetID++){
    Serial << "~BeckCarSetClass(): Destructor, call delete _apoProbe[" << wProbeSetID << "]" << endl;
    delete _apoProbeSet[wProbeSetID];
    _apoProbeSet[wProbeSetID]= nullptr;
  }   //for
  return;
} //destructor

//  BeckSampleDataClass*    _apoCarSample [_wNumProbeSets + 1] [_wNumProbes + 1];

void BeckCarSetClass::BuildObjectData(){
  Serial << "BuildObjectData(): Build _apoProbeSet[] using new for each BeckProbeSetClass" << endl;
  for (int wProbeSetID= 0; wProbeSetID <= _wNumProbeSets; wProbeSetID++){
    _apoProbeSet[wProbeSetID]= new BeckProbeSetClass(wProbeSetID);
  } //for(int wProbeSetID=0

  Serial << "BuildObjectData(): Build _apoProbeSet[] using new for each BeckProbeSetClass" << endl;
  for (int wProbeSetID= 0; wProbeSetID <= _wNumProbeSets; wProbeSetID++){
    for (int wProbeID= 0; wProbeID <= _wNumProbeSets; wProbeID++){
      _apoCarSamples[wProbeSetID][wProbeID]= new BeckSampleDataClass(wProbeSetID, wProbeID);
    } //for(int wProbeID=0
  } //for(int wProbeSetID=0
  return;
} //BuildObjectData

void BeckCarSetClass::PrintLogData(){
  _apoProbeSet[_wLoggingProbeSetID]->PrintProbeSetData();
  return;
} //PrintLogData

void BeckCarSetClass::ReadProbeSet(uint32_t uwSampleTime, int wProbeID) {
  //Have the ProbeSet handle itself, like have each of its Probes read its TCouple
  _apoProbeSet[wProbeID]->ReadProbeSet(uwSampleTime, wProbeID);
  return;
} //ReadProbeSet
//Last line.
