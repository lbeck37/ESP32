// BeckSwitchClass.h, 4/22/21b

class SwitchClass{
protected:
#if ESP32
  const int    sSDA_GPIO             = 21;   //I2C, TTGO pin 21
  const int    sSCL_GPIO             = 22;   //I2C, TTGO pin 22
  const int    sOneWireGPIO          = 32;   //TTGO pin 32
  //const int    sAlexaPin             = 38;   //Relay 2, TTGO pin 38
  const int    wThermostatPin        = 38;   //Relay 2, TTGO pin 38
  const int    wHeatSwitchPin        = 37;   //Relay 1, TTGO pin 37
#else
  const int    sAlexaPin             =  2;     //GPIO 2 is D4 and Blue LED on NodeMCU
  const int    sSDA_GPIO             =  4;   //I2C, GPIO 4 is D2 on NodeMCU
  const int    sSCL_GPIO             =  5;   //I2C, GPIO 5 is D1 on NodeMCU and labeled D2
  const int    sOneWireGPIO          = 12;   //GPIO 12 is D6 on NodeMCU
  const int    sHeatSwitchGPIO       = 14;   //GPIO 14 is D5 on NodeMCU
#endif

  const int    sSwitchOpen           = 0;
  const int    sSwitchClosed         = 1;
  const int    sOff                  = 0;
  const int    sOn                   = 1;
  const int    sNotInit              = -3737;
  const int    sNoSwitch             = -1;
  const int    sNumSwitches          = 2;
  const int    sHeatSwitchNum        = 1;      //Switch number that turns Heat on and off.
  const int    sThermoSwitchNum      = 2;      //Switch number that turns Thermostat on and off.
  const int    sThermoDummySwitch    = 0;      //Thermostat Blynk LED lives at unused switch #0.
  //const int    asSwitchPin[]         = {-1, sHeatSwitchGPIO, sAlexaPin, sNoSwitch, sNoSwitch};    //0 is not a switch, switches are at 1,2,3,4
  //const bool   abSwitchInverted[]    = {0, true, true, true, true};  //Opto-isolated relays close when pulled low.

  //extern int          asSwitchState[];
  //extern int          asSwitchLastState[];
  bool  bMyState;
  bool  bMyLastState;
  bool  bMyPinIsInverted;
  int   wMyPinNumber;

protected:
  virtual void  SetMyPin(void);

public:
  SwitchClass();
  virtual ~SwitchClass();

  virtual void Setup    (void);
  virtual void Handle   (void);
};  //SwitchClass


class ThermostatSwitchClass : public SwitchClass{
protected:
public:
  ThermostatSwitchClass();
  virtual ~ThermostatSwitchClass();

  virtual void Setup      (void);
  virtual void Handle     (void);
};  //ThermostatSwitchClass


class HeatSwitchClass : public SwitchClass{
protected:
  //virtual void  SetMyPin(void);
public:
  HeatSwitchClass();
  virtual ~HeatSwitchClass();

  virtual void Setup      (void);
  virtual void Handle     (void);
};  //HeatSwitchClass


class SwitchesClass{
protected:
  HeatSwitchClass         HeatSwitch;
  ThermostatSwitchClass   ThermostatSwitch;
public:
  SwitchesClass();
  virtual ~SwitchesClass();

  virtual void Setup    (void);
  virtual void Handle   (void);
};  //SwitchesClass

extern SwitchesClass       BiotaSwitches;

//Last line.
