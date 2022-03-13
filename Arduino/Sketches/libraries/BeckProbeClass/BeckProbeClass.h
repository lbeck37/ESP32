// BeckProbeClass.h, 3/13/22b
#pragma once
#include <BeckSampleDataClass.h>
#include <BeckE32_Defines.h>
#include <BeckTCoupleReaderClass.h>

class BeckProbeClass{
public:
  BeckProbeClass();
  BeckProbeClass(int8_t cProbeID, uint8_t ucI2CAddress);
  virtual ~BeckProbeClass();

  void    Begin           (void);
  double  Handle          (void);

protected:
  int8_t                    _cProbeID;          //1, 2, 3 for Left, Center, Right
  uint8_t                   _ucI2CAddress   {0};
  BeckTCoupleReaderClass*   _poTCoupleReader;
  double                    _dfDegF         {0.00};
};  //BeckProbeClass
//Last line.
