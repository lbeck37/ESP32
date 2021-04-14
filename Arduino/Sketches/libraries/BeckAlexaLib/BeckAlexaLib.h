// BeckAlexaLib.h 4/14/21a
#pragma once

#include <BeckBiotaLib.h>
#include <BeckThermostatClass.h>

extern int            wAlexaHandleCount;
extern bool           _bAlexaChanged;

void SetupAlexa             (char acAlexaName[]);
void HandleAlexa            ();
void DoAlexaCommand         (unsigned char ucDdeviceID, const char* szDeviceName,
                             bool bState, unsigned char ucValue);
//Last line.
