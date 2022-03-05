// BeckProbeClass.h, 3/4/22a
#pragma once
#include <BeckSampleDataClass.h>
#include <BeckE32_Defines.h>
#include <BeckTCoupleReaderClass.h>

class BeckProbeClass{
public:
  BeckProbeClass();
  BeckProbeClass(uint8_t ucCS_Pin);
  BeckProbeClass(uint8_t ucCS_Pin, ProbePosition ePosition);
  virtual ~BeckProbeClass();

  double  Handle          (void);

protected:
  ProbePosition           _eProbePosition{ProbePosition::LeftProbe};
  uint16_t                _usDegF_Value{0};
  uint8_t                 _ucCS_Pin{};
  BeckTCoupleReaderClass  _oTCoupleReader{};
};  //BeckProbeClass
//Last line.
