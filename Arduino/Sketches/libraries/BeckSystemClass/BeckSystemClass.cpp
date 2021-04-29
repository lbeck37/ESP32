const char szSystemFileName[]  = "BeckSystemClass.cpp";
const char szSystemFileDate[]  = "4/28/21";

#include <BeckSystemClass.h>
#include <BeckAlexaClass.h>
#include <BeckBiotaDefines.h>
#include <BeckDisplayClass.h>
#include <BeckLogLib.h>
#include <BeckSwitchClass.h>
#include <BeckThermostatClass.h>
#include <BeckWiFiLib.h>
#include <Streaming.h>

SystemClass           BiotaSystem;       //This is so every module can use the same object

SystemClass::SystemClass() {
  Serial << "SystemClass::SystemClass(): " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor


SystemClass::~SystemClass() {
  Serial << "~SystemClass(): Destructing" << endl;
} //destructor


void SystemClass::Setup(ProjectType eBiotaProjectType){
  Serial.begin(lSerialMonitorBaud);
  delay(100);

  Serial << LOG0 << "\n\nSystemClass::Setup(): Begin" << endl;
  SetProjectType(eBiotaProjectType);

  Serial << LOG0 << "SystemClass::Setup(): Call SetupProjectData()" << endl;
  //SetupProjectData(eBiotaProjectType);
  SetupProjectData();

  Serial << LOG0 << "SystemClass::Setup(): Call BiotaThermostat.Setup()" << endl;
  BiotaThermostat.Setup();

  Serial << LOG0 << "SystemClass::Setup(): Call BiotaDisplay.Setup()" << endl;
  BiotaDisplay.Setup();

  Serial << LOG0 << "SystemClass::Setup(): Call BiotaSwitches.Setup()" << endl;
  BiotaSwitches.Setup();

  Serial << LOG0 << "SystemClass::Setup(): Call SetupWiFi()" << endl;
  bWiFiOn= SetupWiFi();

#if DO_ALEXA
  BiotaAlexa.Setup(ALEXA_NAME);
#endif
  return;
} //Setup


void SystemClass::SetupProjectData(void){
  //bool  bOk= true;
  switch (BiotaSystem.GetProjectType()){
  //switch (eBiotaProjectType){
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
      //BiotaSystem.SetProjectType(eThermoDev);
      break;
    case eFireplace:
      strcpy(_acHostname        , "BeckFireplace");
      strcpy(_acProjectType     , "FIREPLACE");
      strcpy(_acAlexaName       , "Fireplace");
      strcpy(_acRouterName      , "Aspot24");
      strcpy(_acRouterPW        , "Qazqaz11");
      strcpy(_acAccessPointSSID , "FireplaceSpot");
      strcpy(_acAccessPointPW   , "Qazqaz11");

      ThermostatData.SetSetpoint     (71.0);
      ThermostatData.SetMaxHeatRange ( 0.1);
      ThermostatData.SetMinSetpoint  (60.0);
      ThermostatData.SetMaxSetpoint  (95.0);
      //BiotaSystem.SetProjectType(eFireplace);
      break;
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
      //BiotaSystem.SetProjectType(eHeater);
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
      //BiotaSystem.SetProjectType(eGarage);
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
      //BiotaSystem.SetProjectType(ePitchMeter);
      break;
    case eFrontLights:
      strcpy(_acHostname        , "BeckFrontLights");
      strcpy(_acProjectType     , "FRONT_LIGHTS");
      strcpy(_acAlexaName       , "Front Lights");
      strcpy(_acRouterName      , "Aspot24");
      strcpy(_acRouterPW        , "Qazqaz11");
      strcpy(_acAccessPointSSID , "FrontLightsSpot");
      strcpy(_acAccessPointPW   , "Qazqaz11");
      //BiotaSystem.SetProjectType(eFrontLights);
      break;
    case eNoProject:
    default:
      Serial << LOG0 << "SetupProjectData: SetupProjectData(): Bad switch, _ProjectType= " << BiotaSystem.GetProjectType() << endl;
      //bOk= false;
      break;
  } //switch
  Serial << LOG0 << "SetupProjectData: SetupProjectData(): Project Type set to: " << _acProjectType << endl;

  return;
} //SetupProjectData


void SystemClass::Handle(){
#if DO_ALEXA
  BiotaAlexa.Handle();
#endif
  BiotaThermostat.Handle();
  BiotaSwitches.Handle();
  BiotaDisplay.Handle();
  return;
} //Handle


ProjectType SystemClass::GetProjectType(void){
  return eProjectType;
}

void SystemClass::SetProjectType(ProjectType eNewProjectType){
  eProjectType= eNewProjectType;
 return;
}
//Last line.
