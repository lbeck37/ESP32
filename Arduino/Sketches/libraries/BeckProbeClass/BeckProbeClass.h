// BeckProbeClass.h, 2/27/22b
#pragma once
#include <BeckTireTempDefines.h>
#include <BeckTCoupleReaderClass.h>
//#include <max6675.h>

class BeckProbeClass{
public:
  BeckProbeClass();
  BeckProbeClass(uint8_t ucCS_Pin);
  virtual ~BeckProbeClass();

  double  Handle          (void);

protected:
  uint16_t    _usDegF_Value     = 0;

  BeckTCoupleReaderClass _oTCoupleReader;
};  //BeckProbeClass

//Last line.
