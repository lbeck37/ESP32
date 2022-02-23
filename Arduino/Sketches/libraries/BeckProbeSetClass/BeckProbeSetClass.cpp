const char szSystemFileName[]  = "BeckProbeSetClass.cpp";
const char szSystemFileDate[]  = "2/22/22b";  //From 5/31/21e

#include <BeckProbeSetClass.h>
//#include <BeckEnviroDataClass.h>
#include <BeckProbeClass.h>
#include <max6675.h>
#include <Streaming.h>
//#include <Wire.h>

//BeckProbeSetClass      ProbeSet;       //This is so every module can use the same object

//ESP32
// https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
//static const byte    cSPI_MOSI_Pin    = 23;     // MasterOutSlaveIn is not used, chips are read only


BeckProbeSetClass::BeckProbeSetClass() {
  Serial << "BeckProbeSetClass:: Constructor " << szSystemFileName << ", " << szSystemFileDate << endl;
  return;
} //constructor


BeckProbeSetClass::BeckProbeSetClass(int wNumProbes, BeckProbeClass* aoProbes){
  _aoProbes   = aoProbes;
  _wNumProbes = wNumProbes;
  Serial << "BeckProbeSetClass: Construtor, NumProbes= " << _wNumProbes << endl;
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
