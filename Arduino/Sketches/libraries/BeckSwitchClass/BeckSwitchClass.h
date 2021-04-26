// BeckSwitchClass.h, 4/26/21b
#include<BeckPinNumbers.h>

class SwitchClass{
protected:
  bool  bMyState;
  bool  bMyLastState;
  bool  bMyPinIsInverted;
  int   wMyPinNumber;

protected:
  virtual void  SetPin  (void){}
  //virtual void  SetHeatPin        (void);

public:
  SwitchClass();
  virtual ~SwitchClass();

  virtual void Setup    (void);
  virtual void Handle   (void){}
};  //SwitchClass


class ThermostatSwitchClass : public SwitchClass{
protected:
  virtual void  SetPin  (void);
public:
  ThermostatSwitchClass();
  virtual ~ThermostatSwitchClass();

  virtual void Setup    (void);
  virtual void Handle   (void);
};  //ThermostatSwitchClass


class HeatSwitchClass : public SwitchClass{
protected:
  virtual void  SetPin  (void);
public:
  HeatSwitchClass();
  virtual ~HeatSwitchClass();

  virtual void Setup    (void);
  virtual void Handle   (void);
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
