const char szSystemFileName[]  = "BeckSystemClass.cpp";
const char szSystemFileDate[]  = "4/20/21b";

#include <BeckSystemClass.h>
#include <BeckAlexaClass.h>
#include <BeckBiotaDefines.h>
#include <BeckBiotaLib.h>
#include <BeckDisplayClass.h>
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


void SystemClass::Setup(){
  Serial.begin(lSerialMonitorBaud);
  delay(100);

  String szLogString= "\n\nSystemClass::Setup(): Begin";
  LogToSerial(szLogString);

  Serial << LOG0 << "SystemClass::Setup(): Call SetupProjectData()" << endl;
  SetupProjectData();

  Serial << LOG0 << "SystemClass::Setup(): Call BiotaSwitches.Setup()" << endl;
  BiotaSwitches.Setup();

  Serial << LOG0 << "SystemClass::Setup(): Call BiotaThermostat.Setup()" << endl;
  BiotaThermostat.Setup();

  Serial << LOG0 << "SystemClass::Setup(): Call BiotaDisplay.Setup()" << endl;
  BiotaDisplay.Setup();

  Serial << LOG0 << "SystemClass::Setup(): Call SetupWiFi()" << endl;
  bWiFiOn= SetupWiFi();

#if DO_ALEXA
  BiotaAlexa.Setup(ALEXA_NAME);
#endif
  return;
} //Setup


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
