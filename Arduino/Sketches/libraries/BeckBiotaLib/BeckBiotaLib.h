//BeckBiotaLib.h, "4/19/21a";
#pragma once

#include <BeckI2cLib.h>
#include <BeckLogLib.h>

#if USE_IMU
  #include <BeckMPU9150Lib.h>
#endif

bool  SetupProjectData    (void);
//Last line.
