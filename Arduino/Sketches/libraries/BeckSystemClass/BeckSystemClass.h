// 4/19/21b, BeckSystemClass.h
#pragma once

#include <BeckBiotaLib.h>
#include <BeckAlexaClass.h>
#include <BeckDisplayClass.h>
//#include <BeckThermoDisplayClass.h>
#include <BeckThermostatClass.h>
#include <BeckThermostatDataStruct.h>

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
  char          szAlexaName[50]= ALEXA_NAME;
  //char        *pAlexaName         = "Larry's Device";

  ProjectType   eProjectType         = eThermoDev;
  int           sThermoTimesCount     = 0;      //Number of times temperature out of range

public:
  SystemClass();
  virtual ~SystemClass();

  void          Setup             (void);
  void          Handle            (void);
  ProjectType   GetProjectType    (void);
  void          SetProjectType    (ProjectType NewProjectType);
};  //SystemClass

extern SystemClass          BiotaSystem;       //This is so every module can use the same object

//Last line.
