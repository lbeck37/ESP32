const char szFileName[]  = "BeckDisplayClass.cpp";
const char szFileDate[]  = "4/6/21e";

#include <BeckDisplayClass.h>
#include "Free_Fonts.h"
#include <Streaming.h>

//Scalable fonts created by Font Creator, http://oleddisplay.squix.ch/#/home
#ifdef REDRESSED__REGULAR_20
  #include <Redressed_Regular_20.h>
#endif
#ifdef ROBOTO_CONDENSED_30
  #include <Roboto_Condensed_30.h>
#endif
#ifdef ROBOTO_MEDIUM_40
  #include <Roboto_Medium_40.h>
#endif
#ifdef ROBOTO_MEDIUM_100
  #include <Roboto_Medium_100.h>
#endif
#ifdef ROBOTO_CONDENSED_130
  #include <Roboto_Condensed_130.h>
#endif
#ifdef ROBOTO_CONDENSED_BOLD_130
  #include <Roboto_Condensed_Bold_130.h>
#endif
#ifdef ROBOTO_MEDIUM_150
  #include <Roboto_Medium_150.h>
#endif

//ColorDisplay cDisplay;

PUnit     ScreenWidth    = 240;
PUnit     ScreenHeight   = 135;
//uint8_t   DegreeSymbol   = '\xA7';   //Decimal 167

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


void ColorDisplay::SelectFont(FontFaceType eFontFace, FontPointType eFontPoint){
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
      break;  //eRondoCondencedFace

    case eTextFace:
      Serial << "ColorDisplay::SelectFont(): eTextFace selected" << endl;
      switch (eFontPoint){
      case eText9px:
        Serial << "ColorDisplay::SelectFont(): Font set to Text #1 (9px)" << endl;
        GLib.setTextFont(1);
        break;
      case eText26px:
        Serial << "ColorDisplay::SelectFont(): Font set to Text #4 (26px)" << endl;
        GLib.setTextFont(4);
        break;
        default:
          Serial << "ColorDisplay::SelectFont() Font point not yet supported= " << eFontPoint << endl;
          break;
        } //switch(eFontPoint)
      break;


      case   eRedressedRegularFace:
        Serial << "ColorDisplay::SelectFont(): eRedressedRegularFace selected" << endl;
        switch (eFontPoint){
          #ifdef REDRESSED__REGULAR_20
            case e20point:
              Serial << "ColorDisplay::SelectFont(): Font set to Redressed_Regular_20" << endl;
              GLib.setFreeFont(&Redressed_Regular_20);
              break;
          #endif
          default:
            Serial << "ColorDisplay::SelectFont() Font point not yet supported= " << eFontPoint << endl;
            break;
          } //switch(eFontPoint)
        break;  //eRedressedRegularFace


      case   eRobotoMediumFace:
        Serial << "ColorDisplay::SelectFont(): eRobotoMediumFace selected" << endl;
        switch (eFontPoint){
          #ifdef ROBOTO_MEDIUM_40
            case e40point:
              Serial << "ColorDisplay::SelectFont(): Font set to Roboto_Medium_40" << endl;
              GLib.setFreeFont(&Roboto_Medium_40);
              break;
          #endif
          #ifdef ROBOTO_MEDIUM_100
            case e40point:
              Serial << "ColorDisplay::SelectFont(): Font set to Roboto_Medium_100" << endl;
              GLib.setFreeFont(&Roboto_Medium_100);
              break;
          #endif
          #ifdef ROBOTO_MEDIUM_150
            case e150point:
              Serial << "ColorDisplay::SelectFont(): Font set to Roboto_Medium_150" << endl;
              GLib.setFreeFont(&Roboto_Medium_150);
              break;
          #endif
          default:
            Serial << "ColorDisplay::SelectFont() Font point not yet supported= " << eFontPoint << endl;
            break;
          } //switch(eFontPoint)
        break;  //eRobotoMediumFace


        case eRobotoCondensedFace:
          Serial << "ColorDisplay::SelectFont(): eRobotoCondensedFace selected" << endl;
          switch (eFontPoint){
            #ifdef ROBOTO_CONDENSED_30
              case e30point:
                Serial << "ColorDisplay::SelectFont(): Font set to Roboto_Condensed_30" << endl;
                  GLib.setFreeFont(&Roboto_Condensed_30);
                break;
            #endif
            #ifdef ROBOTO_CONDENSED_130
              case e130point:
                Serial << "ColorDisplay::SelectFont(): Font set to Roboto_Condensed_130" << endl;
                  GLib.setFreeFont(&Roboto_Condensed_130);
                break;
            #endif
            default:
              Serial << "ColorDisplay::SelectFont() Font point not yet supported= " << eFontPoint << endl;
              break;
          } //switch(eFontPoint)
          break;

        case eRobotoCondensedBoldFace:
          Serial << "ColorDisplay::SelectFont(): eRobotoCondensedBoldFace selected" << endl;
          switch (eFontPoint){
            #ifdef ROBOTO_CONDENSED_BOLD_130
              case e130point:
                Serial << "ColorDisplay::SelectFont(): Font set to Roboto_Condensed_Bold_130" << endl;
                  GLib.setFreeFont(&Roboto_Condensed_Bold_130);
                break;
            #endif
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
  Serial << "ColorDisplay::DrawRectangle(): XLeft= " << XLeft << ", YTop= " << YTop <<
      ", Width= " << Width << ", Height= " << Height << endl;
  Serial << "ColorDisplay::DrawRectangle()" << endl;
  GLib.drawRect(XLeft, YTop, Width, Height, _LineColor);
  return;
}


void ColorDisplay::DrawFilledRectangle(PUnit XLeft, PUnit YTop, PUnit Width, PUnit Height){
  Serial << "ColorDisplay::DrawFilledRectangle(): XLeft= " << XLeft << ", YTop= " << YTop <<
      ", Width= " << Width << ", Height= " << Height << endl;
  GLib.fillRect(XLeft, YTop, Width, Height, _FillColor);
  return;
}


void ColorDisplay::DrawFilledCircle(PUnit XCenter, PUnit YCenter, PUnit Radius){
  Serial << "ColorDisplay::DrawFilledCircle(FillColor): Center= " << XCenter << ", " << YCenter << ", Radius= " << Radius  << endl;
  GLib.fillCircle(XCenter, YCenter, Radius, _FillColor);
  return;
}


//For reference, draw a grid of lines with labels under every 25 horizontal lines.
void ColorDisplay::DrawGrid(void){
  Serial << "ColorDisplay::DrawGrid()" << endl;
  SetLineColor(TFT_BLACK);

  //Draw vertical lines
  PUnit StepSize    = 5;
  PUnit OffsetStop  = ScreenWidth;
  for(PUnit Offset= StepSize; Offset < OffsetStop; Offset= (Offset + StepSize)){
    PUnit X1= Offset;
    PUnit X2= Offset;
    PUnit Y1= 0;
    PUnit Y2= ScreenHeight;
    DrawLine(X1, Y1, X2, Y2);
  }   //for

  //Draw horizontal lines
  OffsetStop  = ScreenHeight;
  for(PUnit Offset= StepSize; Offset < OffsetStop; Offset= (Offset + StepSize)){
    PUnit X1= 0;
    PUnit X2= ScreenWidth;
    PUnit Y1= Offset;
    PUnit Y2= Offset;
    DrawLine(X1, Y1, X2, Y2);
  }   //for

  //Put label under lines every 25 pixels (5 lines)
  SelectFont(eTextFace, eText9px);
  SetTextColor(TFT_RED);
  for(PUnit Ypixel= 0; Ypixel < ScreenHeight; Ypixel= (Ypixel + 25)){
    PUnit X1= 0;
    SetCursor(X1, Ypixel);
    sprintf(sz100CharBuffer, "%d", Ypixel);
    Print(sz100CharBuffer);
  }   //for

  return;
} //DrawGrid


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

