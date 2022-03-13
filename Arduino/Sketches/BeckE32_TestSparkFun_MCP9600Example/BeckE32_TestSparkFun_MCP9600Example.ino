const char szSketchName[]  = "BeckE32_TestSparkFun_MCP9600Example.ino";
const char szFileDate[]    = "3/11/22p";
#include <Streaming.h>

/*
  Temperature Measurements with the MCP9600 Thermocouple Amplifier
  By: Fischer Moseley
  SparkFun Electronics
  Date: July 8, 2019
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware License).

  This example outputs the ambient and thermocouple temperatures from the MCP9600 sensor.

  Hardware Connections:
  Attach the Qwiic Shield to your Arduino/Photon/ESP32 or other
  Plug the sensor onto the shield
  Serial.print it out at 115200 baud to serial monitor.
*/

#include <SparkFun_MCP9600.h>
MCP9600 tempSensor;

static const int8_t     _cI2C_SDA_Pin     = 26;
static const int8_t     _cI2C_SCL_Pin     = 27;

void setup(){
    Serial.begin(115200);
    Serial << "\nsetup(): Begin " << szSketchName << ", " << szFileDate << endl;

    //uint32_t  uwBusFrequency  =  20000;
    uint32_t  uwBusFrequency    = 100000;
    //Wire.begin();
    //Wire.setClock(100000);
    Wire.begin(_cI2C_SDA_Pin, _cI2C_SCL_Pin, uwBusFrequency);
    //Wire.setClock(uwBusFrequency);
    Serial << "setup(): I2C frequency set to " << uwBusFrequency << endl;

    uint8_t   ucI2CAddress= 0x60;
    //uint8_t   ucI2CAddress= 0x67;
    //uint8_t   ucI2CAddress= 0x66;
    Serial << "setup(): Call tempSensor.begin(" << ucI2CAddress << ")" << endl;
    //tempSensor.begin();       // Uses the default address (0x60) for SparkFun Thermocouple Amplifier
    tempSensor.begin(ucI2CAddress);       // Uses the default address (0x60) for SparkFun Thermocouple Amplifier
    //tempSensor.begin(0x66); // Default address (0x66) for SparkX Thermocouple Amplifier

    //check if the sensor is connected
    Serial << "setup(): Call tempSensor.isConnected()\n";
    if(tempSensor.isConnected()){
        Serial.println("Device will acknowledge!");
    }
    else {
        Serial.println("Device did not acknowledge! Freezing.");
        while(1); //hang forever
    }

    //check if the Device ID is correct
    Serial << "setup(): Call tempSensor.checkDeviceID()\n";
    if(tempSensor.checkDeviceID()){
        Serial.println("Device ID is correct!");        
    }
    else {
        Serial.println("Device ID is not correct! Freezing.");
        while(1);
    }
}

void loop(){ //print the thermocouple, ambient and delta temperatures every 200ms if available
    if(tempSensor.available()){
        Serial.print("Thermocouple: ");
        Serial.print(tempSensor.getThermocoupleTemp());
        Serial.print(" °C   Ambient: ");
        Serial.print(tempSensor.getAmbientTemp());
        Serial.print(" °C   Temperature Delta: ");
        Serial.print(tempSensor.getTempDelta());
        Serial.print(" °C");
        Serial.println();
        delay(20); //don't hammer too hard on the I2C bus
    }
}
