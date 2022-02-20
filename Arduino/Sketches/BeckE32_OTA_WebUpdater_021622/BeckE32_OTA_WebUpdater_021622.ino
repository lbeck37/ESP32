// LastMinuteEngineers.com
//Works with ESP32 1.0.6, 2/17/22
const char szSketchName[]  = "BeckE32_OTA_WebUpdater_021622.ino";
const char szFileDate[]    = "2/20/22n"
    "";

#define DO_MAX6675      true
#define DO_MAX31855     true
#define DO_WEBSERVER    true

#if DO_WEBSERVER
  #include <BeckE32_OTALib.h>
#endif

#if DO_MAX6675
  #include <max6675.h>
#endif
#if DO_MAX31855
  #include <MAX31855.h>
#endif

#include <WiFi.h>
#include <Streaming.h>

const char* szRouterName  = "Aspot24b";
const char* szRouterPW    = "Qazqaz11";

const char* szWebHostName = "OTADemo";
const float fLibraryError = 2000.00;

//ESP32
// https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
//static const byte    cSPI_MOSI_Pin    = 23;     // MasterOutSlaveIn is not used, chips are read only
static const byte      cSPI_MISO_Pin    = 19;
static const byte      cSPI_CLK_Pin     = 18;
//static const int       wNumThermos      =  3;
static const int       wNumThermos      =  1;

//static const uint8_t   acSPI_CS_Pin[wNumThermos + 1]= {0, 5, 4, 2};
//static const uint8_t   acSPI_CS_Pin[]       = {0, 5, 4, 2};
static const uint8_t   acSPI_CS_Pin[] {0, 5, 4, 2};

#if DO_MAX31855
MAX31855  MAX31855_Object0(acSPI_CS_Pin[0]);     //Dummy so we can call thermocouples 1, 2 and 3
//MAX31855  MAX31855_Object1(acSPI_CS_Pin[1]);
MAX31855  MAX31855_Object1(acSPI_CS_Pin[3]);      // 2-20-22 Just for test, swapped CS pins with MAX6675
MAX31855  MAX31855_Object2(acSPI_CS_Pin[2]);
MAX31855  MAX31855_Object3(acSPI_CS_Pin[3]);

//MAX31855  aThermos[wNumThermos + 1]= {MAX31855_Object0, MAX31855_Object1, MAX31855_Object2, MAX31855_Object3};
//MAX31855  aThermos[]= {MAX31855_Object0, MAX31855_Object1, MAX31855_Object2, MAX31855_Object3};
MAX31855  aoMAX31855[] {MAX31855_Object0, MAX31855_Object1, MAX31855_Object2, MAX31855_Object3};
#endif

#if DO_MAX6675
//Test SPI bus by connecting a MAX6675 and a MAX31855 on a small BB
//The pin-outs for the two break-out boards are the same except CS and MISO are reversed
//I had to connect red thermo wire to "+" on the MAX6675
//MAX6675   oMAX6675(cSPI_CLK_Pin, acSPI_CS_Pin[3], cSPI_MISO_Pin);
MAX6675   oMAX6675(cSPI_CLK_Pin, acSPI_CS_Pin[1], cSPI_MISO_Pin); // 2/20/22
#endif


void setup(void) {
  Serial.begin(115200);

  Serial << endl << "setup(): Sketch: " << szSketchName << ", " << szFileDate << endl;
  Serial << "setup(): Built for WRover-Kit, SPI MISO(green) on pin " << cSPI_MISO_Pin << ", SPI CLK(orange) on pin " << cSPI_CLK_Pin << endl;

  for (int wThermo= 1; wThermo <= wNumThermos; wThermo++){
    Serial << "setup(): Thermo #" << wThermo << " CS pin is " << acSPI_CS_Pin[wThermo] << endl;
  } //for
#if DO_MAX6675
  Serial << "setup(): Test with MAX6675 in place of Thermo #3 MAX31855, CS and MISO reversed" << endl;
#endif

  // Start WiFi and wait for connection to the network
  WiFi.begin(szRouterName, szRouterPW);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial << endl << "setup(): Connected to " << szRouterName << ", IP address to connect to is " << WiFi.localIP() << endl;

#if DO_MAX31855     //MAX6675 thermocouple reader doesn't have a setup routine
  for (int wThermo= 1; wThermo > wNumThermos; wThermo++){
    aoMAX31855[wThermo].begin();
  } //for

  for (int wThermo= 1; wThermo <= wNumThermos; wThermo++){
    uint16_t usChipID= aoMAX31855[wThermo].getChipID();
    if (usChipID != MAX31855_ID){
      Serial << "loop(): ERROR: Thermocouple Number " << wThermo << " is not connected." << endl;
    }
  } //for
#endif

#if DO_WEBSERVER
  Serial << "setup(): Call SetupWebServer(" << szWebHostName << ")" << endl;
  SetupWebserver(szWebHostName);
#endif
  Serial << "setup(): Done" << endl;
  return;
} //setup


void loop(void) {
  int32_t   wRawData;
  float     afDegreeC[] { 37.00, 37.01, 37.02, 37.03};

#if DO_MAX31855
  for (int wThermo= 1; wThermo <= wNumThermos; wThermo++){
    wRawData= aoMAX31855[wThermo].readRawData();
    afDegreeC[wThermo]= aoMAX31855[wThermo].getTemperature(wRawData);
    if (afDegreeC[wThermo] == fLibraryError){
      Serial << "loop(): ERROR: MAX31855 Thermocouple Number " << wThermo << " is open, shorted or there is a communication error. " << endl;
    }
    else{
      Serial << "loop(): Thermocouple Number " << wThermo << " is at " << afDegreeC[wThermo] << "C" << endl;
    }
  } //for
#endif

#if DO_MAX6675
  double dfMAX6675DegF= oMAX6675.readFahrenheit();
  double dfMAX6675DegC= oMAX6675.readCelsius();
  Serial << "Loop(): MAX6675 Degrees C= " << dfMAX6675DegC << ", F= " << dfMAX6675DegF << endl;
#endif
  delay(1000);

#if DO_WEBSERVER
  HandleOTAWebserver();
#endif
  return;
} //loop
//Last Line.
