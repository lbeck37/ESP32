const char szDisplayClassFileName[]  = "BeckDisplayClass.cpp";
const char szDisplayClassFileDate[]  = "4/21/21a";
#include <BeckDisplayClass.h>
#include <BeckThermostatDataClass.h>
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

char                  sz100CharDisplayBuffer[100];    //For building strings for display

TTGO_DisplayClass     BiotaDisplay;                   //So every module can use the same object

DisplayClass::DisplayClass() {
  Serial << "Display::Display(): " << szDisplayClassFileName << ", " << szDisplayClassFileDate << endl;
} //constructor

DisplayClass::~DisplayClass() {
  Serial << "~Display(): Destructing" << endl;
} //destructor

TTGO_DisplayClass::TTGO_DisplayClass() {
  Serial << "ColorDisplay::ColorDisplay(): " << szDisplayClassFileName << ", " << szDisplayClassFileDate << endl;
  GLib.init             ();
  GLib.setRotation      (_eScreenOrientation);
  GLib.setTextColor     (_TextColor, _BackgroundColor);
  GLib.setTextFont      (4);   //26 pixels
  GLib.fillScreen       (_FillColor);
  GLib.setCursor        (0, 10);             //Upper left corner, no inverting, good with text
  GLib.println("Setting up WiFi.");
  GLib.println("Why so long?");
  GLib.println("\nShould be- BOOM!");

  GLib.setCursor(_CursorX, _CursorY);
  return;
} //constructor

TTGO_DisplayClass::~TTGO_DisplayClass() {
  Serial << "~ColorDisplay(): Destructing" << endl;
} //destructor

void TTGO_DisplayClass::Setup(void){
  Serial << "TTGO_DisplayClass::Setup(): Call Handle()" << endl;
  Handle();
  return;
} //Setup

//void TTGO_DisplayClass::Handle(DisplayThermoStruct ThermoData){
void TTGO_DisplayClass::Handle(){
  //Serial << "TTGO_DisplayClass::Handle(): Begin" << endl;
  DisplayThermoOnBar        ();
  DisplaySetpointLine       ();
  DisplayHeatOnBox          ();
  DisplayCurrentSetpoint    ();
  DisplayCurrentTemperature ();
  return;
} //Handle

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

//**********************************************************************************************//
//***** Was in ThermoDisplayClass
void TTGO_DisplayClass::DisplayCurrentTemperature(){
  //Serial << "TTGO_DisplayClass::DisplayCurrentTemperature(): Begin" << endl;

  if (millis() > ulNextCurrentDegFDisplay){
    if(fCurrentDegFLast != ThermostatData.GetCurrentDegF()){
      fCurrentDegFLast= ThermostatData.GetCurrentDegF();
      Serial << "TTGO_DisplayClass::DisplayCurrentTemperature(): New fCurrentDegFLast= " << fCurrentDegFLast << endl;

      //Clear the rectangular area where the DegF is displayed
      SetFillColor(_BackgroundColor);
      PUnit YBottom= (ThermoOnBarBottom + ThermoOnBarHeight);
      DrawFilledRectangle( 0, YBottom, ScreenWidth, ScreenHeight);

      SetCursor     (DegF_XLeftSide, DegF_YBaseline);
      SetTextColor  (DegF_Color);
      SelectFont    (eDegF_Font, eDegF_PointSize);

      sprintf(sz100CharDisplayBuffer, "%04.1f", ThermostatData.GetCurrentDegF());
      Serial << "TTGO_DisplayClass::DisplayCurrentTemperature(): Writing " << sz100CharDisplayBuffer << " to the display" << endl;
      Print(sz100CharDisplayBuffer);

      //Set time for Setpoint to display, it will do same for me
      ulNextSetpointDisplay= millis() + ulCurrentDegFOnTimeMsec;

      //Set next DegF does't fire before Setpoint
      ulNextCurrentDegFDisplay= millis() + ulVeryLargeExtraWaitMsec;
    } //if(millis()>ulNextCurrentDegFDisplay)
    else{
      Serial << "TTGO_DisplayClass::DisplayCurrentTemperature(): Time not up, do nothing" << endl;
    }
  } //if(millis()>ulNextCurrentDegFDisplay)
  return;
} //DisplayCurrentTemperature

void TTGO_DisplayClass::DisplayCurrentSetpoint(){
  //Serial << "TTGO_DisplayClass::DisplayCurrentSetpoint(): Begin" << endl;
  //If the thermostat is off then do nothing, and let current temperature stay on the display
  if (!ThermostatData.GetThermostatOn()){
    return;
  } //if(!ThermostatData.GetThermostatOn())

  //if (ThermostatData.GetThermostatOn() && (millis() > ulNextSetpointDisplay)){
  if (fSetpointLast != ThermostatData.GetSetpoint()){
    fSetpointLast= ThermostatData.GetSetpoint();
    Serial << "TTGO_DisplayClass::DisplayCurrentSetpoint(): New fSetpointLast= " << fSetpointLast << endl;
    //Clear the rectangular area where the Setpoint is displayed
    SetFillColor(_BackgroundColor);
    PUnit YBottom= (ThermoOnBarBottom + ThermoOnBarHeight);
    DrawFilledRectangle( 0, YBottom, ScreenWidth, ScreenHeight);

    //Display the setpoint, don't worry about flashing, it will change infrequently
    SetCursor     (DegF_XLeftSide, DegF_YBaseline);
    SetTextColor  (ThermoSetpoint_Color);
    SelectFont    (eDegF_Font, eDegF_PointSize);
    sprintf(sz100CharDisplayBuffer, "%04.1f", ThermostatData.GetSetpoint());
    Serial << "TTGO_DisplayClass::DisplayCurrentSetpoint(): Writing " << sz100CharDisplayBuffer << " to the display" << endl;
    Print(sz100CharDisplayBuffer);

    //Set next time the CurrentDegF is displayed, it will do same for me
    ulNextCurrentDegFDisplay= millis() + ulSetpointOnTimeMsec;

    //Set so my next timeout does't fire before next DegF is able write over me
    ulNextSetpointDisplay= millis() + ulVeryLargeExtraWaitMsec;
  } //if(fSetpointLast! ThermostatData.GetSetpoint()
  return;
} //DisplayCurrentSetpoint

void TTGO_DisplayClass::DisplayThermoOnBar(){
  //Draw a fat bar, the ThermoOnBar, under the large current temperature display, present when thermostat is on.
  if (bThermoOnLast != ThermostatData.GetThermostatOn()){
    bThermoOnLast= ThermostatData.GetThermostatOn();
    if (ThermostatData.GetThermostatOn()){
      SetFillColor(ThermoOnBarColor);
      bThermoOnLast= true;
    } //if(stData.GetThermostatOn())
    else{
      SetFillColor(_BackgroundColor);
      bThermoOnLast= false;
    } //if(stData.GetThermostatOn())else
    DrawFilledRectangle(ThermoOnBarLeft, ThermoOnBarBottom, ThermoOnBarWidth, ThermoOnBarHeight);
  } //if(bThermoOnLast!=stData.GetThermostatOn())
  return;
} //DisplayThermoOnBar

void TTGO_DisplayClass::DisplaySetpointLine(){
  //Print a line with the string containing the Setpoint and Offpoint values, call it SetpointLine
  if (fSetpointLast != ThermostatData.GetSetpoint()){
    fSetpointLast= ThermostatData.GetSetpoint();

    //Clear the Setpoint area
    SetFillColor(_BackgroundColor);
    DrawFilledRectangle(0, 0, ScreenWidth, ThermoOnBarBottom);

    //Display set-point and off-point at the bottom as in "Set= 87.0, Off= 87.1"
    SetCursor     (Setpoint_XLeft , Setpoint_YTop);
    SetTextColor  (Setpoint_Color);
    SelectFont    (eSetpoint_TextFace, eSetpoint_TextPointSize);

    sprintf(sz100CharDisplayBuffer, "Set= %4.1f       Off= %4.1f", ThermostatData.GetSetpoint(),
        (ThermostatData.GetSetpoint() + ThermostatData.GetMaxHeatRange()));
    Print(sz100CharDisplayBuffer);
  } //if(fSetpointLast!=stData.fSetpointDegF)
  return;
} //DisplaySetpointLine

void TTGO_DisplayClass::DisplayHeatOnBox(){
  //Draw a box, the HeatOnBox, between the Setpoint and Offpoint text, present when heat is on.
  //Draws on top of SetpointText, position it to not overwrite text
  if (bHeatOnLast != ThermostatData.GetHeatOn()){
    bHeatOnLast= ThermostatData.GetHeatOn();
    //Only turn on the HeatOn box if the thermostat is also on.
    if (ThermostatData.GetThermostatOn() && ThermostatData.GetHeatOn()){
      SetFillColor(HeatOnBoxColor);
      //bHeatOnLast= true;
    } //if(stData.GetThermostatOn())
    else{
      SetFillColor(_BackgroundColor);
      //bHeatOnLast= false;
    } //if(stData.GetThermostatOn())else
    DrawFilledRectangle( (HeatOnBoxCenter - HeatOnBoxWidth/2), HeatOnBoxBottom, HeatOnBoxWidth, HeatOnBoxHeight);
  } //if(stData.GetThermostatOn()&&...
  return;
} //DisplayHeatOnBox
//Last line.
