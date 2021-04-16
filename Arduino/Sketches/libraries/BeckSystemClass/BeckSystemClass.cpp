const char szFileName[]  = "BeckSystemClass.cpp";
const char szFileDate[]  = "4/16/21b";

#include <BeckSystemClass.h>

//These are from BeckThermoLib.cpp
float           _fMaxHeatRangeF       = 0.10;   //Temp above setpoint before heat is turned off
float           _fLastDegF            = 37.01;  //Last temperature reading.
float           _fSetpointF           = 70.0;
float           _fMinSetpoint         = 32.0;
float           _fMaxSetpoint         = 80.0;
float           _fThermoOffDegF       = _fSetpointF + _fMaxHeatRangeF;
int             sThermoTimesCount     = 0;      //Number of times temperature out of range
bool            _bThermoOn;             //Whether thermostat is running, set in BeckBiotaLib
bool            _bHeatOn              = true;  //If switch is on to turn on Heat.

SystemClass        BiotaSystem;       //This is so every module can use the same object

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
  SystemAlexa.Setup           ((char *)_acAlexaName);
  //SystemAlexa.Setup           (pAlexaName);
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
