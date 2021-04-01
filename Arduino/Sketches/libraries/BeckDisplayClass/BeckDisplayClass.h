#pragma once
const char szFileName2[]  = "BeckDisplayClass.h";
const char szFileDate2[]  = "3/31/21b";

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


class Display {
protected:
	TFT_eSPI 				tft	= TFT_eSPI();
	ScreenOrientationType	_eScreenOrientation= eUSBLeft;
	//int					_wRotation;

public:
	Display();
/*
	Display() {
		Serial << "Display::Display(): " << szFileName2 << ", " << szFileDate2 << endl;}
*/

	virtual ~Display();

	//virtual void  PrintLine			(string sLineToPrint){}
	virtual void  PrintLine			(char* szLineToPrint){}
	virtual void  ClearDisplay		(){}
	//virtual void  SetupDisplay		(){}
	//virtual void  UpdateDisplay		(){}
	//virtual void  ClearZeros		(){}
};  //Display


class ColorDisplay : public Display {
public:
	ColorDisplay();
	virtual ~ColorDisplay();

	//void  PrintLine			(string sLineToPrint);
	void  PrintLine			(char* szLineToPrint);
	void  ClearDisplay      ();
	//void  SetupDisplay            ();
	//void  UpdateDisplay           ();
	//void  ClearZeros              ();
};

