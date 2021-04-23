// BeckPinNumbers.h 4/22/21a
#pragma once
#if ESP32
  static const int    sSDA_GPIO             = 21;   //I2C, TTGO pin 21
  static const int    sSCL_GPIO             = 22;   //I2C, TTGO pin 22
  static const int    sOneWireGPIO          = 32;   //TTGO pin 32
  static const int    sHeatSwitchGPIO       = 37;   //Relay 1, TTGO pin 37
  static const int    sThermostatGPIO       = 38;   //Relay 2, TTGO pin 38
#else //ESP8266
  static const int    sAlexaPin             =  2;     //GPIO 2 is D4 and Blue LED on NodeMCU
  static const int    sSDA_GPIO             =  4;   //I2C, GPIO 4 is D2 on NodeMCU
  static const int    sSCL_GPIO             =  5;   //I2C, GPIO 5 is D1 on NodeMCU and labeled D2
  static const int    sOneWireGPIO          = 12;   //GPIO 12 is D6 on NodeMCU
  static const int    sHeatSwitchGPIO       = 14;   //GPIO 14 is D5 on NodeMCU
#endif
//Last line
