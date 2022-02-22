const char szSystemFileName[]  = "BeckProbeSetClass.cpp";
const char szSystemFileDate[]  = "2/22/22b";  //From 5/31/21e

#include <BeckProbeSetClass.h>
//#include <BeckEnviroDataClass.h>
#include <BeckProbeClass.h>
#include <max6675.h>
#include <Streaming.h>
//#include <Wire.h>

BeckProbeSetClass      ProbeSet;       //This is so every module can use the same object

//ESP32
// https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
//static const byte    cSPI_MOSI_Pin    = 23;     // MasterOutSlaveIn is not used, chips are read only

byte      _cSPI_MISO_Pin;
byte      _cSPI_CLK_Pin;
int       _wNumProbes;

uint8_t   _acSPI_CS_Pin[4];

/*
BeckProbeClass   oBeckProbe0(cSPI_CLK_Pin, acSPI_CS_Pin[3], cSPI_MISO_Pin);
BeckProbeClass   oBeckProbe1(cSPI_CLK_Pin, acSPI_CS_Pin[3], cSPI_MISO_Pin);
BeckProbeClass   oBeckProbe2(cSPI_CLK_Pin, acSPI_CS_Pin[3], cSPI_MISO_Pin);
BeckProbeClass   oBeckProbe3(cSPI_CLK_Pin, acSPI_CS_Pin[3], cSPI_MISO_Pin);
*/

BeckProbeClass  _aoProbes[];


BeckProbeSetClass::BeckProbeSetClass() {
  Serial << "BeckProbeSetClass::BeckProbeSetClass(): " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor


BeckProbeSetClass::BeckProbeSetClass(BeckProbeClass aoProbes[4]){
  _wNumProbes     = sizeof(aoProbes)/sizeof(aoProbes[0]);
  Serial << "BeckProbeSetClass::BeckProbeSetClass(...): NumProbes= " << _wNumProbes << endl;
} //constructor


BeckProbeSetClass::~BeckProbeSetClass() {
  Serial << "~BeckProbeSetClass(): Destructing" << endl;
} //destructor


/*
bool BeckProbeSetClass::SetupProbe() {
  Serial << "SetupProbe(): return true" << endl;
  return true;
} //SetupProbe
*/


bool BeckProbeSetClass::Setup(void){
  bool    bReturn= true;
  Serial << "BeckProbeSetClass::setup(): Begin" << endl;
  //Serial << "setup(): Call SetupProbe()" << endl;
  for (int wProbe= 1; wProbe <= _wNumProbes; wProbe++){
  }
  //SetupProbe();
  Serial << "BeckProbeSetClass::Setup(): return " << bReturn << endl;
  return bReturn;
} //Setup


bool BeckProbeSetClass::Handle(){
  bool    bReturn= true;
  double adMAX6675DegF[4];

  for (int wProbe= 1; wProbe <= _wNumProbes; wProbe++){
    double dfMAX6675DegC= aoMAX6675[wProbe].readCelsius();
    double dfMAX6675DegF= aoMAX6675[wProbe].readFahrenheit();
    adMAX6675DegF[wThermo]= dfMAX6675DegF;
    //Serial << "loop(): Thermocouple Number " << wThermo << " is at " << dfMAX6675DegF << "F" << ", " << dfMAX6675DegC << "C" << endl;
   }
  Serial << "BeckProbeSetClass::Handle(): " << endl <<
      "    Thermo #1= " << adMAX6675DegF[1] << "F, #2= " << adMAX6675DegF[2] << "F, #3=" << adMAX6675DegF[3] << endl;

  Serial << "BeckProbeSetClass::Handle(): return " << bReturn << endl;
  return bReturn;
} //Handle


/*
bool BeckProbeSetClass::ReadProbeTemp() {
  //TempAndHumidity   newValues= dht.getTempAndHumidity();
  //float CurrentDegF= ((newValues.temperature) * 1.8) + 32.0;
  //EnviroData.SetDegF_Value  (CurrentDegF);
  //EnviroData.SetRH_Value    (newValues.humidity);
  //Serial.println(" T:" + String(newValues.temperature) + " H:" + String(newValues.humidity) + " I:" + String(heatIndex) + " D:" + String(dewPoint) + " " + comfortStatus);

  Serial << "ReadProbeTemp(): return true" << endl;
  return true;
} //ReadProbeTemp
*/
//Last line.
