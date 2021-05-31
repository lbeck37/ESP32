// BeckBiotaDefines.h, 5/29/21b
#pragma once
#include <cstdint>

enum ProjectType{
  eNoProject  = 0,
  eThermoDev,
  eEnviro,
  eFireplace,
  eGarage,
  eHeater,
  eFrontLights,
  ePitchMeter,
  eLastProjectType
};

//Define the code that is built
#define DO_ACCESS_POINT         false
#define DO_ALEXA                false
//#define DO_ASYNC_WEB_SERVER   false
#define DO_FIREBASE             false
#define USE_IMU                 false
#define DO_NTP                  false
#define DO_OTA                  false
#define DO_ROVER                  true
#define DO_THERMOSTAT           false
#define DO_TTGO                 false
#define DO_WEB_SERVER           false
//Last line.
