// BeckSwitchClass.h, 4/24/21b
//#include<BeckPinNumbers.h>

class SwitchClass{
protected:
#if 1
#if ESP32
  const int    sSDA_GPIO             = 21;   //I2C, TTGO pin 21
  const int    sSCL_GPIO             = 22;   //I2C, TTGO pin 22
  const int    sOneWireGPIO          = 32;   //TTGO pin 32
  const int    wHeatSwitchPin        = 37;   //Relay 1, TTGO pin 37
  const int    wThermostatPin        = 38;   //Relay 2, TTGO pin 38
#else
  const int    sAlexaPin             =  2;     //GPIO 2 is D4 and Blue LED on NodeMCU
  const int    sSDA_GPIO             =  4;   //I2C, GPIO 4 is D2 on NodeMCU
  const int    sSCL_GPIO             =  5;   //I2C, GPIO 5 is D1 on NodeMCU and labeled D2
  const int    sOneWireGPIO          = 12;   //GPIO 12 is D6 on NodeMCU
  const int    sHeatSwitchGPIO       = 14;   //GPIO 14 is D5 on NodeMCU
#endif
#endif

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
};  //ThermostatSwitchClass


class HeatSwitchClass : public SwitchClass{
protected:
  //virtual void  SetMyPin(void);
public:
  HeatSwitchClass();
  virtual ~HeatSwitchClass();

  virtual void Setup      (void);
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
