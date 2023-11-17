const char szSketchName[]  = "DummyTest2.ino";
const char szFileDate[]    = "10/4/23c";
#include "Arduino.h"
//The setup function is called once at startup of the sketch
#include <Streaming.h>

void setup()
{
  Serial.begin(115200);
  delay(100);
  Serial << endl << "setup(): Sketch: " << szSketchName << ", " << szFileDate << endl;
  return;
}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
}
