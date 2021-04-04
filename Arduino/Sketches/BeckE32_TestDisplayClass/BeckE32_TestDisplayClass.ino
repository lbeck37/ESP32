const char szSketchName[]  = "BeckE32_TestDisplayClass.ino";
const char szFileDate[]    = "4/4/21c";

#include <BeckDisplayClass.h>
#include <Streaming.h>
#include <string>

void setup(){
	//Colortype	FillColor;

	Serial.begin(115200);
	delay(100);
	Serial << endl << "setup(): Sketch: " << szSketchName << ", " << szFileDate << endl;

	ColorDisplay cDisplay;

  //Draw rectangle, TTGO is 135 x 240
  PUnit  XLeft;
  PUnit  YTop;
  PUnit  Width;
  PUnit  Height;

  //For reference, draw series of lines, first vertical then horizontal
  PUnit StepSize    = 5;

  //Draw vertical lines
  PUnit OffsetStop  = ScreenWidth;
  for(PUnit Offset= StepSize; Offset < OffsetStop; Offset= (Offset + StepSize)){
    PUnit X1= Offset;
    PUnit X2= Offset;
    PUnit Y1= 0;
    PUnit Y2= ScreenHeight;
    cDisplay.DrawLine(X1, Y1, X2, Y2);
  }   //for

  //Draw horizontal lines
  OffsetStop  = ScreenHeight;
  for(PUnit Offset= StepSize; Offset < OffsetStop; Offset= (Offset + StepSize)){
    PUnit X1= 0;
    PUnit X2= ScreenWidth;
    PUnit Y1= Offset;
    PUnit Y2= Offset;
    cDisplay.DrawLine(X1, Y1, X2, Y2);
  }   //for


	cDisplay.SetCursor(5, 20);
  cDisplay.SelectGFXFont(eMonoFace, e12point);

  cDisplay.PrintLine("12ptA");
  cDisplay.PrintLine("12ptB");
  cDisplay.PrintLine("12ptC");

	//Test printing a string composed of "Now: " and the current "temperature".
	Serial << "setup(): Test printing the Now: temperature line." << endl;

	char* 		szStringToPrint		= "Now:";
	DegreeType	fCurrentDegF		= 37.73;

	//Construct string to print since TFT_eSPI.println only supports printing a string
	sprintf(sz100CharBuffer, "%s %6.2f", szStringToPrint, fCurrentDegF);
	cDisplay.PrintLine(sz100CharBuffer);

	return;
} //setup


void loop(){
  return;
} //loop
//Last line.
