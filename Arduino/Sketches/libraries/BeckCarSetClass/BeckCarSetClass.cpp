const char szSystemFileName[]  = "BeckCarSetClass.cpp";
const char szSystemFileDate[]  = "3/13/22a";

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
  for (int8_t cProbeSetID= 1; cProbeSetID <= _wNumProbeSets; cProbeSetID++){
    _apoProbeSet[cProbeSetID]= new BeckProbeSetClass();
   }
  return;
} //BuildProbeSets


/*
void BeckCarSetClass::Handle() {
  //Have each ProbeSet handle itself,and read its (3) probes
  for (int8_t cProbe= 1; cProbe <= _wNumProbes; cProbe++){
    _apoProbeSet[cProbe]->Handle();
   }
  return;
} //Handle
*/
//Last line.
