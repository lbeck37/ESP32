// BeckTireTempNTPClass.h, 3/19/22b
#pragma once
#include <BeckE32_Defines.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

class BeckTireTempNTPClass{
public:
  BeckTireTempNTPClass();
  virtual ~BeckTireTempNTPClass();

  void      SetupNTP              ();
  void      HandleNTP             ();
  uint32_t  uwGetEpochTime        ();
  void      PrintCurrentTime      ();
  void      PrintSecondsSinceY2K  ();

private:
  // Define NTP Client to get time
  WiFiUDP           ntpUDP;
  NTPClient*        _poNTPClient  {nullptr};

};
//Last line.
