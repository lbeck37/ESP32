const char szSystemFileName[]  = "BeckProbeSetClass.cpp";
const char szSystemFileDate[]  = "3/6/22a";

#include <BeckProbeSetClass.h>
#include <BeckProbeClass.h>
#include <BeckSampleDataClass.h>
#include <BeckE32_Defines.h>
#include <Streaming.h>

uint8_t   _aucI2CAdresses[] {0, _ucI2CAddress1, _ucI2CAddress2, _ucI2CAddress3};

BeckProbeSetClass::BeckProbeSetClass(){
  return;
} //constructor


BeckProbeSetClass::~BeckProbeSetClass() {
  Serial << "~BeckProbeSetClass(): Destructing" << endl;
} //destructor


void BeckProbeSetClass::BuildProbes(){
  double adProbeDegF[4];

  Serial << "BeckProbeSetClass::BuildProbes(): Construct probes " << endl;
  for (int wProbe= 1; wProbe <= _wNumProbes; wProbe++){
    uint8_t ucI2CAddress= _aucI2CAdresses[wProbe];
    Serial << "BeckProbeSetClass::BuildProbes(): Call BeckProbeClass(" << ucI2CAddress << ")" << endl;
    _aoProbes[wProbe]= BeckProbeClass(ucI2CAddress);

    Serial << "BeckProbeSetClass::BuildProbes(): Call _aoProbes[" << wProbe << "].Begin()" << endl;
    _aoProbes[wProbe].Begin();
    Serial << "BeckProbeSetClass::BuildProbes(): Do next probe in for loop" << endl;
   }
  Serial << "BeckProbeSetClass::BuildProbes(): return after 1 sec delay" << endl;
  delay(1000);
  return;
} //Handle


void BeckProbeSetClass::Handle(){
  double adProbeDegF[4];

  for (int wProbe= 1; wProbe <= _wNumProbes; wProbe++){
    adProbeDegF[wProbe]= _aoProbes[wProbe].Handle();
   }
  Serial << "BeckProbeSetClass::Handle(): " << endl <<
      "    Thermo #1= " << adProbeDegF[1] << "F, #2= " << adProbeDegF[2] << "F, #3=" << adProbeDegF[3] << endl;
  return;
} //Handle
//Last line.
