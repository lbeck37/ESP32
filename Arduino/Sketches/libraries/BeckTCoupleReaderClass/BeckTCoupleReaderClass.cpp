const char szSystemFileName[]  = "BeckTCoupleReaderClass.cpp";
const char szSystemFileDate[]  = "2/28/22b";

#include <BeckTCoupleReaderClass.h>
#include <Streaming.h>

BeckTCoupleReaderClass::BeckTCoupleReaderClass() : _oMAX6675_Thermocouple(_cSPI_CLK_Pin, 0, _cSPI_MISO_Pin)
{
  Serial << "BeckTCoupleReaderClass::BeckTCoupleReaderClass(): " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor


BeckTCoupleReaderClass::BeckTCoupleReaderClass(int8_t cSPI_CS_Pin) : _oMAX6675_Thermocouple(_cSPI_CLK_Pin, cSPI_CS_Pin, _cSPI_MISO_Pin)
 {
  Serial << "BeckTCoupleReaderClass::BeckTCoupleReaderClass(): " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor


BeckTCoupleReaderClass::~BeckTCoupleReaderClass() {
  Serial << "~BeckTCoupleReaderClass(): Destructing" << endl;
} //destructor


double BeckTCoupleReaderClass::Handle(){
  double dfDegF= 0.00;

  Serial << "BeckTCoupleReaderClass::Handle(): Call _poMAX6675_Thermocouple->readFahrenheit()" << dfDegF << endl;
  dfDegF= _oMAX6675_Thermocouple.readFahrenheit();
  Serial << "BeckTCoupleReaderClass::Handle(): dfDegF= " << dfDegF << endl;
  return dfDegF;
} //Handle
//Last line.
