// BeckTireTempDefines.h, 3/2/22d
#pragma once
#include <cstdint>

//Define the code that is built
#define DO_ROVER                true
#define DO_OTA                  true

#define DO_ACCESS_POINT         false
#define DO_FIREBASE             false
//#define DO_ALEXA                false

#if DO_ROVER
  #include <WROVER_KIT_LCD.h>
#endif

typedef   int16_t       ColorType;      //See Adafruit_GFX.h
typedef   int16_t       PUnit;          //Pixel Unit
typedef   uint8_t       FontSize;

//ESP32
//Pinout using unused camera pins for MISO and CLK
static const int8_t     _cSPI_MISO_Pin    = 26;
static const int8_t     _cSPI_CLK_Pin     = 27;

static const int8_t     _cSPI_CS_Pin1     = 12;
static const int8_t     _cSPI_CS_Pin2     = 13;
static const int8_t     _cSPI_CS_Pin3     = 14;

static const int8_t     _cRGB_RedPin      =  0;
static const int8_t     _cRGB_GreenPin    =  2;
static const int8_t     _cRGB_BluePin     =  4;

/*
// https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
#if true
//Pinout for V-SPI
//static const int8_t   _cSPI_MOSI_Pin    = 23;     // MasterOutSlaveIn is not used, chips are read only
static const int8_t     _cSPI_MISO_Pin    = 19;
static const int8_t     _cSPI_CLK_Pin     = 18;
#else
//Pinout for H-SPI
//static const int8_t   _cSPI_MOSI_Pin    = 13;     // MasterOutSlaveIn is not used, chips are read only
static const int8_t     _cSPI_MISO_Pin    = 12;
static const int8_t     _cSPI_CLK_Pin     = 14;
#endif
*/
static const int        _wNumProbes       =  3;

extern uint8_t   _acSPI_CS_Pins[];
