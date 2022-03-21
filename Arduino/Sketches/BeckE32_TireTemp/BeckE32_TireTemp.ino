const char szSketchName[]  = "BeckE32_TireTemp.ino";
const char szFileDate[]    = "3/20/22k";      //From Commit 42331... "3/16/22k"

#include <BeckE32_Defines.h>
#define LOCAL_BUTTONS   true
#if DO_OTA
  #include <BeckE32_OTALib.h>
#endif
#include <BeckCarSetClass.h>
#include <BeckI2cClass.h>
#include <BeckLogLib.h>
#include <BeckMiniLib.h>

#include <BeckTireTempDisplayClass.h>
#include <BeckTireTempNTPClass.h>

#include <WiFi.h>
#include <Streaming.h>

const char* szWebHostName = "TireTemp";

#define min(X, Y)       (((X) < (Y)) ? (X) : (Y))

//Protos
void  setup                 ();
void  loop                  ();
#if LOCAL_BUTTONS
  void  SetupButtons          ();
  void  ReadButtons           ();
  void  HandleButton          (int wSensorSet);
  void  onPressed1            ();
  void  onPressed2            ();
  void  onPressed3            ();
  void  onPressed4            ();

  #include <EasyButton.h>

  //Setup buttons, Defaults: 35msec debounce, Pullup enabled, Returns true on button press
  //EasyButton        TireButton1   (_cButton_Pin1);
  EasyButton        TireButton2   (_cButton_Pin2);
  EasyButton        TireButton3   (_cButton_Pin3);
  EasyButton        TireButton4   (_cButton_Pin4);
#endif
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

#if LOCAL_BUTTONS
  Serial << LOG0 << "setup(): Call SetupButtons()\n";
  SetupButtons();
#endif
  //Check the t-couple hardware
  _poCarSet->Begin();

  Serial << LOG0 << "setup(): return\n";
  return;
}  //setup


void loop(){
#if LOCAL_BUTTONS
  ReadButtons();
#endif
  //_poCarSet->HandleLogging();
  //_poCarSet->UpdateDisplay();
  _poCarSet->HandleLoop();

#if DO_OTA
  HandleOTAWebserver();
#endif
  return;
}  //loop()

#if LOCAL_BUTTONS
void SetupButtons() {
  Serial << "SetupButtons(): Call TireButton1/2/3/4.begin()\n";
  //TireButton1.begin();
  TireButton2.begin();
  TireButton3.begin();
  TireButton4.begin();

  Serial << "SetupButtons(): Setup Callback, call onPressed(callback) for the 4 buttons\n";
  //TireButton1.onPressed(onPressed1);
  TireButton2.onPressed(onPressed2);
  TireButton3.onPressed(onPressed3);
  TireButton4.onPressed(onPressed4);
  return;
} //SetupButtons

void ReadButtons(){
  //TireButton1.read();   //This has to get called for onPressed() to get called back
  TireButton2.read();
  TireButton3.read();
  TireButton4.read();
  return;
} //ReadButtons

void HandleButton(int wSensorSet){
  Serial << "onPressed1(): You pressed Button " << wSensorSet << "\n";
  _poCarSet->ReadSensorSet(wSensorSet);
  return;
} //HandleButton

void onPressed1(){
  int   wSensorSet= 1;
  HandleButton(wSensorSet);
  return;
} //onPressed1

void onPressed2(){
  int   wSensorSet= 2;
  HandleButton(wSensorSet);
  return;
} //onPressed2

void onPressed3(){
  int   wSensorSet= 3;
  HandleButton(wSensorSet);
  return;
} //onPressed3

void onPressed4(){
  int   wSensorSet= 4;
  HandleButton(wSensorSet);
  return;
} //onPressed4
#endif
//Last line
