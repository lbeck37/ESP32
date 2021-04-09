const char szFileName[]  = "BeckDisplayClass.cpp";
const char szFileDate[]  = "4/9/21a";
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

PUnit   ScreenWidth    = 240;
PUnit   ScreenHeight   = 135;
char    sz100CharBuffer[100];   //For building strings for display

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
  GLib.setCursor        (_CursorX, _CursorY);
  return;
} //SetupDisplay


ColorDisplay::~ColorDisplay() {
  Serial << "~ColorDisplay(): Destructing" << endl;
} //destructor


void ColorDisplay::SetCursor(PUnit CursorX, PUnit CursorY){
  _CursorX= CursorX;
  _CursorY= CursorY;
  GLib.setCursor(CursorX, CursorY);
  return;
}

void  ColorDisplay::SetBackgroundColor(Colortype NewBackgroundColor){
  _BackgroundColor= NewBackgroundColor;
  return;
}

void  ColorDisplay::SetTextColor(Colortype NewTextColor){
  _TextColor= NewTextColor;
  GLib.setTextColor(_TextColor);
  return;
}

void  ColorDisplay::SetTextBGColor(Colortype NewTextBGColor){
  _TextBGColor= NewTextBGColor;
  GLib.setTextColor(_TextColor, _TextBGColor);    //No seperate call to set the Text BG color.
  return;
}

void  ColorDisplay::SetFillColor(Colortype NewFillColor){
  _FillColor= NewFillColor;
  GLib.setTextColor(_TextColor, _TextBGColor);    //No seperate call to set the Text BG color.
  return;
}

void  ColorDisplay::SetLineColor(Colortype NewLineColor){
  _LineColor= NewLineColor;
  GLib.setTextColor(_TextColor, _TextBGColor);    //No seperate call to set the Text BG color.
  return;
}

void ColorDisplay::SelectFont(FontFaceType eFontFace, FontPointType eFontPoint){
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

void ColorDisplay::FillScreen(void){
  GLib.fillScreen(_BackgroundColor);
  return;
} //FillScreen(void)

void ColorDisplay::FillScreen(Colortype FillColor){
  GLib.fillScreen(FillColor);
  return;
} //FillScreen(ColorType)

void ColorDisplay::DrawLine(PUnit X1, PUnit Y1, PUnit X2, PUnit Y2){
  GLib.drawLine(X1, Y1, X2, Y2, _LineColor);
  return;
}

void ColorDisplay::DrawRectangle(PUnit XLeft, PUnit YTop, PUnit Width, PUnit Height){
  GLib.drawRect(XLeft, YTop, Width, Height, _LineColor);
  return;
}

void ColorDisplay::DrawFilledRectangle(PUnit XLeft, PUnit YTop, PUnit Width, PUnit Height){
  GLib.fillRect(XLeft, YTop, Width, Height, _FillColor);
  return;
}

void ColorDisplay::DrawFilledCircle(PUnit XCenter, PUnit YCenter, PUnit Radius){
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
  GLib.print(szLineToPrint);
  return;
} //Print

void ColorDisplay::PrintLine(const char* szLineToPrint) {
  GLib.println(szLineToPrint);
  return;
} //PrintLine

/*
ThermoColorDisplay::ThermoColorDisplay() {
  Serial << "ThermoColorDisplay::ThermoColorDisplay(): Constructing" << endl;
  return;
} //constructor


ThermoColorDisplay::~ThermoColorDisplay() {
  Serial << LOG0 << "~ThermoColorDisplay(): Destructing" << endl;
} //destructor


void ThermoColorDisplay::Update(ThermoStruct stData){
  Serial << LOG0 << "Update(): _szLastDegF= " << _szLastDegF << ", _wDisplayCount= " << _wDisplayCount << endl;
  //Format the string to display.
  sprintf(sz100CharBuffer, "%04.1f", stData.fCurrentDegF);

  //Potentially update the display every _wFrequency times that Update() is called
  bool  bUpdateDisplay= false;
  if ((_wDisplayCount++ % _wFrequency) != 0){
    if (strcmp(sz100CharBuffer, _szLastDegF) != 0){
      //Strings are not the same, so we will update the display
      bUpdateDisplay= true;
    }
    else{
      Serial << LOG0 << "Update(): DegF hasn't changed: " << _szLastDegF << " = " << sz100CharBuffer << endl;
      bUpdateDisplay= false;
    }
  }
  else{
    Serial << LOG0 << "Update(): Not MOD _Frequincy, _wDisplayCount= " << _wDisplayCount << endl;
    bUpdateDisplay= false;
  }

  if (true && !bUpdateDisplay){
    //Don't update the display.
    return;
  }

  //_wDisplayCount++;
  //Remember this string to compare to.
  strcpy(_szLastDegF, sz100CharBuffer);

  FillScreen(_BackgroundColor);
  //cDisplay.DrawGrid();

  //Show the current temperature in very large font as in "89.4"
  SetCursor     (DegF_XLeftSide, DegF_YBaseline);
  SetTextColor  (DegF_Color);
  SelectFont    (eDegF_Font, eDegF_PointSize);

  //sprintf(sz100CharBuffer, "%04.1f", stData.fCurrentDegF);
  //Print(sz100CharBuffer);

  Print(_szLastDegF);

  //Fat bar under the large current temperature display, present when thermostat is on.
  if (stData.bThermoOn){
    SetFillColor(BarColor);
  }
  else{
    SetFillColor(_BackgroundColor);
  }

  DrawFilledRectangle( BarLeft, BarTop, BarWidth, BarHeight);

  //Display setpoint and offpoint at the bottom as in "Set= 87.0, Off= 87.1"
  SetCursor(Setpoint_XLeft , Setpoint_YTop);
  SetTextColor(Setpoint_Color);
  SelectFont(eSetpoint_TextFace, eSetpoint_TextPointSize);

  sprintf(sz100CharBuffer, "Set= %4.1f    Off= %4.1f", stData.fSetpointDegF, (stData.fSetpointDegF + stData.fMaxHeatRangeF));
  Print(sz100CharBuffer);

  return;
} //Update
*/
//Last line.

