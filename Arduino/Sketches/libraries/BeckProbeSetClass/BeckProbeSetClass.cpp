const char szSystemFileName[]  = "BeckProbeSetClass.cpp";
const char szSystemFileDate[]  = "2/28/22h";

#include <BeckProbeSetClass.h>
#include <BeckProbeClass.h>
#include <BeckTireTempDefines.h>
#include <Streaming.h>


uint8_t   _acSPI_CS_Pins[] {0, 2, 4, 5};    //Declared "extern" in BeckTireTempDefines.h

BeckProbeSetClass::BeckProbeSetClass(){
/*
  for (int wProbe= 1; wProbe <= _wNumProbes; wProbe++){
    _aoProbes[wProbe]= BeckProbeClass(_acSPI_CS_Pins[wProbe]);
   }
  Serial << "BeckProbeSetClass:: Constructor " << szSystemFileName << ", " << szSystemFileDate << endl;
*/
  return;
} //constructor


BeckProbeSetClass::~BeckProbeSetClass() {
  Serial << "~BeckProbeSetClass(): Destructing" << endl;
} //destructor


void BeckProbeSetClass::BuildProbes(){
  double adProbeDegF[4];

  Serial << "BeckProbeSetClass::BuildProbes(): Construct probes " << endl;
  for (int wProbe= 1; wProbe <= _wNumProbes; wProbe++){
    byte cCS_Pin= _acSPI_CS_Pins[wProbe];
    //_aoProbes[wProbe]= BeckProbeClass(_acSPI_CS_Pins[wProbe]);
    Serial << "BeckProbeSetClass::BuildProbes(): Call BeckProbeClass(" << cCS_Pin << ")" << endl;
    _aoProbes[wProbe]= BeckProbeClass(cCS_Pin);
    delay(1000);
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

  Serial << "BeckProbeSetClass::Handle(): return " << endl;
  return;
} //Handle
//Last line.
