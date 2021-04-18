//BeckBiotaLib.h, "4/16/21b";   //was 3/29/21b, was 12/28/19a
#pragma once

#include <BeckI2cLib.h>
#include <BeckLogLib.h>

#if USE_IMU
  #include <BeckMPU9150Lib.h>
#endif

bool  SetupSystem           (void);
//Last line.
