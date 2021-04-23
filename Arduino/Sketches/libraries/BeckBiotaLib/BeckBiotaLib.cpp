const char szBiotaLibFileName[]  = "BeckBiotaLib.cpp";
const char szBiotaLibFileDate[]    = "4/22/21a";

#include <BeckBiotaLib.h>
#include <BeckPinNumbers.h>
#include <BeckSystemClass.h>
#include <BeckThermostatDataClass.h>

bool          _bSystemOk        = true;

char          _acHostname       [50];
char          _acAlexaName      [50];
char          _acProjectType    [50];
char          _acRouterName     [50];
char          _acRouterPW       [50];
char          _acAccessPointSSID[50];
char          _acAccessPointPW  [50];

bool SetupProjectData(void){
  Serial << LOG0 << "BeckBiotaLib.cpp: SetupProjectData(): Begin" << endl;
  bool  bOk= true;
  switch (BiotaSystem.GetProjectType()){
    case eThermoDev:
      strcpy(_acHostname        , "BeckThermoDev");
      strcpy(_acProjectType     , "THERMO_DEV");
      strcpy(_acAlexaName       , "Larry's Device");
      strcpy(_acRouterName      , "Aspot24");
      strcpy(_acRouterPW        , "Qazqaz11");
      strcpy(_acAccessPointSSID , "BiotaSpot");
      strcpy(_acAccessPointPW   , "Qazqaz11");

      ThermostatData.SetSetpoint     (71.0);
      ThermostatData.SetMaxHeatRange ( 0.1);
      ThermostatData.SetMinSetpoint  (60.0);
      ThermostatData.SetMaxSetpoint  (95.0);
      break;
    case eFireplace:
      strcpy(_acHostname        , "BeckFireplace");
      strcpy(_acProjectType     , "FIREPLACE");
      //strcpy(_acAlexaName       , "Fireplace");
      strcpy(_acRouterName      , "Aspot24");
      strcpy(_acRouterPW        , "Qazqaz11");
      strcpy(_acAccessPointSSID , "FireplaceSpot");
      strcpy(_acAccessPointPW   , "Qazqaz11");

      ThermostatData.SetSetpoint     (71.0);
      ThermostatData.SetMaxHeatRange ( 0.1);
      ThermostatData.SetMinSetpoint  (60.0);
      ThermostatData.SetMaxSetpoint  (95.0);
    case eHeater:
      strcpy(_acHostname        , "BeckHeater");
      strcpy(_acProjectType     , "HEATER");
      strcpy(_acAlexaName       , "Candy's Heater");
      strcpy(_acRouterName      , "Aspot24");
      strcpy(_acRouterPW        , "Qazqaz11");
      strcpy(_acAccessPointSSID , "HeaterSpot");
      strcpy(_acAccessPointPW   , "Qazqaz11");

      ThermostatData.SetSetpoint     (75.0);
      ThermostatData.SetMaxHeatRange ( 0.1);
      ThermostatData.SetMinSetpoint  (60.0);
      ThermostatData.SetMaxSetpoint  (80.0);
      break;
    case eGarage:
      strcpy(_acHostname        , "BeckGarage");
      strcpy(_acProjectType     , "GARAGE");
      strcpy(_acAlexaName       , "Garage");
      strcpy(_acRouterName      , "Aspot24");
      strcpy(_acRouterPW        , "Qazqaz11");
      strcpy(_acAccessPointSSID , "GarageSpot");
      strcpy(_acAccessPointPW   , "Qazqaz11");

      ThermostatData.SetSetpoint     (35.0);
      ThermostatData.SetMaxHeatRange ( 0.1);
      ThermostatData.SetMinSetpoint  (33.0);
      ThermostatData.SetMaxSetpoint  (70.0);
      break;
    case ePitchMeter:
      strcpy(_acHostname        , "BeckPitch");
      strcpy(_acProjectType     , "PITCH");
      strcpy(_acAlexaName       , "Pitch Meter");
      //strcpy(_acRouterName      , "Aspot24");
      strcpy(_acRouterName      , "Dspot");
      strcpy(_acRouterPW        , "Qazqaz11");
      strcpy(_acAccessPointSSID , "PitchSpot");
      strcpy(_acAccessPointPW   , "Qazqaz11");
      break;
    case eFrontLights:
      strcpy(_acHostname        , "BeckFrontLights");
      strcpy(_acProjectType     , "FRONT_LIGHTS");
      strcpy(_acAlexaName       , "Front Lights");
      strcpy(_acRouterName      , "Aspot24");
      strcpy(_acRouterPW        , "Qazqaz11");
      strcpy(_acAccessPointSSID , "FrontLightsSpot");
      strcpy(_acAccessPointPW   , "Qazqaz11");
      break;
    case eNoProject:
    default:
      Serial << LOG0 << "SetupSystem(): Bad switch, _ProjectType= " << BiotaSystem.GetProjectType() << endl;
      bOk= false;
      break;
  } //switch
  switch (BiotaSystem.GetProjectType()){
    case eThermoDev:
    case eFireplace:
    case eHeater:
    case eGarage:
    	break;
    case ePitchMeter:
    case eFrontLights:
      break;
    case eNoProject:
    default:
      Serial << LOG0 << "SetupSystem(): Bad switch, ProjectType= " << BiotaSystem.GetProjectType() << endl;
      bOk= false;
      break;
  } //switch
  Serial << LOG0 << "SetupSystem(): Project Type set to: " << _acProjectType << endl;
  return bOk;
} //SetupProjectData
//Last line.
