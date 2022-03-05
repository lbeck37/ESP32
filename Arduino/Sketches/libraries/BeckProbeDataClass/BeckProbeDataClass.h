// BeckProbeDataClass.h, 3/4/22b
#pragma once
#include <BeckTireTempDefines.h>

enum class  ProbePosition           {LeftProbe=1, CenterProbe, RightProbe};

class BeckProbeDataClass{
public:
  BeckProbeDataClass           ();
  BeckProbeDataClass           (ProbePosition ePosition);
  virtual ~BeckProbeDataClass  ();


  void            SetProbePosition        (ProbePosition ePosition);
  ProbePosition   eGetProbePosition       (void);
  uint32_t        uwGetSampleTime         (void);
  void            SetSampleTime           (uint32_t uwSampleTime);

  void            SetDegF_Value           (int16_t wNewDegFValue);
  int16_t         wGetDegF_Value          (void);
  bool            bDegFChanged            (void);
  void            SetLastDegF_Value       (int16_t wLastDegFValue);
  int16_t         wGetLastDegF_Value      (void);
protected:
  uint32_t        _uwSampleTime         =   0;    //Also called Epoc time
  int16_t         _wDegF_Value          = 0.0;
  int16_t         _wLastDegF_Value      = 0.0;
  bool            _bDegF_FirstTime      = true;
  ProbePosition   _eProbePosition       = ProbePosition::LeftProbe;
};  //BeckProbeDataClass

extern BeckProbeDataClass ProbeReadingData;
//Last line.
