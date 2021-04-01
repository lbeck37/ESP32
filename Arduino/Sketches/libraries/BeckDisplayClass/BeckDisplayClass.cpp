const char szFileName[]  = "BeckDisplayClass.cpp";
const char szFileDate[]  = "4/1/21d";

#include <BeckDisplayClass.h>
#include <Streaming.h>

char	sz100CharBuffer[100];		//For use in char[[ functions, wish string or String would work

Display::Display() {
	Serial << "Display::Display(): " << szFileName << ", " << szFileDate << endl;
}	//constructor


Display::~Display() {
	Serial << "~Display(): Destructing" << endl;
}	//destructor


ColorDisplay::ColorDisplay() {
	Serial << "ColorDisplay::ColorDisplay(): " << szFileName << ", " << szFileDate << endl;
	_eScreenOrientation	= eUSBLeft;
	_BackgroundColor	= TFT_RED;
	_TextColor			= TFT_GREEN;
	_FillColor			= TFT_RED;

	GLib.init			();
	GLib.setRotation	(_eScreenOrientation);
	GLib.fillScreen		(_FillColor);
	GLib.setTextColor	(_TextColor, _BackgroundColor);
	GLib.setTextFont	(4);	 //26 pixels

	// Set starting coordinates (x, y)
	GLib.setCursor(_CursorX, _CursorY);
	return;
}	//SetupDisplay


ColorDisplay::~ColorDisplay() {
	Serial << "~ColorDisplay(): Destructing" << endl;
}	//destructor


void ColorDisplay::PrintLine(const char* szLineToPrint) {
	Serial << "ColorDisplay::PrintLine(): szLineToPrint= " << szLineToPrint << endl;

	GLib.println(szLineToPrint);
	return;
}	//SetupDisplay


void ColorDisplay::FillScreen(void){
	//Leave FillColor out and you get the current background.
	Serial << "ColorDisplay::FillScreen()" << endl;

	GLib.fillScreen(_BackgroundColor);
	return;
}	//ClearDisplay


void ColorDisplay::FillScreen(Colortype FillColor){
	Serial << "ColorDisplay::FillScreen(FillColor), FillColor= " << FillColor << endl;

	GLib.fillScreen(FillColor);
	return;
}	//ClearDisplay


void  ColorDisplay::SetBackground(Colortype NewBackgroundColor){
	Serial << "ColorDisplay::SetBackground(): NewBackgroundColor= " << NewBackgroundColor << endl;
	_BackgroundColor= NewBackgroundColor;
	return;
}


void  ColorDisplay::SetTextColor(Colortype NewTextColor){
	Serial << "ColorDisplay::SetTextColor(): NewTextColor= " << NewTextColor << endl;
	_TextColor= NewTextColor;

	GLib.setTextColor(_TextColor);
	return;
}


void  ColorDisplay::SetTextBGColor(Colortype NewTextBGColor){
	Serial << "ColorDisplay::SetTextBGColor(): NewTextBGColor= " << NewTextBGColor << endl;
	_TextBGColor= NewTextBGColor;

	GLib.setTextColor(_TextColor, _TextBGColor);		//No seperate call to set the Text BG color.
	return;
}
//Last line.
