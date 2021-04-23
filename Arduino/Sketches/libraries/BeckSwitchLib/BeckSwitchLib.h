// BeckSwitchLib.h 4/8/21a
#pragma once
//#include <BeckMiniLib.h>

#if ESP32
static const int    sSDA_GPIO             = 21;   //I2C, TTGO pin 21
static const int    sSCL_GPIO             = 22;   //I2C, TTGO pin 22
static const int    sOneWireGPIO          = 32;   //TTGO pin 32
static const int    sHeatSwitchGPIO       = 37;   //Relay 1, TTGO pin 37
static const int    sAlexaPin             = 38;   //Relay 2, TTGO pin 38
#else
static const int    sAlexaPin             =  2;     //GPIO 2 is D4 and Blue LED on NodeMCU
static const int    sSDA_GPIO             =  4;   //I2C, GPIO 4 is D2 on NodeMCU
static const int    sSCL_GPIO             =  5;   //I2C, GPIO 5 is D1 on NodeMCU and labeled D2
static const int    sOneWireGPIO          = 12;   //GPIO 12 is D6 on NodeMCU
static const int    sHeatSwitchGPIO       = 14;   //GPIO 14 is D5 on NodeMCU
#endif

static const int    sSwitchOpen           = 0;
static const int    sSwitchClosed         = 1;
static const int    sOff                  = 0;
static const int    sOn                   = 1;
static const int    sNotInit              = -3737;
static const int    sNoSwitch             = -1;
static const int    sNumSwitches          = 2;
static const int    sHeatSwitchNum        = 1;      //Switch number that turns Heat on and off.
static const int    sThermoSwitchNum      = 2;      //Switch number that turns Thermostat on and off.
static const int    sThermoDummySwitch    = 0;      //Thermostat Blynk LED lives at unused switch #0.
static const int    asSwitchPin[]         = {-1, sHeatSwitchGPIO, sAlexaPin, sNoSwitch, sNoSwitch};    //0 is not a switch, switches are at 1,2,3,4
static const bool   abSwitchInverted[]    = {0, true, true, true, true};  //Opto-isolated relays close when pulled low.

extern int          asSwitchState[];
extern int          asSwitchLastState[];

void  SetupSwitches     ();
void  SetHeatSwitch     (int sSwitchState);
void  SetThermoSwitch   (int sSwitchState);
void  SetSwitch         (int sSwitch, int sSwitchState);

//Last line
