// LastMinuteEngineers.com
const char szSketchName[]  = "BeckE32_OTA_WebUpdater_021622.ino";
const char szFileDate[]    = "2/17/22e";

#include <BeckE32_OTALib.h>
#include <WiFi.h>
#include <Streaming.h>

const char* ssid = "Aspot24b";
const char* password = "Qazqaz11";



void setup(void) {
  Serial.begin(115200);

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial << endl << "setup(): Sketch: " << szSketchName << ", " << szFileDate << endl;

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  SetupWebserver();
  return;
} //setup


void loop(void) {
  //server.handleClient();
  HandleOTAWebserver();
  delay(1);
  return;
} //loop
//Last Line.
