const char szSketchName[]  = "BeckE32_TireTemp.ino";
const char szFileDate[]    = "3/10/22j";

#include <BeckE32_Defines.h>
#if DO_OTA
  #include <BeckE32_OTALib.h>
#endif
#include <BeckTireTempDataClass.h>
#include <BeckI2cClass.h>
#include <BeckLogLib.h>
#include <BeckMiniLib.h>
#include <BeckProbeSetClass.h>

#if DO_ROVER
  #include <WROVER_KIT_LCD.h>
#endif

#include <Adafruit_GFX.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansOblique18pt7b.h>
#include <EasyButton.h>
#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <Streaming.h>

#include <ctime>
#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

const char* szWebHostName = "TireTemp";

#define min(X, Y)       (((X) < (Y)) ? (X) : (Y))
const UINT16       usTopText_CursorY              =  35;

UINT16            usTextSpacing                  = 20;
UINT16            usDegF_CursorY                 = usTopText_CursorY;

char              sz100CharString[101];

unsigned long     ulNextDisplayMsec         =    0;
unsigned long     ulDisplayPeriodMsec       = 2000; //mSec between output to display

unsigned long     ulNextHandleProbesMsec    =    0;
unsigned long     ulHandleProbesPeriodMsec  = 5000; //mSec between handling probes

const char*       szRouterName              = "Aspot24b";
const char*       szRouterPW                = "Qazqaz11";

#if DO_ROVER
  WROVER_KIT_LCD     RoverLCD;
  const ColorType    BackgroundColor         = WROVER_BLACK;
#endif

//Protos
void  setup                 (void);
void  loop                  (void);
void  onPressed1            (void);
void  onPressed2            (void);
void  onPressed3            (void);
void  onPressed4            (void);
void  SetupNTP              (void);
void  HandleNTP             (void);
void  PrintCurrentTime      (void);
void  PrintSecondsSinceY2K  (void);
#if DO_ROVER
  void  DisplayBegin        (void);
  void  DisplayClear        (void);
  void  FillScreen          (UINT16 usColor);
  void  DisplayUpdate       (void);
  void  DisplayTemperature  (void);
  void  DisplayLowerBanner  (void);
  void  DisplayText         (UINT16 usCursorX, UINT16 usCursorY, char *pcText,
                             const GFXfont *pFont, UINT8 ucSize, UINT16 usColor);
  void  ClearTextBackground (INT16 sUpperLeftX, INT16 sUpperLeftY, UINT16 usWidth, UINT16 usHeight);
#endif

  //Setup buttons, Defaults: 35msec debounce, Pullup enabled, Returns true on button press
EasyButton TireButton1(_cButton_Pin1);
EasyButton TireButton2(_cButton_Pin2);
EasyButton TireButton3(_cButton_Pin3);
EasyButton TireButton4(_cButton_Pin4);

BeckProbeSetClass _oProbeSet;

/*
BeckProbeSetClass _aoProbeSet[4];
_aoProbeSet[1]= BeckProbeSetClass(LeftFrontTire);
*/
//BeckProbeSetClass _aoProbeSet[] {BeckProbeSetClass(LeftFrontTire), BeckProbeSetClass(RightFrontTire)};

// Define NTP Client to get time
WiFiUDP     ntpUDP;
NTPClient   _oNTPClient(ntpUDP);

uint32_t    _uwEpochTime;


void setup(){
  Serial.begin(115200);
  Serial << "\n" << LOG0 << "setup(): Begin " << szSketchName << ", " << szFileDate << "\n";

#if DO_ROVER
  Serial << LOG0 << "setup(): Call DisplayBegin()\n";
  DisplayBegin();
#endif
  //FlashRGB_LED();

  // Start WiFi and wait for connection to the network
  WiFi.begin(szRouterName, szRouterPW);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //The following cout statement caused the WiFi.localIP() to not print 192.168.0.197 it was a single integer
  //cout << "\nsetup(): Connected to " << szRouterName << ", IP address to connect to is " << WiFi.localIP() << "\n" << std::endl;
  Serial << "\nsetup(): Connected to " << szRouterName << ", IP address to connect to is " << WiFi.localIP() << "\n";

#if DO_OTA
  Serial << "setup(): Call SetupWebServer(" << szWebHostName << ")\n";
  SetupWebserver(szWebHostName);
#endif

  Serial << LOG0 << "setup(): Call SetupNTP()\n";
  SetupNTP();

  Serial << LOG0 << "setup(): Call PrintCurrentTime()\n";
  PrintCurrentTime();

  //Setup I2C bus to be able to scan for devices
  //_oBeckI2C.Setup();
  //_oBeckI2C.ScanForDevices();

  Serial << LOG0 << "setup(): Call BuildProbes()\n";
  _oProbeSet.BuildProbes();

  Serial << "setup(): Call TireButton1/2/3/4.begin()\n";
  TireButton1.begin();
  TireButton2.begin();
  TireButton3.begin();
  TireButton4.begin();

  Serial << "setup(): Setup Callback, call TireButton1/2/3/4.onPressed(onPressed1/2/3/4)\n";
  TireButton1.onPressed(onPressed1);
  TireButton2.onPressed(onPressed2);
  TireButton3.onPressed(onPressed3);
  TireButton4.onPressed(onPressed4);

  Serial << LOG0 << "setup(): return\n";
  return;
}  //setup


void loop() {
  TireButton1.read();   //This has to get called for onPressed() to get called back
  TireButton2.read();   //This has to get called for onPressed() to get called back
  TireButton3.read();   //This has to get called for onPressed() to get called back
  TireButton4.read();   //This has to get called for onPressed() to get called back
  if (millis() > ulNextHandleProbesMsec){
    ulNextHandleProbesMsec= millis() + ulHandleProbesPeriodMsec;
    HandleNTP();
    _uwEpochTime= _oNTPClient.getEpochTime();
    Serial << LOG0 << "loop(): Call _oProbeSet.Handle(_uwEpochTime)\n";
    _oProbeSet.Handle(_uwEpochTime);
    Serial << LOG0 << "loop(): Call _oProbeSet.PrintProbeSetData()\n";
    _oProbeSet.PrintProbeSetData();
    //unsigned long ulCurrentEpochSeconds= _oNTPClient.getEpochTime();
    //_oBeckI2C.ScanForDevices();
  } //if (millis()>ulNextDisplayMsec)
#if DO_ROVER
  DisplayUpdate();
#endif
#if DO_OTA
  HandleOTAWebserver();
#endif
  return;
}  //loop()


void onPressed1(){
  Serial << "onPressed1(): You pressed Button 1.\n";
  return;
} //onPressed1


void onPressed2(){
  Serial << "onPressed2(): You pressed Button 2.\n";
  return;
} //onPressed2


void onPressed3(){
  Serial << "onPressed3(): You pressed Button 3.\n";
  return;
} //onPressed3


void onPressed4(){
  Serial << "onPressed4(): You pressed Button 4.\n";
  return;
} //onPressed4


void SetupNTP(){
// Initialize a NTPClient to get time
  Serial << "SetupNTP(): Call oNTPClient.begin()\n";
  _oNTPClient.begin();

  Serial << "SetupNTP(): Call oNTPClient.setTimeOffset() with an offset of " << _wOffsetUTC << " hours\n";
  _oNTPClient.setTimeOffset(_wOffsetUTC * 3600);

  return;
} //SetupNTP


void HandleNTP(void){
  // https://randomnerdtutorials.com/esp32-ntp-client-date-time-arduino-ide/
  // Variables to save date and time
  String formattedDate;
  String dayStamp;
  String timeStamp;

  Serial << "HandleNTP(): Enter while loop with oNTPClient.update and oNTPClient.forceUpdate()\n";
  while(!_oNTPClient.update()) {
    _oNTPClient.forceUpdate();
  } //while
  Serial << "HandleNTP(): Done with while loop\n";

  // The formattedDate comes with the following format:
  // 2018-05-28T16:00:13Z
  // We need to extract date and time
  formattedDate = _oNTPClient.getFormattedDate();
  Serial.println(formattedDate);

  // Extract date
  int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);
  Serial.print("DATE: ");
  Serial.println(dayStamp);
  // Extract time
  timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-1);
  Serial.print("HOUR: ");
  Serial.println(timeStamp);
  return;
}   //HandleNTP


void PrintCurrentTime(void){
  //Print the current time (Pro C++ pg 801)
  //Serial << "PrintCurrentTime(): Get a time_point for the current time\n";
  system_clock::time_point  oCurentTime{system_clock::now()};

  //Serial << "PrintCurrentTime(): Convert the time_point to a time_t\n";
  time_t  oCurrentTime_time_t{system_clock::to_time_t(oCurentTime)};

  //Convert to local time
  //Serial << "PrintCurrentTime(): Convert to local time\n";
  tm*   pLocalTime{localtime(&oCurrentTime_time_t)};

  //Print the current time
  //Serial << "PrintCurrentTime(): Stream put_time() to cout\n";
  cout << "PrintCurrentTime(),(via cout): Current time is " << put_time(pLocalTime, "%H:%M:%S") << "\n";
  return;
}   //PrintCurrentTime


void PrintSecondsSinceY2K(void)
{
  time_t timer;
  struct tm y2k = {0};
  double seconds;

  y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
  y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

  time(&timer);  /* get current time; same as: timer = time(NULL)  */

  seconds = difftime(timer,mktime(&y2k));

  //printf ("%.f seconds since January 1, 2000 in the current timezone", seconds);

  Serial << "PrintSecondsSinceY2K(): " << seconds << "seconds since January 1, 2000\n";
  return;
} //PrintSecondsSinceY2K


#if DO_ROVER
void DisplayBegin() {
  Serial << LOG0 << "DisplayBegin(): Call RoverLCD.begin()\n";
  RoverLCD.begin();
  RoverLCD.setRotation(1);
  DisplayClear();
  return;
}  //DisplayBegin


void DisplayClear() {
  FillScreen(BackgroundColor);
  return;
}  //DisplayClear


void FillScreen(UINT16 usColor) {
#if DO_ROVER
  RoverLCD.fillScreen(usColor);
#else
#endif
  return;
}  //FillScreen


void DisplayUpdate(void) {
if (millis() > ulNextDisplayMsec){
  ulNextDisplayMsec= millis() + ulDisplayPeriodMsec;
  DisplayTemperature();
} //if (millis()>ulNextDisplayMsec)
DisplayLowerBanner();
return;
}  //DisplayUpdate


void DisplayTemperature() {
  UINT16          usTextCursorX   =  100;
  UINT16          usTextCursorY   =  15;  //Zero for font is lower-left
  UINT16          usTempCursorX   =   0;
  UINT16          usTempCursorY   = 100;
  UINT8           ucSize          =   1;
  ColorType       usColor         = WROVER_WHITE;
  float           fDegFValue      = 0.0;

  //if(true || TireTempData.bDegFChanged()) {
  if(true) {
    //Erase the currently displayed value by overwriting it with the background color
/*
    float fLastDegFValue= TireTempData.GetLastDegF_Value();
    sprintf(sz100CharString, "%6.1f", fLastDegFValue);
*/
    sprintf(sz100CharString, "%6.1f", 37.37);
    DisplayText( usTempCursorX, usTempCursorY, sz100CharString, &FreeMonoBold24pt7b, ucSize, BackgroundColor);

    //Display the new value
/*
    fDegFValue= TireTempData.GetDegF_Value();
    sprintf(sz100CharString, "%6.1f", fDegFValue);
    DisplayText( usTempCursorX, usTempCursorY, sz100CharString, &FreeMonoBold24pt7b, ucSize, usColor);
*/

    sprintf(sz100CharString, "Front Tires");
    DisplayText( usTextCursorX, usTextCursorY, sz100CharString, &FreeSans9pt7b, ucSize, usColor);

    usTextCursorX  =  0;
    usTextCursorY += 20;
    sprintf(sz100CharString, "179  167  159    209  104  178");
    DisplayText( usTextCursorX, usTextCursorY, sz100CharString, &FreeSans9pt7b, ucSize, usColor);

    //Set the last value to be the displayed value
    //TireTempData.SetLastDegF_Value(fDegFValue);
  } //if(TireTempData.bDegFChanged())
  return;
}  //DisplayTemperature


void DisplayLowerBanner(){
  const GFXfont   *pFont          = &FreeSansOblique18pt7b;
  UINT16          usCursorX       = 45;
  UINT16          usCursorY       = 232;    //Was 72
  UINT8           ucSize          = 1;
  ColorType       usColor         = WROVER_CYAN;

  DisplayText( usCursorX, usCursorY, "Tire Degrees F", pFont, ucSize, usColor);
  return;
} //DisplayLowerBanner


void DisplayText(UINT16 usCursorX, UINT16 usCursorY, char *pcText,
                 const GFXfont *pFont, UINT8 ucSize, UINT16 usColor) {
  //240x320 3.2", 10 lines => 24 pixels/line
#if DO_ROVER
  RoverLCD.setFont(pFont);
  RoverLCD.setTextColor(usColor);
  RoverLCD.setTextSize(ucSize);
  RoverLCD.setTextWrap(false);
  RoverLCD.setCursor(usCursorX, usCursorY);
  RoverLCD.print(pcText);
#else
#endif
  return;
}  //DisplayText


void ClearTextBackground(INT16 sUpperLeftX, INT16 sUpperLeftY, UINT16 usWidth, UINT16 usHeight){
  RoverLCD.fillRect(sUpperLeftX, sUpperLeftY, usWidth, usHeight, BackgroundColor);
  return;
} //ClearTextBackground
#endif
//Last line
