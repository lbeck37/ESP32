const char szFileName[]  = "BeckAlexaClass.cpp";
const char szFileDate[]  = "4/15/21b";

#include <BeckAlexaClass.h>
#include <BeckBiotaLib.h>
#include <BeckThermoDataClass.h>

AlexaClass        SystemAlexa;

//Prototypes
void    CallbackAlexaCommand    (unsigned char ucDdeviceID,const char* szDeviceName,bool bState,unsigned char ucValue);
void    HandleThermostat  (bool bState, unsigned char ucValue);
//void  HandleThermostatProject (bool bState, unsigned char ucValue);


void CallbackAlexaCommand(unsigned char ucDdeviceID,const char* szDeviceName,bool bState,unsigned char ucValue){
  char    szCharString[100];
  sprintf(szCharString, "DoAlexaCommand(): Device #%d (%s) bState: %s value: %d",
      ucDdeviceID, szDeviceName, (bState ? "ON " : "OFF"), ucValue);
  String szLogString= szCharString;
  LogToSerial(szLogString);
  switch (_eProjectType){
    case eFireplace:
    case eGarage:
    case eThermoDev:
    case eHeater:
      HandleThermostat(bState, ucValue);
      break;
    case ePitchMeter:
      break;
    case eFrontLights:
      break;
    default:
      Serial << LOG0 << "DoAlexaCommand(): Bad switch, _eProjectType= " << _eProjectType << endl;
      break;
  } //switch
  //bAlexaChanged= true;
  return;
} //CallbackAlexaCommand


//void AlexaClass::HandleThermostatProject(bool bState, unsigned char ucValue){
void HandleThermostat(bool bState, unsigned char ucValue){
  int wValuePercent= round(((float)ucValue / 255.0) * 100);
  Serial << LOG0 << "HandleThermostat(): Received wValuePercent= " << wValuePercent << endl;
  //LastThermostatOnState= bState;
  //SetThermoSwitch(bState);
  if(wValuePercent == 100){
    //Alexa thinks the setpoint is 100% on power-up until Alexa is used to set the setpoint.
    //Don't do anything and it will continue to use the existing Setpoint.
    //fSetThermoSetpoint(_fSetpointF);
  } //if(wValuePercent==100)
  else{
    //fSetThermoSetpoint(ucValue);
    //ThermostatObject.Set_Setpoint(ucValue);
    //BiotaThermostat.Set_Setpoint(ucValue);
    //_fSetpoint= round( ((float)ucValue / 255.0) * 100.0);
    SystemAlexa.SetLastSetpoint(round( ((float)ucValue / 255.0) * 100.0));
  } //if(wValuePercent==100)else
  //_bThermostatOn= bState;
  SystemAlexa.SetLastThermostatOnState(bState);
  return;
} //HandleThermostatProject


AlexaClass::AlexaClass() {
  Serial << "AlexaClass::AlexaClass(): " << szFileName << ", " << szFileDate << endl;
} //constructor


AlexaClass::~AlexaClass() {
  Serial << "~AlexaClass(): Destructing" << endl;
} //destructor


void AlexaClass::Setup(char szAlexaName[]){
  String szLogString= "AlexaClass::Setup(): Begin";
  LogToSerial(szLogString);

  // You have to call enable(true) once you have a WiFi connection
  // You can enable or disable the library at any moment
  // Disabling it will prevent the devices from being discovered and switched
  //Beck 12/3/18 I don't know why we do enable, disable, enable but it is necessary
  AlexaDevice.enable(true);
  AlexaDevice.enable(false);
  AlexaDevice.enable(true);

  // You can use different ways to invoke Alexa to modify the devices state:
  // "Alexa, turn light one on" ("light one" is the name of the first device below)
  // "Alexa, turn on light one"
  // "Alexa, set light one to fifty" (50 means 50% of brightness)

  // Add virtual devices
  AlexaDevice.addDevice(szAlexaName);

  //Define the callback
  AlexaDevice.onSetState([](unsigned char device_id, const char *device_name, bool state, unsigned char value)
    {
    CallbackAlexaCommand(device_id, device_name, state, value);
    } );  //AlexaClass.onSetState

  Serial << LOG0 << "SetupAlexa(): Alexa set up for " << szAlexaName << endl;
  return;
} //SetupAlexa


void AlexaClass::Handle(){
  wAlexaHandleCount++;  //Track how many times this is called before next handle system (10 sec)
  AlexaDevice.handle();
  return;
} //HandleAlexa


void AlexaClass::SetLastThermostatOnState(bool bNewThermostatOnState){
  LastThermostatOnState= bNewThermostatOnState;
}


void AlexaClass::SetLastSetpoint(float fNewSetpoint){
  LastSetpoint= fNewSetpoint;
  return;
}


bool AlexaClass::GetLastThermostatOnState(){
  return(LastThermostatOnState);
}


float AlexaClass::GetLastSetpoint(){
  return(LastSetpoint);
}
//Last line.
