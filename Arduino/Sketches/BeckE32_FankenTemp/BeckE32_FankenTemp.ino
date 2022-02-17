const String SketchName  = "BeckE32_FankenTemp.ino";
const String FileDate    = "Feb 17, 2022a";
#ifndef ESP8266
  #define ESP32
#endif

#include <BeckLogLib.h>
#include <BeckMiniLib.h>
//#include <SPI.h>
#include <Adafruit_GFX.h>
#ifdef ESP32
//#include <WROVER_KIT_LCD.h>
#endif
#include <max6675.h>
/*
//#include <esp_wp1.h>
//#include <esp_wp2.h>
//#include <Wire.h>
#include <EasyButton.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansOblique18pt7b.h>

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
*/

/*
#define min(X, Y)     (((X) < (Y)) ? (X) : (Y))
#define PAUSE_DELAY   delay(2000)
#define RADIX_10      10
#define DO_BUTTONS    false

static const int       sNormalMode           = 0;
static const int       sCalibMode            = 1;

static const int       sUp                   = 0;
static const int       sDown                 = 1;
static const boolean   bButtonPullUp         = true;

//Digital Pins
static const int       sUpButton             =  2;
static const int       sDownButton           =  4;
static const int       sI2C_SDA              = 26;
static const int       sI2C_SCL              = 27;

static const int       sMaxButtonPresses  = 10;

static const unsigned long    ulModeSwitchTime  = 1000;  //Minimum msecs between mode changes
static const unsigned long    ulModeWaitTime    = 2000;  //Minimum msecs before mode is on
static const unsigned long    ulReadTimeSpacing    = 2000;   //Gyro and ADC reads spaced by this.

//static const uint16_t  usBackgroundColor    = WROVER_BLACK;
static const UINT16    usBoostTop           = 90;
static const UINT16    usAccelMotorTop      = 135;
static const UINT16    usMotorLeft          = 130;
static const INT16     sPCF8591             = 0x48;  // I2C address of the PCF8591 A/D DAC
//End of the const's

static int sCurrentMode= sNormalMode;

//WROVER_KIT_LCD    RoverLCD;

#if DO_BUTTONS
//Create EasyButton objects to handle button presses.
EasyButton UpButton     (sUpButton,     NULL, CALL_NONE, bButtonPullUp);
EasyButton DownButton   (sDownButton,   NULL, CALL_NONE, bButtonPullUp);
//EasyButton SelectButton (sSelectButton, NULL, CALL_NONE, bButtonPullUp);
#endif  //DO_BUTTONS

//Number of unhandled presses, up to sMaxButtonPresses
static int              sButtonCount[]       = { 0, 0, 0};
static boolean          abButtonBeingHeld[]  = { false, false, false};
static unsigned long    ulNextModeTime       = 0;  //msec when a mode switch can take place
static unsigned long    ulModeReadyTime      = 0;  //msec when button presses can be handled
static unsigned long    ulNextReadTime       = 0;  //msec when the gyro will be read

//State of display items being changed and needing refresh.
static boolean     bButtonsChanged          = true;
static boolean     bModeChanged             = true;

static int         sLineCount= 0;     //Used in outputs to Serial Monitor for clarity.

static char       szTempBuffer[100];   //DOGS102 line is 17 chars with 6x8 normal font.
static char       sz100CharString[101];
*/


#ifdef ESP8266
// nodeMCU ESP8266
// https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/
static const byte      cSPI_MISO_Pin         = 12;
static const byte      cSPI_MOSI_Pin         = 13;
static const byte      cSPI_CLK_Pin          = 14;    //Pin 14, D5
static const byte      cSPIChipSelectPin     = 15;    //Pin 15, D8
#else
//ESP32
// https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
static const byte      cSPI_MISO_Pin         = 19;
static const byte      cSPI_MOSI_Pin         = 23;
static const byte      cSPI_CLK_Pin          = 18;
static const byte      cSPIChipSelectPin     =  5;
#endif

//MAX6675   Thermo1(cSCLK, cMOSI_CS, cMISO);
MAX6675   Thermo1(cSPI_CLK_Pin, cSPIChipSelectPin, cSPI_MISO_Pin);

void setup()   {
  Serial.begin(115200);
  Serial << endl << "setup(): Begin " << SketchName << ", " << FileDate << endl;

  //DisplayBegin();
  //bButtonsChanged= true;  //Make the display show up during debugging.
  Serial << "setup(): Done " << endl;
  return;
}  //setup


// The Arduino loop() method gets called over and over.
void loop() {
  double    dfDegF;
  dfDegF= Thermo1.readFahrenheit();
  Serial << "Loop(): Degrees F= " << dfDegF << endl;
  delay(1000);

  //CheckButtons();
 // DisplayUpdate();
  //HandleButtons();
  //CheckKeyboard();
  return;
}  //loop()


/*
void CheckKeyboard() {
  if (Serial.available()) {
    Serial <<" CheckKeyboard(): Character available, call Serial.read()" << endl;
    char cChar= Serial.read();
    int sChar= cChar;
    if (sChar != 13) {
      Serial <<" CheckKeyboard(): Character read= "<< cChar <<", "<< sChar << endl;
    }
    else {
      Serial <<" CheckKeyboard(): Character read= CR" << endl;
    }
    switch (cChar) {
      case 'r':
      case 'R':
        //ResetESP32();
        break;
      case 'u':
      case 'U':
        sButtonCount[sUp]++;
        break;
      case 'd':
      case 'D':
        sButtonCount[sDown]++;
        break;
      default:
        break;
    } //switch
  } //if(Serial.available()
  return;
}  //CheckKeyboard
*/
//Last line
