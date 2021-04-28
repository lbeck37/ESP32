//BeckBiotaLib.h, "4/27/21a";
#pragma once

#include <BeckI2cLib.h>
#include <BeckLogLib.h>
#include <BeckSystemClass.h>

#if USE_IMU
  #include <BeckMPU9150Lib.h>
#endif

//bool  SetupProjectData    (ProjectType eBiotaProjectType);
bool  SetupProjectData    (void);
//Last line.
