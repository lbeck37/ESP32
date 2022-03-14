const char szSystemFileName[]  = "BeckCarSetClass.cpp";
const char szSystemFileDate[]  = "3/13/22b";

#include <BeckCarSetClass.h>
#include <BeckProbeClass.h>
#include <BeckSampleDataClass.h>
#include <BeckE32_Defines.h>
#include <Streaming.h>

BeckCarSetClass::BeckCarSetClass()  {
  Serial << "BeckCarSetClass(): Default constructor" << endl;
  Serial << "BeckCarSetClass(): Default constructor, " << szSystemFileName << ", " << szSystemFileDate << endl;
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
  for (int8_t cProbeSetID= 0; cProbeSetID <= _wNumProbeSets; cProbeSetID++){
    _apoProbeSet[cProbeSetID]= new BeckProbeSetClass();
   }
  return;
} //BuildProbeSets

void BeckCarSetClass::PrintLogData(){
  _apoProbeSet[_cLogProbeSetID]->PrintProbeSetData();
  return;
} //PrintLogData

void BeckCarSetClass::Handle(uint32_t uwSampleTime, int8_t cProbeID) {
  //_uwSampleTime= uwSampleTime;
/*
  for (int8_t cProbe= 1; cProbe <= _wNumProbes; cProbe++){
    _apoProbe[cProbe]->Handle(uwSampleTime);
   }
  //Serial << "    Thermo #1= " << _apoProbe[1]->fGetDegF() << "F, #2= " << _apoProbe[2]->fGetDegF() << "F, #3=" << _apoProbe[3]->fGetDegF() << endl;
*/
  //Have the ProbeSet handle itself, like have each of its Probes read its TCouple
  _apoProbeSet[cProbeID]->Handle(uwSampleTime, cProbeID);
  return;
} //Handle
//Last line.
