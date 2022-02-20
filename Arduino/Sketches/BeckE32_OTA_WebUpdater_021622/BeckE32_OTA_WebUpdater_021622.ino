// LastMinuteEngineers.com
//Works with ESP32 1.0.6, 2/17/22
const char szSketchName[]  = "BeckE32_OTA_WebUpdater_021622.ino";
const char szFileDate[]    = "2/19/22b";

#define DO_MAX6675      false
#define DO_MAX31855     true
#define DO_WEBSERVER    true

#if DO_WEBSERVER
  #include <BeckE32_OTALib.h>
#endif

//#if DO_TEMP
  #if DO_MAX6675
    #include <max6675.h>
  #endif
  #if DO_MAX31855
    #include <MAX31855.h>
  #endif
//#endif

#include <WiFi.h>
#include <Streaming.h>

const char* szRouterName  = "Aspot24b";
const char* szRouterPW    = "Qazqaz11";

const char* szWebHostName = "OTADemo";

//ESP32
// https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
static const byte      cSPI_MISO_Pin         = 19;
static const byte      cSPI_MOSI_Pin         = 23;
static const byte      cSPI_CLK_Pin          = 18;
/*
static const byte      cSPI_CS_Thermo1Pin    =  5;
static const byte      cSPI_CS_Thermo2Pin    =  4;
static const byte      cSPI_CS_Thermo3Pin    =  2;
*/
static const int      wNumberOfThermos      = 3;
static uint8_t   acSPI_CS_Pins[wNumberOfThermos + 1]= {0, 5, 4, 2};

#if DO_MAX31855
MAX31855  MAX31855_Object0(acSPI_CS_Pins[0]);     //Dummy so we can call thermocouples 1, 2 and 3
MAX31855  MAX31855_Object1(acSPI_CS_Pins[1]);
MAX31855  MAX31855_Object2(acSPI_CS_Pins[2]);
MAX31855  MAX31855_Object3(acSPI_CS_Pins[3]);

MAX31855  aThermos[wNumberOfThermos + 1]= {MAX31855_Object0, MAX31855_Object1, MAX31855_Object2, MAX31855_Object3};
#endif

#if DO_MAX6675
  MAX6675   Thermo1(cSPI_CLK_Pin, cSPI_CS_Thermo1Pin, cSPI_MISO_Pin);
  MAX6675   Thermo2(cSPI_CLK_Pin, cSPI_CS_Thermo2Pin, cSPI_MISO_Pin);
  MAX6675   Thermo3(cSPI_CLK_Pin, cSPI_CS_Thermo3Pin, cSPI_MISO_Pin);
#endif

void setup(void) {
  Serial.begin(115200);

  Serial << endl << "setup(): Sketch: " << szSketchName << ", " << szFileDate << endl;

  // Connect to WiFi network
  WiFi.begin(szRouterName, szRouterPW);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial << endl << "setup(): Connected to " << szRouterName << ", IP address to connect to is " << WiFi.localIP() << endl;

#if DO_MAX31855     //MAX6675 (obsolete) thermocouple reader doesn't have a setup routine
  for (int wThermo= 1; wThermo > wNumberOfThermos; wThermo++){
    aThermos[wThermo].begin();
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
  float     afDegreeC[4]= { 37.00, 37.01, 37.02, 37.03};

#if DO_MAX31855
  int32_t   wRawData= aThermos[1].readRawData();
  afDegreeC[1]= aThermos[1].getTemperature(wRawData);
#endif

#if DO_MAX6675
  dfDegF1= Thermo1.readFahrenheit();
  dfDegF2= Thermo2.readFahrenheit();
#endif
 Serial << "Loop(): Degrees F1= " << dfDegF1 << ", Thermo2= " << dfDegF2 << endl;
  delay(1000);

#if DO_WEBSERVER
  HandleOTAWebserver();
#endif
  //HandleOTAWebserver();
  //delay(1);
  return;
} //loop
//Last Line.
