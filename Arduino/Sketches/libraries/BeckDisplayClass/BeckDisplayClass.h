#pragma once
const char szFileName2[]  = "BeckDisplayClass.h";
const char szFileDate2[]  = "3/30/21d";

#include <Streaming.h>

/*
enum DisplayType{
  eNoDisplay  = 0,
  eColorTFT,
  eMonoSSD1306,
  eLastDisplayType
};
*/

class Display {
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

