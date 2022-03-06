const char szSketchName[]  = "BeckE32_Test_MCP9600.ino";
const char szFileDate[]    = "3/6/22g";
//Program to test MCP9600 Thermocouple reader using I2C

#define DO_OTA          true
#define DO_MAX6675      false
#define DO_MCP9600      true

#include <BeckE32_Defines.h>

#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include "Adafruit_MCP9600.h"
#define I2C_ADDRESS (0x67)


#if DO_OTA
  #include <BeckE32_OTALib.h>
  #include <WiFi.h>
#endif
#include <Streaming.h>

const char* szRouterName  = "Aspot24b";
const char* szRouterPW    = "Qazqaz11";
const char* szWebHostName = "Test_MAX6675";

//Pin numbers on WROVER-Kit
int8_t    cSPI_CLK    = 18;
int8_t    cSPI_MISO   = 19;
int8_t    cSPI_CS1    =  2;
int8_t    cSPI_CS2    =  4;
int8_t    cSPI_CS3    =  5;

unsigned long     ulNextSensorReadMsec    =    0;
unsigned long     ulSensorReadPeriodMsec  = 3000; //mSec between reading tcouple

bool    _abSensorFound[] {false, false, false, false};

//Adafruit_MCP9600 mcp;

Adafruit_MCP9600    oMCP9600_TCouple1;
Adafruit_MCP9600    oMCP9600_TCouple2;
Adafruit_MCP9600    oMCP9600_TCouple3;

uint8_t             _aucI2CAdresses[] {0, _ucI2CAddress1, _ucI2CAddress2, _ucI2CAddress3};
//Adafruit_MCP9600    _aoMCP9600[];
Adafruit_MCP9600    _aoMCP9600[] {oMCP9600_TCouple1, oMCP9600_TCouple2, oMCP9600_TCouple3};

//Protos
void setup      ();
void loop       ();
void SetupCode  ();
void LoopCode   ();

void setup() {
  Serial.begin(115200);
  Serial << endl << "setup(): Begin " << szSketchName << ", " << szFileDate << endl;
  delay(500);
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
  SetupCode();
  return;
} //setup


void loop() {
#if DO_OTA
  HandleOTAWebserver();
#endif
  LoopCode();
  return;
} //loop


void SetupCode() {
  //Put code for setting up test here.
  Serial.println("MCP9600 HW test");

  /* Initialise the driver with I2C_ADDRESS and the default I2C bus. */
/*
  if (! mcp.begin(I2C_ADDRESS)) {
      Serial.println("Sensor not found. Check wiring!");
     //while (1); //Glad I found this, no wonder OTA didn't work.
  }
  else{
    _bSensorFound= true;
  }
*/
  for (int wProbe= 1; wProbe <= (_wNumProbes + 1); wProbe++){
    _aoMCP9600[wProbe]= _aoMCP9600[wProbe].begin(_aucI2CAdresses[wProbe]);
    if(_aoMCP9600[wProbe]){
      _abSensorFound[wProbe]= true;
      Serial << "SetupCode(): Found MCP9600 at address= " << _aucI2CAdresses[wProbe] << endl
    }
  } //for(int wProb=1; wProbe<=(_wNumProbes+1);wProbe++)

  for (int wProbe= 1; wProbe <= (_wNumProbes + 1); wProbe++){
    if (_abSensorFound[wProbe]){
      Serial.println("Found MCP9600!"); _aoMCP9600[wProbe]

      _aoMCP9600[wProbe].setADCresolution(MCP9600_ADCRESOLUTION_18);
      Serial.print("ADC resolution set to ");
      switch (_aoMCP9600[wProbe].getADCresolution()) {
        case MCP9600_ADCRESOLUTION_18:   Serial.print("18"); break;
        case MCP9600_ADCRESOLUTION_16:   Serial.print("16"); break;
        case MCP9600_ADCRESOLUTION_14:   Serial.print("14"); break;
        case MCP9600_ADCRESOLUTION_12:   Serial.print("12"); break;
      }
      Serial.println(" bits");

      _aoMCP9600[wProbe].setThermocoupleType(MCP9600_TYPE_K);
      Serial.print("Thermocouple type set to ");
      switch (_aoMCP9600[wProbe].getThermocoupleType()) {
        case MCP9600_TYPE_K:  Serial.print("K"); break;
        case MCP9600_TYPE_J:  Serial.print("J"); break;
        case MCP9600_TYPE_T:  Serial.print("T"); break;
        case MCP9600_TYPE_N:  Serial.print("N"); break;
        case MCP9600_TYPE_S:  Serial.print("S"); break;
        case MCP9600_TYPE_E:  Serial.print("E"); break;
        case MCP9600_TYPE_B:  Serial.print("B"); break;
        case MCP9600_TYPE_R:  Serial.print("R"); break;
      }
      Serial.println(" type");

      _aoMCP9600[wProbe].setFilterCoefficient(3);
      Serial.print("Filter coefficient value set to: ");
      Serial.println(_aoMCP9600[wProbe].getFilterCoefficient());

      _aoMCP9600[wProbe].setAlertTemperature(1, 30);
      Serial.print("Alert #1 temperature set to ");
      Serial.println(_aoMCP9600[wProbe].getAlertTemperature(1));
      _aoMCP9600[wProbe].configureAlert(1, true, true);  // alert 1 enabled, rising temp

      _aoMCP9600[wProbe].enable(true);

      Serial.println(F("------------------------------"));
    } //if(_bSensorFound)
  } //for
 return;
} //SetupCode


void LoopCode() {
  float     fTCoupleDegC;
  float     fAmbientDegC;
  float     fTCoupleDegF;
  float     fAmbientDegF;
  int32_t   wADC2;

  if (millis() > ulNextSensorReadMsec){
    ulNextSensorReadMsec= millis() + ulSensorReadPeriodMsec;
    for (int wProbe= 1; wProbe <= (_wNumProbes + 1); wProbe++){
      if (_abSensorFound[wProbe]){
        fTCoupleDegC  = _aoMCP9600[wProbe].readThermocouple();
        fAmbientDegC  = _aoMCP9600[wProbe].readAmbient();
        wADC2         = (_aoMCP9600[wProbe].readADC() * 2);

        fTCoupleDegF= (1.8 * fTCoupleDegC) + 32.0;
        fAmbientDegF= (1.8 * fAmbientDegC) + 32.0;

        Serial << "LoopCode(): TCouple DegF: " << fTCoupleDegF << ", Ambient DegF= " << fAmbientDegF << ", ADC * 2= " << wADC2 << endl;
    } //if(_bSensorFound)
    else{
      Serial << "LoopCode(): Sensor was not found, skipped code." << endl;
    } //if(_bSensorFound)else
   } //for
  } //if (millis()>ulNextDisplayMsec)
  return;
} //LoopCode
//Last line.
