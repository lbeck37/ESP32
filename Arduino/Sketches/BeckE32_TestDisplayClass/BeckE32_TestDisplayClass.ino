const char szSketchName[]  = "BeckE32_TestDisplayClass.ino";
const char szFileDate[]    = "4/7/21a";

#include <BeckDisplayClass.h>
#include <Streaming.h>

void setup(){
	Serial.begin(115200);
	delay(100);
	Serial << endl << "setup(): Sketch: " << szSketchName << ", " << szFileDate << endl;

	ColorDisplay cDisplay;

  cDisplay.FillScreen(TFT_WHITE);
  //cDisplay.DrawGrid();

  float   fDummyCurrentF  = 89.5;
  float   fDummySetF      = 87.0;
  float   fDummyOffF      = 87.1;

  //Show the current temperature in very large font as in "89.4"
  PUnit   XLeftDegF =  5;
  PUnit   YBaseline = 97;
  cDisplay.SetCursor(XLeftDegF, YBaseline);
  //cDisplay.SetTextColor(TFT_RED);
  cDisplay.SetTextColor(TFT_BLACK);
  cDisplay.SelectFont(eRobotoCondensedFace, e130point);

  sprintf(sz100CharBuffer, "%04.1f", fDummyCurrentF);
  cDisplay.Print(sz100CharBuffer);

  //Black or red fat line under DegF when on.
  PUnit   BarLeft   = 0;  // PUnit XLeft, PUnit YTop, PUnit Width, PUnit Height
  PUnit   BarTop    = 102;
  PUnit   BarWidth  = 240;
  PUnit   BarHeight = 10;
  //cDisplay.SetFillColor(TFT_BLACK);
  cDisplay.SetFillColor(TFT_RED);
  cDisplay.DrawFilledRectangle( BarLeft, BarTop, BarWidth, BarHeight);

  //Put the lower line in "Set= 87.0, Off= 87.1"
  PUnit   XLeft = 10;
  PUnit   YTop  = 113;
  cDisplay.SetCursor(XLeft , YTop);
  cDisplay.SetTextColor(TFT_BLACK);
  cDisplay.SelectFont(eTextFace, eText26px);

  sprintf(sz100CharBuffer, "Set= %4.1f    Off= %4.1f", fDummySetF, fDummyOffF);
  cDisplay.Print(sz100CharBuffer);

	return;
} //setup


void loop(){
  return;
} //loop
//Last line.
