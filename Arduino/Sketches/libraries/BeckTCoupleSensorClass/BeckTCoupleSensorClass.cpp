static const char szSystemFileName[]  = "BeckTCoupleSensorClass.cpp";
static const char szSystemFileDate[]  = "3/16/22c";

#include <BeckTCoupleSensorClass.h>
#include <SparkFun_MCP9600.h>
#include <Streaming.h>

BeckTCoupleSensorClass::BeckTCoupleSensorClass() {
  Serial << "BeckTCoupleSensorClass(void) Default CTR: " << szSystemFileName << ", " << szSystemFileDate << endl << endl;
  return;
} //CTR


BeckTCoupleSensorClass::BeckTCoupleSensorClass(int wI2CAddress) {
  _wI2CAddress= wI2CAddress;
  //  Serial << "BeckTCoupleSensorClass(uint8_t) CTR: _wI2CAddress= " << _wI2CAddress << endl;
  Serial << ".TCR CTR: " << _wI2CAddress << " ";
  bBegin();
  return;
} //BeckTCoupleSensorClass(uint8_t)


BeckTCoupleSensorClass::~BeckTCoupleSensorClass() {
  Serial << "~BeckTCoupleSensorClass(): Destructor, deleting _poMCP9600_TCouple" << endl;
  delete _poMCP9600_TCouple;
  _poMCP9600_TCouple= nullptr;
   return;
} //destructor


bool BeckTCoupleSensorClass::bBegin(){
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


//void BeckTCoupleSensorClass::SetupMCP9600(int wI2CAddress){
void BeckTCoupleSensorClass::SetupMCP9600(){
//  Serial << "SetupMCP9600(" << _wI2CAddress << "): Call isConnected() to test for MCP9600" << endl;
  if(_bTCoupleOK && (_poMCP9600_TCouple != nullptr)) {
    if (_poMCP9600_TCouple->isConnected()) {
      Serial << "BeckTCoupleSensorClass::SetupMCP9600(" << _wI2CAddress << "): Call to isConnected() PASSED " << endl;
    } //if(_poMCP9600_TCouple->isConnected())
    else {
        Serial << "\nBeckTCoupleSensorClass::SetupMCP9600(" << _wI2CAddress << "): Call to isConnected() FAILED" << endl;
        _bTCoupleOK= false;
    } //if(_poMCP9600_TCouple->isConnected())else

    if (_bTCoupleOK) {
      //check if the Device ID is correct
      //Serial << "SetupMCP9600(" << _wI2CAddress << "): Call checkDeviceID() to test for MCP9600 ID" << endl;
      if(_poMCP9600_TCouple->checkDeviceID()) {
        Serial << "BeckTCoupleSensorClass::SetupMCP9600(" << _wI2CAddress << "): Call to checkDeviceID() PASSED" << endl;
      } //if(_poMCP9600_TCouple->checkDeviceID())
      else {
        Serial << "\nBeckTCoupleSensorClass::SetupMCP9600(" << _wI2CAddress << "): Call to checkDeviceID() FAILED" << endl;
        _bTCoupleOK= false;
      } //if(_poMCP9600_TCouple->checkDeviceID())else
    } //if(_bTCoupleOK)
  } // if(_bTCoupleOK)
  else {
  } // if(_bTCoupleOK)else

  return;
} //SetupMCP9600


float BeckTCoupleSensorClass::fReadProbe(){
  if(_bTCoupleOK){
    _fDegF= fGetDegF();
    Serial << "BeckTCoupleSensorClass::ReadProbe(): fGetDegF() returned " << _fDegF << " from Probe _wI2CAddress= " << _wI2CAddress << endl;
  }
  else{
    _fDegF= 37.99;
    Serial << "\nBeckTCoupleSensorClass::ReadProbe(): Skip fGetDegF() since MCP9600 didn't connect" << endl;
  }
  return _fDegF;
} //ReadProbe


float BeckTCoupleSensorClass::fGetDegF() {
  float   fDegF= 0.99;
  float   fDegC= 0.99;
  if (_bTCoupleOK){
   //Serial << "BeckTCoupleSensorClass::fGetDegF(): Call _poMCP9600_TCouple->getThermocoupleTemp()" << endl;
   fDegC=_poMCP9600_TCouple->getThermocoupleTemp();
   fDegF= (1.80 * fDegC) + 32.00;
  } //if(_bTCoupleOK)
  else {
    Serial << "BeckTCoupleSensorClass::fGetDegF(): Skipped reading tCouple because _bTCoupleOK is false" << endl;
  }
  return fDegF;
} //fGetDegF


bool BeckTCoupleSensorClass::bGetProbeOK() {
  return _bTCoupleOK;
} //bGetProbeOK
//Last line.
