// BeckBiotaDefines.h, 6/16/21a
#pragma once
#include <cstdint>

//Define the code that is built
#define DO_ACCESS_POINT         false
#define DO_ALEXA                false
//#define DO_ASYNC_WEB_SERVER   false
#define DO_FIREBASE             false
#define USE_IMU                 false
#define DO_NTP                  false
#define DO_OTA                  false
#define DO_THERMOSTAT           false
#define DO_WEB_SERVER           false
#define DO_ROVER                  true
//If DO_ROVER is not true, then the display is on TTGO instead of the ESP-WROVER-KIT

#include <WROVER_KIT_LCD.h>
//#include <TFT_eSPI.h>


typedef   int16_t       ColorType;      //See Adafruit_GFX.h
typedef   int16_t       PUnit;          //Pixel Unit
typedef   uint8_t       FontSize;
typedef   float         DegreeType;

enum ProjectType{
  eNoProject  = 0,
  eThermoDev,
  eEnviro,
  eFireplace,
  eGarage,
  eHeater,
  eFrontLights,
  ePitchMeter,
  eLastProjectType
};

// Color definitions, ripped off from WROVER_KIT_LCD.h
#define BECK_BLACK       0x0000 /*   0,   0,   0 */
#define BECK_NAVY        0x000F /*   0,   0, 128 */
#define BECK_DARKGREEN   0x03E0 /*   0, 128,   0 */
#define BECK_DARKCYAN    0x03EF /*   0, 128, 128 */
#define BECK_MAROON      0x7800 /* 128,   0,   0 */
#define BECK_PURPLE      0x780F /* 128,   0, 128 */
#define BECK_OLIVE       0x7BE0 /* 128, 128,   0 */
#define BECK_LIGHTGREY   0xC618 /* 192, 192, 192 */
#define BECK_DARKGREY    0x7BEF /* 128, 128, 128 */
#define BECK_BLUE        0x001F /*   0,   0, 255 */
#define BECK_GREEN       0x07E0 /*   0, 255,   0 */
#define BECK_CYAN        0x07FF /*   0, 255, 255 */
#define BECK_RED         0xF800 /* 255,   0,   0 */
#define BECK_MAGENTA     0xF81F /* 255,   0, 255 */
#define BECK_YELLOW      0xFFE0 /* 255, 255,   0 */
#define BECK_WHITE       0xFFFF /* 255, 255, 255 */
#define BECK_ORANGE      0xFD20 /* 255, 165,   0 */
#define BECK_GREENYELLOW 0xAFE5 /* 173, 255,  47 */
#define BECK_PINK        0xF81F
//Last line.
