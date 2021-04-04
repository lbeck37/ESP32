const char szFileName[]  = "BeckDisplayClass.cpp";
const char szFileDate[]  = "4/4/21b";

#include <BeckDisplayClass.h>
#include <Streaming.h>

//#include <Adafruit_GFX.h>
//#include <gfxfont.h>
#include "Free_Fonts.h"
//#include <Fonts/FreeMono18pt7b.h>
#include <Redressed_Regular_20.h>

PUnit  ScreenWidth    = 240;
PUnit  ScreenHeight   = 135;

char  sz100CharBuffer[100];   //For building strings for display

Display::Display() {
  Serial << "Display::Display(): " << szFileName << ", " << szFileDate << endl;
} //constructor


Display::~Display() {
  Serial << "~Display(): Destructing" << endl;
} //destructor


ColorDisplay::ColorDisplay() {
  Serial << "ColorDisplay::ColorDisplay(): " << szFileName << ", " << szFileDate << endl;

  GLib.init             ();
  GLib.setRotation      (_eScreenOrientation);
  GLib.fillScreen       (_FillColor);
  GLib.setTextColor     (_TextColor, _BackgroundColor);
  GLib.setTextFont      (4);   //26 pixels

  // Set starting coordinates (x, y)
  GLib.setCursor(_CursorX, _CursorY);
  return;
} //SetupDisplay


ColorDisplay::~ColorDisplay() {
  Serial << "~ColorDisplay(): Destructing" << endl;
} //destructor


void ColorDisplay::SetCursor(PUnit CursorX, PUnit CursorY){
  Serial << "ColorDisplay::SetCursor(): CursorX= " << CursorX << ", CursorY= " << CursorY << endl;
  _CursorX= CursorX;
  _CursorY= CursorY;

  GLib.setCursor(CursorX, CursorY);
  return;
}


void ColorDisplay::PrintLine(const char* szLineToPrint) {
  Serial << "ColorDisplay::PrintLine(): szLineToPrint= " << szLineToPrint << endl;

  GLib.println(szLineToPrint);
  return;
} //SetupDisplay


void ColorDisplay::FillScreen(Colortype FillColor){
  Serial << "ColorDisplay::FillScreen(FillColor), FillColor= " << FillColor << endl;

  GLib.fillScreen(FillColor);
  return;
} //ClearDisplay


void  ColorDisplay::SetBackgroundColor(Colortype NewBackgroundColor){
  Serial << "ColorDisplay::SetBackgroundColor(): NewBackgroundColor= " << NewBackgroundColor << endl;
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

  GLib.setTextColor(_TextColor, _TextBGColor);    //No seperate call to set the Text BG color.
  return;
} //void  SetTextSize         (FontSize NewFontSize)


void ColorDisplay::SelectGFXFont(FontFaceType eFontFace, FontPointType eFontPoint){
    _eFontLibrary= eGFXFont;
    _eFontFace= eFontFace;
    _eFontPoint= eFontPoint;
  switch (eFontFace){
    case eMonoFace:
      Serial << "ColorDisplay::SelectGFXFont(): eMonoFace selected" << endl;
      switch (eFontPoint){
        case e12point:
          GLib.setFreeFont(&FreeMonoBold12pt7b);
          break;
        default:
          Serial << "ColorDisplay::SelectGFXFont() Font point not yet supported= " << eFontPoint << endl;
          break;
      } //switch(eFontPoint)
    break;
    default:
      Serial << "ColorDisplay::SelectGFXFont() Font face not yet supported= " << eFontFace << endl;
  } //switch (eFontFace)
  return;
} //SelectGFXFont


void ColorDisplay::DrawLine(PUnit X1, PUnit Y1, PUnit X2, PUnit Y2){
  GLib.drawLine(X1, Y1, X2, Y2, _LineColor);
  return;
}


void ColorDisplay::DrawRectangle(PUnit XLeft, PUnit YTop, PUnit Width, PUnit Height){
  GLib.drawRect(XLeft, YTop, Width, Height, _LineColor);
  return;
}
//Last line.

