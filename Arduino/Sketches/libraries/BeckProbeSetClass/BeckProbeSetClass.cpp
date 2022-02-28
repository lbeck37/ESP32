const char szSystemFileName[]  = "BeckProbeSetClass.cpp";
const char szSystemFileDate[]  = "2/27/22c";  //From 5/31/21e

#include <BeckProbeSetClass.h>
#include <BeckProbeClass.h>
#include <BeckTireTempDefines.h>
#include <max6675.h>
#include <Streaming.h>


//Create array of Probe objects to pass to the ProbeSet constructor
//BeckProbeClass  aoProbes[] {oProbe0, oProbe1, oProbe2, oProbe3};

uint8_t   _acSPI_CS_Pins[] {0, 2, 4, 5};
//uint8_t   _acSPI_CS_Pins[];

BeckProbeSetClass::BeckProbeSetClass() {
  Serial << "BeckProbeSetClass:: Constructor " << szSystemFileName << ", " << szSystemFileDate << endl;
  return;
} //constructor

BeckProbeSetClass::BeckProbeSetClass(MAX6675 _aoMAX6675[]){
  for (int wProbe= 1; wProbe <= _wNumProbes; wProbe++){
    //_aoProbes[wProbe]= new BeckProbeClass(_acSPI_CS_Pins[wProbe]);
    _aoProbes[wProbe]= BeckProbeClass(_aoMAX6675[wProbe]);
   }
  //Serial << "BeckProbeSetClass: Construtor, NumProbes= " << _wNumProbes << endl;
  return;
} //constructor


BeckProbeSetClass::~BeckProbeSetClass() {
  Serial << "~BeckProbeSetClass(): Destructing" << endl;
} //destructor


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
