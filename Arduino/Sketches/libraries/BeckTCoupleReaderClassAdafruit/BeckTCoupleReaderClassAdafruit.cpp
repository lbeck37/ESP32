const char szSystemFileName[]  = "BeckTCoupleReaderClass.cpp";
const char szSystemFileDate[]  = "3/11/22c";

#include <BeckTCoupleReaderClass.h>
#include <Streaming.h>

BeckTCoupleReaderClass::BeckTCoupleReaderClass()
{
Serial << "BeckTCoupleReaderClass(void) constructor: " << szSystemFileName << ", " << szSystemFileDate << endl << endl;
return;
} //constructor


BeckTCoupleReaderClass::BeckTCoupleReaderClass(uint8_t ucI2CAddress)
{
  _ucI2CAddress= ucI2CAddress;
  Serial << "BeckTCoupleReaderClass(uint8_t) constructor: _ucI2CAddress= " << _ucI2CAddress << endl;
  Serial << "BeckTCoupleReaderClass(uint8_t) constructor: " << szSystemFileName << ", " << szSystemFileDate << endl << endl;
  Serial << "BeckTCoupleReaderClass(uint8_t) constructor: Call _poMCP9600_TCouple= new Adafruit_MCP9600" <<endl << endl;
  _poMCP9600_TCouple= new Adafruit_MCP9600;
  return;
} //BeckTCoupleReaderClass(uint8_t)


BeckTCoupleReaderClass::~BeckTCoupleReaderClass() {
  Serial << "~BeckProbeClass(): Destructor, deleting _poMCP9600_TCouple" << endl;
  delete _poMCP9600_TCouple;
  _poMCP9600_TCouple= nullptr;
   return;
} //destructor


bool BeckTCoupleReaderClass::begin(uint8_t ucI2CAddress){
  bool    bReturn= true;
  Serial << endl << "BeckTCoupleReaderClass::begin(" << ucI2CAddress << ")"<< endl;
  Serial << "BeckTCoupleReaderClass::begin(): " << szSystemFileName << ", " << szSystemFileDate << endl;
  Serial << "BeckTCoupleReaderClass::begin(): Call _poMCP9600_TCouple->begin(" << _ucI2CAddress << ")" << endl;
  bReturn= _poMCP9600_TCouple->begin(ucI2CAddress);
  if (bReturn){
    Serial << "BeckTCoupleReaderClass::begin(): Setting _bTCoupleOK to TRUE" << endl;
    _bTCoupleOK= true;
  }
  else{
    Serial << "BeckTCoupleReaderClass::begin(): _poMCP9600_TCouple->begin() failed, setting _bTCoupleOK to FALSE" << endl;
    _bTCoupleOK= false;
  }
  Serial << "BeckTCoupleReaderClass::begin(): Return bReturn= " << bReturn << endl;
  return bReturn;
} //Begin


double BeckTCoupleReaderClass::Handle(){
  float fDegC=  0.00;

  if(_bTCoupleOK){
    Serial << "BeckTCoupleReaderClass::Handle():Call fDegC= _poMCP9600_TCouple->readThermocouple()" << endl;
    fDegC= _poMCP9600_TCouple->readThermocouple();
  }
  else{
    fDegC= 40.0;
    Serial << "\nBeckTCoupleReaderClass::Handle(): Skip readThermocouple() since MCP9600 didn't connect" << endl;
    Serial << "BeckTCoupleReaderClass::Handle(): Set fDegC to " << fDegC << endl;
  }

  _fDegF_Value= (1.8 * fDegC) + 32.00;
  Serial << "BeckTCoupleReaderClass::Handle(): _fDegF_Value= " << _fDegF_Value << endl;
  return _fDegF_Value;
} //Handle
//Last line.
