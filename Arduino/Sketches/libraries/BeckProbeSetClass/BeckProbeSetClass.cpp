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

/*
//Create the Probes, with a dummy one for a non existant probe 0.
BeckProbeClass   oProbe0(cSPI_MISO_Pin, cSPI_CLK_Pin, acSPI_CS_Pin[0]);
BeckProbeClass   oProbe1(cSPI_MISO_Pin, cSPI_CLK_Pin, acSPI_CS_Pin[1]);
BeckProbeClass   oProbe2(cSPI_MISO_Pin, cSPI_CLK_Pin, acSPI_CS_Pin[2]);
BeckProbeClass   oProbe3(cSPI_MISO_Pin, cSPI_CLK_Pin, acSPI_CS_Pin[3]);
*/

//Create array of Probe objects to pass to the ProbeSet constructor
//BeckProbeClass  aoProbes[] {oProbe0, oProbe1, oProbe2, oProbe3};

BeckProbeSetClass::BeckProbeSetClass() {
  Serial << "BeckProbeSetClass:: Constructor " << szSystemFileName << ", " << szSystemFileDate << endl;
  return;
} //constructor

//BeckProbeSetClass::BeckProbeSetClass(int wNumProbes, BeckProbeClass* aoProbes){
//                   BeckProbeSetClass(byte cSPI_MISO_Pin, byte cSPI_CLK_Pin, int wNumProbes, uint8_t acSPI_CS_Pins[]);
//BeckProbeSetClass::BeckProbeSetClass(byte cSPI_MISO_Pin, byte cSPI_CLK_Pin, int wNumProbes, BeckProbeClass* aoProbes){
BeckProbeSetClass::BeckProbeSetClass(byte cSPI_MISO_Pin, byte cSPI_CLK_Pin, int wNumProbes, uint8_t acSPI_CS_Pins[]){
  //_aoProbes   = aoProbes;
  _wNumProbes = wNumProbes;

  for (int wProbe= 1; wProbe <= _wNumProbes; wProbe++){
    //BeckTCoupleClass(byte cSPI_MISO_Pin, byte cSPI_CLK_Pin, uint8_t ucCS_Pin);
    //adProbeDegF[wProbe]= _aoProbes[wProbe].Handle();
    BeckTCoupleReaderClass oTCoupleReader(cSPI_MISO_Pin, cSPI_CLK_Pin, acSPI_CS_Pins[wProbe]);
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
