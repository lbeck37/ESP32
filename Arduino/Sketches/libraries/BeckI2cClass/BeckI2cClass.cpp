const char szI2cClassFileName[]  = "BeckI2cClass.cpp";
const char szI2cClassFileDate[]  = "3/12/22a";

#include <BeckI2cClass.h>
#include <BeckE32_Defines.h>
#include <BeckLogLib.h>
#include <BeckPinNumbers.h>
#include <Streaming.h>
#include <Wire.h>

//BeckI2cClass    _oBeckI2C;

BeckI2cClass::BeckI2cClass() {
} //constructor


BeckI2cClass::~BeckI2cClass() {
  Serial << "~SystemClass(): Destructing" << endl;
} //destructor


void BeckI2cClass::Setup(){
  Serial << LOG0 << "BeckI2cClass::Setup() File: " << szI2cClassFileName << ", " << szI2cClassFileDate << endl;
#if !DO_MAX6675
  Serial << LOG0 << "BeckI2cClass::Setup(): Call Wire.begin(_cI2C_SDA_Pin= " << _cI2C_SDA_Pin <<
      ", _cI2C_SCL_Pin= " << _cI2C_SCL_Pin << ")" << endl;
  Wire.begin(_cI2C_SDA_Pin, _cI2C_SCL_Pin);
#endif
  return;
} //Setup


void BeckI2cClass::ScanForDevices(){
  byte ucError, ucAddress;
  int nDevices;
  nDevices = 0;
  Serial << LOG0 << "BeckI2cClass::ScanForDevices(): Perform scan" << endl;
  for(ucAddress = 1; ucAddress < 127; ucAddress++ ){
    //The i2c_scanner uses the return value of the Write.endTransmisstion to see if
    //a device did acknowledge to the address.
    switch (ucAddress) {
    case 96:
    case 102:
    case 103:
      //Serial << LOG0 << "BeckI2cClass::ScanForDevices(): Call Wire.beginTransmission(" << ucAddress << ")" << endl;
      Wire.beginTransmission(ucAddress);
      //Serial << LOG0 << "BeckI2cClass::ScanForDevices(): Call Wire.endTransmission()" << endl;
      //ucError = Wire.endTransmission();
      ucError = Wire.endTransmission();
      //Serial << LOG0 << "BeckI2cClass::ScanForDevices(): Wire.endTransmission() returned " << ucError << endl;
      break;
    default:
      Wire.beginTransmission(ucAddress);
      ucError = Wire.endTransmission();
      break;
    } //switch
    Wire.beginTransmission(ucAddress);
    ucError = Wire.endTransmission();

    if (ucError == 0){
      Serial << LOG0 << "BeckI2cClass::ScanForDevices(): I2C device found at address 0x";
      if (ucAddress<16){
        Serial.print("0");
      } //if(ucAddress<16)
      Serial.println(ucAddress,HEX);
      nDevices++;
    } //if(ucError==0)
    else if (ucError==4) {
      Serial << LOG0 << "BeckI2cClass::ScanForDevices(): Unknown error at address 0x";
      if (ucAddress<16) {
        Serial << "0";
      } //if(ucAddress<16)
      Serial.println(ucAddress,HEX);
    } //else if(ucError==4)
  } //for
 if (nDevices == 0){
    Serial << LOG0 << "BeckI2cClass::ScanForDevices(): ***No I2C devices found***" << endl;
 }  //if(nDevices==0)
  return;
} //ScanForDevices
//Last line.
