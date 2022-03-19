const char szSystemFileName[]  = "BeckTireTempNTPClass.cpp";
const char szSystemFileDate[]  = "3/19/22b";

#include <BeckTireTempNTPClass.h>
#include <BeckE32_Defines.h>
#include <BeckLogLib.h>
#include <Streaming.h>

#include <ctime>
#include <iostream>

#include <iomanip>

using namespace std;
#include <chrono>
using namespace std::chrono;

BeckTireTempNTPClass::BeckTireTempNTPClass(void) {
  Serial << "BeckTireTempNTPClass(void): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << "\n";
  _poNTPClient= new NTPClient(ntpUDP);
  return;
} //constructor

BeckTireTempNTPClass::~BeckTireTempNTPClass() {
  Serial << "~BeckTireTempNTPClass(): Destructor, deleting _poTCoupleSensor\n";
  return;
} //destructor


void BeckTireTempNTPClass::SetupNTP(){
// Initialize a NTPClient to get time
  Serial << "SetupNTP(): Call oNTPClient.begin()\n";
  _poNTPClient->begin();

  Serial << "SetupNTP(): Call oNTPClient.setTimeOffset() with an offset of " << _wOffsetUTC << " hours\n";
  _poNTPClient->setTimeOffset(_wOffsetUTC * 3600);

  return;
} //SetupNTP


uint32_t BeckTireTempNTPClass::uwGetEpochTime(){
  return _poNTPClient->getEpochTime();
} //uwGetEpochTime


void BeckTireTempNTPClass::HandleNTP(){
  // https://randomnerdtutorials.com/esp32-ntp-client-date-time-arduino-ide/
  // Variables to save date and time
  String formattedDate;
  String szFormattedTime;
  String dayStamp;
  String timeStamp;

  //Serial << "HandleNTP(): Enter while loop with oNTPClient.update and oNTPClient.forceUpdate()\n";
  while(!_poNTPClient->update()) {
    _poNTPClient->forceUpdate();
  } //while
  //Serial << "HandleNTP(): Done with while loop\n";

  // The formattedDate comes with the following format:
  // 2018-05-28T16:00:13Z
  // We need to extract date and time
#if false
  //formattedDate = _poNTPClient->getFormattedDate();
  formattedDate = _poNTPClient->getFormattedTime();
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

void BeckTireTempNTPClass::PrintCurrentTime(){
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

void BeckTireTempNTPClass::PrintSecondsSinceY2K(){
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
} //PrintSecondsSinceY2K//Last line.
