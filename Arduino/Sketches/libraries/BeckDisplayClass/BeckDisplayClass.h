#pragma once
const char szFileName2[]  = "BeckDisplayClass.h";
const char szFileDate2[]  = "4/1/21a";

#include <TFT_eSPI.h>
#include <Adafruit_GFX.h>
#include <Streaming.h>

#include <string>
using namespace std;

enum ScreenOrientationType {
	eUSBDown= 0,
	eUSBRight,
	eUSBUp,
	eUSBLeft,
	eLastUSBOrientation
};

typedef TFT_eSPI	GraphicsLibrary;
typedef uint32_t	Colortype;
typedef uint16_t	CursorUnit;


class Display {
protected:
	//TFT_eSPI 				tft	= TFT_eSPI();
	GraphicsLibrary 		GLib				= GraphicsLibrary();
	ScreenOrientationType	_eScreenOrientation	= eUSBLeft;
	Colortype				_BackgroundColor	= TFT_BLACK;
	Colortype				_TextColor			= TFT_WHITE;
	Colortype				_FillColor			= TFT_RED;
	CursorUnit				_CursorX			= 0;
	CursorUnit				_CursorY			= 0;

public:
	Display();
/*
	Display() {
		Serial << "Display::Display(): " << szFileName2 << ", " << szFileDate2 << endl;}
*/

	virtual ~Display();

	virtual void  PrintLine			(const char* szLineToPrint){}
	virtual void  FillScreen      	(){}
	virtual void  FillScreen      	(Colortype FillColor){}
	virtual void  SetBackground		(Colortype NewBackgroundColor){}
	virtual void  SetTextColor		(Colortype NewTextColor){}
	//virtual void  FillScreen		(Colortype FillColor= TFT_RED){}
};  //Display


class ColorDisplay : public Display {
protected:

public:
	ColorDisplay();
	virtual ~ColorDisplay();

	void  PrintLine			(const char* szLineToPrint);
	void  FillScreen      	();
	void  FillScreen      	(Colortype FillColor);
	void  SetBackground		(Colortype NewBackgroundColor);
	void  SetTextColor		(Colortype NewTextColor);
};

