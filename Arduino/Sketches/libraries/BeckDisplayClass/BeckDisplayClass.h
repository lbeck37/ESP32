#pragma once
const char szFileName2[]  = "BeckDisplayClass.h";
const char szFileDate2[]  = "3/30/21d";

#include <TFT_eSPI.h>
#include <Adafruit_GFX.h>
#include <Streaming.h>

/*
enum DisplayType{
  eNoDisplay  = 0,
  eColorTFT,
  eMonoSSD1306,
  eLastDisplayType
};
*/

enum USBOrientationType {
	eUSBDown= 0,
	eUSBRight,
	eUSBUp,
	eUSBLeft,
	eLastUSBOrientation
};


class Display {
protected:
	TFT_eSPI 			tft	= TFT_eSPI();
	USBOrientationType	_eUSBOrientation;
	//int					_wRotation;

public:
	//Display();
	Display() {
		Serial << "Display::Display(): " << szFileName2 << ", " << szFileDate2 << endl;}

	virtual ~Display();

	virtual void  SetupDisplay		(){}
	virtual void  ClearDisplay		(){}
	virtual void  UpdateDisplay		(){}
	//virtual void  ClearZeros		(){}
};  //Display


class ColorDisplay : public Display {
public:
	ColorDisplay();
	virtual ~ColorDisplay();

	void  SetupDisplay            ();
	void  ClearDisplay            ();
	void  UpdateDisplay           ();
	//void  ClearZeros              ();
};

