// BeckProbeClass.h, 3/14/22b
#pragma once
#include <BeckSampleDataClass.h>
#include <BeckE32_Defines.h>
#include <BeckTCoupleReaderClass.h>

class BeckProbeClass{
public:
  BeckProbeClass();
  BeckProbeClass(int8_t cProbeID, uint8_t ucI2CAddress);
  virtual ~BeckProbeClass();

  void    Begin           ();
  void    Handle          (uint32_t uwSampleTime, int8_t cProbeID);
  //float   fGetDegF        ();

private:
  int8_t                    _cProbeID;
  uint8_t                   _ucI2CAddress     {0};
  //SampleDataStruct          _stSampleData;
  BeckTCoupleReaderClass*   _poTCoupleReader  {nullptr};
};  //BeckProbeClass
//Last line.
