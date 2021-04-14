const char szSketchName[]  = "BeckE32_Biota.ino";
const char szFileDate[]    = "4/14/21b";

#include <BeckBiotaDefines.h>
#include <BeckBiotaLib.h>
#include <BeckMiniLib.h>
#include <BeckSwitchLib.h>
#include <BeckThermoDisplayClass.h>
//#include <BeckThermoLib.h>
#include <BeckThermostatClass.h>
#include <BeckWiFiLib.h>
#include <Streaming.h>
#include <Time.h>
#include <WiFiClient.h>

//Select type of project to build for.
ProjectType      eProjectType            = eThermoDev;
//ProjectType      eProjectType            = eFireplace;
//ProjectType      eProjectType            = eHeater;
//ProjectType      eProjectType            = eGarage;
//ProjectType      eProjectType           = ePitchMeter;

#if DO_ALEXA || DO_OTA || DO_ACCESS_POINT || DO_FIREBASE || DO_WEB_SERVER || DO_NTP || USE_IMU
  #if DO_OTA
    #include <BeckOTALib.h>
  #endif

  #if DO_WEB_SERVER
    #include <BeckWebPages.h>
    #include <BeckWebServer.h>
  #endif

  #if DO_ALEXA
    #include <BeckAlexaLib.h>
  #endif

  #if DO_ACCESS_POINT
    #include <BeckAccessPointLib.h>
  #endif

  #if DO_NTP
    #include <BeckNTPLib.h>
  #endif

  #if DO_FIREBASE
    #include <FirebaseArduino.h>
    #include <ArduinoJson.h>
    #include <ESP8266HTTPClient.h>

   /*
    #define FIREBASE_HOST   "//test-70884.firebaseio.com"
    #define FIREBASE_HOST   "https://test-70884.firebaseio.com"

    #define FIREBASE_HOST   "https://test-70884.firebaseio.com/"
    #define FIREBASE_AUTH   "AIzaSyD-Nm1dYBV6ehphAOQgkM5sz4oYLKF9ahg"
    */
    #define FIREBASE_HOST   "https://thermo-2b830.firebaseio.com/"
    #define FIREBASE_AUTH   "AIzaSyAkFumb-wjDUQ9HQjTOoHeXqTKztFSqf6o"
  #endif  //DO_FIREBASE

  #if USE_IMU
    //static const  uint32_t    ulMPU9150HandlerPeriodMsec  = 200;
    static const  uint32_t    ulMPU9150HandlerPeriodMsec  = 0;
    static const  uint32_t    ulMPU9150DisplayPeriodMsec  = 1000;
    static        uint32_t    ulNextMPU9150DisplayMsec    = 0;
    static        bool        bMPU9150_On;
  #endif
#endif  //All defines

static const  uint32_t    ulThermHandlerPeriodMsec    = 1 * lMsecPerSec; //mSec between running system handler
static        uint32_t    ulNextThermHandlerMsec      = 0;
static        int         _wBadCount                  = 0;
static        int         _wGoodCount                 = 0;

bool            _bOTA_Started       = false;
unsigned long   _ulOTATimeoutMsec   = millis();

ThermoDisplay     cDisplay;
Thermostat        BiotaThermostat;

//Prototypes for functions in this file.
void HandleSystem();

void setup(){
  Serial.begin(lSerialMonitorBaud);
  delay(100);
  Serial << endl << LOG0 << "setup(): Sketch: " << szSketchName << ", " << szFileDate << endl;

  _bSystemOk= SetupSystem(eProjectType);  //BeckBiotaib.cpp
  if(_bSystemOk){
    //Skip WiFi until ESP32 is coming up with the TTGO display
    if (true){
      SetupWiFi();
    }
    else{
      Serial << LOG0 << "setup(): Skipping Wifi until TTGO graphics are up" << endl;
      _bWiFiConnected= false;
    }

    #if DO_ALEXA || DO_OTA || DO_ACCESS_POINT || DO_FIREBASE || DO_WEB_SERVER || DO_NTP || USE_IMU
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
        #if DO_ALEXA
              SetupAlexa(_acAlexaName);
        #endif
      } //if(_bWiFiConnected)
      else{
        Serial << "setup(): WiFi is not connected" << endl;
      }

      #if DO_FIREBASE
          Serial << LOG0 << "setup(): SetupSystem(): Call Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH)" << endl;
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
    #endif  //All defines

    SetupSwitches();
    ulLastTaskMsec= millis();
  } //if(_bSystemOk)
  else{
    while(true){
      Serial << LOG0 << "setup(): SetupSystem(): Returned false" << endl;
      delay(10000); //10 sec
     }  //while(true)
  } //if(_bSystemOk)else
  Serial << LOG0 << "setup(): Done" << endl;
  return;
} //setup


void loop(){
  ulLastTaskMsec= millis();

  #if DO_ACCESS_POINT || DO_FIREBASE || DO_WEB_SERVER || DO_NTP
    #if DO_WEB_SERVER
      if (_bWiFiConnected){
        HandleWebServer();
        CheckTaskTime("loop(): HandleWebServer()");
      } //if(_bWiFiConnected)
    #endif
    #if DO_FIREBASE
      //TestFirefox();
      //CheckTaskTime("loop(): TestFirefox()");
    #endif
    #if DO_NTP
      if (_bWiFiConnected){
        HandleNTPUpdate();
        CheckTaskTime("loop(): HandleNTPUpdate()");
      } //if(_bWiFiConnected)
    #endif
    #if DO_ACCESS_POINT
      if (_bWiFiConnected){
        HandleSoftAPClient();       //Listen for HTTP requests from clients
        CheckTaskTime("loop(): HandleSoftAPClient()");
      } //if(_bWiFiConnected)
    #endif  //DO_ACCESS_POINT
  #endif  //Multiple conditionals

  if (!_bOTA_Started){
    HandleSystem();
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


  void UpdateDisplay(void){
    ThermoStruct    stData;
    stData.fCurrentDegF     = _fLastDegF;
    stData.fSetpointDegF    = _fSetpointF;
    stData.fMaxHeatRangeF   = _fMaxHeatRangeF;
    stData.bThermoOn        = _bThermoOn;
    stData.bHeatOn          = _bHeatOn;

    cDisplay.DrawScreen(stData);
    return;
  } //UpdateDisplay


void HandleSystem(){
#if DO_ALEXA
  if (_bWiFiConnected){
    HandleAlexa();
    CheckTaskTime("HandleAlexa");
    if(_bAlexaChanged){
      _bAlexaChanged= false;
      UpdateDisplay();
    } //if(bAlexaChanged)
  } //if(_bWiFiConnected)
  wAlexaHandleCount= 0;
#endif
  switch (_eProjectType){
    case eFireplace:
    case eHeater:
    case eGarage:
    case eThermoDev:
      if (millis() >= ulNextThermHandlerMsec){
        ulNextThermHandlerMsec= millis() + ulThermHandlerPeriodMsec;
        _wGoodCount= 0;
        _wBadCount= 0;
        #if DO_ALEXA
          if (false && (wAlexaHandleCount < 1000)){
            //HandleAlexa() gets called ~8,000 times every 10 sec, except when it's 1 or 2
            LogToSerial("HandleSystem():HandleAlexa() Times called=", wAlexaHandleCount);
          } //if (wAlexaHandleCount<1000)
        #endif
        Serial << endl << LOG0 << "BeckE32_Biota.ino: HandleSystem(): Call HandleThermostat()" << endl;
        //HandleThermostat();   //BeckThermoLib.cpp
        BiotaThermostat.HandleThermostat();   //BeckThermoLib.cpp
        //HandleHeatSwitch();
        UpdateDisplay();
      } //if(millis()>=ulNextThermHandlerMsec)
     break;
    case ePitchMeter:
      #if USE_IMU
        if (bMPU9150_On){
          HandleMPU9150();
        } //if(bMPU9150_On)
        if (millis() >= ulNextMPU9150DisplayMsec){
          ulNextMPU9150DisplayMsec= millis() + ulMPU9150DisplayPeriodMsec;
          UpdateDisplay();
        } //if(millis()>=ulNextMPU9150DisplayMsec)
      #endif  //USE_IMU
      break;
    case eFrontLights:
      //HandleFrontLights();
      break;
    default:
      Serial << LOG0 << "HandleSystem(): Bad switch, _eProjectType= " << _eProjectType << endl;
      break;
  } //switch
  return;
} //HandleSystem


#if DO_FIREBASE
  void TestFirefox(){
    unsigned long         ulTestFirefoxPeriodMsec = 5 * 1000;
    static unsigned long  ulNextTestFirefoxMsec   = millis() + ulTestFirefoxPeriodMsec;

    if (millis() >= ulNextTestFirefoxMsec){
      ulNextTestFirefoxMsec= millis() + ulTestFirefoxPeriodMsec;

      // set value
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
