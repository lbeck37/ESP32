const char szSketchName[]  = "BeckE32_IteratorTest.ino";
const char szFileDate[]    = "3/27/22b";
#include "Arduino.h"
//#include "FirebaseESP8266.h"
//#include <ESP8266WiFi.h>
//#include "ArduinoJson.h"
//#include "FirebaseArduino.h"
#include <Streaming.h>
/*
import <vector>;
import <iterator>;
import <iostream>;
*/

using namespace std;

void setup(){
  Serial.begin(115200);
  delay(500);
  Serial << "\n" << "setup(): Begin " << szSketchName << ", " << szFileDate << "\n";
  Serial << "Hello World!\n";
  return;
} //setup


void loop()
{
  //Do nothing.
  return;
} //loop

/*
//Pro C++ Chapter 17
import <vector>;
import <iterator>;
import <iostream>;

using namespace std;

template <typename IteratorType>
void iteratorTraitsTest(IteratorType it)
{
  typename iterator_traits<IteratorType>::value_type temp;
  temp = *it;
  //auto temp{ *it };
  cout << temp << endl;
}

int main()
{
  vector v{ 5 };
  iteratorTraitsTest(cbegin(v));
}
*/

//Last line.
