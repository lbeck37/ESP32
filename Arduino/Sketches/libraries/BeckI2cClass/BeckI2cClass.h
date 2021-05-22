// BeckI2cClass.h, 5/21/21a
#pragma once

class I2cClass{
public:
I2cClass();
  virtual ~I2cClass();

  void  Setup             ();
  void  ScanForDevices    ();
protected:
};  //I2cClass

extern I2cClass     I2C_Object;

//Last line.
