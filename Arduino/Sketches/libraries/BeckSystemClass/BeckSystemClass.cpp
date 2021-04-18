const char szFileName[]  = "BeckSystemClass.cpp";
const char szFileDate[]  = "4/17/21b";

#include <BeckSystemClass.h>
#include <BeckAlexaClass.h>
#include <BeckBiotaDefines.h>
#include <BeckThermoDisplayClass.h>
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
  //strcpy(szAlexaName, "Larry's Device");

  //SystemAlexa.Setup           ((char *)szAlexaName);
#if DO_ALEXA
    BiotaAlexa.Setup(ALEXA_NAME);
#endif
  //BiotaAlexa.Setup           ((char *)szAlexaName);
  //SystemAlexa.Setup           (pAlexaName);
  BiotaThermostat.Setup       ();
  BiotaDisplay.Setup   ();
  return;
} //Setup


void SystemClass::Handle(){
#if DO_ALEXA
  BiotaAlexa.Handle           ();
#endif
  BiotaThermostat.Handle      ();
  BiotaDisplay.Handle         ();
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
