// BeckTTGODisplayClass.cpp, 5/17/21b

#include <BeckTTGODisplayClass.h>
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


TTGO_DisplayClass::TTGO_DisplayClass() {
  GLib.init             ();
  GLib.setRotation      (_eScreenOrientation);
  GLib.setTextColor     (_TextColor, _BackgroundColor);
  GLib.setTextFont      (4);   //26 pixels
  GLib.fillScreen       (_FillColor);
  //GLib.setCursor        (0, 10);             //Upper left corner, no inverting, good with text
  GLib.setCursor    (_CursorX, _CursorY);
  return;
} //constructor

TTGO_DisplayClass::~TTGO_DisplayClass() {
  Serial << "~ColorDisplay(): Destructing" << endl;
} //destructor

PUnit TTGO_DisplayClass::Invert_Y(PUnit Y1){
  return(ScreenHeight - Y1);
}

void TTGO_DisplayClass::SetCursor(PUnit CursorX, PUnit CursorY){
  _CursorX= CursorX;
  _CursorY= CursorY;
  GLib.setCursor(CursorX, Invert_Y(CursorY));
  return;
}

void  TTGO_DisplayClass::SetBackgroundColor(Colortype NewBackgroundColor){
  _BackgroundColor= NewBackgroundColor;
  return;
}

void  TTGO_DisplayClass::SetTextColor(Colortype NewTextColor){
  _TextColor= NewTextColor;
  GLib.setTextColor(_TextColor);
  return;
}

void  TTGO_DisplayClass::SetTextBGColor(Colortype NewTextBGColor){
  _TextBGColor= NewTextBGColor;
  GLib.setTextColor(_TextColor, _TextBGColor);    //No separate call to set the Text BG color.
  return;
}

void  TTGO_DisplayClass::SetFillColor(Colortype NewFillColor){
  _FillColor= NewFillColor;
  GLib.setTextColor(_TextColor, _TextBGColor);    //No separate call to set the Text BG color.
  return;
}

void  TTGO_DisplayClass::SetLineColor(Colortype NewLineColor){
  _LineColor= NewLineColor;
  GLib.setTextColor(_TextColor, _TextBGColor);    //No seperate call to set the Text BG color.
  return;
}

void TTGO_DisplayClass::SelectFont(FontFaceType eFontFace, FontPointType eFontPoint){
  _eFontFace    = eFontFace;
  _eFontPoint   = eFontPoint;
  switch (eFontFace){
    case eMonoFace:
      switch (eFontPoint){
        case e12point:
          GLib.setFreeFont(&FreeMonoBold12pt7b);
          break;
        default:
          Serial << "ColorDisplay::SelectFont() Font point not yet supported= " << eFontPoint << endl;
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
          Serial << "ColorDisplay::SelectFont() Font point not yet supported= " << eFontPoint << endl;
          break;
        } //switch(eFontPoint)
      break;
      case   eMonospacedBold:
        switch (eFontPoint){
      #ifdef MONOSPACED_BOLD_30
        case e30point:
         GLib.setFreeFont(&Monospaced_bold_30);
        break;
      #endif
      #ifdef MONOSPACED_BOLD_60
        case e60point:
         GLib.setFreeFont(&Monospaced_bold_60);
        break;
      #endif
          default:
            Serial << "ColorDisplay::SelectFont() Font point not yet supported= " << eFontPoint << endl;
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
              Serial << "ColorDisplay::SelectFont() Font point not yet supported= " << eFontPoint << endl;
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
              //Serial << "ColorDisplay::SelectFont(): Font set to Roboto_Medium_150" << endl;
              GLib.setFreeFont(&Roboto_Medium_150);
              break;
          #endif
          default:
            Serial << "ColorDisplay::SelectFont() Font point not yet supported= " << eFontPoint << endl;
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
              Serial << "ColorDisplay::SelectFont() Font point not supported= " << eFontPoint << endl;
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
              Serial << "ColorDisplay::SelectFont() Font point not supported= " << eFontPoint << endl;
              break;
          } //switch(eFontPoint)
          break;
        default:
          Serial << "ColorDisplay::SelectFont() Font face not yet supported= " << eFontFace << endl;
          break;
  } //switch (eFontFace)
  return;
} //SelectFont

void TTGO_DisplayClass::FillScreen(void){
  GLib.fillScreen(_BackgroundColor);
  return;
} //FillScreen(void)

void TTGO_DisplayClass::FillScreen(Colortype FillColor){
  GLib.fillScreen(FillColor);
  return;
} //FillScreen(ColorType)

void TTGO_DisplayClass::DrawLine(PUnit X1, PUnit Y1, PUnit X2, PUnit Y2){
  GLib.drawLine(X1, Invert_Y(Y1), X2, Invert_Y(Y2), _LineColor);
  return;
}

void TTGO_DisplayClass::DrawRectangle(PUnit XLeft, PUnit YBottom, PUnit Width, PUnit Height){
  PUnit   X1= XLeft;
  PUnit   Y1= ScreenHeight - (YBottom + Height);
  GLib.drawRect(X1, Y1, Width, Height, _LineColor);
  return;
}

void TTGO_DisplayClass::DrawFilledRectangle(PUnit XLeft, PUnit YBottom, PUnit Width, PUnit Height){
  PUnit   X1= XLeft;
  PUnit   Y1= ScreenHeight - (YBottom + Height);
  GLib.fillRect(X1, Y1, Width, Height, _FillColor);
  return;
}

void TTGO_DisplayClass::DrawFilledCircle(PUnit XCenter, PUnit YCenter, PUnit Radius){
  GLib.fillCircle(XCenter, Invert_Y(YCenter), Radius, _FillColor);
  return;
}

//For reference, draw a grid of lines with labels under every 25 horizontal lines.
void TTGO_DisplayClass::DrawGrid(void){
  Serial << "ColorDisplay::DrawGrid()" << endl;
  SetLineColor(AFXBlack);

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
  SetTextColor(AFXRed);
  for(PUnit Ypixel= 0; Ypixel < ScreenHeight; Ypixel= (Ypixel + 25)){
    PUnit X1= 0;
    SetCursor(X1, Ypixel);
    sprintf(sz100CharDisplayBuffer, "%d", Ypixel);
    Print(sz100CharDisplayBuffer);
  }   //for
  return;
} //DrawGrid

void TTGO_DisplayClass::Print(const char* szLineToPrint) {
  GLib.print(szLineToPrint);
  return;
} //Print

void TTGO_DisplayClass::PrintLine(const char* szLineToPrint) {
  GLib.println(szLineToPrint);
  return;
} //PrintLine
//Last line.
