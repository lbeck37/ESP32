const char szSketchName[]  = "BeckE32_Test_MCP9600.ino";
const char szFileDate[]    = "3/6/22f";
//Program to test MCP9600 Thermocouple reader using I2C

#define DO_OTA          true
#define DO_MAX6675      false
#define DO_MCP9600      true

#if DO_MAX6675
  #include <BeckMAX6675Lib.h>
#endif

#if DO_MCP9600
  #include <Wire.h>
  #include <Adafruit_I2CDevice.h>
  #include <Adafruit_I2CRegister.h>
  #include "Adafruit_MCP9600.h"
  #define I2C_ADDRESS (0x67)

  Adafruit_MCP9600 mcp;
#endif

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

bool    _bSensorFound = false;

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
  if (! mcp.begin(I2C_ADDRESS)) {
      Serial.println("Sensor not found. Check wiring!");
     //while (1); //Glad I found this, no wonder OTA didn't work.
  }
  else{
    _bSensorFound= true;
  }

  if (_bSensorFound){
    Serial.println("Found MCP9600!");

    mcp.setADCresolution(MCP9600_ADCRESOLUTION_18);
    Serial.print("ADC resolution set to ");
    switch (mcp.getADCresolution()) {
      case MCP9600_ADCRESOLUTION_18:   Serial.print("18"); break;
      case MCP9600_ADCRESOLUTION_16:   Serial.print("16"); break;
      case MCP9600_ADCRESOLUTION_14:   Serial.print("14"); break;
      case MCP9600_ADCRESOLUTION_12:   Serial.print("12"); break;
    }
    Serial.println(" bits");

    mcp.setThermocoupleType(MCP9600_TYPE_K);
    Serial.print("Thermocouple type set to ");
    switch (mcp.getThermocoupleType()) {
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

    mcp.setFilterCoefficient(3);
    Serial.print("Filter coefficient value set to: ");
    Serial.println(mcp.getFilterCoefficient());

    mcp.setAlertTemperature(1, 30);
    Serial.print("Alert #1 temperature set to ");
    Serial.println(mcp.getAlertTemperature(1));
    mcp.configureAlert(1, true, true);  // alert 1 enabled, rising temp

    mcp.enable(true);

    Serial.println(F("------------------------------"));
  } //if(_bSensorFound)
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
    if (_bSensorFound){
/*
      Serial.print("Hot Junction: ");
      Serial.println(mcp.readThermocouple());
      Serial.print("Cold Junction: ");
      Serial.println(mcp.readAmbient());
      Serial.print("ADC: "); Serial.print(mcp.readADC() * 2); Serial.println(" uV");
*/
      fTCoupleDegC  = mcp.readThermocouple();
      fAmbientDegC  = mcp.readAmbient();
      wADC2         = (mcp.readADC() * 2);

      fTCoupleDegF= (1.8 * fTCoupleDegC) + 32.0;
      fAmbientDegF= (1.8 * fAmbientDegC) + 32.0;

      //Serial << "LoopCode(): TCouple DegC: " << fTCoupleDegC << ", Ambient DegC= " << fAmbientDegC << ", ADC * 2= " << wADC2 << endl;
      Serial << "LoopCode(): TCouple DegF: " << fTCoupleDegF << ", Ambient DegF= " << fAmbientDegF << ", ADC * 2= " << wADC2 << endl;
    } //if(_bSensorFound)
    else{
      Serial << "LoopCode(): Sensor was not found, skipped code." << endl;
    } //if(_bSensorFound)else
  } //if (millis()>ulNextDisplayMsec)
  return;
} //LoopCode
//Last line.
