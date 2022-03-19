const char szSketchName[]  = "BeckE32_TireTemp.ino";
const char szFileDate[]    = "3/18/22_WasWorking_am";      //From Commit 42331... "3/16/22k"

#include <BeckE32_Defines.h>
#if DO_OTA
  #include <BeckE32_OTALib.h>
#endif
#include <BeckCarSetClass.h>
#include <BeckI2cClass.h>
#include <BeckLogLib.h>
#include <BeckMiniLib.h>

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

#include <iomanip>

using namespace std;
#include <chrono>
using namespace std::chrono;

const char* szWebHostName = "TireTemp";

#define min(X, Y)       (((X) < (Y)) ? (X) : (Y))
const UINT16       usTopText_CursorY              =  35;

UINT16            usTextSpacing                  = 20;
UINT16            usDegF_CursorY                 = usTopText_CursorY;

char              sz100CharString[101];

unsigned long     ulNextDisplayMsec         =    0;
unsigned long     ulDisplayPeriodMsec       = 2000; //mSec between output to display

unsigned long     ulNextHandleSensorsMsec    =    0;
unsigned long     ulHandleSensorsPeriodMsec  = 5000; //mSec between handling probes

//const char*       szRouterName              = "Aspot24b";
//const char*       szRouterPW                = "Qazqaz11";

//Protos
void  setup                 ();
void  loop                  ();
void  SetupButtons          ();
void  onPressed1            ();
void  onPressed2            ();
void  onPressed3            ();
void  onPressed4            ();
void  SetupNTP              ();
void  HandleNTP             ();
void  PrintCurrentTime      ();
void  PrintSecondsSinceY2K  ();
#if DO_ROVER
  void  DisplayBegin        ();
  void  DisplayClear        ();
  void  FillScreen          (UINT16 usColor);
  void  DisplayUpdate       ();
  void  DisplayTemperature  ();
  void  DisplayLowerBanner  ();
  void  DisplayText         (UINT16 usCursorX, UINT16 usCursorY, char *pcText,
                             const GFXfont *pFont, UINT8 ucSize, UINT16 usColor);
  void  ClearTextBackground (INT16 sUpperLeftX, INT16 sUpperLeftY, UINT16 usWidth, UINT16 usHeight);
#endif

//Setup buttons, Defaults: 35msec debounce, Pullup enabled, Returns true on button press
EasyButton TireButton1(_cButton_Pin1);
EasyButton TireButton2(_cButton_Pin2);
EasyButton TireButton3(_cButton_Pin3);
EasyButton TireButton4(_cButton_Pin4);

#if DO_ROVER
  WROVER_KIT_LCD     RoverLCD;
  const ColorType    BackgroundColor         = WROVER_BLACK;
#endif

BeckCarSetClass*  _poCarSet;

// Define NTP Client to get time
WiFiUDP           ntpUDP;
NTPClient         _oNTPClient(ntpUDP);

const uint32_t    _uwI2CBusFrequency= 100000;
uint32_t          _uwEpochTime;

void setup(){
  Serial.begin(115200);
  Serial << "\n" << LOG0 << "setup(): Begin " << szSketchName << ", " << szFileDate << "\n";

#if DO_ROVER
  Serial << LOG0 << "setup(): Call DisplayBegin()\n";
  DisplayBegin();
#endif
  //FlashRGB_LED();

  Serial << "Connect to WiFi router " << _szRouterName << " with " << _szRouterPW << " as the PW\n";
  // Start WiFi and wait for connection to the network
  WiFi.begin(_szRouterName, _szRouterPW);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
    Serial << ".";
  }
  Serial << "\n";

#if DO_OTA
  Serial << "setup(): Call SetupWebServer(" << szWebHostName << ")\n";
  SetupWebserver(szWebHostName);
#endif

  Serial << LOG0 << "setup(): Call Wire.begin with bus frequency at " << _uwI2CBusFrequency << "\n";
  Wire.begin(_cI2C_SDA_Pin, _cI2C_SCL_Pin, _uwI2CBusFrequency);

  Serial << LOG0 << "setup(): Call SetupNTP()\n";
  SetupNTP();

  Serial << LOG0 << "setup(): Call PrintCurrentTime()\n";
  PrintCurrentTime();

  Serial << LOG0 << "setup(): Create _poCarSet using new BeckCarSetClass\n";
  _poCarSet= new BeckCarSetClass();

  Serial << LOG0 << "setup(): Call SetupButtons()\n";
  SetupButtons();

  //Check the t-couple hardware
  _poCarSet->bBegin();

  Serial << LOG0 << "setup(): return\n";
  return;
}  //setup


void loop() {
  TireButton1.read();   //This has to get called for onPressed() to get called back
  TireButton2.read();
  TireButton3.read();
  TireButton4.read();

  if (millis() > ulNextHandleSensorsMsec){
    ulNextHandleSensorsMsec= millis() + ulHandleSensorsPeriodMsec;
    HandleNTP();
    _uwEpochTime= _oNTPClient.getEpochTime();
    //Serial << LOG0 << "loop(): Timer ulNextHandleSensorsMsec fired\n";
    //_poSensorSet->Handle(_uwEpochTime);
    _poCarSet->ReadSensorSet(_uwEpochTime, _wLoggingSensorSetID);
    _poCarSet->PrintLogData();
  } //if (millis()>ulNextDisplayMsec)

#if DO_ROVER
  DisplayUpdate();
#endif
#if DO_OTA
  HandleOTAWebserver();
#endif
  return;
}  //loop()


void SetupButtons() {
  Serial << "SetupButtons(): Call TireButton1/2/3/4.begin()\n";
  TireButton1.begin();
  TireButton2.begin();
  TireButton3.begin();
  TireButton4.begin();

  Serial << "SetupButtons(): Setup Callback, call onPressed(callback) for the 4 buttons\n";
  TireButton1.onPressed(onPressed1);
  TireButton2.onPressed(onPressed2);
  TireButton3.onPressed(onPressed3);
  TireButton4.onPressed(onPressed4);
  return;
} //SetupButtons

void onPressed1(){
  int   wSensorSet= 1;
  Serial << "onPressed2(): You pressed Button " << wSensorSet << "\n";
  _poCarSet->ReadSensorSet(_uwEpochTime, wSensorSet);
  return;
} //onPressed1

void onPressed2(){
  int   wSensorSet= 2;
  Serial << "onPressed2(): You pressed Button " << wSensorSet << "\n";
  _poCarSet->ReadSensorSet(_uwEpochTime, wSensorSet);
  return;
} //onPressed2

void onPressed3(){
  int   wSensorSet= 1;
  Serial << "onPressed2(): You pressed Button " << wSensorSet << "\n";
  _poCarSet->ReadSensorSet(_uwEpochTime, wSensorSet);
  return;
} //onPressed3

void onPressed4(){
  int   wSensorSet= 1;
  Serial << "onPressed2(): You pressed Button " << wSensorSet << "\n";
  _poCarSet->ReadSensorSet(_uwEpochTime, wSensorSet);
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

void HandleNTP(){
  // https://randomnerdtutorials.com/esp32-ntp-client-date-time-arduino-ide/
  // Variables to save date and time
  String formattedDate;
  String szFormattedTime;
  String dayStamp;
  String timeStamp;

  //Serial << "HandleNTP(): Enter while loop with oNTPClient.update and oNTPClient.forceUpdate()\n";
  while(!_oNTPClient.update()) {
    _oNTPClient.forceUpdate();
  } //while
  //Serial << "HandleNTP(): Done with while loop\n";

  // The formattedDate comes with the following format:
  // 2018-05-28T16:00:13Z
  // We need to extract date and time
#if false
  //formattedDate = _oNTPClient.getFormattedDate();
  formattedDate = _oNTPClient.getFormattedTime();
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
#endif
  return;
}   //HandleNTP

void PrintCurrentTime(){
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

void PrintSecondsSinceY2K()
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


void DisplayUpdate() {
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

/*
  sprintf(sz100CharString, "%6.1f", 37.37);
  DisplayText( usCursorX, usCursorY, "Tire Degrees F", pFont, ucSize, usColor);
*/
  sprintf(sz100CharString, "%s", "Tire Degrees F");
  DisplayText( usCursorX, usCursorY, sz100CharString, pFont, ucSize, usColor);
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
