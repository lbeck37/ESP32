// BeckSampleDataClass.h, 3/14/22d
#pragma once
#include <BeckE32_Defines.h>

class BeckSampleDataClass{
public:
  BeckSampleDataClass           ();
  BeckSampleDataClass           (int wProbeSetID, int wProbeID);
  virtual ~BeckSampleDataClass  ();

  uint32_t              uwGetSampleTime       (int wProbeSetID, int wProbeID);
  void                  SetSampleTime         (int wProbeSetID, int wProbeID, uint32_t uwSampleTime);

  void                  SetDegF               (int wProbeSetID, int wProbeID, float fNewDegFValue);
  float                 fGetDegF              (int wProbeSetID, int wProbeID);

  void                  SetLastDegF           (int wProbeSetID, int wProbeID, float fLastDegFValue);
  float                 fGetLastDegF          (int wProbeSetID, int wProbeID);

  void                  SetDegFChanged        (int wProbeSetID, int wProbeID);
  bool                  bGetDegFChanged       (int wProbeSetID, int wProbeID);

private:
  int                   _wProbeID             = 0;
  int                   _wProbeSetID          = 0;
  uint32_t              _uwSampleTime         = 0;    //Also called Epoc time
  float                 _fDegF                = 0.0;
  float                 _fLastDegF            = 0.0;
  bool                  _bDegF_FirstTime      = true;
  bool                  _bDegFChanged         = true;
  bool                  _bProbeOK             = true;
};  //BeckSampleDataClass
//Last line.
