const char szSystemFileName[]  = "BeckCarSetClass.cpp";
const char szSystemFileDate[]  = "3/15/22g";

#include <BeckCarSetClass.h>
#include <BeckProbeClass.h>
#include <BeckSampleDataClass.h>
#include <BeckE32_Defines.h>
#include <Streaming.h>

BeckCarSetClass::BeckCarSetClass()  {
  Serial << "BeckCarSetClass(): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckCarSetClass(): Default CTR, Call BuildProbeSets()" << endl;
  //BuildProbeSets();
  BuildObjectData();
  Serial << "BeckCarSetClass(): Default CTR, Done" << endl;
  return;
} //constructor


BeckCarSetClass::~BeckCarSetClass() {
  Serial << "~BeckCarSetClass(): Destructor, Deleting probes" << endl;
  for (int wProbeSetID= 1; wProbeSetID <= _wNumProbeSets; wProbeSetID++){
    Serial << "~BeckCarSetClass(): Destructor, call delete _apoProbe[" << wProbeSetID << "]" << endl;
    delete _apoProbeSet[wProbeSetID];
    _apoProbeSet[wProbeSetID]= nullptr;
  }   //for
  return;
} //destructor

//  BeckSampleDataClass*    _apoCarSample [_wNumProbeSets + 1] [_wNumProbes + 1];


void BeckCarSetClass::BuildObjectData(){
//  Serial << "BeckCarSetClass::BuildObjectData(): Begin\n" <<

  int w_apoCarSamplesCount= 1;
  int wTotalProbeSets = _wNumProbeSets + 1;
  int wTotalProbes    = _wNumProbes    + 1;
  int wGrandTotal     = (wTotalProbeSets * wTotalProbes);
  Serial << "BuildObjectData(): Build " << wTotalProbeSets << " X " << wTotalProbes << " = " << wGrandTotal << " _apoCarSamples[][]" << endl;
  Serial << "    ";
  for (int wProbeSetID= 0; wProbeSetID <= _wNumProbeSets; wProbeSetID++){
    for (int wProbeID= 0; wProbeID <= _wNumProbes; wProbeID++){
      Serial << "." << w_apoCarSamplesCount++;
      _apoCarSamples[wProbeSetID][wProbeID]= new BeckSampleDataClass(wProbeSetID, wProbeID);
    } //for(int wProbeID=0...
    Serial << ".*";
  } //for(int wProbeSetID=0...
  Serial << endl;

  Serial << "BuildObjectData(): Build " << (_wNumProbeSets + 1) << " _apoProbeSet[] objects using new" << endl;
  Serial << "    ";
  int w_apoProbeSetCount= 1;
  for (int wProbeSetID= 0; wProbeSetID <= _wNumProbeSets; wProbeSetID++){
    Serial << "*" << w_apoProbeSetCount++;
    _apoProbeSet[wProbeSetID]= new BeckProbeSetClass(wProbeSetID);
  } //for(int wProbeSetID=0
  Serial << ".*" << endl;

  return;
} //BuildObjectData


bool BeckCarSetClass::bBegin(){
  // Call one probe set since all (4) probe-sets use the same (3) probes
  return _apoProbeSet[1]->bBegin();
} //bBegin


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
