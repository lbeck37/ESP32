// BeckI2cClass.h, 3/5/22a
#pragma once

class BeckI2cClass{
public:
BeckI2cClass();
  virtual ~BeckI2cClass();

  void  Setup             ();
  void  ScanForDevices    ();
protected:
};  //BeckI2cClass

extern BeckI2cClass     _oBeckI2C;

//Last line.
