const char szSystemFileName[]  = "BeckProbeSetClass.cpp";
const char szSystemFileDate[]  = "3/15/22c";

#include <BeckProbeClass.h>
#include <BeckProbeSetClass.h>
#include <BeckCarSetClass.h>
#include <BeckSampleDataClass.h>
#include <BeckE32_Defines.h>
#include <Streaming.h>

//BeckProbeSetClass::BeckProbeSetClass() : _aucI2CAdresses{0, _ucI2CAddress1, _ucI2CAddress2, _ucI2CAddress3} {
BeckProbeSetClass::BeckProbeSetClass() {
  Serial << "BeckProbeSetClass(): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
  return;
} //constructor


BeckProbeSetClass::BeckProbeSetClass(int wProbeSetID){
  //Serial << "BeckProbeSetClass(cProbeSetID): CTR, _aucI2CAdresses{} filled with I2CAddresses" << endl;
  _wProbeSetID= wProbeSetID;
  BuildProbes();
  return;
} //constructor


BeckProbeSetClass::~BeckProbeSetClass() {
  Serial << "~BeckProbeSetClass(): Destructor, deleting probes" << endl;
  for (int wProbeID= 1; wProbeID <= _wNumProbes; wProbeID++){
    Serial << "~BeckProbeSetClass(): Destructor, call delete _apoProbe[" << wProbeID << "]" << endl;
    delete _apoProbe[wProbeID];
    _apoProbe[wProbeID]= nullptr;
  }   //for
  return;
} //destructor


void BeckProbeSetClass::BuildProbes(){
  for (int wProbeID= 0; wProbeID <= _wNumProbes; wProbeID++){
    _apoProbe[wProbeID]= new BeckProbeClass(wProbeID, _awI2CAdresses[wProbeID]);
   }
  return;
} //Handle


bool BeckProbeSetClass::bBegin(){
  bool bOK= true;
  // Call bBegin() for each TC probe
  for (int wProbeID= 1; wProbeID <= _wNumProbes; wProbeID++){
    if (_apoProbe[wProbeID]->bBegin() != true) {
      Serial << "BeckProbeSetClass::bBegin(): Failed call to bBegin() for wProbeID= " << wProbeID << endl;
      bOK= false;
    } //if
  } //for
  return bOK;
} //bBegin


void BeckProbeSetClass::PrintProbeSetData(void) {
/*
  for (int wProbe= 1; cProbe <= _wNumProbes; cProbe++){
    //Serial << "BeckProbeSetClass::PrintProbeSetData(): Printing data for Probe #" << cProbe << endl;
   }
*/
  //Serial << "    Thermo #1= " << _apoProbe[1]->fGetDegF() << "F, #2= " << _apoProbe[2]->fGetDegF() << "F, #3=" << _apoProbe[3]->fGetDegF() << endl;
/*
  float   fDegF1, fDegF2, fDeg3;
  float   fDeg1= fGetDegF(1, 1);

  Serial << "    Thermo #1= " << _astSampleData[1][1].fDegF << "F, #2= " << _astSampleData[1][2].fDegF << "F, #3=" << _astSampleData[1][3].fDegF << endl;
*/
  return;
}


void BeckProbeSetClass::ReadProbeSet(uint32_t uwSampleTime, int wProbeID) {
  //_uwSampleTime= uwSampleTime;
  //Have each Probe handle itself, like read the tcouple
/*
  for (int wProbe= 1; cProbe <= _wNumProbes; cProbe++){
    _apoProbe[cProbe]->Handle(uwSampleTime);
   }
  Serial << "    Thermo #1= " << _apoProbe[1]->fGetDegF() << "F, #2= " << _apoProbe[2]->fGetDegF() << "F, #3=" << _apoProbe[3]->fGetDegF() << endl;
*/
  for (int wProbeID= 1; wProbeID <= _wNumProbes; wProbeID++){
    _apoProbe[wProbeID]->fReadProbe(uwSampleTime, wProbeID);
  }
  return;
} //Handle
//Last line.
