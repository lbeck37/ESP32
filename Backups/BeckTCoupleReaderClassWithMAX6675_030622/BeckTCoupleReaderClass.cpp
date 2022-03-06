const char szSystemFileName[]  = "BeckTCoupleReaderClass.cpp";
const char szSystemFileDate[]  = "3/5/22b";

#include <BeckTCoupleReaderClass.h>
#include <Streaming.h>

//Not sure about what CS to use for default, so I used probe 1's CS pin
#if DO_MAX6675
  BeckTCoupleReaderClass::BeckTCoupleReaderClass() : _oMAX6675_TCouple(_cSPI_CLK_Pin, 2, _cSPI_MISO_Pin), _cSPI_CS_Pin{2}
{
  Serial << "BeckTCoupleReaderClass(void) constructor: " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor


BeckTCoupleReaderClass::BeckTCoupleReaderClass(int8_t cSPI_CS_Pin) : _oMAX6675_TCouple(_cSPI_CLK_Pin, cSPI_CS_Pin, _cSPI_MISO_Pin)
{
  _cSPI_CS_Pin= cSPI_CS_Pin;
  Serial << "BeckTCoupleReaderClass(int8_t) constructor: " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckTCoupleReaderClass(int8_t) constructor: _cSPI_CS_Pin= " << _cSPI_CS_Pin << endl;
} // BeckTCoupleReaderClass(int8_t)
#else

BeckTCoupleReaderClass::BeckTCoupleReaderClass()
{
Serial << "BeckTCoupleReaderClass(void) constructor: " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor


BeckTCoupleReaderClass::BeckTCoupleReaderClass(uint8_t ucI2CAddress)
{
  _ucI2CAddress= ucI2CAddress;
  Serial << "BeckTCoupleReaderClass(uint8_t) constructor: " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckTCoupleReaderClass(uint8_t) constructor: _ucI2CAddress= " << _ucI2CAddress << endl;
} //BeckTCoupleReaderClass(uint8_t)
#endif

BeckTCoupleReaderClass::~BeckTCoupleReaderClass() {
  Serial << "~BeckTCoupleReaderClass(): Destructing" << endl;
} //destructor


bool BeckTCoupleReaderClass::begin(uint8_t ucI2CAddress){
  bool    bReturn= true;
  bReturn= _oMCP9600_TCouple.begin(ucI2CAddress);
  return bReturn;
} //Begin


double BeckTCoupleReaderClass::Handle(){
  float fDegF=  0.00;

#if DO_MAX6675
  //Serial << "BeckTCoupleReaderClass::Handle(): _cSPI_CS_Pin= " << _cSPI_CS_Pin << endl;
  //Serial << "BeckTCoupleReaderClass::Handle(): Call _oMAX6675_TCouple.ReadDegF()" << endl;
  dfDegF= _oMAX6675_TCouple.ReadDegF();
#else
  Serial << "BeckTCoupleReaderClass::Handle():Call _oMCP9600_TCouple.readThermocouple()" << endl;
  fDegF= _oMCP9600_TCouple.readThermocouple();
#endif

  Serial << "BeckTCoupleReaderClass::Handle(): fDegF= " << fDegF << endl;
  return fDegF;
} //Handle
//Last line.
