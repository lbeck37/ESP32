const char szSystemFileName[]  = "BeckProbesClass.cpp";
const char szSystemFileDate[]  = "2/21/22b";  //From 5/31/21e

#include <BeckEnviroDataClass.h>
#include <BeckProbesClass.h>
#include <Streaming.h>
//#include <Wire.h>

BeckProbesClass      Probes;       //This is so every module can use the same object


BeckProbesClass::BeckProbesClass() {
  Serial << "BeckProbesClass::BeckProbesClass(): " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor


BeckProbesClass::~BeckProbesClass() {
  Serial << "~BeckProbesClass(): Destructing" << endl;
} //destructor


bool BeckProbesClass::SetupProbe() {
  Serial << "SetupProbe(): return true" << endl;
  return true;
} //SetupProbe


void BeckProbesClass::Setup(void){
  Serial << "BeckProbesClass::setup(): Begin" << endl;
  Serial << "setup(): Call SetupProbe()" << endl;
  SetupProbe();
  Serial << "BeckProbesClass::Setup(): return" << endl;
return;
} //Setup


void BeckProbesClass::Handle(){
  Serial << "ReadProbeTemp(): return" << endl;
  return;
} //Handle


bool BeckProbesClass::ReadProbeTemp() {
  //TempAndHumidity   newValues= dht.getTempAndHumidity();
  //float CurrentDegF= ((newValues.temperature) * 1.8) + 32.0;
  //EnviroData.SetDegF_Value  (CurrentDegF);
  //EnviroData.SetRH_Value    (newValues.humidity);
  //Serial.println(" T:" + String(newValues.temperature) + " H:" + String(newValues.humidity) + " I:" + String(heatIndex) + " D:" + String(dewPoint) + " " + comfortStatus);

  Serial << "ReadProbeTemp(): return true" << endl;
  return true;
} //ReadProbeTemp
//Last line.
