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

  SystemAlexa.Setup       ((char *)szAlexaName);
  SystemThermostat.Setup  ();
  return;
} //Setup


void SystemClass::Handle(){
  SystemAlexa.Handle        ();
  SystemThermostat.Handle   ();
  return;
} //Handle
//Last line.