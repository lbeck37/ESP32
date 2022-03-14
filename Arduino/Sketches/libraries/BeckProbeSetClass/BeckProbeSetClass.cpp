const char szSystemFileName[]  = "BeckProbeSetClass.cpp";
const char szSystemFileDate[]  = "3/13/22g";

#include <BeckProbeClass.h>
#include <BeckProbeSetClass.h>
#include <BeckCarSetClass.h>
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
  for (int8_t cProbeID= 1; cProbeID <= _wNumProbes; cProbeID++){
    uint8_t ucI2CAddress= _aucI2CAdresses[cProbeID];
    _apoProbe[cProbeID]= new BeckProbeClass(cProbeID, ucI2CAddress);
    _apoProbe[cProbeID]->Begin();
   }
  return;
} //Handle

void BeckProbeSetClass::PrintProbeSetData(void) {
  for (int8_t cProbe= 1; cProbe <= _wNumProbes; cProbe++){
    //Serial << "BeckProbeSetClass::PrintProbeSetData(): Printing data for Probe #" << cProbe << endl;
   }
  return;
}

void BeckProbeSetClass::Handle(uint32_t uwSampleTime) {
  _uwSampleTime= uwSampleTime;
  //Have each Probe handle itself, like read the tcouple
  for (int8_t cProbe= 1; cProbe <= _wNumProbes; cProbe++){
    _apoProbe[cProbe]->Handle(uwSampleTime);
   }
  Serial << "    Thermo #1= " << _apoProbe[1]->fGetDegF() << "F, #2= " << _apoProbe[2]->fGetDegF() << "F, #3=" << _apoProbe[3]->fGetDegF() << endl;
  return;
} //Handle
//Last line.
