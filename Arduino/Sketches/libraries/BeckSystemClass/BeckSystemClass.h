//4/16/21c, BeckSystemClass.h
#pragma once

#include <BeckDisplayClass.h>
#include <BeckBiotaLib.h>
#include <BeckAlexaClass.h>
#include <BeckThermostatClass.h>
//#include <BeckThermoDisplayClass.h>


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
protected:
  char          szAlexaName[50]= "Larry's Device";
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
extern AlexaClass           BiotaAlexa;       //This is so every module can use the same Alexa object

//extern ThermoDisplayClass   BiotaDisplay;       //This is so every module can use the same object
//extern Display              BiotaDisplay;       //This is so every module can use the same object
//extern ThermostatClass      BiotaThermostat;

//Last line.
