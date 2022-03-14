const char szSystemFileName[]  = "BeckCarSetClass.cpp";
const char szSystemFileDate[]  = "3/14/22d";

#include <BeckCarSetClass.h>
#include <BeckProbeClass.h>
#include <BeckSampleDataClass.h>
#include <BeckE32_Defines.h>
#include <Streaming.h>

BeckCarSetClass::BeckCarSetClass()  {
  Serial << "BeckCarSetClass(): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckCarSetClass(): Default CTR, call BuildProbeSets()" << endl;
  BuildProbeSets();
  return;
} //constructor


BeckCarSetClass::~BeckCarSetClass() {
  Serial << "~BeckCarSetClass(): Destructor, deleting probes" << endl;
  for (int8_t cProbeSetID= 1; cProbeSetID <= _wNumProbeSets; cProbeSetID++){
    Serial << "~BeckCarSetClass(): Destructor, call delete _apoProbe[" << cProbeSetID << "]" << endl;
    delete _apoProbeSet[cProbeSetID];
    _apoProbeSet[cProbeSetID]= nullptr;
  }   //for
  return;
} //destructor

void BeckCarSetClass::BuildProbeSets(){
  Serial << "BuildProbeSets(): Build _apoProbeSet[] using new for each BeckProbeSetClass" << endl;
  for (int8_t cProbeSetID= 0; cProbeSetID <= _wNumProbeSets; cProbeSetID++){
    _apoProbeSet[cProbeSetID]= new BeckProbeSetClass(cProbeSetID);
   }
  return;
} //BuildProbeSets

void BeckCarSetClass::PrintLogData(){
  _apoProbeSet[_cLogProbeSetID]->PrintProbeSetData();
  return;
} //PrintLogData

void BeckCarSetClass::Handle(uint32_t uwSampleTime, int8_t cProbeID) {
  //Have the ProbeSet handle itself, like have each of its Probes read its TCouple
  _apoProbeSet[cProbeID]->Handle(uwSampleTime, cProbeID);
  return;
} //Handle
//Last line.
