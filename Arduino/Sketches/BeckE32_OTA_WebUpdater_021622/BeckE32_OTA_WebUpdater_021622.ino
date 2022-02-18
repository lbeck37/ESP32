// LastMinuteEngineers.com
//Works with ESP32 1.0.6, 2/17/22
const char szSketchName[]  = "BeckE32_OTA_WebUpdater_021622.ino";
const char szFileDate[]    = "2/17/22s";

#define DO_TEMP       true
#define DO_WEBSERVER  true

#if DO_WEBSERVER
  #include <BeckE32_OTALib.h>
#endif
#if DO_TEMP
  #include <max6675.h>
#endif
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
static const byte      cSPI_CS_Thermo1Pin    =  5;
static const byte      cSPI_CS_Thermo2Pin    =  4;

#if DO_TEMP
  //MAX6675   Thermo1(cSCLK, cMOSI_CS, cMISO);
MAX6675   Thermo1(cSPI_CLK_Pin, cSPI_CS_Thermo1Pin, cSPI_MISO_Pin);
MAX6675   Thermo2(cSPI_CLK_Pin, cSPI_CS_Thermo2Pin, cSPI_MISO_Pin);
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

#if DO_WEBSERVER
  Serial << "setup(): Call SetupWebServer(" << szWebHostName << ")" << endl;
  SetupWebserver(szWebHostName);
#endif
  //Serial << "setup(): Call SetupWebServer(" << szWebHostName << ")" << endl;
  //SetupWebserver(szWebHostName);

  Serial << "setup(): Done" << endl;
  return;
} //setup


void loop(void) {
  double    dfDegF1= 37.01;
  double    dfDegF2= 37.02;
#if DO_TEMP
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
