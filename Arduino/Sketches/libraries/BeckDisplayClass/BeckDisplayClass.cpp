const char szFileName[]  = "BeckDisplayClass.cpp";
const char szFileDate[]  = "3/31/21b";

#include <BeckDisplayClass.h>
#include <Streaming.h>


Display::Display() {
	Serial << "Display::Display(): " << szFileName << ", " << szFileDate << endl;
}	//constructor


Display::~Display() {
	Serial << "~Display(): Destructing" << endl;
}	//destructor


ColorDisplay::ColorDisplay() {
	Serial << "ColorDisplay::ColorDisplay(): " << szFileName << ", " << szFileDate << endl;
	_eScreenOrientation= eUSBLeft;

	tft.init();
	tft.setRotation(_eScreenOrientation);
	tft.fillScreen(TFT_BLACK);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.setTextFont(4);	 //26 pixels

	// Set starting coordinates (x, y)
	tft.setCursor(0, 0);
	return;
}	//SetupDisplay


ColorDisplay::~ColorDisplay() {
	Serial << "~ColorDisplay(): Destructing" << endl;
}	//destructor


void ColorDisplay::PrintLine(char* szLineToPrint) {
	Serial << "ColorDisplay::PrintLine(): szLineToPrint= " << szLineToPrint << endl;
	tft.println(szLineToPrint);
	return;
}	//SetupDisplay


void ColorDisplay::FillScreen(Colortype FillColor){
	Serial << "ColorDisplay::FillScreen()" << endl;
	tft.fillScreen(FillColor);
	return;
}	//ClearDisplay


void  ColorDisplay::SetBackground(Colortype NewBackgroundColor){
	_BackgroundColor= NewBackgroundColor;
	return;
}
//Last line.
