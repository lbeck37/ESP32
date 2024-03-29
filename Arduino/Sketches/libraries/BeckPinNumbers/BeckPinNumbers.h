// BeckPinNumbers.h 3/17/22a
#pragma once
//#include <BeckBiotaDefines.h>

#if ESP32
#if DO_TTGO
  static const int    sSDA_GPIO             = 21;   //I2C, TTGO pin 21
  static const int    sSCL_GPIO             = 22;   //I2C, TTGO pin 22
#else
  static const int    sSDA_GPIO             = 26;   //I2C, Rover pin 26
  static const int    sSCL_GPIO             = 27;   //I2C, Rover pin 27
#endif
  static const int    sOneWireGPIO          = 32;   //TTGO pin 32
  static const int    wHeatPin              = 15;   //Relay 1, was 12
  static const int    wThermostatPin        = 13;   //Relay 2, was 13
#else //ESP8266
  static const int    sAlexaPin             =  2;   //GPIO 2 is D4 and Blue LED on NodeMCU
  static const int    sSDA_GPIO             =  4;   //I2C, GPIO 4 is D2 on NodeMCU
  static const int    sSCL_GPIO             =  5;   //I2C, GPIO 5 is D1 on NodeMCU and labeled D2
  static const int    sOneWireGPIO          = 12;   //GPIO 12 is D6 on NodeMCU
  static const int    sHeatSwitchGPIO       = 14;   //GPIO 14 is D5 on NodeMCU
#endif
//Last line
