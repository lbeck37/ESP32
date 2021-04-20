const char szFileName[]  = "BeckAlexaClass.cpp";
const char szFileDate[]  = "4/19/21a";

#include <BeckAlexaClass.h>
#include <BeckSystemClass.h>
#include <BeckThermostatDataStruct.h>

AlexaClass            BiotaAlexa;

//Prototypes
void    CallbackAlexaCommand    (unsigned char ucDdeviceID,const char* szDeviceName,bool bState,unsigned char ucValue);
void    SetThermostatValues  (bool bState, unsigned char ucValue);

void CallbackAlexaCommand(unsigned char ucDdeviceID,const char* szDeviceName,bool bState,unsigned char ucValue){
  char    szCharString[100];
  sprintf(szCharString, "DoAlexaCommand(): Device #%d (%s) bState: %s value: %d",
      ucDdeviceID, szDeviceName, (bState ? "ON " : "OFF"), ucValue);
  String szLogString= szCharString;
  LogToSerial(szLogString);
  //switch (_eProjectType){
  switch (BiotaSystem.GetProjectType()){
    case eFireplace:
    case eGarage:
    case eThermoDev:
    case eHeater:
      SetThermostatValues(bState, ucValue);
      break;
    case ePitchMeter:
      break;
    case eFrontLights:
      break;
    default:
      Serial << LOG0 << "DoAlexaCommand(): Bad switch, _eProjectType= " << BiotaSystem.GetProjectType() << endl;
      break;
  } //switch
  //bAlexaChanged= true;
  return;
} //CallbackAlexaCommand


void SetThermostatValues(bool bThermostatState, unsigned char ucSetpointValue){
  // ucSetpointValue is a number between 0 and 255 and represents the desired Setpoint
  // in integer Degrees farenheit between 0 and 100. BiotaThermostat stores setpoint as a float
  // The value 100 is the power-up value retained until Alexa is used to set the setpoint.
  int wValuePercent= round(((float)ucSetpointValue / 255.0) * 100);
  Serial << LOG0 << "SetThermostatValues(): Received wValuePercent= " << wValuePercent << endl;
  if(wValuePercent != 100){
    //BiotaThermostat.SetSetpoint((float)wValuePercent);
    ThermostatData.fProposedSetpoint= (float)wValuePercent;
   } //if(wValuePercent==100)
  else{
    //Alexa thinks the setpoint is 100% on power-up until Alexa is used to set the setpoint.
    //Don't do anything and it will continue to use the existing Setpoint.
  } //if(wValuePercent==100)else

  //Tell the thermostat to turn itself on or off.
  //BiotaThermostat.SetThermostatOn(bThermostatState);
  ThermostatData.bThermoOn= bThermostatState;
  return;
} //SetThermostatValues


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

  Serial << LOG0 << "AlexaClass::Setup(): Alexa set up for " << szAlexaName << endl;
  return;
} //SetupAlexa


void AlexaClass::Handle(){
  //wAlexaHandleCount++;  //Track how many times this is called before next handle system (10 sec)
  AlexaDevice.handle();
  return;
} //HandleAlexa
//Last line.
