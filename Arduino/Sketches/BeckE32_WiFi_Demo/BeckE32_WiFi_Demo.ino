const char szSketchName[]  = "BeckE32_WiFi_Demo.ino";
const char szFileDate[]    = "3/29/21f";

//Ref- https://techtutorialsx.com/2017/06/29/esp32-arduino-getting-started-with-wifi/

#include <WiFi.h>
#include <Streaming.h>

const char* ssid 		= "Aspot24";
const char* password 	=  "Qazqaz11";

String translateEncryptionType(wifi_auth_mode_t encryptionType) {
  switch (encryptionType) {
    case (WIFI_AUTH_OPEN):
      return "Open";
    case (WIFI_AUTH_WEP):
      return "WEP";
    case (WIFI_AUTH_WPA_PSK):
      return "WPA_PSK";
    case (WIFI_AUTH_WPA2_PSK):
      return "WPA2_PSK";
    case (WIFI_AUTH_WPA_WPA2_PSK):
      return "WPA_WPA2_PSK";
    case (WIFI_AUTH_WPA2_ENTERPRISE):
      return "WPA2_ENTERPRISE";
    case (WIFI_AUTH_MAX):
	  return "WIFI_AUTH_MAX";
    default:
	  Serial << "Bad case in translateEncryptionType(), encryptionType= " << encryptionType << endl;
	  break;
  }	//switch

  return("BadCase");
}  //translateEncryptionType


void scanNetworks() {
  int numberOfNetworks = WiFi.scanNetworks();

  Serial.print("Number of networks found: ");
  Serial.println(numberOfNetworks);

  for (int i = 0; i < numberOfNetworks; i++) {
    Serial.print("Network name: ");
    Serial.println(WiFi.SSID(i));

    Serial.print("Signal strength: ");
    Serial.println(WiFi.RSSI(i));

    Serial.print("MAC address: ");
    Serial.println(WiFi.BSSIDstr(i));

    Serial.print("Encryption type: ");
    String encryptionTypeDescription = translateEncryptionType(WiFi.encryptionType(i));
    Serial.println(encryptionTypeDescription);
    Serial.println("-----------------------");
  }	//for
  return;
}	//scanNetworks


void connectToNetwork() {
  Serial << "connectToNetwork(): Call WiFi.begin(" << ssid << ", " << password << ")" << endl;
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Establishing connection to WiFi..");
  }	//while
  Serial.println("Connected to network");

  return;
}	//connectToNetwork


void setup() {
  Serial.begin(115200);
  delay(100);
  Serial << endl << "setup(): Sketch: " << szSketchName << ", " << szFileDate << endl;

  scanNetworks();
  connectToNetwork();

  Serial << "setup(): WiFi.macAddress= " << WiFi.macAddress() << endl;
  Serial << "setup(): WiFi.localIP   = " << WiFi.localIP() << endl;

  //Disconnect from network and show that IP address has gone away
  Serial << "setup(): Call WiFi.disconnect(true)" << endl;
  WiFi.disconnect(true);
  Serial << "setup(): WiFi.localIP   = " << WiFi.localIP() << endl;

  return;
}	//setup


void loop(){
	return;
}	//loop
//Last line.
