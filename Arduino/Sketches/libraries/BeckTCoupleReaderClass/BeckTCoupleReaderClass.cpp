const char szSystemFileName[]  = "BeckTCoupleReaderClass.cpp";
const char szSystemFileDate[]  = "2/27/22b";  //From 5/31/21e

#include <BeckTCoupleReaderClass.h>
#include <Streaming.h>

BeckTCoupleReaderClass::BeckTCoupleReaderClass() {
  Serial << "BeckTCoupleReaderClass::BeckTCoupleReaderClass(): " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor


BeckTCoupleReaderClass::BeckTCoupleReaderClass(uint8_t ucSPI_MISO_Pin, uint8_t ucSPI_CLK_Pin, uint8_t ucSPI_CS_Pin){
  _ucSPI_MISO_Pin = ucSPI_MISO_Pin;
  _ucSPI_CLK_Pin  = ucSPI_CLK_Pin;
  _ucSPI_CS_Pin   = ucSPI_CS_Pin;

  //MAX6675   _oMAX6675_Thermocouple(_cSPI_CLK_Pin, _ucSPI_CS_Pin, _cSPI_MISO_Pin);
  //MAX6675 *_poMAX6675_Thermocouple= new MAX6675(_cSPI_CLK_Pin, _ucSPI_CS_Pin, _cSPI_MISO_Pin);
  //*_poMAX6675_Thermocouple= new MAX6675(_cSPI_CLK_Pin, _ucSPI_CS_Pin, _cSPI_MISO_Pin);
  //MAX6675 _oMAX6675_Thermocouple(_cSPI_CLK_Pin, _ucSPI_CS_Pin, _cSPI_MISO_Pin);
  Serial << "BeckTCoupleReaderClass::BeckTCoupleReaderClass(): " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor


BeckTCoupleReaderClass::~BeckTCoupleReaderClass() {
  Serial << "~BeckTCoupleReaderClass(): Destructing" << endl;
} //destructor

/*
//double dfMAX6675DegC= _aoProbes[wProbe].readCelsius();
double dfMAX6675DegF= _aoProbes[wProbe].readFahrenheit();
adMAX6675DegF[wThermo]= dfMAX6675DegF;
//Serial << "loop(): Thermocouple Number " << wThermo << " is at " << dfMAX6675DegF << "F" << ", " << dfMAX6675DegC << "C" << endl;
*/

double BeckTCoupleReaderClass::Handle(){
  double dfDegF= 0.00;

  Serial << "BeckTCoupleReaderClass::Handle(): Call _poMAX6675_Thermocouple->readFahrenheit()" << dfDegF << endl;
  //dfDegF= _poMAX6675_Thermocouple->readFahrenheit();
  //dfDegF= _oMAX6675_Thermocouple.readFahrenheit();
  Serial << "BeckTCoupleReaderClass::Handle(): dfDegF= " << dfDegF << endl;
  return dfDegF;
} //Handle
//Last line.
