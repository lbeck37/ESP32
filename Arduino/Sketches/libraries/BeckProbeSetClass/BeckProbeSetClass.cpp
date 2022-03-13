const char szSystemFileName[]  = "BeckProbeSetClass.cpp";
const char szSystemFileDate[]  = "3/13/22d";

#include <BeckProbeSetClass.h>
#include <BeckProbeClass.h>
#include <BeckSampleDataClass.h>
#include <BeckE32_Defines.h>
#include <Streaming.h>

BeckProbeSetClass::BeckProbeSetClass(void) : _aucI2CAdresses{0, _ucI2CAddress1, _ucI2CAddress2, _ucI2CAddress3} {
  Serial << "BeckProbeSetClass(): Default constructor, _aucI2CAdresses{} filled with I2CAddresses" << endl;
  Serial << "BeckProbeSetClass(): Default constructor, " << szSystemFileName << ", " << szSystemFileDate << endl;
  return;
} //constructor


BeckProbeSetClass::BeckProbeSetClass(int8_t cProbeSetID) : _aucI2CAdresses{0, _ucI2CAddress1, _ucI2CAddress2, _ucI2CAddress3} {
  Serial << "BeckProbeSetClass(ProbeSetLocationEnum): Constructor, _aucI2CAdresses{} filled with I2CAddresses" << endl;
  _cProbeSetID= cProbeSetID;
  return;
} //constructor


BeckProbeSetClass::~BeckProbeSetClass() {
  Serial << "~BeckProbeSetClass(): Destructor, deleting probes" << endl;
  for (int8_t cProbeID= 1; cProbeID <= _wNumProbes; cProbeID++){
    Serial << "~BeckProbeSetClass(): Destructor, call delete _apoProbe[" << cProbeID << "]" << endl;
    delete _apoProbe[cProbeID];
    _apoProbe[cProbeID]= nullptr;
  }   //for
  return;
} //destructor


void BeckProbeSetClass::BuildProbes(){
  double adProbeDegF[4];

  //Serial << "BeckProbeSetClass::BuildProbes(): Construct probes " << endl;
  for (int8_t cProbeID= 1; cProbeID <= _wNumProbes; cProbeID++){
    uint8_t ucI2CAddress= _aucI2CAdresses[cProbeID];
    //Serial << "BeckProbeSetClass::BuildProbes(): Call _apoProbe[cProbeID]= new BeckProbeClass(" << ucI2CAddress << ")\n\n";
    _apoProbe[cProbeID]= new BeckProbeClass(cProbeID, ucI2CAddress);
    //Serial << "BeckProbeSetClass::BuildProbes(): Call _apoProbe[" << cProbeID << "]->Begin()" << endl;
    _apoProbe[cProbeID]->Begin();
   }
  return;
} //Handle

void BeckProbeSetClass::PrintProbeSetData(void) {
  for (int8_t cProbe= 1; cProbe <= _wNumProbes; cProbe++){
    //_aoSampleData[cProbe].FillSampleData(_uwSampleTime, _afProbeDegF[cProbe]);
    Serial << "BeckProbeSetClass::PrintProbeSetData(): Printing data for Probe #" << cProbe << endl;
   }
  return;
}

void BeckProbeSetClass::Handle(uint32_t uwSampleTime) {
  _uwSampleTime= uwSampleTime;
  //Have each Probe handle itself, like read the tcouple
  for (int8_t cProbe= 1; cProbe <= _wNumProbes; cProbe++){
    _afProbeDegF[cProbe]= _apoProbe[cProbe]->Handle();
    //Serial << "BeckProbeSetClass::Handle(): Call _aoProbes[cProbe].FillSampleData() for probe #" << cProbe << endl;
    //_aoSampleData[cProbe].FillSampleData(_uwSampleTime, _afProbeDegF[cProbe]);

   }
      Serial << "    Thermo #1= " << _afProbeDegF[1] << "F, #2= " << _afProbeDegF[2] << "F, #3=" << _afProbeDegF[3] << endl;
  return;
} //Handle
//Last line.
