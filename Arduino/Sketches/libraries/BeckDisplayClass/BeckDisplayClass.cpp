const char szFileName[]  = "BeckDisplayClass.cpp";
const char szFileDate[]  = "4/5/21b";

#include <BeckDisplayClass.h>
#include <Streaming.h>

//#include <Adafruit_GFX.h>
//#include <gfxfont.h>
#include "Free_Fonts.h"
//#include <Fonts/FreeMono12pt7b.h>   //Included in TFT_eSPI
//#include <Redressed_Regular_20.h>
//#include <Roboto_Medium_40.h>
//#include <Roboto_Medium_100.h>
#include <Roboto_Medium_150.h>

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
}


void  ColorDisplay::SetFillColor(Colortype NewFillColor){
  Serial << "ColorDisplay::SetFillColor(): NewFillColor= " << NewFillColor << endl;
  _FillColor= NewFillColor;

  GLib.setTextColor(_TextColor, _TextBGColor);    //No seperate call to set the Text BG color.
  return;
}


void  ColorDisplay::SetLineColor(Colortype NewLineColor){
  Serial << "ColorDisplay::SetFillColor(): NewLineColor= " << NewLineColor << endl;
  _LineColor= NewLineColor;

  GLib.setTextColor(_TextColor, _TextBGColor);    //No seperate call to set the Text BG color.
  return;
}


//void ColorDisplay::SelectGFXFont(FontFaceType eFontFace, FontPointType eFontPoint){
void ColorDisplay::SelectFont(FontFaceType eFontFace, FontPointType eFontPoint){
  //_eFontLibrary = eGFXFont;
  _eFontFace    = eFontFace;
  _eFontPoint   = eFontPoint;

  switch (eFontFace){
    case eMonoFace:
      Serial << "ColorDisplay::SelectFont(): eMonoFace selected" << endl;
      switch (eFontPoint){
        case e12point:
          Serial << "ColorDisplay::SelectGFXFont(): Font set to FreeMonoBold12pt7b" << endl;
          GLib.setFreeFont(&FreeMonoBold12pt7b);
          break;
        default:
          Serial << "ColorDisplay::SelectFont() Font point not yet supported= " << eFontPoint << endl;
          break;
        } //switch(eFontPoint)
      break;  //Redressed_Regular_20

      case eTextFace:
        Serial << "ColorDisplay::SelectFont(): eTextFace selected" << endl;
        switch (eFontPoint){
          case e9point:
            GLib.setTextFont(1);
            break;
          default:
            Serial << "ColorDisplay::SelectFont() Font point not yet supported= " << eFontPoint << endl;
            break;
          } //switch(eFontPoint)
        break;


    case eRobotoFace:
      Serial << "ColorDisplay::SelectFont(): eRobotoFace selected" << endl;
      switch (eFontPoint){
      case e40point:
        Serial << "ColorDisplay::SelectFont(): Font set to Roboto_Medium_40" << endl;
        //GLib.setFreeFont(&Roboto_Medium_40);
        break;
      case e100point:
        Serial << "ColorDisplay::SelectFont(): Font set to Roboto_Medium_100" << endl;
        //GLib.setFreeFont(&Roboto_Medium_100);
      case e150point:
        Serial << "ColorDisplay::SelectFont(): Font set to Roboto_Medium_150" << endl;
        GLib.setFreeFont(&Roboto_Medium_150);
        break;
      default:
        Serial << "ColorDisplay::SelectFont() Font point not yet supported= " << eFontPoint << endl;
        break;
      } //switch(eFontPoint)
      break;

    default:
      Serial << "ColorDisplay::SelectFont() Font face not yet supported= " << eFontFace << endl;
      break;
  } //switch (eFontFace)
  return;
} //SelectFont


void ColorDisplay::FillScreen(Colortype FillColor){
  Serial << "ColorDisplay::FillScreen(FillColor), FillColor= " << FillColor << endl;

  GLib.fillScreen(FillColor);
  return;
} //FillScreen


void ColorDisplay::DrawLine(PUnit X1, PUnit Y1, PUnit X2, PUnit Y2){
  GLib.drawLine(X1, Y1, X2, Y2, _LineColor);
  return;
}


void ColorDisplay::DrawRectangle(PUnit XLeft, PUnit YTop, PUnit Width, PUnit Height){
  GLib.drawRect(XLeft, YTop, Width, Height, _LineColor);
  return;
}


void ColorDisplay::Print(const char* szLineToPrint) {
  Serial << "ColorDisplay::PrintLine(): szLineToPrint= " << szLineToPrint << endl;

  GLib.print(szLineToPrint);
  return;
} //Print


void ColorDisplay::PrintLine(const char* szLineToPrint) {
  Serial << "ColorDisplay::PrintLine(): szLineToPrint= " << szLineToPrint << endl;

  GLib.println(szLineToPrint);
  return;
} //PrintLine
//Last line.

