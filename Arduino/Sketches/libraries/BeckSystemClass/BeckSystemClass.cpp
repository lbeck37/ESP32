const char szSystemFileName[]  = "BeckSystemClass.cpp";
const char szSystemFileDate[]  = "5/21/21d";

#include <BeckSystemClass.h>
#include <BeckAlexaClass.h>
#include <BeckBiotaDefines.h>
#if DO_ROVER
  #include <BeckEnviroDisplayClass.h>
#else
  #if DO_TTGO
    #include <BeckGasSensorDisplayClass.h>
  #endif
#endif
#if DO_THERMOSTAT
  #include <BeckSwitchClass.h>
  #include <BeckThermostatClass.h>
  #include <BeckThermostatDisplayClass.h>
  #include <BeckThermostatDataClass.h>
#endif
#include <BeckGasSensorClass.h>
#include <BeckGasSensorDataClass.h>
#include <BeckIncludeOptionalFiles.h>
#include <BeckLogLib.h>
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
  Serial.begin(115200);
  delay(100);

  Serial << LOG0 << "\n\nSystemClass::Setup(): Begin" << endl;
  SetProjectType(eBiotaProjectType);

  Serial << LOG0 << "SystemClass::Setup(): Call SetupProjectData()" << endl;
  SetupProjectData();

#if DO_THERMOSTAT
    Serial << LOG0 << "SystemClass::Setup(): Call BiotaThermostat.Setup()" << endl;
    BiotaThermostat.Setup();
    Serial << LOG0 << "SystemClass::Setup(): Call BiotaSwitches.Setup()" << endl;
    BiotaSwitches.Setup();

#endif

  Serial << LOG0 << "SystemClass::Setup(): Call GasSensor.Setup()" << endl;
  GasSensor.Setup();

#if DO_TTGO
  Serial << LOG0 << "SystemClass::Setup(): Call BiotaDisplay.Setup()" << endl;
  GasSensorDisplay.Setup();
#endif

#if DO_ROVER
  Serial << LOG0 << "SystemClass::Setup(): Call EnviroDisplay.Setup()" << endl;
  EnviroDisplay.Setup();
#endif

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
  #if DO_THERMOSTAT
    BiotaThermostat.Handle();
    BiotaSwitches.Handle();
  #endif
  HandleOptionalModules();
  GasSensor.Handle();
  //ThermostatDisplay.Handle();
  #if DO_TTGO
    GasSensorDisplay.Handle();
  #endif
  #if DO_ROVER
    EnviroDisplay.Handle();
  #endif
  return;
} //Handle


void SystemClass::SetProjectType(ProjectType eNewProjectType){
  Serial << "SystemClass::SetProjectType(): Set eProjectType to: " << eNewProjectType << endl;
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
  Serial << "SystemClass::SetupProjectData(): Begin" << endl;
  switch (BiotaSystem.GetProjectType()){
  case eEnviro:
    Serial << "SystemClass::SetupProjectData(): Setup eEnviro project" << endl;
    strcpy(_acHostname        , "BeckEnviro");
    strcpy(_acProjectType     , "ENVIRO");
    strcpy(_acAlexaName       , "Larry's Device");
    strcpy(_acRouterName      , "Aspot24");
    strcpy(_acRouterPW        , "Qazqaz11");
    strcpy(_acAccessPointSSID , "BiotaSpot");
    strcpy(_acAccessPointPW   , "Qazqaz11");
    break;
  case eThermoDev:
    Serial << "SystemClass::SetupProjectData(): Setup eThermoDev project" << endl;
    strcpy(_acHostname        , "BeckThermoDev");
    strcpy(_acProjectType     , "THERMO_DEV");
    strcpy(_acAlexaName       , "Larry's Device");
    strcpy(_acRouterName      , "Aspot24");
    strcpy(_acRouterPW        , "Qazqaz11");
    strcpy(_acAccessPointSSID , "BiotaSpot");
    strcpy(_acAccessPointPW   , "Qazqaz11");

#if DO_THERMOSTAT
    ThermostatData.SetSetpoint     (71.0);
    ThermostatData.SetMaxHeatRange ( 0.1);
    ThermostatData.SetMinSetpoint  (40.0);
    ThermostatData.SetMaxSetpoint  (75.0);
    ThermostatData.SetThermostatOn (false);
#endif
    break;
    case eFireplace:
      strcpy(_acHostname        , "BeckFireplace");
      strcpy(_acProjectType     , "FIREPLACE");
      strcpy(_acAlexaName       , "Fireplace");
      strcpy(_acRouterName      , "Aspot24");
      strcpy(_acRouterPW        , "Qazqaz11");
      strcpy(_acAccessPointSSID , "FireplaceSpot");
      strcpy(_acAccessPointPW   , "Qazqaz11");

#if DO_THERMOSTAT
      ThermostatData.SetSetpoint     (71.0);
      ThermostatData.SetMaxHeatRange ( 0.1);
      ThermostatData.SetMinSetpoint  (40.0);
      ThermostatData.SetMaxSetpoint  (75.0);
      ThermostatData.SetThermostatOn (false);
#endif
      break;
    case eHeater:
      strcpy(_acHostname        , "BeckHeater");
      strcpy(_acProjectType     , "HEATER");
      strcpy(_acAlexaName       , "Candy's Heater");
      strcpy(_acRouterName      , "Aspot24");
      strcpy(_acRouterPW        , "Qazqaz11");
      strcpy(_acAccessPointSSID , "HeaterSpot");
      strcpy(_acAccessPointPW   , "Qazqaz11");

#if DO_THERMOSTAT
      ThermostatData.SetSetpoint     (75.0);
      ThermostatData.SetMaxHeatRange ( 0.1);
      ThermostatData.SetMinSetpoint  (60.0);
      ThermostatData.SetMaxSetpoint  (75.0);
      ThermostatData.SetThermostatOn(false);
#endif
      break;
    case eGarage:
      strcpy(_acHostname        , "BeckGarage");
      strcpy(_acProjectType     , "GARAGE");
      strcpy(_acAlexaName       , "Garage");
      strcpy(_acRouterName      , "Aspot24");
      strcpy(_acRouterPW        , "Qazqaz11");
      strcpy(_acAccessPointSSID , "GarageSpot");
      strcpy(_acAccessPointPW   , "Qazqaz11");

#if DO_THERMOSTAT
      ThermostatData.SetSetpoint     (35.0);
      ThermostatData.SetMaxHeatRange ( 0.1);
      ThermostatData.SetMinSetpoint  (33.0);
      ThermostatData.SetMaxSetpoint  (70.0);
      ThermostatData.SetThermostatOn (true);
#endif
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
