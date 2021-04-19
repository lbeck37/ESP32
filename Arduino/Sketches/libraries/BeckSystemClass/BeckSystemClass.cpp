const char szFileName[]  = "BeckSystemClass.cpp";
const char szFileDate[]  = "4/18/21a";

#include <BeckSystemClass.h>
#include <BeckAlexaClass.h>
#include <BeckBiotaDefines.h>
#include <BeckDisplayClass.h>
//#include <BeckThermoDisplayClass.h>
#include <BeckThermostatClass.h>
#include <Streaming.h>

SystemClass           BiotaSystem;       //This is so every module can use the same object

SystemClass::SystemClass() {
  Serial << "SystemClass::SystemClass(): " << szFileName << ", " << szFileDate << endl;
} //constructor


SystemClass::~SystemClass() {
  Serial << "~SystemClass(): Destructing" << endl;
} //destructor


void SystemClass::Setup(){
  String szLogString= "SystemClass::Setup(): Begin";
  LogToSerial(szLogString);
  Serial << LOG0 << "SystemClass::Setup(): Begin" << endl;
  //strcpy(szAlexaName, "Larry's Device");
  //SystemAlexa.Setup           ((char *)szAlexaName);
#if DO_ALEXA
  Serial << LOG0 << "SystemClass::Setup(): Call BiotaAlexa.Setup(ALEXA_NAME)" << endl;
  BiotaAlexa.Setup(ALEXA_NAME);
#endif
  Serial << LOG0 << "SystemClass::Setup(): Call BiotaThermostat.Setup()" << endl;
  BiotaThermostat.Setup();
  Serial << LOG0 << "SystemClass::Setup(): Call BiotaDisplay.Setup()" << endl;
  BiotaDisplay.Setup();
  return;
} //Setup


void SystemClass::Handle(){
#if DO_ALEXA
  BiotaAlexa.Handle();
#endif
  BiotaThermostat.Handle();
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
