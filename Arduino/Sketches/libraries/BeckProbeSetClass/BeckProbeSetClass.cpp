const char szSystemFileName[]  = "BeckProbeSetClass.cpp";
const char szSystemFileDate[]  = "3/5/22a";

#include <BeckProbeSetClass.h>
#include <BeckProbeClass.h>
#include <BeckSampleDataClass.h>
#include <BeckE32_Defines.h>
#include <Streaming.h>

//import <iostream>;
//#include <iostream>

//using namespace std;

#if true || DO_MAX6675
uint8_t   _acSPI_CS_Pins[] {0, _cSPI_CS_Pin1, _cSPI_CS_Pin2, _cSPI_CS_Pin3};    //Declared "extern" in BeckE32_Defines.h
#endif

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
#if DO_MAX6675
    byte cCS_Pin= _acSPI_CS_Pins[wProbe];
    Serial << "BeckProbeSetClass::BuildProbes(): Call BeckProbeClass(" << cCS_Pin << ")" << endl;
    _aoProbes[wProbe]= BeckProbeClass(cCS_Pin);
#else

#endif
    //delay(1000);
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

  //Serial << "BeckProbeSetClass::Handle(): return " << endl;
  return;
} //Handle
//Last line.
