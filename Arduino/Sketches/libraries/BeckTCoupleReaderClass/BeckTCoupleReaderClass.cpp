static const char szSystemFileName[]  = "BeckTCoupleReaderClass.cpp";
static const char szSystemFileDate[]  = "3/15/22e";

#include <BeckTCoupleReaderClass.h>
#include <SparkFun_MCP9600.h>
#include <Streaming.h>

BeckTCoupleReaderClass::BeckTCoupleReaderClass() {
  Serial << "BeckTCoupleReaderClass(void) Default CTR: " << szSystemFileName << ", " << szSystemFileDate << endl << endl;
  return;
} //CTR


BeckTCoupleReaderClass::BeckTCoupleReaderClass(int wI2CAddress) {
  _wI2CAddress= wI2CAddress;
  //  Serial << "BeckTCoupleReaderClass(uint8_t) CTR: _wI2CAddress= " << _wI2CAddress << endl;
  Serial << ".TCR CTR: " << _wI2CAddress << " ";
  bBegin();
  return;
} //BeckTCoupleReaderClass(uint8_t)


BeckTCoupleReaderClass::~BeckTCoupleReaderClass() {
  Serial << "~BeckProbeClass(): Destructor, deleting _poMCP9600_TCouple" << endl;
  delete _poMCP9600_TCouple;
  _poMCP9600_TCouple= nullptr;
   return;
} //destructor


bool BeckTCoupleReaderClass::bBegin(){
  //Serial << "SetupMCP9600(" << wI2CAddress << "): Use new() to create an MCP9600 object" << endl;
  _poMCP9600_TCouple= new (std::nothrow) MCP9600 {};

  if (_poMCP9600_TCouple != nullptr) {
    //Serial << "SetupMCP9600(): Call begin() for MCP9600 at I2C address " << wI2CAddress << endl;
    _poMCP9600_TCouple->begin(_wI2CAddress);
  } //if(_poMCP9600_TCouple!=nullptr)
  else{
    Serial << "\nSetupMCP9600(" << _wI2CAddress << "): new() FAILED for MCP9600 object at I2C address " << _wI2CAddress << endl;
    _bTCoupleOK= false;
  } //if(_poMCP9600_TCouple!=nullptr)else

} //bBegin


//void BeckTCoupleReaderClass::SetupMCP9600(int wI2CAddress){
void BeckTCoupleReaderClass::SetupMCP9600(){
//  Serial << "SetupMCP9600(" << _wI2CAddress << "): Call isConnected() to test for MCP9600" << endl;
  if(_bTCoupleOK && (_poMCP9600_TCouple != nullptr)) {
    if (_poMCP9600_TCouple->isConnected()) {
      //Serial << "SetupMCP9600(" << _wI2CAddress << "): Call to isConnected() PASSED " << endl;
    } //if(_poMCP9600_TCouple->isConnected())
    else {
        Serial << "\nSetupMCP9600(" << _wI2CAddress << "): Call to isConnected() FAILED" << endl;
        _bTCoupleOK= false;
    } //if(_poMCP9600_TCouple->isConnected())else

    if (_bTCoupleOK) {
      //check if the Device ID is correct
      //Serial << "SetupMCP9600(" << _wI2CAddress << "): Call checkDeviceID() to test for MCP9600 ID" << endl;
      if(_poMCP9600_TCouple->checkDeviceID()) {
        //Serial << "SetupMCP9600(" << wI2CAddress << "): Call to checkDeviceID() PASSED" << endl;
      } //if(_poMCP9600_TCouple->checkDeviceID())
      else {
        Serial << "\nSetupMCP9600(" << _wI2CAddress << "): Call to checkDeviceID() FAILED" << endl;
        _bTCoupleOK= false;
      } //if(_poMCP9600_TCouple->checkDeviceID())else
    } //if(_bTCoupleOK)
  } // if(_bTCoupleOK)
  else {
  } // if(_bTCoupleOK)else

  return;
} //SetupMCP9600


float BeckTCoupleReaderClass::fReadProbe(){
  if(_bTCoupleOK){
    _fDegF= fGetDegF();
  }
  else{
    _fDegF= 37.99;
    Serial << "\nBeckTCoupleReaderClass::ReadProbe(): Skip fGetDegF() since MCP9600 didn't connect" << endl;
    Serial << "BeckTCoupleReaderClass::ReadProbe(): Set fDegF to " << _fDegF << endl;
  }
  return _fDegF;
} //ReadProbe


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
