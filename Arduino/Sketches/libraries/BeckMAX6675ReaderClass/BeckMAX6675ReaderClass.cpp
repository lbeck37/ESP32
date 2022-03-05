const char szSystemFileName[]  = "BeckMAX6675ReaderClass.cpp";
const char szSystemFileDate[]  = "3/5/22a";

#include <BeckMAX6675ReaderClass.h>
#include <Streaming.h>

//Not sure about what CS to use for default, so I used probe 1's CS pin
BeckMAX6675ReaderClass::BeckMAX6675ReaderClass() : _oMAX6675_Thermocouple(_cSPI_CLK_Pin, 2, _cSPI_MISO_Pin), _cSPI_CS_Pin{2}
{
  Serial << "BeckMAX6675ReaderClass(void) constructor: " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor


BeckMAX6675ReaderClass::BeckMAX6675ReaderClass(int8_t cSPI_CS_Pin) : _oMAX6675_Thermocouple(_cSPI_CLK_Pin, cSPI_CS_Pin, _cSPI_MISO_Pin), _cSPI_CS_Pin{cSPI_CS_Pin}
 {
  Serial << "BeckMAX6675ReaderClass(int8_t) constructor: " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckMAX6675ReaderClass(int8_t) constructor: _cSPI_CS_Pin= " << _cSPI_CS_Pin << endl;
} //constructor


BeckMAX6675ReaderClass::~BeckMAX6675ReaderClass() {
  Serial << "~BeckMAX6675ReaderClass(): Destructing" << endl;
} //destructor


double BeckMAX6675ReaderClass::Handle(){
  double dfDegF= 0.00;

  //Serial << "BeckMAX6675ReaderClass::Handle(): _cSPI_CS_Pin= " << _cSPI_CS_Pin << endl;
  //Serial << "BeckMAX6675ReaderClass::Handle(): Call _oMAX6675_Thermocouple.ReadDegF()" << endl;

  dfDegF= _oMAX6675_Thermocouple.ReadDegF();

  //Serial << "BeckMAX6675ReaderClass::Handle(): dfDegF= " << dfDegF << endl;
  return dfDegF;
} //Handle
//Last line.
