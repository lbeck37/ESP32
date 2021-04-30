// BeckSystemClass.h, 4/30/21a
#pragma once

#include <BeckAlexaClass.h>
#include <BeckDisplayClass.h>
#include <BeckThermostatClass.h>
#include <BeckThermostatDataClass.h>

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

#define ALEXA_NAME      "Larry's Device"

class SystemClass{
protected:
  char          _acHostname       [50];
  char          _acAlexaName      [50];
  char          _acProjectType    [50];
  char          _acRouterName     [50];
  char          _acRouterPW       [50];
  char          _acAccessPointSSID[50];
  char          _acAccessPointPW  [50];

  char              szAlexaName[50]       = ALEXA_NAME;
  ProjectType       eProjectType          = eThermoDev;
  int               sThermoTimesCount     = 0;      //Number of times temperature out of range
  bool              bWiFiOn               = false;
  unsigned long     ulHandlePeriodMsec    = 5 * 1000;
  unsigned long     ulNextHandleMsec      = 0;

  void          SetupProjectData  (void);
public:
  SystemClass();
  virtual ~SystemClass();

  void          Setup             (ProjectType eBiotaProjectType);
  void          Handle            (void);
  ProjectType   GetProjectType    (void);
  void          SetProjectType    (ProjectType NewProjectType);
};  //SystemClass

extern SystemClass          BiotaSystem;       //This is so every module can use the same object

//Last line.
