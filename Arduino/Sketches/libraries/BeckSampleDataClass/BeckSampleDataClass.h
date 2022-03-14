// BeckSampleDataClass.h, 3/13/22b
#pragma once
#include <BeckE32_Defines.h>

struct SampleDataStruct{
  int8_t      cProbeID      = 0;
  uint32_t    uwSampleTime  = 0;
  float       fDegF         = 0.00;
  bool        bProbeOK      = true;
};

class BeckSampleDataClass{
public:
  BeckSampleDataClass           ();
  BeckSampleDataClass           (int8_t cProbeID);
  virtual ~BeckSampleDataClass  ();

  void                  FillSampleData        (SampleDataStruct& stSampleData);

  uint32_t              uwGetSampleTime       (void);
  void                  SetSampleTime         (uint32_t uwSampleTime);

  void                  SetDegF_Value         (float fNewDegFValue);
  float                 fGetDegF_Value        (void);

  void                  SetProbeID            (int8_t cProbeID);
  int8_t                cGetProbeID           (void);

  void                  SetLastDegF_Value     (float fLastDegFValue);
  float                 fGetLastDegF_Value    (void);

  bool                  bDegFChanged          (void);

private:
  int8_t                _cProbeID              = 0;
  uint32_t              _uwSampleTime         = 0;    //Also called Epoc time
  float                 _fDegF_Value          = 0.0;
  float                 _fLastDegF_Value      = 0.0;
  bool                  _bDegF_FirstTime      = true;
  bool                  _bDegFChanged         = true;
  SampleDataStruct      _stSampleData;
};  //BeckSampleDataClass

extern BeckSampleDataClass ProbeReadingData;
//Last line.
