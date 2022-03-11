const char szSketchName[]  = "BeckE32_TestButtons.ino";
const char szFileDate[]    = "3/10/22d";

#include <EasyButton.h>
#include <Streaming.h>

#define DO_OTA          true
#if DO_OTA
  #include <BeckE32_OTALib.h>
  #include <WiFi.h>
#endif


static const int8_t     _cButton_Pin1     = 12;
static const int8_t     _cButton_Pin2     = 13;
static const int8_t     _cButton_Pin3     = 14;
static const int8_t     _cButton_Pin4     = 15;

//Setup buttons, Defaults: 35msec debounce, Pullup enabled, Returns true on button press
EasyButton TireButton1(_cButton_Pin1);
EasyButton TireButton2(_cButton_Pin2);
EasyButton TireButton3(_cButton_Pin3);
EasyButton TireButton4(_cButton_Pin4);

const char* szRouterName  = "Aspot24b";
const char* szRouterPW    = "Qazqaz11";
const char* szWebHostName = "Test_I2C";


//Protos
void  setup                 (void);
void  loop                  (void);
void  onPressed1            (void);
void  onPressed2            (void);
void  onPressed3            (void);
void  onPressed4            (void);

void setup()
{
  Serial.begin(115200);
  Serial << "\nsetup(): Begin " << szSketchName << ", " << szFileDate << "\n";

#if DO_OTA
  // Start WiFi and wait for connection to the network
  WiFi.begin(szRouterName, szRouterPW);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial << endl << "setup(): Connected to " << szRouterName << ", IP address to connect to is " << WiFi.localIP() << endl;
  Serial << "setup(): Call SetupWebServer(" << szWebHostName << ")" << endl;
  SetupWebserver(szWebHostName);
#endif

  Serial << "setup(): Call TireButton1/2/3/4.begin()\n";
  TireButton1.begin();
  TireButton2.begin();
  TireButton3.begin();
  TireButton4.begin();

  Serial << "setup(): Setup Callback, call TireButton1/2/3/4.onPressed(onPressed1/2/3/4)\n";
  TireButton1.onPressed(onPressed1);
  TireButton2.onPressed(onPressed2);
  TireButton3.onPressed(onPressed3);
  TireButton4.onPressed(onPressed4);

  Serial << "setup(): Done, press buttons to test\n";
  return;
}


void loop()
{
#if DO_OTA
  HandleOTAWebserver();
#endif
  TireButton1.read();   //This has to get called for onPressed() to get called back
  TireButton2.read();   //This has to get called for onPressed() to get called back
  TireButton3.read();   //This has to get called for onPressed() to get called back
  TireButton4.read();   //This has to get called for onPressed() to get called back
  return;
} //loop


void onPressed1(){
  Serial << "onPressed1(): You pressed Button 1.\n";
  return;
} //onPressed1


void onPressed2(){
  Serial << "onPressed2(): You pressed Button 2.\n";
  return;
} //onPressed2


void onPressed3(){
  Serial << "onPressed3(): You pressed Button 3.\n";
  return;
} //onPressed3


void onPressed4(){
  Serial << "onPressed4(): You pressed Button 4.\n";
  return;
} //onPressed4
//Last line.
