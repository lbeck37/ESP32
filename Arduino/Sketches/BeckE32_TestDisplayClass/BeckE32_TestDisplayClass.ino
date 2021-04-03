const char szSketchName[]  = "BeckE32_TestDisplayClass.ino";
const char szFileDate[]    = "4/3/21e";

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

	//Select Adafruit fonts
  cDisplay.SelectFont(eGFXFont, 0);

	//cDisplay.PrintLine("The Dude is cool! g");
	cDisplay.PrintLine("Green on Red");
	delay(2000);

	BackgroundColor= TFT_BLUE;
	cDisplay.SetBackgroundColor(BackgroundColor);

	FillColor= BackgroundColor;
	cDisplay.FillScreen(FillColor);

	cDisplay.SetTextColor(TFT_WHITE);
	cDisplay.PrintLine("White on Blue");
	delay(2000);

	BackgroundColor= TFT_MAGENTA;
	cDisplay.SetBackgroundColor(BackgroundColor);
	//cDisplay.FillScreen(NULL);      //No parameter, use current background color.
	cDisplay.FillScreen(BackgroundColor);      //No parameter, use current background color.

	cDisplay.SetTextColor(TFT_ORANGE);
	cDisplay.PrintLine("Orange on Magenta");
	delay(2000);

	BackgroundColor= TFT_WHITE;
	cDisplay.SetBackgroundColor(BackgroundColor);
	//cDisplay.FillScreen(NULL);      //No parameter, use current background color.
	cDisplay.FillScreen(BackgroundColor);      //No parameter, use current background color.

	cDisplay.SetTextColor(TFT_BLACK);
	cDisplay.PrintLine("Black on White");
	delay(2000);

	//Test printing a string composed of "Now: " and the current "temperature".
	Serial << "setup(): Test printing the Now: temperature line." << endl;

	char* 		szStringToPrint		= "Now:";
	DegreeType	fCurrentDegF		= 37.73;

	sprintf(sz100CharBuffer, "%s %6.2f", szStringToPrint, fCurrentDegF);
	cDisplay.PrintLine(sz100CharBuffer);

	//Verify that TTGO is 135 x 240 (not 240 x 360 like I thought)
  CursorUnit  XLeft   =   5;
  CursorUnit  YTop    =   5;
  CursorUnit  Width   = 230;
  CursorUnit  Height  = 125;

  cDisplay.DrawRectangle(XLeft, YTop, Width, Height);

	return;
} //setup


void loop(){
  return;
} //loop
//Last line.
