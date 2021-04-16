const char szFileName[]  = "BeckSystemClass.cpp";
const char szFileDate[]  = "4/15/21b";

#include <BeckSystemClass.h>

SystemClass::SystemClass() {
  Serial << "SystemClass::SystemClass(): " << szFileName << ", " << szFileDate << endl;
} //constructor


SystemClass::~SystemClass() {
  Serial << "~SystemClass(): Destructing" << endl;
} //destructor


void SystemClass::Setup(){
  String szLogString= "SystemClass::Setup(): Begin";
  LogToSerial(szLogString);
  strcpy(szAlexaName, "Larry's Device");

  SystemAlexa.Setup           ((char *)szAlexaName);
  BiotaThermostat.Setup       ();
  SystemThermoDisplay.Setup   ();
  return;
} //Setup


void SystemClass::Handle(){
  SystemAlexa.Handle          ();
  BiotaThermostat.Handle      ();
  SystemThermoDisplay.Handle  ();
  return;
} //Handle
//Last line.
