// BeckSampleDataClass.h, 3/14/22b
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

  //void                  FillSampleData        (SampleDataStruct& stSampleData);

  uint32_t              uwGetSampleTime       (int wProbeSetID, int wProbeID);
  void                  SetSampleTime         (int wProbeSetID, int wProbeID, uint32_t uwSampleTime);

  void                  SetDegF               (int wProbeSetID, int wProbeID, float fNewDegFValue);
  float                 fGetDegF              (int wProbeSetID, int wProbeID);

  //void                  SetProbeID            (int8_t cProbeID);
  //int8_t                cGetProbeID           (void);

  void                  SetLastDegF           (int wProbeSetID, int wProbeID, float fLastDegFValue);
  float                 fGetLastDegF          (int wProbeSetID, int wProbeID);

  bool                  bDegFChanged          (int wProbeSetID, int wProbeID);

private:
  int8_t                _cProbeID             = 0;
  int8_t                _cProbeSetID          = 0;
  uint32_t              _uwSampleTime         = 0;    //Also called Epoc time
  float                 _fDegF                = 0.0;
  float                 _fLastDegF            = 0.0;
  bool                  _bDegF_FirstTime      = true;
  bool                  _bDegFChanged         = true;
  SampleDataStruct      _stSampleData;
};  //BeckSampleDataClass

//extern SampleDataStruct           _astSampleData[];
//extern SampleDataStruct    _astSampleData[_wNumProbeSets + 1] [_wNumProbes + 1];
//Last line.
