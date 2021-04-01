#pragma once
const char szFileName2[]  = "BeckDisplayClass.h";
const char szFileDate2[]  = "3/31/21c";

#include <TFT_eSPI.h>
#include <Adafruit_GFX.h>
#include <Streaming.h>

#include <string>
using namespace std;

//string	Larry= "hello";
//char szBuffer[100] = "Hello";

enum ScreenOrientationType {
	eUSBDown= 0,
	eUSBRight,
	eUSBUp,
	eUSBLeft,
	eLastUSBOrientation
};

typedef uint32_t	Colortype;


class Display {
protected:
	TFT_eSPI 				tft	= TFT_eSPI();
	ScreenOrientationType	_eScreenOrientation= eUSBLeft;

public:
	Display();
/*
	Display() {
		Serial << "Display::Display(): " << szFileName2 << ", " << szFileDate2 << endl;}
*/

	virtual ~Display();

	virtual void  PrintLine			(char* szLineToPrint){}
	//virtual void  FillScreen		(Colortype FillColor= TFT_RED){}
};  //Display


class ColorDisplay : public Display {
protected:
	Colortype	_BackgroundColor	= TFT_BLACK;
	Colortype	_TextColor			= TFT_WHITE;
	Colortype	_FillColor			= TFT_RED;

public:
	ColorDisplay();
	virtual ~ColorDisplay();

	void  PrintLine			(char* szLineToPrint);
	void  FillScreen      	(Colortype FillColor);
	void  SetBackground		(Colortype NewBackgroundColor);
};

