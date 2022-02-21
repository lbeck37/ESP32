const char szSystemFileName[]  = "BeckTempProbeClass.cpp";
const char szSystemFileDate[]  = "2/21/22b";  //From 5/31/21e

#include <BeckEnviroDataClass.h>
#include <BeckTempProbeClass.h>
#include <Streaming.h>
//#include <Wire.h>

BeckTempProbeClass      TempProbe;       //This is so every module can use the same object


BeckTempProbeClass::BeckTempProbeClass() {
  Serial << "BeckTempProbeClass::BeckTempProbeClass(): " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor


BeckTempProbeClass::~BeckTempProbeClass() {
  Serial << "~BeckTempProbeClass(): Destructing" << endl;
} //destructor


bool BeckTempProbeClass::SetupProbe() {
  Serial << "SetupProbe(): return true" << endl;
  return true;
} //SetupProbe


void BeckTempProbeClass::Setup(void){
  Serial << "BeckTempProbeClass::setup(): Begin" << endl;
  Serial << "setup(): Call SetupProbe()" << endl;
  SetupProbe();
  Serial << "BeckTempProbeClass::Setup(): return" << endl;
return;
} //Setup


void BeckTempProbeClass::Handle(){
  Serial << "ReadProbeTemp(): return" << endl;
  return;
} //Handle


bool BeckTempProbeClass::ReadProbeTemp() {
  //TempAndHumidity   newValues= dht.getTempAndHumidity();
  //float CurrentDegF= ((newValues.temperature) * 1.8) + 32.0;
  //EnviroData.SetDegF_Value  (CurrentDegF);
  //EnviroData.SetRH_Value    (newValues.humidity);
  //Serial.println(" T:" + String(newValues.temperature) + " H:" + String(newValues.humidity) + " I:" + String(heatIndex) + " D:" + String(dewPoint) + " " + comfortStatus);

  Serial << "ReadProbeTemp(): return true" << endl;
  return true;
} //ReadProbeTemp
//Last line.
