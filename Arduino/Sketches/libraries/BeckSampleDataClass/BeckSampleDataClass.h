// BeckSampleDataClass.h, 3/6/22a
#pragma once
#include <BeckE32_Defines.h>

//enum class  ProbePosition           {LeftProbe=1, CenterProbe, RightProbe};

class BeckSampleDataClass{
public:
  BeckSampleDataClass           ();
  BeckSampleDataClass           (ProbePositionEnum eProbePosition, ProbeSetLocationEnum eProbeSetLocation);
  virtual ~BeckSampleDataClass  ();

  void                  FillSampleData        (uint32_t uwSampleTime, float fNewDegFValue);
  uint32_t              uwGetSampleTime       (void);
  void                  SetSampleTime         (uint32_t uwSampleTime);

  void                  SetDegF_Value         (float fNewDegFValue);
  float                 fGetDegF_Value        (void);

  void                  SetProbePosition      (ProbePositionEnum eNewProbePosition);
  ProbePositionEnum     eGetProbePosition     (void);

  void                  SetProbeSetLocation   (ProbeSetLocationEnum ProbeSetLocatio);
  ProbeSetLocationEnum  eGetProbeSetLocation  (void);

  void                  SetLastDegF_Value     (float fLastDegFValue);
  float                 fGetLastDegF_Value    (void);

  bool                  bDegFChanged          (void);

protected:
  uint32_t              _uwSampleTime         =   0;    //Also called Epoc time
  float                 _fDegF_Value          = 0.0;
  float                 _fLastDegF_Value      = 0.0;
  bool                  _bDegF_FirstTime      = true;
  bool                  _bDegFChanged         = true;
  ProbePositionEnum     _eProbePosition;
  ProbeSetLocationEnum  _eProbeSetLocation;
};  //BeckSampleDataClass

extern BeckSampleDataClass ProbeReadingData;
//Last line.
