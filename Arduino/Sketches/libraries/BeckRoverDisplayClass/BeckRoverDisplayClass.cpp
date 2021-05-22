// BeckRoverDisplayClass.cpp, 5/21/21a

#include <BeckRoverDisplayClass.h>
#include <Adafruit_GFX.h>
#include <WROVER_KIT_LCD.h>
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


RoverDisplayClass::RoverDisplayClass() {
  GLib.begin             ();
  GLib.setRotation      (_eScreenOrientation);
  GLib.setTextColor     (_TextColor, _BackgroundColor);
  GLib.fillScreen       (_FillColor);
  GLib.setCursor        (_CursorX, _CursorY);
  //GLib.setFont          (4);   //26 pixels
  return;
} //constructor

RoverDisplayClass::~RoverDisplayClass() {
  Serial << "~ColorDisplay(): Destructing" << endl;
} //destructor

//From BeckE32_RoverGraphics.ino
void RoverDisplayClass::DisplayBegin(void) {
  Serial << "RoverDisplayClass(): Call GLib.begin()" << endl;
  //Begin();
  GLib.begin();
  GLib.setRotation(1);
  //DisplayClear();
  return;
}  //DisplayBegin

void RoverDisplayClass::FillScreen(void){
  GLib.fillScreen(_BackgroundColor);
  return;
} //FillScreen(void)

void RoverDisplayClass::FillScreen(Colortype Color) {
  GLib.fillScreen(Color);
  return;
}  //FillScreen

void RoverDisplayClass::DisplayText(uint16_t usCursorX, uint16_t usCursorY, char *pcText,
                                    const GFXfont *pFont, uint8_t ucSize, Colortype Color) {
  //240x320 3.2", 10 lines => 24 pixels/line
  GLib.setFont(pFont);
  GLib.setTextColor(Color);
  GLib.setTextSize(ucSize);
  GLib.setTextWrap(false);
  GLib.setCursor(usCursorX, usCursorY);
  GLib.print(pcText);
  return;
}  //DisplayText

void RoverDisplayClass::ClearTextBackground(int16_t sUpperLeftX, int16_t sUpperLeftY, uint16_t usWidth, uint16_t usHeight){
  GLib.fillRect(sUpperLeftX, sUpperLeftY, usWidth, usHeight, _BackgroundColor);
  return;
} //ClearTextBackground

void RoverDisplayClass::DisplayLine(const GFXfont stFont, uint16_t usColor, uint16_t usCursorX, uint16_t usCursorY,
                                    uint16_t usClearWidth, uint16_t usClearHeight, char szText[],
                                    bool bClearText, uint8_t ucSize) {
/*
  int16_t           sClearXstart    = (int16_t)usCursorX - 10;
  int16_t           sClearYstart    = (int16_t)usCursorY - 18;
*/
  int16_t           sClearXstart    = max(0, ((int16_t)usCursorX - 10));
  int16_t           sClearYstart    = max(0, ((int16_t)usCursorY - 18));

  if(bClearText){
    ClearTextBackground(sClearXstart, sClearYstart, usClearWidth, usClearHeight);
  }
  DisplayText( usCursorX, usCursorY, szText, &stFont, ucSize, usColor);
  return;
} //DisplayLine

//For Adafruit_GFX support
/*
void RoverDisplayClass::Begin(void){
  GLib.begin();
  return;
}

void RoverDisplayClass::DisplayClear(void){
  GLib.begin();
  return;
}
*/

void RoverDisplayClass::SetRotation(uint8_t r){
  GLib.setRotation(r);
  return;
}

PUnit RoverDisplayClass::Invert_Y(PUnit Y1){
  return(ScreenHeight - Y1);
}

void RoverDisplayClass::SetCursor(PUnit CursorX, PUnit CursorY){
  _CursorX= CursorX;
  _CursorY= CursorY;
  GLib.setCursor(CursorX, Invert_Y(CursorY));
  return;
}

void  RoverDisplayClass::SetBackgroundColor(Colortype NewBackgroundColor){
  _BackgroundColor= NewBackgroundColor;
  return;
}

void  RoverDisplayClass::SetTextColor(Colortype NewTextColor){
  _TextColor= NewTextColor;
  GLib.setTextColor(_TextColor);
  return;
}

void  RoverDisplayClass::SetTextBGColor(Colortype NewTextBGColor){
  _TextBGColor= NewTextBGColor;
  GLib.setTextColor(_TextColor, _TextBGColor);    //No separate call to set the Text BG color.
  return;
}

void  RoverDisplayClass::SetFillColor(Colortype NewFillColor){
  _FillColor= NewFillColor;
  GLib.setTextColor(_TextColor, _TextBGColor);    //No separate call to set the Text BG color.
  return;
}

void  RoverDisplayClass::SetLineColor(Colortype NewLineColor){
  _LineColor= NewLineColor;
  GLib.setTextColor(_TextColor, _TextBGColor);    //No seperate call to set the Text BG color.
  return;
}

void RoverDisplayClass::SelectFont(FontFaceType eFontFace, FontPointType eFontPoint){
  _eFontFace    = eFontFace;
  _eFontPoint   = eFontPoint;
  switch (eFontFace){
    case eMonoFace:
      switch (eFontPoint){
/*
        case e12point:
          GLib.setFont(&FreeMonoBold12pt7b);
          break;
*/
        default:
          Serial << "RoverDisplayClass::SelectFont() Font point not yet supported= " << eFontPoint << endl;
          break;
        } //switch(eFontPoint)
      break;  //eRondoCondencedFace

    case eTextFace:
      Serial << "RoverDisplayClass::SelectFont() Font point not yet supported= " << eFontPoint << endl;
      break;
      case   eMonospacedBold:
        switch (eFontPoint){
          #ifdef MONOSPACED_BOLD_30
          case e30point:
            GLib.setFont(&Monospaced_bold_30);
          break;  //e30point
      #endif
      #ifdef MONOSPACED_BOLD_60
        case e60point:
         GLib.setFont(&Monospaced_bold_60);
        break;  //e60point
      #endif
        default:
          Serial << "RoverDisplayClass::SelectFont() Font point not yet supported= " << eFontPoint << endl;
          break;
        } //switch(eFontPoint)
        break;  //eRedressedRegularFace

        case   eRedressedRegularFace:
          switch (eFontPoint){
            #ifdef REDRESSED__REGULAR_20
              case e20point:
                 GLib.setFont(&Redressed_Regular_20);
                break;  //e20point
            #endif
            default:
              Serial << "RoverDisplayClass::SelectFont() Font point not yet supported= " << eFontPoint << endl;
              break;
            } //switch(eFontPoint)
          break;  //eRedressedRegularFace

      case eRobotoMediumFace:
        switch (eFontPoint){
          #ifdef ROBOTO_MEDIUM_40
            case e40point:
              GLib.setFont(&Roboto_Medium_40);
              break;
          #endif
          #ifdef ROBOTO_MEDIUM_100
            case e40point:
               GLib.setFont(&Roboto_Medium_100);
              break;
          #endif
          #ifdef ROBOTO_MEDIUM_150
            case e150point:
              //Serial << "RoverDisplayClass::SelectFont(): Font set to Roboto_Medium_150" << endl;
              GLib.setFont(&Roboto_Medium_150);
              break;  //ROBOTO_MEDIUM_150
          #endif
          default:
            Serial << "RoverDisplayClass::SelectFont() Font point not yet supported= " << eFontPoint << endl;
            break;
          } //switch(eFontPoint)
        break;  //eRobotoMediumFace

        case eRobotoCondensedFace:
          switch (eFontPoint){
            #ifdef ROBOTO_CONDENSED_30
              case e30point:
                   GLib.setFont(&Roboto_Condensed_30);
                break;
            #endif
            #ifdef ROBOTO_CONDENSED_130
              case e130point:
                  GLib.setFont(&Roboto_Condensed_130);
                break;
            #endif
            default:
              Serial << "RoverDisplayClass::SelectFont() Font point not supported= " << eFontPoint << endl;
              break;
          } //switch(eFontPoint)
          break;
        case eRobotoCondensedBoldFace:
          switch (eFontPoint){
            #ifdef ROBOTO_CONDENSED_BOLD_130
              case e130point:
                  GLib.setFont(&Roboto_Condensed_Bold_130);
                break;
            #endif
            default:
              Serial << "RoverDisplayClass::SelectFont() Font point not supported= " << eFontPoint << endl;
              break;
          } //switch(eFontPoint)
          break;
        default:
          Serial << "RoverDisplayClass::SelectFont() Font face not yet supported= " << eFontFace << endl;
          break;
  } //switch (eFontFace)
  return;
} //SelectFont

void RoverDisplayClass::DrawLine(PUnit X1, PUnit Y1, PUnit X2, PUnit Y2){
  GLib.drawLine(X1, Invert_Y(Y1), X2, Invert_Y(Y2), _LineColor);
  return;
}

void RoverDisplayClass::DrawRectangle(PUnit XLeft, PUnit YBottom, PUnit Width, PUnit Height){
  PUnit   X1= XLeft;
  PUnit   Y1= ScreenHeight - (YBottom + Height);
  GLib.drawRect(X1, Y1, Width, Height, _LineColor);
  return;
}

void RoverDisplayClass::DrawFilledRectangle(PUnit XLeft, PUnit YBottom, PUnit Width, PUnit Height){
  PUnit   X1= XLeft;
  PUnit   Y1= ScreenHeight - (YBottom + Height);
  GLib.fillRect(X1, Y1, Width, Height, _FillColor);
  return;
}

void RoverDisplayClass::DrawFilledCircle(PUnit XCenter, PUnit YCenter, PUnit Radius){
  GLib.fillCircle(XCenter, Invert_Y(YCenter), Radius, _FillColor);
  return;
}

//For reference, draw a grid of lines with labels under every 25 horizontal lines.
void RoverDisplayClass::DrawGrid(void){
  Serial << "RoverDisplayClass::DrawGrid()" << endl;
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

void RoverDisplayClass::Print(const char* szLineToPrint) {
  GLib.print(szLineToPrint);
  return;
} //Print

void RoverDisplayClass::PrintLine(const char* szLineToPrint) {
  GLib.println(szLineToPrint);
  return;
} //PrintLine
//Last line.
