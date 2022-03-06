// BeckProbeClass.h, 3/5/22b
#pragma once
#include <BeckSampleDataClass.h>
#include <BeckE32_Defines.h>
#include <BeckTCoupleReaderClass.h>

class BeckProbeClass{
public:
  BeckProbeClass();
  BeckProbeClass(int8_t cCS_Pin);
  BeckProbeClass(int8_t cCS_Pin, ProbePosition ePosition);

  BeckProbeClass(uint8_t ucI2CAddress);
  BeckProbeClass(uint8_t ucI2CAddress, ProbePosition ePosition);
  virtual ~BeckProbeClass();

  void    Begin           (void);
  double  Handle          (void);

protected:
  ProbePosition           _eProbePosition{ProbePosition::LeftProbe};
  uint16_t                _usDegF_Value{0};
  int8_t                  _cCS_Pin;
  uint8_t                 _ucI2CAddress;
  BeckTCoupleReaderClass  _oTCoupleReader;
};  //BeckProbeClass
//Last line.
