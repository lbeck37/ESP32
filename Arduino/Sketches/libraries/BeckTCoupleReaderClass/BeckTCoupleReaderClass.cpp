const char szSystemFileName[]  = "BeckTCoupleReaderClass.cpp";
const char szSystemFileDate[]  = "3/10/22b";

#include <BeckTCoupleReaderClass.h>
#include <Streaming.h>

BeckTCoupleReaderClass::BeckTCoupleReaderClass()
{
Serial << "BeckTCoupleReaderClass(void) constructor: " << szSystemFileName << ", " << szSystemFileDate << endl << endl;
} //constructor


BeckTCoupleReaderClass::BeckTCoupleReaderClass(uint8_t ucI2CAddress)
{
  _ucI2CAddress= ucI2CAddress;
  Serial << "BeckTCoupleReaderClass(uint8_t) constructor: _ucI2CAddress= " << _ucI2CAddress << endl;
  Serial << "BeckTCoupleReaderClass(uint8_t) constructor: " << szSystemFileName << ", " << szSystemFileDate << endl << endl;
} //BeckTCoupleReaderClass(uint8_t)


BeckTCoupleReaderClass::~BeckTCoupleReaderClass() {
  Serial << "~BeckTCoupleReaderClass(): Destructing" << endl << endl;
} //destructor


bool BeckTCoupleReaderClass::begin(uint8_t ucI2CAddress){
  bool    bReturn= true;
  Serial << endl << "BeckTCoupleReaderClass::begin(" << ucI2CAddress << ")"<< endl;
  Serial << "BeckTCoupleReaderClass::begin(): " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckTCoupleReaderClass::begin(): Return  _oMCP9600_TCouple.begin(" << _ucI2CAddress << ")" << endl;
  bReturn= _oMCP9600_TCouple.begin(ucI2CAddress);
  return bReturn;
} //Begin


double BeckTCoupleReaderClass::Handle(){
  float fDegC=  0.00;

  Serial << "\nBeckTCoupleReaderClass::Handle():Call fDegC= _oMCP9600_TCouple.readThermocouple()" << endl;
  fDegC= _oMCP9600_TCouple.readThermocouple();

  _fDegF_Value= (1.8 * fDegC) + 32.00;

  Serial << "BeckTCoupleReaderClass::Handle(): _fDegF_Value= " << _fDegF_Value << endl;
  return _fDegF_Value;
} //Handle
//Last line.
