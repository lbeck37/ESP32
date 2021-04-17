const char szFileName[]  = "BeckSystemClass.cpp";
const char szFileDate[]  = "4/16/21b";

#include <BeckSystemClass.h>
#include <BeckAlexaClass.h>
#include <BeckDisplayClass.h>

SystemClass           BiotaSystem;       //This is so every module can use the same object
AlexaClass            BiotaAlexa;
//ThermoDisplayClass    BiotaDisplay;       //This is so every module can use the same object
//ThermostatClass       BiotaThermostat;

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
  BiotaAlexa.Setup           ((char *)szAlexaName);
  //SystemAlexa.Setup           (pAlexaName);
  BiotaThermostat.Setup       ();
  BiotaDisplay.Setup   ();
  return;
} //Setup


void SystemClass::Handle(){
  BiotaAlexa.Handle          ();
  BiotaThermostat.Handle      ();
  BiotaDisplay.Handle  ();
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
