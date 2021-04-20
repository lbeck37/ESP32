const char szSketchName[]  = "BeckE32_Biota.ino";
const char szFileDate[]    = "4/20/21a";

#include <BeckBiotaDefines.h>
#include <BeckBiotaLib.h>
#include <BeckIncludeOptionalFiles.h>
#include <BeckMiniLib.h>
#include <BeckSwitchLib.h>
#include <BeckSystemClass.h>
#include <BeckDisplayClass.h>
#include <BeckThermostatClass.h>
#include <BeckThermostatDataClass.h>
#include <BeckWiFiLib.h>
#include <Streaming.h>
#include <Time.h>
#include <WiFiClient.h>

//Select type of project to build for.
ProjectType      eProjectType            = eThermoDev;
//ProjectType      eProjectType            = eFireplace;
//ProjectType      eProjectType            = eHeater;
//ProjectType      eProjectType            = eGarage;
//ProjectType      eProjectType            = ePitchMeter;

bool            _bOTA_Started       = false;
unsigned long   _ulOTATimeoutMsec   = millis();

//Prototypes for functions in this file.
void SetupOptionalModules   (void);
void HandleOptionalModules  (void);

void setup(){
  BiotaSystem.Setup();
  Serial << endl << LOG0 << "setup() finished, Sketch: " << szSketchName << ", " << szFileDate << endl;
  return;
} //setup


void loop(){
  ulLastTaskMsec= millis();

  HandleOptionalModules();    //Nothing turned on as of 4/19/21

  if (!_bOTA_Started){
    BiotaSystem.Handle();
    CheckTaskTime("loop(): HandleSystem()");
  } //if(!_bOTA_Started)
  else{
    Serial << LOG0 << "loop(): Check for update timeout" << endl;
    if (millis() > _ulOTATimeoutMsec) {
      _bOTA_Started = false;
      Serial << LOG0 << "loop(): Set bUpdating to " << _bOTA_Started << endl;
    } //if(millis()>_ulOTATimeoutMsec)
  } //if(!_bOTA_Started)else

  return;
} //loop


void SetupOptionalModules(){
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


void HandleOptionalModules(void){
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

#if DO_FIREBASE
void TestFirefox(){
  unsigned long         ulTestFirefoxPeriodMsec = 5 * 1000;
  static unsigned long  ulNextTestFirefoxMsec   = millis() + ulTestFirefoxPeriodMsec;
  if (millis() >= ulNextTestFirefoxMsec){
    ulNextTestFirefoxMsec= millis() + ulTestFirefoxPeriodMsec;
    float fValue= 42.0;
    //Serial << "TestFirefox(): Call Firebase.setFloat(\"number\", " << fValue << ")" << endl;
    //Firebase.setFloat("number", fValue);
    Serial << endl << LOG0 << "TestFirefox(): Call Firebase.setFloat(\"Setpoint\", " << fValue << ")" << endl;
    Firebase.setFloat("Setpoint", fValue);
    // handle error
    if (Firebase.failed()) {
      Serial.print("setting /Setpoint failed:");
      Serial.println(Firebase.error());
      //Serial << LOG0 << "TestFirefox(): Firebase.setFloat() failed, error= |" << Firebase.error() << "|" << endl;
      Serial << LOG0 << "TestFirefox(): Firebase.setFloat() failed, Call Firebase.error()" << endl;
      Firebase.error();
      return;
    } //if(Firebase.failed())
    delay(1000);
    // get value
    Serial << endl << LOG0 << "TestFirefox(): Call Firebase.getFloat(\"/DevBoard/DegF\")" << endl;
    float fDegF= Firebase.getFloat("/DevBoard/DegF");
    Serial << endl << LOG0 << "TestFirefox(): /DevBoard/DegF= " << fDegF << endl;
  } //if (millis()>=ulNextTestFirefoxMsec)
  return;
} //TestFirefox
#endif  //DO_FIREBASE
//Last line.
