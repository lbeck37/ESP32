// BeckProbeClass.h, 2/27/22d
#pragma once
#include <BeckTireTempDefines.h>
#include <BeckTCoupleReaderClass.h>
//#include <max6675.h>

class BeckProbeClass{
public:
  BeckProbeClass();
  //BeckProbeClass(uint8_t ucCS_Pin);
  BeckProbeClass(MAX6675& oMAX6675);
  virtual ~BeckProbeClass();

  double  Handle          (void);

protected:
  uint16_t    _usDegF_Value     = 0;

  //static BeckTCoupleReaderClass _oTCoupleReader;
  BeckTCoupleReaderClass _oTCoupleReader;
};  //BeckProbeClass

//Last line.
