const char szFileName[]  = "BeckDisplayClass.cpp";
const char szFileDate[]  = "3/30/21d";

#include <BeckDisplayClass.h>
#include <Streaming.h>

/*
Display::Display() {
	Serial << "Display::Display(): " << szFileName << ", " << szFileDate << endl;
}	//constructor
*/


Display::~Display() {
	Serial << "~Display(): Destructing" << endl;
}	//destructor


ColorDisplay::ColorDisplay() {
	Serial << "ColorDisplay::ColorDisplay(): " << szFileName << ", " << szFileDate << endl;
	return;
}	//SetupDisplay


ColorDisplay::~ColorDisplay() {
	Serial << "~ColorDisplay(): Destructing" << endl;
}	//destructor


void ColorDisplay::SetupDisplay() {
	Serial << "ColorDisplay::SetupDisplay(): Begin" << endl;
	return;
}	//SetupDisplay


void ColorDisplay::ClearDisplay(){
	Serial << "ColorDisplay::ClearDisplay(): Begin" << endl;
	return;
}	//ClearDisplay


void ColorDisplay::UpdateDisplay(){
    Serial << "ColorDisplay::UpdateDisplay(): Begin" << endl;
	return;
}	//UpdateDisplay

