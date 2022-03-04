// BeckTireTempDefines.h, 3/3/22a
#pragma once
#include <cstdint>

//Define the code that is built
#define DO_ROVER                true
#define DO_OTA                  true

#define DO_ACCESS_POINT         false
#define DO_FIREBASE             false
//#define DO_ALEXA                false

/*
#if DO_ROVER
  #include <WROVER_KIT_LCD.h>
#endif
*/

typedef   int16_t       ColorType;      //See Adafruit_GFX.h
typedef   int16_t       PUnit;          //Pixel Unit
typedef   uint8_t       FontSize;

//ESP32
//Pins used by WROVER-KIT LCD display (ref. WROVER_KIT_LCD.cpp)
/*
#define WROVER_RST              18
#define WROVER_SCLK             19
#define WROVER_DC               21
#define WROVER_CS               22
#define WROVER_MOSI             23
#define WROVER_MISO             25
#define WROVER_BL               5   //Backlight
*/

//Pinout using unused camera pins for bit-banging MISO and CLK
static const int8_t     _cSPI_MISO_Pin    = 26;
static const int8_t     _cSPI_CLK_Pin     = 27;

static const int8_t     _cSPI_CS_Pin1     = 12;
static const int8_t     _cSPI_CS_Pin2     = 13;
static const int8_t     _cSPI_CS_Pin3     = 14;

static const int8_t     _cRGB_RedPin      =  0;
static const int8_t     _cRGB_GreenPin    =  2;
static const int8_t     _cRGB_BluePin     =  4;

//static const int8_t     _cRF_Button       =  15;
//static const int8_t     _cRF_Button       =  32;

static const int        _wNumProbes       =  3;

extern uint8_t   _acSPI_CS_Pins[];
//Last line
