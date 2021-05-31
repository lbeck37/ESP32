const char szI2cClassFileName[]  = "BeckI2cClass.cpp";
const char szI2cClassFileDate[]  = "5/29/21b";

#include <BeckI2cClass.h>
#include <BeckLogLib.h>
#include <BeckPinNumbers.h>
#include <Streaming.h>
#include <Wire.h>

I2cClass    I2C_Object;

I2cClass::I2cClass() {
} //constructor


I2cClass::~I2cClass() {
  Serial << "~SystemClass(): Destructing" << endl;
} //destructor


void I2cClass::Setup(){
  Serial << LOG0 << "I2cClass::Setup() File: " << szI2cClassFileName << ", " << szI2cClassFileDate << endl;
  Serial << LOG0 << "I2cClass::Setup(): Call Wire.begin(sSDA_GPIO= " << sSDA_GPIO <<
      ", sSCL_GPIO= " << sSCL_GPIO << ")" << endl;
  Wire.begin(sSDA_GPIO, sSCL_GPIO);
  bool  bScanForDevices= true;
  if (bScanForDevices){
    Serial << LOG0 << "I2cClass::Setup(): Call ScanForDevices()" << endl;
    ScanForDevices();
  }
  return;
} //Setup


void I2cClass::ScanForDevices(){
  byte ucError, ucAddress;
  int nDevices;
  nDevices = 0;
  Serial << LOG0 << "I2cClass::ScanForDevices(): Perform scan" << endl;
  for(ucAddress = 1; ucAddress < 127; ucAddress++ ){
    //The i2c_scanner uses the return value of the Write.endTransmisstion to see if
    //a device did acknowledge to the address.
    Wire.beginTransmission(ucAddress);
    ucError = Wire.endTransmission();

    if (ucError == 0){
      Serial << LOG0 << "I2cClass::ScanForDevices(): I2C device found at address 0x";
      if (ucAddress<16){
        Serial.print("0");
      } //if(ucAddress<16)
      Serial.println(ucAddress,HEX);
      nDevices++;
    } //if(ucError==0)
    else if (ucError==4) {
      Serial << LOG0 << "I2cClass::ScanForDevices(): Unknown error at address 0x";
      if (ucAddress<16) {
        Serial << "0";
      } //if(ucAddress<16)
      Serial.println(ucAddress,HEX);
    } //else if(ucError==4)
  } //for
 if (nDevices == 0){
    Serial << LOG0 << "I2cClass::ScanForDevices(): ***No I2C devices found***" << endl;
 }  //if(nDevices==0)
  return;
} //ScanForDevices
//Last line.
