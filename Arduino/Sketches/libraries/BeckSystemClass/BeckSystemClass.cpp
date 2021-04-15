const char szFileName[]  = "BeckSystemClass.cpp";
const char szFileDate[]  = "4/15/21a";

#include <BeckSystemClass.h>

System::System() {
  Serial << "System::System(): " << szFileName << ", " << szFileDate << endl;
} //constructor


System::~System() {
  Serial << "~System(): Destructing" << endl;
} //destructor


void System::Setup(){
  String szLogString= "System::Setup(): Begin";
  LogToSerial(szLogString);
  return;
} //SetupAlexa


void System::Handle(){
  //wAlexaHandleCount++;  //Track how many times this is called before next handle system (10 sec)
  SystemAlexa.Handle();
  return;
} //HandleAlexa
