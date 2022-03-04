// BeckProbeReadingDataClass.h, 3/3/22a
#pragma once
#include <BeckTireTempDefines.h>

enum class  ProbePosition           {Left=1, Center, Right};

class BeckProbeReadingDataClass{
public:
  BeckProbeReadingDataClass           ();
  BeckProbeReadingDataClass           (ProbePosition ePosition);
  virtual ~BeckProbeReadingDataClass  ();


  void            SetPosition             (ProbePosition ePosition);
  ProbePosition   eGetPosition            (void);

  void            SetDegF_Value           (int16_t wNewDegFValue);
  int16_t         wGetDegF_Value          (void);
  bool            bDegFChanged            (void);
  void            SetLastDegF_Value       (int16_t wLastDegFValue);
  int16_t         wGetLastDegF_Value      (void);
protected:
  int16_t         _wDegF_Value          = 0.0;
  int16_t         _wLastDegF_Value      = 0.0;
  bool            _bDegF_FirstTime      = true;
  ProbePosition   _ePosition            = ProbePosition::Left;
};  //BeckProbeReadingDataClass

extern BeckProbeReadingDataClass ProbeReadingData;
//Last line.
