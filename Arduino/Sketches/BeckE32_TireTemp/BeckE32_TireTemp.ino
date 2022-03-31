const char szSketchName[]  = "BeckE32_TireTemp.ino";
const char szFileDate[]    = "3/31/22a";
#include <BeckE32_Defines.h>
#define LOCAL_BUTTONS   false
#if DO_OTA
  #include <BeckE32_OTALib.h>
#endif
#include <BeckCarSetClass.h>
#include <BeckI2cClass.h>
#include <BeckLogLib.h>
#include <BeckMiniLib.h>
#include <BeckDisplayClass.h>
#include <BeckTireTempNTPClass.h>
#include <WiFi.h>
#include <Streaming.h>

using Matcher = bool(*)(int, int);
Matcher aMatchers[4];

const char* szWebHostName = "TireTemp";

#define min(X, Y)       (((X) < (Y)) ? (X) : (Y))

//Protos
void  setup                 ();
void  loop                  ();
BeckCarSetClass*  _poCarSet;
const uint32_t    _uwI2CBusFrequency	= 100000;

void setup(){
  Serial.begin(115200);
  Serial << "\n" << LOG0 << "setup(): Begin " << szSketchName << ", " << szFileDate << "\n";

  Serial << "Connect to WiFi router " << _szRouterName << " with " << _szRouterPW << " as the PW\n";
  WiFi.begin(_szRouterName, _szRouterPW);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial << ".";
  }
  Serial << "\n";

#if DO_OTA
  Serial << "setup(): Call SetupWebServer(" << szWebHostName << ")\n";
  SetupWebserver(szWebHostName);
#endif

  Serial << LOG0 << "setup(): Set up I2C, call Wire.begin with bus frequency at " << _uwI2CBusFrequency << "\n";
  Wire.begin(_cI2C_SDA_Pin, _cI2C_SCL_Pin, _uwI2CBusFrequency);

  Serial << LOG0 << "setup(): Create _poCarSet using new BeckCarSetClass\n";
  _poCarSet= new BeckCarSetClass();

  //Check the t-couple hardware
  _poCarSet->Begin();

  Serial << LOG0 << "setup(): return\n";
  return;
}  //setup

void loop(){
  _poCarSet->HandleLoop();
#if DO_OTA
  HandleOTAWebserver();
#endif
  return;
}  //loop()
//Last line
