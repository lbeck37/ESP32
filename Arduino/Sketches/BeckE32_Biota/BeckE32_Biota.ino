const char szSketchName[]  = "BeckE32_Biota.ino";
const char szFileDate[]    = "6/17/21e";

#include <BeckLogLib.h>
#include <BeckSystemClass.h>
#include <Streaming.h>

//Project types: eThermoDev, eEnviro, eFireplace, eHeater, eGarage, ePitchMeter
ProjectType     eBiotaProjectType   = eEnviro;
//ProjectType     eBiotaProjectType   = eThermoDev;

bool            _bOTA_Started       = false;
unsigned long   _ulOTATimeoutMsec   = millis();

void setup(){
  BiotaSystem.Setup(eBiotaProjectType);
  Serial << endl << LOG0 << "setup() finished, Sketch: " << szSketchName << ", " << szFileDate << endl;
  return;
} //setup


void loop(){
  if (!_bOTA_Started){
    BiotaSystem.Handle();
    //CheckTaskTime("loop(): HandleSystem()");
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


/*
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
*/
//Last line.
