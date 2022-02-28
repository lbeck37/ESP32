// BeckTireTempDefines.h, 2/28/22a
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
// https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
//static const int8_t   _cSPI_MOSI_Pin    = 23;     // MasterOutSlaveIn is not used, chips are read only
static const int8_t     _cSPI_MISO_Pin    = 19;
static const int8_t     _cSPI_CLK_Pin     = 18;
static const int        _wNumProbes       =  3;

extern uint8_t   _acSPI_CS_Pins[];
