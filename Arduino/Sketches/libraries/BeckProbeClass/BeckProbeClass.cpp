const char szSystemFileName[]  = "BeckProbeClass.cpp";
const char szSystemFileDate[]  = "2/22/22e";  //From 5/31/21e

#include <BeckProbeClass.h>
#include <Streaming.h>

BeckProbeClass::BeckProbeClass() {
  Serial << "BeckProbeClass::BeckProbeClass(): " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor


BeckProbeClass::BeckProbeClass(byte cSPI_MISO_Pin, byte cSPI_CLK_Pin, uint8_t ucSPI_CS_Pin){
  _cSPI_MISO_Pin  = cSPI_MISO_Pin;
  _cSPI_CLK_Pin   = cSPI_CLK_Pin;
  _ucSPI_CS_Pin   = ucSPI_CS_Pin;

  MAX6675   _oMAX6675_Thermocouple(_cSPI_CLK_Pin, _ucSPI_CS_Pin, _cSPI_MISO_Pin);
  Serial << "BeckProbeClass::BeckProbeClass(): " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor


BeckProbeClass::~BeckProbeClass() {
  Serial << "~BeckProbeClass(): Destructing" << endl;
} //destructor

/*
//double dfMAX6675DegC= _aoProbes[wProbe].readCelsius();
double dfMAX6675DegF= _aoProbes[wProbe].readFahrenheit();
adMAX6675DegF[wThermo]= dfMAX6675DegF;
//Serial << "loop(): Thermocouple Number " << wThermo << " is at " << dfMAX6675DegF << "F" << ", " << dfMAX6675DegC << "C" << endl;
*/

double BeckProbeClass::Handle(){
  double dfDegF= 0.00;

  dfDegF= _oMAX6675_Thermocouple.readFahrenheit();

  Serial << "BeckProbeClass::Handle(): return " << dfDegF << endl;
  return dfDegF;
} //Handle
//Last line.
