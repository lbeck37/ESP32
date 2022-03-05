// BeckSampleDataClass.h, 3/4/22e
#pragma once
#include <BeckE32_Defines.h>

enum class  ProbePosition           {LeftProbe=1, CenterProbe, RightProbe};

class BeckSampleDataClass{
public:
  BeckSampleDataClass           ();
  virtual ~BeckSampleDataClass  ();

  unsigned long   ulGetSampleTime         (void);
  void            SetSampleTime           (unsigned long ulSampleTime);

  void            SetDegF_Value           (int16_t wNewDegFValue);
  int16_t         wGetDegF_Value          (void);
  bool            bDegFChanged            (void);
  void            SetLastDegF_Value       (int16_t wLastDegFValue);
  int16_t         wGetLastDegF_Value      (void);
protected:
  unsigned long   _ulSampleTime         =   0;    //Also called Epoc time
  int16_t         _wDegF_Value          = 0.0;
  int16_t         _wLastDegF_Value      = 0.0;
  bool            _bDegF_FirstTime      = true;
};  //BeckSampleDataClass

extern BeckSampleDataClass ProbeReadingData;
//Last line.
