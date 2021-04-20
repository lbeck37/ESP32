//BeckWiFiLib.h, 4/19/21b
#pragma once
#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif    //ESP32

extern        bool     _bWiFiConnected;

bool    SetupWiFi     ();
String  szWiFiStatus  (wl_status_t eWiFiStatus);

//Last line.
