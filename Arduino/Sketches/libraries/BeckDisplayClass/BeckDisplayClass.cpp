const char szDisplayClassFileName[]  = "BeckDisplayClass.cpp";
const char szDisplayClassFileDate[]  = "5/17/21c";

#include <BeckDisplayClass.h>
#include <BeckThermostatDataClass.h>
#include "Free_Fonts.h"
#include <Streaming.h>

//Scalable fonts created by Font Creator, http://oleddisplay.squix.ch/#/home
#ifdef REDRESSED__REGULAR_20
  #include <Redressed_Regular_20.h>
#endif
#ifdef ROBOTO_CONDENSED_30
  #include <Roboto_Condensed_30.h>
#endif
#ifdef ROBOTO_MEDIUM_40
  #include <Roboto_Medium_40.h>
#endif
#ifdef LATO_BLACK_60
  #include <Lato_Black_60.h>
#endif
#ifdef MONOSPACED_BOLD_30
  #include <Monospaced_Bold_30.h>
#endif
#ifdef MONOSPACED_BOLD_60
  #include <Monospaced_Bold_60.h>
#endif
#ifdef ROBOTO_MEDIUM_100
  #include <Roboto_Medium_100.h>
#endif
#ifdef ROBOTO_CONDENSED_130
  #include <Roboto_Condensed_130.h>
#endif
#ifdef ROBOTO_CONDENSED_BOLD_130
  #include <Roboto_Condensed_Bold_130.h>
#endif
#ifdef ROBOTO_MEDIUM_150
  #include <Roboto_Medium_150.h>
#endif

DisplayClass::DisplayClass() {
  Serial << "Display::Display(): " << szDisplayClassFileName << ", " << szDisplayClassFileDate << endl;
} //constructor

DisplayClass::~DisplayClass() {
  Serial << "~Display(): Destructing" << endl;
} //destructor

//Last line.
