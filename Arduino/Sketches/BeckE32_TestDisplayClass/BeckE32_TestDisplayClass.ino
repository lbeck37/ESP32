const char szSketchName[]  = "BeckE32_TestDisplayClass.ino";
const char szFileDate[]    = "3/30/21c";

#include <BeckDisplayClass.h>
#include <Streaming.h>
#include <string>

void setup(){
	Serial.begin(115200);
	delay(100);
	Serial << endl << "setup(): Sketch: " << szSketchName << ", " << szFileDate << endl;

	ColorDisplay cDisplay;

	cDisplay.SetupDisplay();
	cDisplay.ClearDisplay();
	cDisplay.UpdateDisplay();

	return;
} //setup


void loop(){
  return;
} //loop
//Last line.
