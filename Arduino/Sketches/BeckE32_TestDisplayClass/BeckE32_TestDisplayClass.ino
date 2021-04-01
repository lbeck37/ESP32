const char szSketchName[]  = "BeckE32_TestDisplayClass.ino";
const char szFileDate[]    = "4/1/21b";

#include <BeckDisplayClass.h>
#include <Streaming.h>
#include <string>

void setup(){
	Colortype	BackgroundColor;
	Colortype	FillColor;

	Serial.begin(115200);
	delay(100);
	Serial << endl << "setup(): Sketch: " << szSketchName << ", " << szFileDate << endl;

	ColorDisplay cDisplay;

	delay(2000);

	//cDisplay.PrintLine("The Dude is cool! g");
	cDisplay.PrintLine("Green/Red)");
	delay(2000);

	BackgroundColor= TFT_BLUE;
	cDisplay.SetBackground(BackgroundColor);

	FillColor= BackgroundColor;
	cDisplay.FillScreen(FillColor);

	cDisplay.SetTextColor(TFT_WHITE);
	cDisplay.PrintLine("White/Blue");
	delay(2000);

	BackgroundColor= TFT_PURPLE;
	cDisplay.FillScreen();			//No parameter, use current background color.

	cDisplay.SetTextColor(TFT_YELLOW);
	cDisplay.PrintLine("Yellow/Purple");
	delay(2000);

	return;
} //setup


void loop(){
  return;
} //loop
//Last line.
