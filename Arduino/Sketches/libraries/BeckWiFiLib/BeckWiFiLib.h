//BeckWiFiLib.h, 3/29/21a  was 4/18/19a
#pragma once
#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif    //ESP32

extern        bool     _bWiFiConnected;

void    SetupWiFi     ();
String  szWiFiStatus  (wl_status_t eWiFiStatus);

//Last line.
