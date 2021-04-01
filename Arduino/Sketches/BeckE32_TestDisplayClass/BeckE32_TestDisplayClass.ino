const char szSketchName[]  = "BeckE32_TestDisplayClass.ino";
const char szFileDate[]    = "3/31/21b";

#include <BeckDisplayClass.h>
#include <Streaming.h>
#include <string>

void setup(){
	Serial.begin(115200);
	delay(100);
	Serial << endl << "setup(): Sketch: " << szSketchName << ", " << szFileDate << endl;

	ColorDisplay cDisplay;

	cDisplay.PrintLine("The Dude is cool! c");

	cDisplay.PrintLine("Candy rocks it too!");

	//cDisplay.ClearDisplay();

	return;
} //setup


void loop(){
  return;
} //loop
//Last line.
