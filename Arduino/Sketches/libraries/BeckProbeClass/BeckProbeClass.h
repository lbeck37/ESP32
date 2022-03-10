// BeckProbeClass.h, 3/10/22a
#pragma once
#include <BeckSampleDataClass.h>
#include <BeckE32_Defines.h>
#include <BeckTCoupleReaderClass.h>

class BeckProbeClass{
public:
  BeckProbeClass();
  BeckProbeClass(uint8_t ucI2CAddress);
  BeckProbeClass(uint8_t ucI2CAddress, ProbePositionEnum ePosition);
  virtual ~BeckProbeClass();

  void    Begin           (void);
  double  Handle          (void);

protected:
  ProbePositionEnum         _eProbePosition {ProbePositionEnum::LeftProbe};
  double                    _dfDegF         {0.00};
  uint8_t                   _ucI2CAddress   {0};
  //BeckTCoupleReaderClass  _oTCoupleReader;
  BeckTCoupleReaderClass*   _poTCoupleReader;
};  //BeckProbeClass
//Last line.
