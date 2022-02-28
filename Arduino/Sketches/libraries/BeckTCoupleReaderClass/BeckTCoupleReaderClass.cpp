const char szSystemFileName[]  = "BeckTCoupleReaderClass.cpp";
const char szSystemFileDate[]  = "2/27/22b";  //From 5/31/21e

#include <BeckTCoupleReaderClass.h>
#include <Streaming.h>

BeckTCoupleReaderClass::BeckTCoupleReaderClass() {
  //MAX6675 _oMAX6675_Thermocouple(_cSPI_CLK_Pin, 0, _cSPI_MISO_Pin);
  //_oMAX6675_Thermocouple= new MAX6675(_cSPI_CLK_Pin, 0, _cSPI_MISO_Pin);
  Serial << "BeckTCoupleReaderClass::BeckTCoupleReaderClass(): " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor


BeckTCoupleReaderClass::BeckTCoupleReaderClass(MAX6675 oMAX6675){
  _oMAX6675_Thermocouple= oMAX6675;
  Serial << "BeckTCoupleReaderClass::BeckTCoupleReaderClass(MAX6675): " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor


BeckTCoupleReaderClass::BeckTCoupleReaderClass(int8_t cSPI_CS_Pin){
  //MAX6675 oMAX6675_Thermocouple(_cSPI_CLK_Pin, cSPI_CS_Pin, _cSPI_MISO_Pin);
  //_oMAX6675_Thermocouple= new MAX6675(_cSPI_CLK_Pin, cSPI_CS_Pin, _cSPI_MISO_Pin);
  //_oMAX6675_Thermocouple= oMAX6675_Thermocouple;
  Serial << "BeckTCoupleReaderClass::BeckTCoupleReaderClass(): " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor


BeckTCoupleReaderClass::~BeckTCoupleReaderClass() {
  Serial << "~BeckTCoupleReaderClass(): Destructing" << endl;
} //destructor


double BeckTCoupleReaderClass::Handle(){
  double dfDegF= 0.00;

  Serial << "BeckTCoupleReaderClass::Handle(): Call _poMAX6675_Thermocouple->readFahrenheit()" << dfDegF << endl;
  //dfDegF= _oMAX6675_Thermocouple.readFahrenheit();
  Serial << "BeckTCoupleReaderClass::Handle(): dfDegF= " << dfDegF << endl;
  return dfDegF;
} //Handle
//Last line.
