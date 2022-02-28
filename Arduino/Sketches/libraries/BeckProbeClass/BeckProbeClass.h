// BeckProbeClass.h, 2/28/22a
#pragma once
#include <BeckTireTempDefines.h>
#include <BeckTCoupleReaderClass.h>

class BeckProbeClass{
public:
  BeckProbeClass();
  //BeckProbeClass(uint8_t ucCS_Pin);
  virtual ~BeckProbeClass();

  double  Handle          (void);

protected:
  uint16_t    _usDegF_Value     = 0;

  BeckTCoupleReaderClass _oTCoupleReader;
};  //BeckProbeClass
//Last line.
