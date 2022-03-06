// BeckESP32_Defines.h, 3/6/22b
#pragma once
#include <cstdint>

//Define the code that is built
#define DO_ROVER                true
#define DO_OTA                  true
#define DO_MAX6675              false

#define DO_ACCESS_POINT         false
#define DO_FIREBASE             false
//#define DO_ALEXA              false

typedef   int16_t       ColorType;      //See Adafruit_GFX.h
typedef   int16_t       PUnit;          //Pixel Unit
typedef   uint8_t       FontSize;

//ESP32
//Pins used by WROVER-KIT LCD display (ref. WROVER_KIT_LCD.cpp)
/*
#define WROVER_RST                          18
#define WROVER_SCLK                         19
#define WROVER_DC                           21
#define WROVER_CS                           22
#define WROVER_MOSI                         23
#define WROVER_MISO                         25
#define WROVER_BL                            5   //Backlight

  //Pinout using unused camera pins for bit-banging MISO and CLK
  //SPI was required by the MAX6675 boards
  static const int8_t     _cSPI_MISO_Pin    = 26;       // 3/5/22: Using pins 26 for I2C
  static const int8_t     _cSPI_CLK_Pin     = 27;

  static const int8_t     _cSPI_CS_Pin1     = 12;
  static const int8_t     _cSPI_CS_Pin2     = 13;
  static const int8_t     _cSPI_CS_Pin3     = 14;
*/
static const int8_t     _cButton_Pin1     = 12;
static const int8_t     _cButton_Pin2     = 13;
static const int8_t     _cButton_Pin3     = 14;
static const int8_t     _cButton_Pin4     = 15;

static const int8_t     _cI2C_SDA_Pin     = 26;
static const int8_t     _cI2C_SCL_Pin     = 27;


static const uint8_t   _ucI2CAddress1     = 0x67;     //decimal 103
static const uint8_t   _ucI2CAddress2     = 0x66;     //decimal 102
static const uint8_t   _ucI2CAddress3     = 0x60;     //decimal  96

static const int8_t     _cRGB_RedPin      =    0;
static const int8_t     _cRGB_GreenPin    =    2;
static const int8_t     _cRGB_BluePin     =    4;

static const int        _wNumProbes       =  3;

static const int        _wOffsetUTC       = -8;       //SLO is 8 time zones after Greenwich _aucI2CAdresses

extern int8_t     _acSPI_CS_Pins    [];
extern uint8_t    _aucI2CAdresses   [];
//Last line
