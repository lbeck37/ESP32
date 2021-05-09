// BeckBiotaDefines.h, 5/9/21b
#pragma once
#include <cstdint>

enum ProjectType{
  eNoProject  = 0,
  eThermoDev,
  eFireplace,
  eGarage,
  eHeater,
  eFrontLights,
  ePitchMeter,
  eLastProjectType
};

#define DO_ACCESS_POINT         false
#define DO_ALEXA                true
//#define DO_ASYNC_WEB_SERVER   false
#define DO_FIREBASE             false
#define USE_IMU                 false
#define DO_NTP                  false
#define DO_OTA                  false
#define DO_THERMOSTAT           false
#define DO_WEB_SERVER           false
//Last line.
