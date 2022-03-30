// BeckESP32_Defines.h, 3/29/22b
#pragma once
#include <cstdint>

//Define the code that is built
#define DO_ROVER                true
#define DO_OTA                  true
#define DO_MAX6675              false

#define DO_ACCESS_POINT         false
#define DO_FIREBASE             false
//#define DO_ALEXA              false

static const  char*     _szRouterName     = "Aspot24b";
static const  char*     _szRouterPW       = "Qazqaz11";

typedef int16_t         ColorType;      //See Adafruit_GFX.h
typedef int16_t         PUnit;          //Pixel Unit
typedef uint8_t         FontSize;

static unsigned long    _ulNextDispLogMsec    =    0;
static unsigned long    _ulDispLogPeriodMsec  =  200;   //mSec between updating the log on the display

static unsigned long    _ulNextPrintLogMsec   =    0;
static unsigned long    _ulPrintLogPeriodMsec = 5000;   //mSec between logging to serial port

static unsigned long    _ulNextReadLogMsec    =    0;
  static unsigned long  _ulReadLogPeriodMsec  =  500;   //mSec between reading and logging to DataMgr as sensor set #0

//unsigned long     ulNextHandleSensorsMsec   =    0;
//unsigned long     ulReadSensorsPeriodMsec   = 5000; //mSec between reading sensors for logging

static char             _sz100Char[101];

static const int8_t     _cButton_Pin1       = 12;
static const int8_t     _cButton_Pin2       = 13;
static const int8_t     _cButton_Pin3       = 14;
static const int8_t     _cButton_Pin4       = 15;

static const int8_t     _acButtonPins[5]    {0, _cButton_Pin1, _cButton_Pin2, _cButton_Pin3, _cButton_Pin4};

static const int8_t     _cI2C_SDA_Pin       = 26;
static const int8_t     _cI2C_SCL_Pin       = 27;

// I2C addresses, (3) temperature probes and a pressure gauge
static const int        _wI2C_Pressure      = 0x18;     //decimal  24
static const int        _wI2C_DegF1         = 0x67;     //decimal 103
static const int        _wI2C_DegF2         = 0x66;     //decimal 102
static const int        _wI2C_DegF3         = 0x60;     //decimal  96

static const int8_t     _cRGB_RedPin        = 0;
static const int8_t     _cRGB_GreenPin      = 2;
static const int8_t     _cRGB_BluePin       = 4;

static const int        _wNumSensors        = 3;
static const int        _wNumSensorSets     = 4;       //A car has 4 tires
static const int        _wNumButtons        = 4;       //Testing w/4 buttons, Green #1, Yellow #2, Red #3, Blue #4
static const int        _wLogSensorSetID    = 0;

static const int        _wOffsetUTC         = -7;       //In winter SLO is 8 time zones after Greenwich, in summer it's 7

extern int8_t           _acSPI_CS_Pins      [];
extern const uint8_t    _aucI2CAdresses     [];

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
//Last line
