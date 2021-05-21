const char szBeckEnviroDisplayClassFileName[]  = "BeckEnviroDisplayClass.cpp";
const char szEnviroDisplayClassFileDate[]  = "5/21/21a";

#include <BeckEnviroDisplayClass.h>
#include <BeckGasSensorDataClass.h>
#include "Free_Fonts.h"
#include <Streaming.h>

EnviroDisplayClass EnviroDisplay;                   //So every module can use the same object

EnviroDisplayClass::EnviroDisplayClass(void) {
  Serial << "EnviroDisplayClass::EnviroDisplayClass(): Do nothing."  << endl;
} //constructor


EnviroDisplayClass::~EnviroDisplayClass(void) {
  Serial << "~EnviroDisplayClass(): Destructing" << endl;
} //destructor


void EnviroDisplayClass::Setup(void){
  //FillScreen(Gas_BackgroundColor);    //Minimize this, later.
  Serial << "EnviroDisplayClass::Setup(): Call DisplayBegin()" << endl;
  DisplayBegin();
  return;
} //Setup


void EnviroDisplayClass::Handle(void){
 if(millis() >= ulNextGasSensorDisplayMsec){
  ulNextGasSensorDisplayMsec= millis() + ulGasSensorDisplayPeriodMsec;
  //DrawCO2andTVOC();
  int32_t   CO2_Value= GasSensorData.GetCO2_Value();
  int32_t   VOC_Value= GasSensorData.GetVOC_Value();

  //DrawCO2andTVOC_text(CO2_Value, VOC_Value);
  //DrawBar(eCO2Gas, CO2_Value);
  //DrawBar(eVOCGas, VOC_Value);
  VOC_LastValue= CO2_Value;
  }
 return;
} //Handle


//Last line.
