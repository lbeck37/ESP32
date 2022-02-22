const char szSystemFileName[]  = "BeckProbeClass.cpp";
const char szSystemFileDate[]  = "2/22/22c";  //From 5/31/21e

#include <BeckEnviroDataClass.h>
#include <BeckProbeClass.h>
#include <max6675.h>
#include <Streaming.h>
//#include <Wire.h>

BeckProbeClass      ProbeSet;       //This is so every module can use the same object

//ESP32
// https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
//static const byte    cSPI_MOSI_Pin    = 23;     // MasterOutSlaveIn is not used, chips are read only
byte      _cSPI_MISO_Pin    = 19;
byte      _cSPI_CLK_Pin     = 18;

static const uint8_t   acSPI_CS_Pin[] {0, 2, 4, 5};

//I had to connect red thermo wire to "+" on the MAX6675
MAX6675   oMAX6675_Obj0(cSPI_CLK_Pin, acSPI_CS_Pin[0], cSPI_MISO_Pin);
MAX6675   oMAX6675_Obj1(cSPI_CLK_Pin, acSPI_CS_Pin[1], cSPI_MISO_Pin);
MAX6675   oMAX6675_Obj2(cSPI_CLK_Pin, acSPI_CS_Pin[2], cSPI_MISO_Pin);
MAX6675   oMAX6675_Obj3(cSPI_CLK_Pin, acSPI_CS_Pin[3], cSPI_MISO_Pin);

MAX6675  aoMAX6675[] {oMAX6675_Obj0, oMAX6675_Obj1, oMAX6675_Obj2, oMAX6675_Obj3};


BeckProbeClass::BeckProbeClass() {
  Serial << "BeckProbeClass::BeckProbeClass(): " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor


BeckProbeClass::BeckProbeClass(byte cSPI_MISO_Pin, byte cSPI_CLK_Pin, uint8_t ucCS_Pin, int wNumProbes, BeckProbeClass aoProbe[]){
  _cSPI_MISO_Pin  = cSPI_MISO_Pin;
  _cSPI_CLK_Pin   = cSPI_CLK_Pin;
  Serial << "BeckProbeClass::BeckProbeClass(): " << szSystemFileName << ", " << szSystemFileDate << endl;
} //constructor


BeckProbeClass::~BeckProbeClass() {
  Serial << "~BeckProbeClass(): Destructing" << endl;
} //destructor


void BeckProbeClass::Setup(void){
  Serial << "BeckProbeClass::setup(): Begin" << endl;
  Serial << "setup(): Call SetupProbe()" << endl;
  Serial << "BeckProbeClass::Setup(): return" << endl;
return;
} //Setup


void BeckProbeClass::Handle(){
/*
  double adMAX6675DegF[4];
  for (int wProbe= 1; wProbe <= wNumThermos; wProbe++){
    double dfMAX6675DegC= aoMAX6675[wProbe].readCelsius();
    double dfMAX6675DegF= aoMAX6675[wProbe].readFahrenheit();
    adMAX6675DegF[wThermo]= dfMAX6675DegF;
    //Serial << "loop(): Thermocouple Number " << wThermo << " is at " << dfMAX6675DegF << "F" << ", " << dfMAX6675DegC << "C" << endl;
   }
  double dfMAX6675DegC= aoMAX6675[wProbe].readCelsius();
  double dfMAX6675DegF= aoMAX6675[wProbe].readFahrenheit();

  Serial << "BeckProbeClass::Handle(): " << endl <<
      "    Thermo #1= " << adMAX6675DegF[1] << "F, #2= " << adMAX6675DegF[2] << "F, #3=" << adMAX6675DegF[3] << endl;

*/

  Serial << "BeckProbeClass::Handle(): return" << endl;
  return;
} //Handle


/*
bool BeckProbeClass::ReadProbe() {
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
