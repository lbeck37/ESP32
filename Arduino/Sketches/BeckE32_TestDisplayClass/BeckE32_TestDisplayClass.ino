const char szSketchName[]  = "BeckE32_TestDisplayClass.ino";
const char szFileDate[]    = "4/6/21d";

#include <BeckDisplayClass.h>
#include <Streaming.h>

void setup(){
	Serial.begin(115200);
	delay(100);
	Serial << endl << "setup(): Sketch: " << szSketchName << ", " << szFileDate << endl;

	ColorDisplay cDisplay;

/*
  PUnit  XLeft;
  PUnit  YTop;
  PUnit  Width;
  PUnit  Height;
*/
  cDisplay.FillScreen(TFT_WHITE);
  //cDisplay.DrawGrid();

//For reference, draw series of lines, first vertical then horizontal
#if false
  cDisplay.SetLineColor(TFT_BLACK);
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

  //Put label under lines every 25 pixels (5 lines)
  //PUnit OffsetStop  = ScreenWidth;
  cDisplay.SelectFont(eTextFace, eText9px);
  cDisplay.SetTextColor(TFT_RED);
  for(PUnit Ypixel= 0; Ypixel < ScreenHeight; Ypixel= (Ypixel + 25)){
    PUnit X1= 0;
    cDisplay.SetCursor(X1, Ypixel);
    sprintf(sz100CharBuffer, "%d", Ypixel);
    cDisplay.Print(sz100CharBuffer);
  }   //for
#endif


  //cDisplay.Print("86.");
  //uint8_t    ucDegreeSymbol = '\xA7';   //Decimal 167
  //uint8_t    ucTilde        = '\x7E';
  //uint8_t    ucTestChar     = '\x7A';
  //sprintf(sz100CharBuffer, "%04.1f%c", 86.9, ucTestChar);

  //cDisplay.SelectFont(eMonoFace, e12point);
  //cDisplay.SelectFont(eRobotoCondensedFace, e30point);
  //cDisplay.SelectFont(eRobotoMediumFace, e150point);

  //Test readability of color combo
  //cDisplay.SetCursor(0, 5);
  //cDisplay.SetCursor(0, 115);

  //Red text on white
  cDisplay.SetTextColor(TFT_RED);

  float   fDummyCurrentF  = 89.5;
  float   fDummySetF      = 87.0;
  float   fDummyOffF      = 87.1;

  PUnit   XLeftDegF =  5;
  PUnit   YBaseline   = 95 + 2;
  cDisplay.SetCursor(XLeftDegF, YBaseline);
  cDisplay.SelectFont(eRobotoCondensedFace, e130point);
  sprintf(sz100CharBuffer, "%04.1f", fDummyCurrentF);
  cDisplay.Print(sz100CharBuffer);

/*
  //Green circle when on.
  PUnit   XCenter   =  20;  //Was 222, 118, 15
  PUnit   YCenter   = 114;
  PUnit   Radius    =  19;
  cDisplay.DrawFilledCircle( XCenter, YCenter, Radius, TFT_GREEN);
*/
  //Green line at top when on.
  PUnit   BarLeft   = 0;  // PUnit XLeft, PUnit YTop, PUnit Width, PUnit Height
  PUnit   BarTop    = 100 + 2;
  PUnit   BarWidth  = 240;
  PUnit   BarHeight = 10;
  cDisplay.SetFillColor(TFT_BLACK);
  cDisplay.DrawFilledRectangle( BarLeft, BarTop, BarWidth, BarHeight);

  //Put the lower line in "Set= 87.0, Off= 87.1"
  //cDisplay.SetCursor(0, 110);
  PUnit   XLeft = 20 - 10;
  PUnit   YTop  = 110 + 5 - 2;
  cDisplay.SetCursor(XLeft , YTop);
  //cDisplay.SelectFont(eMonoFace, e12point);
  cDisplay.SetTextColor(TFT_BLACK);
  cDisplay.SelectFont(eTextFace, eText26px);
  sprintf(sz100CharBuffer, "Set= %4.1f    Off= %4.1f", fDummySetF, fDummyOffF);
  cDisplay.Print(sz100CharBuffer);


#if false
  cDisplay.SetCursor(5, 20);
  cDisplay.SelectFont(eMonoFace, e12point);
  cDisplay.SetTextColor(TFT_RED);

  cDisplay.PrintLine("12ptA");
  //cDisplay.PrintLine("12ptB");
  //cDisplay.PrintLine("12ptC");

	//Test printing a string composed of "Now: " and the current "temperature".
	Serial << "setup(): Test printing the Now: temperature line." << endl;

	char* 		szStringToPrint		= "Now:";
	DegreeType	fCurrentDegF		= 37.73;

	//Construct string to print since TFT_eSPI.println only supports printing a string
	sprintf(sz100CharBuffer, "%s %6.2f", szStringToPrint, fCurrentDegF);
	//cDisplay.PrintLine(sz100CharBuffer);
#endif
	return;
} //setup


void loop(){
  return;
} //loop
//Last line.
