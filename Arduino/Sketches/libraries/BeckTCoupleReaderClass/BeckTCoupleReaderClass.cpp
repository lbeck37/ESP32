static const char szSystemFileName[]  = "BeckTCoupleReaderClass.cpp";
static const char szSystemFileDate[]  = "3/14/22b";

#include <BeckTCoupleReaderClass.h>
#include <SparkFun_MCP9600.h>
#include <Streaming.h>

BeckTCoupleReaderClass::BeckTCoupleReaderClass() {
  Serial << "BeckTCoupleReaderClass(void) Default CTR: " << szSystemFileName << ", " << szSystemFileDate << endl << endl;
  return;
} //CTR


BeckTCoupleReaderClass::BeckTCoupleReaderClass(uint8_t ucI2CAddress) {
//  Serial << "BeckTCoupleReaderClass(uint8_t) CTR: _ucI2CAddress= " << _ucI2CAddress << endl;
  _ucI2CAddress   = ucI2CAddress;
  SetupMCP9600    (_ucI2CAddress);
  return;
} //BeckTCoupleReaderClass(uint8_t)


BeckTCoupleReaderClass::~BeckTCoupleReaderClass() {
  Serial << "~BeckProbeClass(): Destructor, deleting _poMCP9600_TCouple" << endl;
  delete _poMCP9600_TCouple;
  _poMCP9600_TCouple= nullptr;
   return;
} //destructor


void BeckTCoupleReaderClass::SetupMCP9600(int8_t cI2CAddress){
  //Serial << "SetupMCP9600(" << cI2CAddress << "): Use new() to create an MCP9600 object" << endl;
  _poMCP9600_TCouple= new (std::nothrow) MCP9600 {};

  if (_poMCP9600_TCouple != nullptr) {
    //Serial << "SetupMCP9600(" << cI2CAddress << "): Call begin() for MCP9600 at I2C address " << cI2CAddress << endl;
    _poMCP9600_TCouple->begin(cI2CAddress);
  } //if(_poMCP9600_TCouple!=nullptr)
  else{
    Serial << "SetupMCP9600(" << cI2CAddress << "): new() FAILED for MCP9600 object at I2C address " << cI2CAddress << endl;
    _bTCoupleOK= false;
  } //if(_poMCP9600_TCouple!=nullptr)else

//  Serial << "SetupMCP9600(" << cI2CAddress << "): Call isConnected() to test for MCP9600" << endl;
  if(_bTCoupleOK) {
    if (_poMCP9600_TCouple->isConnected()) {
      //Serial << "SetupMCP9600(" << cI2CAddress << "): Call to isConnected() PASSED " << endl;
    } //if(_poMCP9600_TCouple->isConnected())
    else {
        Serial << "SetupMCP9600(" << cI2CAddress << "): Call to isConnected() FAILED" << endl;
        _bTCoupleOK= false;
    } //if(_poMCP9600_TCouple->isConnected())else

    if (_bTCoupleOK) {
      //check if the Device ID is correct
      //Serial << "SetupMCP9600(" << cI2CAddress << "): Call checkDeviceID() to test for MCP9600 ID" << endl;
      if(_poMCP9600_TCouple->checkDeviceID()) {
        //Serial << "SetupMCP9600(" << cI2CAddress << "): Call to checkDeviceID() PASSED" << endl;
      } //if(_poMCP9600_TCouple->checkDeviceID())
      else {
        Serial << "SetupMCP9600(" << cI2CAddress << "): Call to checkDeviceID() FAILED" << endl;
        _bTCoupleOK= false;
      } //if(_poMCP9600_TCouple->checkDeviceID())else
    } //if(_bTCoupleOK)
  } // if(_bTCoupleOK)
  else {
  } // if(_bTCoupleOK)else

  return;
} //SetupMCP9600


bool BeckTCoupleReaderClass::begin(uint8_t ucI2CAddress){
  bool    bReturn= true;
  //Serial << "BeckTCoupleReaderClass::begin(): " << szSystemFileName << ", " << szSystemFileDate << endl;
  //Serial << "BeckTCoupleReaderClass::begin(): Call _poMCP9600_TCouple->begin(" << _ucI2CAddress << ")" << endl;
  bReturn= _poMCP9600_TCouple->begin(ucI2CAddress);

  if (bReturn){
    //Serial << "BeckTCoupleReaderClass::begin(): Setting _bTCoupleOK to TRUE" << endl;
    _bTCoupleOK= true;
  }
  else{
    Serial << "BeckTCoupleReaderClass::begin(): _poMCP9600_TCouple->begin() failed, setting _bTCoupleOK to FALSE" << endl;
    _bTCoupleOK= false;
  }
  return bReturn;
} //Begin


void BeckTCoupleReaderClass::Handle(){
  if(_bTCoupleOK){
    _fDegF= fGetDegF();
  }
  else{
    _fDegF= 37.99;
    Serial << "\nBeckTCoupleReaderClass::Handle(): Skip fGetDegF() since MCP9600 didn't connect" << endl;
    Serial << "BeckTCoupleReaderClass::Handle(): Set fDegF to " << _fDegF << endl;
  }
  return;
} //Handle


float BeckTCoupleReaderClass::fGetDegF() {
  float   fDegF= 0.99;
  float   fDegC= 0.99;
  if (_bTCoupleOK){
   Serial << "BeckTCoupleReaderClass::fGetDegF(): Call _poMCP9600_TCouple->getThermocoupleTemp()" << endl;
   fDegC=_poMCP9600_TCouple->getThermocoupleTemp();
   fDegF= (1.80 * fDegC) + 32.00;
  } //if(_bTCoupleOK)
  else {
    Serial << "BeckTCoupleReaderClass::fGetDegF(): Skipped reading tCouple because _bTCoupleOK is false" << endl;
  }
  return fDegF;
} //fGetDegF


bool BeckTCoupleReaderClass::bGetProbeOK() {
  return _bTCoupleOK;
} //bGetProbeOK
//Last line.
