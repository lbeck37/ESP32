// BeckSystemClass.h, 5/9/21b
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


class SystemClass{
public:
  SystemClass();
  virtual ~SystemClass();

  void          Setup             		(ProjectType eBiotaProjectType);
  void          Handle            		(void);
  ProjectType   GetProjectType    		(void);
  void          SetProjectType    		(ProjectType NewProjectType);
  void			SetupOptionalModules	(void);
  void			HandleOptionalModules	(void);

protected:
  char          _acHostname       [50];
  char          _acAlexaName      [50];
  char          _acProjectType    [50];
  char          _acRouterName     [50];
  char          _acRouterPW       [50];
  char          _acAccessPointSSID[50];
  char          _acAccessPointPW  [50];

  ProjectType       eProjectType          = eThermoDev;
  int               sThermoTimesCount     = 0;      //Number of times temperature out of range
  bool              bWiFiOn               = false;
  unsigned long     ulHandlePeriodMsec    = 5 * 1000;
  unsigned long     ulNextHandleMsec      = 0;

  void          SetupProjectData  (void);
};  //SystemClass

extern SystemClass          BiotaSystem;       //This is so every module can use the same object

//Last line.
