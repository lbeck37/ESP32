const char szSketchName[]  = "BeckE32_Test_DHTespLibrary.ino";
const char szFileDate[]    = "5/29/21a";
#include "DHTesp.h" // Click here to get the library: http://librarymanager/All#DHTesp
#include <Ticker.h>
#include <Streaming.h>

#ifndef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP32 ONLY!)
#error Select ESP32 board.
#endif

/**************************************************************/
/* Example how to read DHT sensors from an ESP32 using multi- */
/* tasking.                                                   */
/* This example depends on the Ticker library to wake up      */
/* the task every 20 seconds                                  */
/**************************************************************/

DHTesp dht;

//void tempTask(void *pvParameters);
void ReadDHT_Task(void *pvParameters);
//bool getTemperature();
bool ReadTempAndHumidity();
void triggerGetTemp();


TaskHandle_t    DHT_TaskHandle  = NULL;   /** Task handle for the light value read task */
Ticker          DHT_Ticker;               /** Ticker for DHT reading */
ComfortState    ComfortLevel;             /** Comfort profile */
bool            tasksEnabled    = false;  /** Flag if task should run */

/** Pin number for DHT11 data pin */
//int dhtPin = 17;      //ESP32 Dev Board
int dhtPin = 25;        //ESP-WROVER-KIT


void setup(){
  Serial.begin(115200);
  Serial << endl << "setup(): Begin " << szSketchName << ", " << szFileDate << endl;
  Serial << "setup(): DHT ESP32 example with tasks" << endl;
  Serial << "setup(): Call SetupDHT()" << endl;
  SetupDHT();

  // Signal end of setup() to tasks
  tasksEnabled= true;
  Serial << "setup(): return" << endl;
  return;
}   //setup


void loop() {
  if (!tasksEnabled) {
    delay(2000);            // Wait 2 seconds to let system settle down
    tasksEnabled = true;    // Enable task that will read values from the DHT sensor
    if (DHT_TaskHandle != NULL) {
      vTaskResume(DHT_TaskHandle);
    } //if (DHT_TaskHandle!=NULL)
  } //if(!tasksEnabled)
  yield();
  return;
} //loop

/* SetupDHT
 * Setup DHT library
 * Setup task and timer for repeated measurement
 * @return bool
 *    true if task and timer are started
 *    false if task or timer couldn't be started */
bool SetupDHT() {
  //byte resultValue = 0;
  //dht.setup(dhtPin, DHTesp::DHT11);
  //dht.setup(dhtPin, DHTesp::DHT22);
  Serial << "SetupDHT(): Call dht.setup(dhtPin, DHTesp::AUTO_DETECT)" << endl;
  dht.setup(dhtPin, DHTesp::AUTO_DETECT);
  Serial << "SetupDHT(): Back from dht.setup()" << endl;

	Serial << "SetupDHT(): DHT initiated" << endl;

  //Start FreeRTOS task to read DHT
  Serial << "SetupDHT(): Call xTaskCreatePinnedToCore()" << endl;
	xTaskCreatePinnedToCore(
			ReadDHT_Task,                   /* Function to implement the task */
			"ReadDHT_Task ",                /* Name of the task */
			4000,                           /* Stack size in words */
			NULL,                           /* Task input parameter */
			5,                              /* Priority of the task */
			&DHT_TaskHandle,                /* Task handle. */
			1);                             /* Core where the task should run */
  Serial << "SetupDHT(): Back from xTaskCreatePinnedToCore()" << endl;

  if (DHT_TaskHandle == NULL) {
    Serial << "SetupDHT(): DHT_TaskHandle is NULL" << endl;
    Serial << "SetupDHT(): Failed to start task for temperature update" << endl;
    Serial << "SetupDHT(): return false" << endl;
    return false;
  } //if(DHT_TaskHandle==NULL)
  else {
    // Start update of environment data every 20 seconds
    Serial << "SetupDHT(): Call DHT_Ticker.attach()" << endl;
    //DHT_Ticker.attach(20, triggerGetTemp);
    DHT_Ticker.attach(5.0, triggerGetTemp);
  } //if(DHT_TaskHandle==NULL)else
  Serial << "SetupDHT(): return true" << endl;
  return true;
} //SetupDHT


/* triggerGetTemp
 * Sets flag dhtUpdated to true for handling in loop()
 * called by Ticker getTempTimer*/
void triggerGetTemp() {
  if (DHT_TaskHandle != NULL) {
	   xTaskResumeFromISR(DHT_TaskHandle);
  }
  return;
} //triggerGetTemp


/* Task to reads temperature from DHT11 sensor
 * @param pvParameters
 *    pointer to task parameters */
void ReadDHT_Task(void *pvParameters) {
	//Serial.println("tempTask loop started");
  Serial << "ReadDHT_Task(): Start while loop" << endl;
	while (1) // ReadDHT_Task loop
  {
    if (tasksEnabled) {
      // Get temperature values
      Serial << "ReadDHT_Task(): Call ReadTempAndHumidity()" << endl;
			ReadTempAndHumidity();
		}
    // Go to sleep again
    Serial << "ReadDHT_Task(): Call vTaskSuspend()" << endl;
		vTaskSuspend(NULL);
	}
	return;   //Never gets here
} //ReadDHT_Task

/* ReadTempAndHumidity
 * Reads temperature from DHT11 sensor
 * @return bool
 *    true if temperature could be acquired
 *    false if acquisition failed */
bool ReadTempAndHumidity() {
	// Reading temperature for humidity takes about 250 milliseconds!
	// Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
  TempAndHumidity   newValues= dht.getTempAndHumidity();

	// Check if any reads failed and exit early (to try again).
	if (dht.getStatus() != 0) {
		Serial.println("DHT11 error status: " + String(dht.getStatusString()));
		return false;
	}
	float heatIndex = dht.computeHeatIndex(newValues.temperature, newValues.humidity);
  float dewPoint = dht.computeDewPoint(newValues.temperature, newValues.humidity);
  float cr = dht.getComfortRatio(ComfortLevel, newValues.temperature, newValues.humidity);

  String comfortStatus;
  switch(ComfortLevel) {
    case Comfort_OK:
      comfortStatus = "Comfort_OK";
      break;
    case Comfort_TooHot:
      comfortStatus = "Comfort_TooHot";
      break;
    case Comfort_TooCold:
      comfortStatus = "Comfort_TooCold";
      break;
    case Comfort_TooDry:
      comfortStatus = "Comfort_TooDry";
      break;
    case Comfort_TooHumid:
      comfortStatus = "Comfort_TooHumid";
      break;
    case Comfort_HotAndHumid:
      comfortStatus = "Comfort_HotAndHumid";
      break;
    case Comfort_HotAndDry:
      comfortStatus = "Comfort_HotAndDry";
      break;
    case Comfort_ColdAndHumid:
      comfortStatus = "Comfort_ColdAndHumid";
      break;
    case Comfort_ColdAndDry:
      comfortStatus = "Comfort_ColdAndDry";
      break;
    default:
      comfortStatus = "Unknown:";
      break;
  };  //switch(ComfortLevel)
  Serial.println(" T:" + String(newValues.temperature) + " H:" + String(newValues.humidity) + " I:" + String(heatIndex) + " D:" + String(dewPoint) + " " + comfortStatus);
	return true;
} //ReadTempAndHumidity
//Last line.
