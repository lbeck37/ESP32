const char szSketchName[]  = "BeckE32_RoverGraphics.ino";
const char szFileDate[]    = "5/15/21a";
#include <BeckLogLib.h>
#include <BeckMiniLib.h>
#include <Adafruit_GFX.h>
#include <WROVER_KIT_LCD.h>
#include <Wire.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansOblique18pt7b.h>

#define min(X, Y)     (((X) < (Y)) ? (X) : (Y))
#define PAUSE_DELAY   delay(2000)
#define RADIX_10      10
#define DO_BUTTONS    true
#define USE_DOGS102   false

static const int       sNormalMode           = 0;
static const int       sCalibMode            = 1;
static const int       sUp                   = 0;
static const int       sDown                 = 1;
static const boolean   bButtonPullUp         = true;

//Digital Pins
static const int       sI2C_SDA              = 26;
static const int       sI2C_SCL              = 27;

static const uint16_t  usBackgroundColor    = WROVER_BLACK;
static const UINT16    usBoostTop           = 90;
static const UINT16    usAccelMotorTop      = 135;
static const UINT16    usMotorLeft          = 130;

static int sCurrentGear                   = 2;

static int sCurrentMode                   = sNormalMode;
static int sServoPosLast                  = 0;

WROVER_KIT_LCD    RoverLCD;

//Number of unhandled presses, up to sMaxButtonPresses
static int              sButtonCount[]       = { 0, 0, 0};
static boolean          abButtonBeingHeld[]  = { false, false, false};
static unsigned long    ulNextModeTime       = 0;  //msec when a mode switch can take place
static unsigned long    ulModeReadyTime      = 0;  //msec when button presses can be handled
static boolean     bButtonsChanged          = true;
static boolean     bGearChanged             = true;
static boolean     bServoChanged            = true;
static boolean     bModeChanged             = true;
static boolean     bGyroChanged             = true;
static boolean     bPitchChanged            = true;
static boolean     bBoostChanged            = true;
static boolean     bMotorChanged            = true;
static boolean     bMPHChanged              = true;

static int         sLineCount= 0;     //Used in outputs to Serial Monitor for clarity.

static char       szTempBuffer[100];   //DOGS102 line is 17 chars with 6x8 normal font.
static char       sz100CharString[101];

const double      dGConvert         = 16383.0;  // 12/06/17 I'm seeing values up to -16,580 with a vertical orientation, 0x3FFF = 16,383
const double      dRadsToDeg        = 180.0/PI;
double            adGvalueXYZ[3];
double            dRollDeg;
double            dPitchDeg;
double            dPitchPercent   = 0.0;
double            dBoostWatts     = 0.0;
double            dMPH            = 0.0;
double            dMotorVolts     = 0.0;
double            dMotorAmps      = 0.0;
double            dMotorWatts     = 0.0;

void(* ResetESP32)(void)= 0;        //Hopefully system crashes and reset when this is called.

void setup()   {
  Serial.begin(115200);
  Serial << endl << "setup(): Begin " << szSketchName << ", " << szFileDate << endl;

  Serial << "setup(): Call Wire.begin(sI2C_SDA, sI2C_SCL) " << sI2C_SDA << ", " << sI2C_SCL << endl;
  Wire.begin(sI2C_SDA, sI2C_SCL);
  DisplayBegin();
  bButtonsChanged= true;  //Make the display show up during debugging.
  return;
}  //setup

void loop() {
  DisplayUpdate();
  return;
}  //loop()

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
   return;
}  //ShowSplash

void DisplayUpdate(void) {
 if (bScreenChanged()) {
    DisplayCurrentGear();
    DisplayServoPos();
    //DisplayGs();
    DisplayPitch();
    DisplayBoost();
    DisplayMotor();
    DisplayMPH();
    DisplayLowerBanner();
    ClearChangeFlags();
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
   bool bChanged= bGyroChanged  || bPitchChanged || bGearChanged  || bButtonsChanged || bServoChanged || bModeChanged ||
                  bBoostChanged || bMotorChanged || bMPHChanged;
   return bChanged;
}  //bScreenChanged

void ClearChangeFlags(){
  bGyroChanged= bPitchChanged= bGearChanged  = bButtonsChanged= bServoChanged= bModeChanged=
                bBoostChanged= bMotorChanged = bMPHChanged= false;
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

void DisplayPitch() {
  UINT16          usCharWidth     = 25;
  UINT16          usCursorX       = 0;
  UINT16          usCursorY       = 30;   //GFX fonts Y is bottom
  UINT8           ucSize          = 1;
  UINT16          usColor         = WROVER_WHITE;
  UINT16          usRightInset    = 2;  //Number of pixels to right of justified text
  INT16           sClearLeftX     = usCursorX;
  INT16           sClearTopY      = 0;
  UINT16          usClearWidth    = 120;
  UINT16          usClearHeight   = 35;
  static UINT16   usLastClearWidth= 0;

  //Serial << "DisplayPitch(): Begin" << endl;
  if(bPitchChanged) {
    sprintf(szTempBuffer, "%+4.1f%%", dPitchPercent);
    //sprintf(szTempBuffer, "%+4.1f %+03.0f", dPitchPercent, dPitchDeg);
    //Calculate width to clear based on number of characters + 2, use that unless last width was bigger
    usClearWidth= (strlen(szTempBuffer) + 2) * usCharWidth;
    usClearWidth= std::max(usClearWidth, usLastClearWidth);
    usLastClearWidth= usClearWidth;
    ClearTextBackground(sClearLeftX, sClearTopY, usClearWidth, usClearHeight);
    DisplayLine(FreeMonoBold24pt7b, usColor, usCursorX, usCursorY, usClearWidth, usClearHeight, szTempBuffer, false, ucSize);

    usCursorX= 50;
    usCursorY += 20;
    sprintf(szTempBuffer, "Pitch");
    DisplayLine(FreeSans9pt7b, usColor, usCursorX, usCursorY, usClearWidth, usClearHeight, szTempBuffer, false);
  } //if(bPitchChanged)
  return;
}  //DisplayPitch

void DisplayBoost() {
  UINT16          usCharWidth     = 25;
  UINT16          usCursorX       = 0;
  UINT16          usCursorY       = usBoostTop;   //GFX fonts Y is bottom 90
  UINT8           ucSize          = 1;
  UINT16          usColor         = WROVER_WHITE;
  //UINT16          usRightInset    = 2;  //Number of pixels to right of justified text
  INT16           sClearLeftX     = usCursorX;
  INT16           sClearTopY      = usCursorY - 32;
  UINT16          usClearWidth    = 120;
  UINT16          usClearHeight   = 40;
  static UINT16   usLastClearWidth= 0;

  //Serial << "DisplayBoost(): Begin" << endl;
  if(bBoostChanged) {
    sprintf(szTempBuffer, "%3.0f W", dBoostWatts);
    //Calculate width to clear based on number of characters + 2, use that unless last width was bigger
    usClearWidth= (strlen(szTempBuffer) + 2) * usCharWidth;
    usClearWidth= std::max(usClearWidth, usLastClearWidth);
    usLastClearWidth= usClearWidth;
    ClearTextBackground(sClearLeftX, sClearTopY, usClearWidth, usClearHeight);
    DisplayLine(FreeMonoBold24pt7b, usColor, usCursorX, usCursorY, usClearWidth, usClearHeight, szTempBuffer, false, ucSize);

    usCursorX= 50;
    usCursorY += 20;
    sprintf(szTempBuffer, "Boost");
    DisplayLine(FreeSans9pt7b, usColor, usCursorX, usCursorY, usClearWidth, usClearHeight, szTempBuffer, false);
  } //if(bBoostChanged)
  return;
}  //DisplayBoost

void DisplayCurrentGear() {
  UINT16          usCharWidth     = 120;
  UINT16          usCursorX       = 200;
  UINT16          usCursorY       = 62;   //GFX fonts Y is bottom
  UINT8           ucSize          = 2;
  //UINT16          usRightInset    = 2;  //Number of pixels to right of justified text
  INT16           sClearLeftX     = usCursorX;
  INT16           sClearTopY      = 0;
  UINT16          usClearWidth    = 120;
  UINT16          usClearHeight   = usCursorY + 10;
  UINT16          usColor         = WROVER_WHITE;

  //Serial << "DisplayCurrentGear(): Begin" << endl;
  if(bGearChanged) {
    if (sCurrentMode == sNormalMode) {
      sprintf(szTempBuffer, "%2d", sCurrentGear);
      usClearWidth= strlen(szTempBuffer) * usCharWidth;
      ClearTextBackground(sClearLeftX, sClearTopY, usClearWidth, usClearHeight);
      DisplayLine(FreeMonoBold24pt7b, usColor, usCursorX, usCursorY, usClearWidth, usClearHeight, szTempBuffer, false, ucSize);
    }  //if (sCurrentMode..
    else {
      sprintf(szTempBuffer, "%2d", 0);
      usClearWidth= strlen(szTempBuffer) * usCharWidth;
      ClearTextBackground(sClearLeftX, sClearTopY, usClearWidth, usClearHeight);
      DisplayLine(FreeMonoBold24pt7b, usColor, usCursorX, usCursorY, usClearWidth, usClearHeight, szTempBuffer, false, ucSize);
    }  //if (sCurrentMode..else

    usCursorX= 255;
    usCursorY += 20;
    sprintf(szTempBuffer, "Gear");
    DisplayLine(FreeSans9pt7b, usColor, usCursorX, usCursorY, usClearWidth, usClearHeight, szTempBuffer, false);
  } //if(bGearChanged)
  return;
}  //DisplayCurrentGear

void DisplayServoPos() {
  const UINT16    usCharWidth   = 17;
  const UINT16    usLineHeight  = 20;
  UINT16          usCursorX     = 252;
  UINT16          usCursorY     = 115;
  UINT16          usClearWidth  = 70;
  UINT16          usClearHeight = 22;
  UINT16          usColor       = WROVER_WHITE;

  //Serial << "DisplayServoPos(): Begin" << endl;
  if(bServoChanged) {
    sprintf(szTempBuffer, "%3d", sServoPosLast);
    usClearWidth= strlen(szTempBuffer) * usCharWidth;
    DisplayLine(FreeMonoBold12pt7b, usColor, usCursorX + 15, usCursorY, usClearWidth, usClearHeight, szTempBuffer);

    sprintf(szTempBuffer, "Servo");
    usClearWidth= strlen(szTempBuffer) * usCharWidth;
    usCursorY += usLineHeight;
    DisplayLine(FreeSans9pt7b, usColor, usCursorX, usCursorY, usClearWidth, usClearHeight, szTempBuffer, false);
  } //if(bServoChanged)
  return;
}  //DisplayServoPos

void DisplayMPH() {
  const UINT16    usCharWidth   = 17;
  const UINT16    usLineHeight  = 20;
  UINT16          usCursorX     = 252;
  UINT16          usCursorY     = 175;
  UINT16          usClearWidth  = 70;
  UINT16          usClearHeight = 22;
  UINT16          usColor       = WROVER_YELLOW;

  //Serial << "DisplayMPH(): Begin" << endl;
  if(bMPHChanged) {
    sprintf(szTempBuffer, "%4.1f", dMPH);
    usClearWidth= strlen(szTempBuffer) * usCharWidth;
    DisplayLine(FreeMonoBold12pt7b, usColor, usCursorX, usCursorY, usClearWidth, usClearHeight, szTempBuffer);

    sprintf(szTempBuffer, "MPH");
    usClearWidth= strlen(szTempBuffer) * usCharWidth;
    usCursorY += usLineHeight;
    DisplayLine(FreeSans9pt7b, usColor, usCursorX, usCursorY, usClearWidth, usClearHeight, szTempBuffer, false);
  } //if(bMPHChanged)
  return;
}  //DisplayMPH

void DisplayMotor() {
  const UINT16    usCharWidth   = 17;
  const UINT16    usLineHeight  = 20;
  UINT16          usCursorX     = usMotorLeft;
  UINT16          usCursorY     = usAccelMotorTop;
  UINT16          usClearWidth;
  UINT16          usClearHeight = 22;

  //Serial << "DisplayMotor(): Begin" << endl;
  sprintf(szTempBuffer, "Motor");
  if(bMotorChanged) {
    usClearWidth= strlen(szTempBuffer) * usCharWidth;
    DisplayLine(FreeMonoBold12pt7b, WROVER_YELLOW, usCursorX, usCursorY, usClearWidth, usClearHeight, szTempBuffer, false);

    sprintf(szTempBuffer, "V  %4.1f", dMotorVolts);
    usClearWidth= strlen(szTempBuffer) * usCharWidth;
    usCursorY += usLineHeight;
    DisplayLine(FreeMonoBold12pt7b, WROVER_YELLOW, usCursorX, usCursorY, usClearWidth, usClearHeight, szTempBuffer);

    sprintf(szTempBuffer, "A  %4.1f", dMotorAmps);
    usClearWidth= strlen(szTempBuffer) * usCharWidth;
    usCursorY += usLineHeight;
    DisplayLine(FreeMonoBold12pt7b, WROVER_YELLOW, usCursorX, usCursorY, usClearWidth, usClearHeight, szTempBuffer);

    //sprintf(szTempBuffer, "W %3.0f", dMotorWatts);
    sprintf(szTempBuffer, "W %4.1f", dMotorWatts);
    usClearWidth= strlen(szTempBuffer) * usCharWidth;
    usCursorY += usLineHeight;
    DisplayLine(FreeMonoBold12pt7b, WROVER_YELLOW, usCursorX, usCursorY, usClearWidth, usClearHeight, szTempBuffer);
  } //if(bMotorChanged)
  return;
}  //DisplayMotor

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
//Last line
