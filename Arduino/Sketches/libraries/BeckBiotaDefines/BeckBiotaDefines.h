// BeckBiotaDefines.h, 5/9/21a
#pragma once
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

/*
//Select type of project to build for.
ProjectType      eBiotaProjectType            = eThermoDev;
//ProjectType      eBiotaProjectType            = eFireplace;
//ProjectType      eBiotaProjectType            = eHeater;
//ProjectType      eBiotaProjectType            = eGarage;
//ProjectType      eBiotaProjectType            = ePitchMeter;
*/

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
