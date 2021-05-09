const char szSystemFileName[]  = "BeckSystemClass.cpp";
const char szSystemFileDate[]  = "5/9/21b";

#include <BeckSystemClass.h>
#include <BeckAlexaClass.h>
#include <BeckBiotaDefines.h>
#include <BeckDisplayClass.h>
#include <BeckIncludeOptionalFiles.h>
#include <BeckLogLib.h>
#include <BeckSwitchClass.h>
#include <BeckThermostatClass.h>
#include <BeckThermostatDataClass.h>
#include <BeckWiFiLib.h>
#include <Streaming.h>

//Select type of project to build for.
ProjectType      eBiotaProjectType            = eThermoDev;
//ProjectType      eBiotaProjectType            = eFireplace;
//ProjectType      eBiotaProjectType            = eHeater;
//ProjectType      eBiotaProjectType            = eGarage;
//ProjectType      eBiotaProjectType            = ePitchMeter;

SystemClass           BiotaSystem;       //This is so every module can use the same object

SystemClass::SystemClass() {
  Serial << "SystemClass::SystemClass(): " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor


SystemClass::~SystemClass() {
  Serial << "~SystemClass(): Destructing" << endl;
} //destructor


void SystemClass::Setup(void){
  Serial.begin(lSerialMonitorBaud);
  delay(100);

  Serial << LOG0 << "\n\nSystemClass::Setup(): Begin" << endl;
  //SetProjectType(eCurrentBiotaProjectType);

  Serial << LOG0 << "SystemClass::Setup(): Call SetupProjectData()" << endl;
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
  BiotaAlexa.Setup(_acAlexaName);
#endif
  SetupOptionalModules();
  return;
} //Setup


void SystemClass::Handle(){
#if DO_ALEXA
  BiotaAlexa.Handle();
#endif
  BiotaThermostat.Handle();
  BiotaSwitches.Handle();
  HandleOptionalModules();
  BiotaDisplay.Handle();
  return;
} //Handle


void SystemClass::SetProjectType(ProjectType eNewProjectType){
  eProjectType= eNewProjectType;
 return;
}


ProjectType SystemClass::GetProjectType(void){
  return eProjectType;
}


void SystemClass::SetupOptionalModules(){
  if (_bWiFiConnected){
#if DO_OTA
    SetupOTAWebPages();
#endif
#if DO_WEB_SERVER
    //SetupTermoWebPage();
    StartWebServer(_acHostname);
#endif
#if DO_ACCESS_POINT
    SetupAccessPt(_acAccessPointSSID, _acAccessPointPW);
#endif
  } //if(_bWiFiConnected)
  else{
    Serial << "SetupOptionalModules(): WiFi is not connected" << endl;
  }
#if DO_FIREBASE
  Serial << LOG0 << "SetupOptionalModules(): Call Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH)" << endl;
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
#endif
#if USE_IMU
  if(eProjectType == ePitchMeter){
    bMPU9150_On= SetupMPU9150(szSketchName, szFileDate, ulMPU9150HandlerPeriodMsec);
  } //if(eProjectType==ePitchMeter)
#endif
#if DO_NTP
  if (_bWiFiConnected){
    SetupNTP();
  } //if(_bWiFiConnected)
#endif  //DO_NTP
  return;
} //SetupOptionalModules


void SystemClass::HandleOptionalModules(){
#if DO_WEB_SERVER
  if (_bWiFiConnected){
    HandleWebServer();
    CheckTaskTime("HandleOptionalModules(): HandleWebServer()");
  } //if(_bWiFiConnected)
#endif
#if DO_FIREBASE
  //TestFirefox();
  //CheckTaskTime("loop(): TestFirefox()");
#endif
#if DO_NTP
  if (_bWiFiConnected){
    HandleNTPUpdate();
    CheckTaskTime("HandleOptionalModules(): HandleNTPUpdate()");
  } //if(_bWiFiConnected)
#endif
#if DO_ACCESS_POINT
  if (_bWiFiConnected){
    HandleSoftAPClient();       //Listen for HTTP requests from clients
    CheckTaskTime("HandleOptionalModules(): HandleSoftAPClient()");
  } //if(_bWiFiConnected)
#endif  //DO_ACCESS_POINT
  return;
} //HandleOptionalModules


void SystemClass::SetupProjectData(void){
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
      ThermostatData.SetMinSetpoint  (40.0);
      ThermostatData.SetMaxSetpoint  (75.0);
      ThermostatData.SetThermostatOn (false);
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
      ThermostatData.SetMinSetpoint  (40.0);
      ThermostatData.SetMaxSetpoint  (75.0);
      ThermostatData.SetThermostatOn (false);
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
      ThermostatData.SetMaxSetpoint  (75.0);
      ThermostatData.SetThermostatOn(false);
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
      ThermostatData.SetThermostatOn (true);
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
      Serial << LOG0 << "SetupProjectData: SetupProjectData(): Bad switch, _ProjectType= " << BiotaSystem.GetProjectType() << endl;
      break;
  } //switch
  Serial << LOG0 << "SetupProjectData: SetupProjectData(): Project Type set to: " << _acProjectType << endl;

  return;
} //SetupProjectData
//Last line.