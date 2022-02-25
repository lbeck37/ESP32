// BeckProbeClass.h, 2/22/22d
#pragma once
#include <BeckBiotaDefines.h>
#include <max6675.h>

class BeckProbeClass{
public:
  BeckProbeClass();
  BeckProbeClass(byte cSPI_MISO_Pin, byte cSPI_CLK_Pin, uint8_t ucCS_Pin);
  virtual ~BeckProbeClass();

  double  Handle          (void);

protected:
//  MAX6675     _oMAX6675_Thermocouple;
  MAX6675     *_poMAX6675_Thermocouple;
  byte        _cSPI_MISO_Pin    = 0;
  byte        _cSPI_CLK_Pin     = 0;
  uint8_t     _ucSPI_CS_Pin     = 0;
  uint16_t    _usDegF_Value     = 0;
};  //BeckProbeClass

//Last line.
