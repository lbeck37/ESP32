// BeckTTGODisplayClass.cpp, 6/17/21a
const char szTTGODisplayClassFileName[]  = "BeckBarClass.cpp";
const char szTTGODisplayClassFileDate[]  = "6/17/21a";


#include <BeckTTGODisplayClass.h>
#include "Free_Fonts.h"
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansOblique18pt7b.h>
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
#ifdef LATO_BLACK_60
  #include <Lato_Black_60.h>
#endif
#ifdef MONOSPACED_BOLD_30
  #include <Monospaced_Bold_30.h>
#endif
#ifdef MONOSPACED_BOLD_60
  #include <Monospaced_Bold_60.h>
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


TTGODisplayClass::TTGODisplayClass() {
  Serial << "TTGODisplayClass::TTGODisplayClass(void): " << szTTGODisplayClassFileName << ", " << szTTGODisplayClassFileDate << endl;
  GLib.init             ();
  GLib.setRotation      (_eScreenOrientation);
  GLib.setTextColor     (_TextColor, _BackgroundColor);
  GLib.setTextFont      (4);   //26 pixels
  GLib.fillScreen       (_FillColor);
  //GLib.setCursor        (0, 10);             //Upper left corner, no inverting, good with text
  GLib.setCursor        (_CursorX, _CursorY);
  return;
} //constructor

TTGODisplayClass::~TTGODisplayClass() {
  Serial << "~TTGODisplayClass(): Destructing" << endl;
} //destructor

PUnit TTGODisplayClass::Invert_Y(PUnit Y1){
  return(ScreenHeight - Y1);
}

void TTGODisplayClass::Print(const char* szTextToPrint) {
  Serial << "TTGODisplayClass::Print(): szTextToPrint=" << szTextToPrint<< endl;
  GLib.print(szTextToPrint);
  return;
} //Print

void TTGODisplayClass::PrintLine(const char* szLineToPrint) {
  Serial << "TTGODisplayClass::PrintLine(): szLineToPrint=" << szLineToPrint<< endl;
  GLib.println(szLineToPrint);
  return;
} //PrintLine

void TTGODisplayClass::SetCursor(PUnit CursorX, PUnit CursorY){
  Serial << "TTGODisplayClass::SetCursor(" << CursorX << ", " << CursorY << "): Begin" << endl;
  _CursorX= CursorX;
  _CursorY= CursorY;
  PUnit   InvertedCursorY= Invert_Y(CursorY);
  //GLib.setCursor(CursorX, Invert_Y(CursorY));
  Serial << "TTGODisplayClass::SetCursor(): Call GLib.setCursor(" << CursorX << ", " << InvertedCursorY << ")" << endl;
  GLib.setCursor(CursorX, InvertedCursorY);
  return;
}

void  TTGODisplayClass::SetBackgroundColor(ColorType NewBackgroundColor){
  _BackgroundColor= NewBackgroundColor;
  return;
}

void  TTGODisplayClass::SetTextColor(ColorType NewTextColor){
  _TextColor= NewTextColor;
  GLib.setTextColor(_TextColor);
  return;
}

void TTGODisplayClass::SetTextBGColor(ColorType NewTextBGColor){
  _TextBGColor= NewTextBGColor;
  GLib.setTextColor(_TextColor, _TextBGColor);    //No separate call to set the Text BG color.
  return;
}

void TTGODisplayClass::SetTextSize(uint8_t ucSize){
  GLib.setTextSize(ucSize);
  return;
}

void TTGODisplayClass::SetTextWrap(bool bWrap){
  Serial << "TTGODisplayClass::SetTextWrap(): bWrap= " << bWrap << endl;
  GLib.setTextWrap(bWrap);
  return;
}

void  TTGODisplayClass::SetFillColor(ColorType NewFillColor){
  _FillColor= NewFillColor;
  GLib.setTextColor(_TextColor, _TextBGColor);    //No separate call to set the Text BG color.
  return;
}

void  TTGODisplayClass::SetLineColor(ColorType NewLineColor){
  _LineColor= NewLineColor;
  GLib.setTextColor(_TextColor, _TextBGColor);    //No seperate call to set the Text BG color.
  return;
}

void TTGODisplayClass::SetFreeFont(const GFXfont *Font){
  Serial << "TTGODisplayClass::SetFreeFont(): Call GLib.setFreeFont()" << endl;
  GLib.setFreeFont(Font);
  return;
}

void TTGODisplayClass::SelectFont(FontFaceType eFontFace, FontPointType eFontPoint){
  _eFontFace    = eFontFace;
  _eFontPoint   = eFontPoint;
  Serial << "TTGODisplayClass::SelectFont(): eFontFace= " << eFontFace <<
      ", eFontPoint= " << eFontPoint << endl;
  switch (eFontFace){
    case eMonoFace:
      switch (eFontPoint){
        case e12point:
          GLib.setFreeFont(&FreeMonoBold12pt7b);
          break;
        default:
          Serial << "TTGODisplayClass::SelectFont() Font point not yet supported= " << eFontPoint << endl;
          break;
        } //switch(eFontPoint)
      break;  //eRondoCondencedFace

    case eTextFace:
      switch (eFontPoint){
      case eText9px:
        GLib.setTextFont(1);
        break;
      case eText26px:
        GLib.setTextFont(4);
        break;
        default:
          Serial << "TTGODisplayClass::SelectFont() Font point not yet supported= " << eFontPoint << endl;
          break;
        } //switch(eFontPoint)
      break;
      case   eMonospacedBold:
        switch (eFontPoint){
      #ifdef MONOSPACED_BOLD_30
        case e30point:
          Serial << "TTGODisplayClass::SelectFont(): Call SetFreeFont(&Monospaced_bold_30)" << endl;
          //GLib.setFreeFont(&Monospaced_bold_30);
          SetFreeFont(&Monospaced_bold_30);
        break;
      #endif
      #ifdef MONOSPACED_BOLD_60
        case e60point:
          GLib.setFreeFont(&Monospaced_bold_60);
        break;
      #endif
          default:
            Serial << "TTGODisplayClass::SelectFont() Font point not yet supported= " << eFontPoint << endl;
            break;
          } //switch(eFontPoint)
        break;  //eRedressedRegularFace

        case   eRedressedRegularFace:
          switch (eFontPoint){
            #ifdef REDRESSED__REGULAR_20
              case e20point:
                 GLib.setFreeFont(&Redressed_Regular_20);
                break;
            #endif
            default:
              Serial << "TTGODisplayClass::SelectFont() Font point not yet supported= " << eFontPoint << endl;
              break;
            } //switch(eFontPoint)
          break;  //eRedressedRegularFace

      case eRobotoMediumFace:
        switch (eFontPoint){
          #ifdef ROBOTO_MEDIUM_40
            case e40point:
              GLib.setFreeFont(&Roboto_Medium_40);
              break;
          #endif
          #ifdef ROBOTO_MEDIUM_100
            case e40point:
               GLib.setFreeFont(&Roboto_Medium_100);
              break;
          #endif
          #ifdef ROBOTO_MEDIUM_150
            case e150point:
              //Serial << "TTGODisplayClass::SelectFont(): Font set to Roboto_Medium_150" << endl;
              GLib.setFreeFont(&Roboto_Medium_150);
              break;
          #endif
          default:
            Serial << "TTGODisplayClass::SelectFont() Font point not yet supported= " << eFontPoint << endl;
            break;
          } //switch(eFontPoint)
        break;  //eRobotoMediumFace

        case eRobotoCondensedFace:
          switch (eFontPoint){
            #ifdef ROBOTO_CONDENSED_30
              case e30point:
                   GLib.setFreeFont(&Roboto_Condensed_30);
                break;
            #endif
            #ifdef ROBOTO_CONDENSED_130
              case e130point:
                  GLib.setFreeFont(&Roboto_Condensed_130);
                break;
            #endif
            default:
              Serial << "TTGODisplayClass::SelectFont() Font point not supported= " << eFontPoint << endl;
              break;
          } //switch(eFontPoint)
          break;
        case eRobotoCondensedBoldFace:
          switch (eFontPoint){
            #ifdef ROBOTO_CONDENSED_BOLD_130
              case e130point:
                  GLib.setFreeFont(&Roboto_Condensed_Bold_130);
                break;
            #endif
            default:
              Serial << "TTGODisplayClass::SelectFont() Font point not supported= " << eFontPoint << endl;
              break;
          } //switch(eFontPoint)
          break;
        default:
          Serial << "TTGODisplayClass::SelectFont() Font face not yet supported= " << eFontFace << endl;
          break;
  } //switch (eFontFace)
  return;
} //SelectFont

void TTGODisplayClass::FillScreen(void){
  GLib.fillScreen(_BackgroundColor);
  return;
} //FillScreen(void)

void TTGODisplayClass::FillScreen(ColorType FillColor){
  GLib.fillScreen(FillColor);
  return;
} //FillScreen(ColorType)

void TTGODisplayClass::DrawLine(PUnit X1, PUnit Y1, PUnit X2, PUnit Y2){
  GLib.drawLine(X1, Invert_Y(Y1), X2, Invert_Y(Y2), _LineColor);
  return;
}

void TTGODisplayClass::DrawRectangle(PUnit XLeft, PUnit YBottom, PUnit Width, PUnit Height){
  PUnit   X1= XLeft;
  PUnit   Y1= ScreenHeight - (YBottom + Height);
  GLib.drawRect(X1, Y1, Width, Height, _LineColor);
  return;
}

void TTGODisplayClass::DrawFilledRectangle(PUnit XLeft, PUnit YBottom, PUnit Width, PUnit Height){
  Serial << "TTGODisplayClass::DrawFilledRectangle(" << XLeft << ", " <<
      YBottom << ", " << Width << ", " << Height << "): Begin" << endl;
  PUnit   X1= XLeft;
  PUnit   Y1= ScreenHeight - (YBottom + Height);
  GLib.fillRect(X1, Y1, Width, Height, _FillColor);
  return;
}

void TTGODisplayClass::DrawFilledCircle(PUnit XCenter, PUnit YCenter, PUnit Radius){
  GLib.fillCircle(XCenter, Invert_Y(YCenter), Radius, _FillColor);
  return;
}

//For reference, draw a grid of lines with labels under every 25 horizontal lines.
void TTGODisplayClass::DrawGrid(void){
  Serial << "TTGODisplayClass::DrawGrid()" << endl;
  SetLineColor(BECK_BLACK);

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
  SetTextColor(BECK_RED);
  for(PUnit Ypixel= 0; Ypixel < ScreenHeight; Ypixel= (Ypixel + 25)){
    PUnit X1= 0;
    SetCursor(X1, Ypixel);
    sprintf(sz100CharDisplayBuffer, "%d", Ypixel);
    Print(sz100CharDisplayBuffer);
  }   //for
  return;
} //DrawGrid
//Last line.
