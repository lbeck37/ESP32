const char szSystemFileName[]  = "BeckProbeSetClass.cpp";
const char szSystemFileDate[]  = "2/22/22d";  //From 5/31/21e

#include <BeckProbeSetClass.h>
//#include <BeckEnviroDataClass.h>
#include <BeckProbeClass.h>
#include <BeckTireTempDefines.h>
#include <max6675.h>
#include <Streaming.h>
//#include <Wire.h>

//BeckProbeSetClass      ProbeSet;       //This is so every module can use the same object

//ESP32
// https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
//static const byte    cSPI_MOSI_Pin    = 23;     // MasterOutSlaveIn is not used, chips are read only


//Create array of Probe objects to pass to the ProbeSet constructor
//BeckProbeClass  aoProbes[] {oProbe0, oProbe1, oProbe2, oProbe3};

uint8_t   acSPI_CS_Pins[] {0, 2, 4, 5};

BeckProbeSetClass::BeckProbeSetClass() {
  Serial << "BeckProbeSetClass:: Constructor " << szSystemFileName << ", " << szSystemFileDate << endl;
  return;
} //constructor

//BeckProbeSetClass::BeckProbeSetClass(int wNumProbes, BeckProbeClass* aoProbes){
//                   BeckProbeSetClass(byte cSPI_MISO_Pin, byte cSPI_CLK_Pin, int wNumProbes, uint8_t acSPI_CS_Pins[]);
//BeckProbeSetClass::BeckProbeSetClass(byte cSPI_MISO_Pin, byte cSPI_CLK_Pin, int wNumProbes, BeckProbeClass* aoProbes){
BeckProbeSetClass::BeckProbeSetClass(){

  for (int wProbe= 1; wProbe <= _wNumProbes; wProbe++){
    //BeckTCoupleClass(byte cSPI_MISO_Pin, byte cSPI_CLK_Pin, uint8_t ucCS_Pin);
    //adProbeDegF[wProbe]= _aoProbes[wProbe].Handle();
    //BeckTCoupleReaderClass oTCoupleReader(cSPI_MISO_Pin, cSPI_CLK_Pin, acSPI_CS_Pins[wProbe]);
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
