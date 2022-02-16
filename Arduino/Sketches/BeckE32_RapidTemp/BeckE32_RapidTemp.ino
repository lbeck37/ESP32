const String SketchName  = "BeckE32_RapidTemp.ino";
const String FileDate    = "Feb 16, 2022a";
#ifndef ESP8266
  #define ESP32
#endif

#include <BeckLogLib.h>
#include <BeckMiniLib.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#ifdef ESP32
//#include <WROVER_KIT_LCD.h>
#endif
//#include <esp_wp1.h>
//#include <esp_wp2.h>
//#include <Wire.h>
#include <EasyButton.h>
#include <max6675.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansOblique18pt7b.h>

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

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

//void(* ResetESP32)(void)= 0;        //Hopefully system crashes and reset when this is called.

//Prototype: MAX6675(int8_t SCLK, int8_t CS, int8_t MISO);
/*
INT8    cMISO     = 19;
INT8    cMOSI_CS  = 23;
INT8    cSCLK     =  5;
*/

/*
//Try number 2
//static const byte      cSPICmdDataPin        = 16;    //Pin 16, D0
static const byte      cSPI_MOSI_Pin         = 13;    //Pin 13, D7
static const byte      cSPI_CLK_Pin          = 14;    //Pin 14, D5
static const byte      cSPIChipSelectPin     = 15;    //Pin 15, D8
static const byte      cSPI_MISO_Pin         = 16;    //Pin 16, D0

//Try number 3
static const byte      cSPI_MOSI_Pin         = 23;
static const byte      cSPI_CLK_Pin          = 18;    //Pin 14, D5
static const byte      cSPIChipSelectPin     = 5;    //Pin 15, D8
static const byte      cSPI_MISO_Pin         = 19;
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
  bButtonsChanged= true;  //Make the display show up during debugging.
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
  CheckKeyboard();
  return;
}  //loop()


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


/*
void DisplayBegin() {
  Serial << "DisplayBegin(): Call RoverLCD.begin()" << endl;
  RoverLCD.begin();
  RoverLCD.setRotation(1);
  DisplayClear();
  return;
}  //DisplayBegin


void ShowStartScreen(void) {
  Serial << "ShowStartScreen(): Call DisplayBegin()" << endl;
  DisplayBegin();
  Serial << "ShowStartScreen(): Call sShowSplash()" << endl;
  ShowSplash();
  delay(3000);
  DisplayClear();
  return;
}  //ShowStartScreen


void ShowSplash(void) {
   DisplayClear();

   //2 lines of big font takes lines 0-3
   RoverLCD.setTextColor(WROVER_YELLOW);
   sDisplayText(0, 0, sFontSize3, (char *)"PowerShift");
   RoverLCD.setTextColor(WROVER_GREEN);
   sDisplayText(2, 0, sFontSize3, (char *)"  by ShiftE");

   //2 lines in normal font
   RoverLCD.setTextColor(WROVER_RED);
   sDisplayText(5, 0, sFontSize2, (char *)"\nAlways ride safe!");
   //sDisplayText(7, 0, sFontNormal, (char *)"**Larry & Candy**");
   sDisplayText(7, 0, sFontSize2, (char *)"October 19, 2017J ");
   //sDisplayText(7, 0, sFontSize2, (char *)FileDate);

   return;
}  //ShowSplash


void DisplayUpdate(void) {
 if (bScreenChanged()) {
   DisplayButtons();
   } //if(bScreenChanged())
   return;
}  //DisplayUpdate


void DisplayClear() {
  FillScreen(usBackgroundColor);
  return;
}  //DisplayClear


void FillScreen(UINT16 usColor) {
  RoverLCD.fillScreen(usColor);
  return;
}  //FillScreen


bool bScreenChanged() {
   //Determine if something being displayed has changed & clear the flags.
  bool bChanged=  bButtonsChanged;
   return bChanged;
}  //bScreenChanged


void ClearChangeFlags(){
  bButtonsChanged= false;
  return;
} //ClearChangeFlags


void DisplayText(UINT16 usCursorX, UINT16 usCursorY, char *pcText,
                 const GFXfont *pFont, UINT8 ucSize, UINT16 usColor) {
  //240x320 3.2", 10 lines => 24 pixels/line
  RoverLCD.setFont(pFont);
  RoverLCD.setTextColor(usColor);
  RoverLCD.setTextSize(ucSize);
  RoverLCD.setTextWrap(false);
  RoverLCD.setCursor(usCursorX, usCursorY);
  RoverLCD.print(pcText);
  return;
}  //DisplayText


void ClearTextBackground(INT16 sUpperLeftX, INT16 sUpperLeftY, UINT16 usWidth, UINT16 usHeight){
  RoverLCD.fillRect(sUpperLeftX, sUpperLeftY, usWidth, usHeight, usBackgroundColor);
  return;
} //ClearTextBackground


void DisplayLine(const GFXfont stFont, UINT16 usColor, UINT16 usCursorX, UINT16 usCursorY, UINT16 usClearWidth, UINT16 usClearHeight,
                 char szText[], bool bClearText= true, UINT8 ucSize= 1) {
  INT16           sClearXstart    = usCursorX - 10;
  INT16           sClearYstart    = usCursorY - 18;

  if(bClearText){
    ClearTextBackground(sClearXstart, sClearYstart, usClearWidth, usClearHeight);
  }
  DisplayText( usCursorX, usCursorY, szText, &stFont, ucSize, usColor);
  return;
} //DisplayLine


void DisplayButtons() {
  const GFXfont   *pFont          = &FreeSans9pt7b;
  UINT16          usCursorX       = 260;
  UINT16          usCursorY       = 160;
  UINT8           ucSize          = 1;
  UINT16          usColor         = WROVER_ORANGE;
  bool            bRightJustify   = false;

  //Show 2 lines at right bottom for U d, D d
  strcpy(szTempBuffer, "U ");
  itoa(sButtonCount[sUp]  ,sz100CharString  , 10);
  strcat(szTempBuffer, sz100CharString);
  DisplayText( usCursorX, usCursorY, szTempBuffer, pFont, ucSize, usColor);

  strcpy(szTempBuffer, "D ");
  itoa(sButtonCount[sDown]  ,sz100CharString  , 10);
  strcat(szTempBuffer, sz100CharString);
  usCursorY= usCursorY + 20;
  DisplayText( usCursorX, usCursorY, szTempBuffer, pFont, ucSize, usColor);
  return;
}  //DisplayButtons


void DisplayLowerBanner(){
  const GFXfont   *pFont          = &FreeSansOblique18pt7b;
  UINT16          usCursorX       = 7;
  UINT16          usCursorY       = 232;    //Was 72
  UINT8           ucSize          = 1;
  UINT16          usColor         = WROVER_CYAN;
  bool            bRightJustify   = false;

  DisplayText( usCursorX, usCursorY, "PowerShift Coach", pFont, ucSize, usColor);
  return;
} //DisplayLowerBanner


void HandleButtons(void) {
  if (!bHandleBothHeld()) {
     if (millis() > ulModeReadyTime) {
       switch(sCurrentMode) {
         case sNormalMode:
            //HandleNormalMode();
            break;   //sNormalMode
         case sCalibMode:
            //HandleCalibMode();
            break;   //sCalibMode
         default:
            Serial << "HandleButtons(): Unexpected switch value." << endl;
            break;
        } //switch
     }   //if(millis()...
   }  //if(!bHandleBothHeld())
   return;
}  //HandleButtons


boolean bHandleBothHeld(void) {
   if (abButtonBeingHeld[sUp] &&  abButtonBeingHeld[sDown]) {
      if (millis() > ulNextModeTime) {
         Serial << sLineCount++ << " bHandleBothHeld(): Both buttons are being held." << endl;
         //Clear the button counts;
         sButtonCount[sUp]  = 0;
         sButtonCount[sDown]= 0;
         switch (sCurrentMode) {
            case sNormalMode:
               sCurrentMode= sCalibMode;
               bModeChanged= true;
               Serial << sLineCount++
                      << " bHandleBothHeld(): Switch from Normal to Calib mode." << endl;
               break;
            case sCalibMode:
               sCurrentMode= sNormalMode;
               bModeChanged= true;
               Serial << sLineCount++
                      << " bHandleBothHeld(): Switch from Calib to Normal mode." << endl;
               break;
            default:
               Serial << sLineCount++
                      << " bHandleBothHeld(): Bad switch :" << sCurrentMode << endl;
               break;
         }  //switch
         //Create the guard times between mode switches or button handling
         ulNextModeTime= millis() + ulModeSwitchTime;
         ulModeReadyTime= millis() + ulModeWaitTime;
      }  //if(millis()...
      return true;
   }    //if((sButtonCount[sUp]==sHoldCode)...
   else {
      return false;
   }  //if((sButtonCount[sUp]==sHoldCode)...
}  //bHandleBothHeld


void HandleNormalMode(void) {
  return;
}  //HandleNormalMode


void HandleCalibMode(void) {
 return;
}  //HandleCalibMode
*/


/*
void CheckButtons(void) {
Algorithm to determine when a button has been pressed or held.
 * Use IsRelease() to indicate the button has been pressed
 * Use IsHold() to indicate the button has been held down
 * States (Initial idea, not sure how close method is to this 4/25/15)
 *    0 - Button open
 *    1 - Button pressed, IsPushed() returned true once
 *          Moves State to 2 when InPush() first returns true
 *    2 - InPush() returning true, button is down
 *    3 - IsRelease() returned true, button has been released
 *          Moves State to 0
 *    4 - IsHold() returned true, button  held past threshhold
 *          Moves State to 0 when IsRelease returns true.
 * sUpButtonCount will be:
 *    0   Nothing to be done
 *   99   Button was held and not yet released
 *   1-10 Number of button presses not yet handled, max 10

  //static int   sLocalButtonState[]  = {0, 0};
  boolean      bReturn              = false;
  int          sButton;

#if DO_BUTTONS
  UpButton.update();
  DownButton.update();
  //SelectButton.update();

   //Run through the buttons, use short-circuiting to select
   for (sButton= sUp; sButton <= sDown; sButton++) {
      //Check for IsRelease for all buttons.
      if ( ((sButton == sUp)   && UpButton.IsRelease  ()) ||
      ((sButton == sDown) && DownButton.IsRelease()) ) {
         Serial << sLineCount++ << " sCheckButtons(): Button " << sButton
                << " was released." << endl;
         //Check to see if button is being held
         //if (sLocalButtonState[sButton] != sButtonHeld) {
         if ( !abButtonBeingHeld[sButton]) {
            if (sButtonCount[sButton] < sMaxButtonPresses) {
               //Increment the count of button presses to be handled.
               //Serial << sLineCount++ << " sCheckButtons(): Button " << sButton << " count incremented." << endl;
               sButtonCount[sButton]++;
               bButtonsChanged= true;
            } //if(sLocalUpButtonState!=sButtonHeld)
         }    //if(sLocalButtonState!=...
         else {
            //The button was being held down, update the state variable..
            Serial << sLineCount++ << " sCheckButtons(): Button " << sButton
                   << " done being held." << endl;
            //sLocalButtonState[sButton]= sButtonOpen;
            abButtonBeingHeld[sButton]= false;
         } //if(sLocalUpButtonState!=sButtonHeld)else
         bReturn= true;
      }   //if(((sButton==sUp)&&...

      //Check IsHold for up and down buttons.
      if (!bReturn &&
      (((sButton == sUp)   && UpButton.IsHold  ()) ||
       ((sButton == sDown) && DownButton.IsHold()) )) {
         Serial << sLineCount++ << " sCheckButtons(): Button " << sButton
                << " being held." << endl;
         //Set state to indicate in hold.
         //sLocalButtonState[sButton]= sButtonHeld;
         //sButtonCount[sButton]= sHoldCode;
         abButtonBeingHeld[sButton] = true;
         sButtonCount[sButton]      = 0;  //Clear the count
         bButtonsChanged= true;
      }   //if(!bReturn&&UpButton.IsHold()
      bReturn= false;
   } //for (sButton= sUp...
#endif  //DO_BUTTONS
  return;
}  //CheckButtons


void TestButtonPins() {
  int sUpButtonLocal    = 2;
  int sDownButtonLocal  = 4;
  Serial << "SetupPins(): Call pinMode(" << sUpButtonLocal << ", INPUT_PULLUP) for Up" << endl;
  pinMode(sUpButtonLocal, INPUT_PULLUP);

  Serial << "SetupPins(): Call pinMode(" << sDownButtonLocal << ", INPUT_PULLUP) for Down" << endl;
  pinMode(sDownButtonLocal, INPUT_PULLUP);

  int sValueUp;
  int sValueDown;
  for (int i= 0; i<10; i++){
    Serial << "SetupPins(): Read buttons, Try= " << i << endl;
    sValueUp= digitalRead(sUpButtonLocal);
    sValueDown= digitalRead(sDownButtonLocal);
    Serial << "SetupPins(): Read buttons, Pin "
        << sUpButtonLocal << "= " << sValueUp << ", Pin " << sDownButtonLocal <<  "= " << sValueDown << endl;
    delay(1000);
  } //for(inti= 0;...
  return;
}  //TestButtonPins
*/
//Last line
