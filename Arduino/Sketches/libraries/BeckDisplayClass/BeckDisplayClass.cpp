const char szFileName[]  = "BeckDisplayClass.cpp";
const char szFileDate[]  = "4/1/21e";

#include <BeckDisplayClass.h>
#include <Redressed_Regular_20.h>
#include <Streaming.h>

//#include <Adafruit_GFX.h>
#include <gfxfont.h>

char  sz100CharBuffer[100];   //For building strings for display

Display::Display() {
  Serial << "Display::Display(): " << szFileName << ", " << szFileDate << endl;
} //constructor


Display::~Display() {
  Serial << "~Display(): Destructing" << endl;
} //destructor


ColorDisplay::ColorDisplay() {
  Serial << "ColorDisplay::ColorDisplay(): " << szFileName << ", " << szFileDate << endl;
  _eScreenOrientation   = eUSBLeft;
  _BackgroundColor      = TFT_RED;
  _TextColor            = TFT_GREEN;
  _FillColor            = TFT_RED;

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


void ColorDisplay::PrintLine(const char* szLineToPrint) {
  Serial << "ColorDisplay::PrintLine(): szLineToPrint= " << szLineToPrint << endl;

  GLib.println(szLineToPrint);
  return;
} //SetupDisplay


void ColorDisplay::FillScreen(void){
  //Leave FillColor out and you get the current background.
  Serial << "ColorDisplay::FillScreen()" << endl;

  GLib.fillScreen(_BackgroundColor);
  return;
} //ClearDisplay


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
}


void  ColorDisplay::SelectFont(FontType eFontType, FontSize eFontSize){
  Serial << "ColorDisplay::SelectFont(): eFontType= " << eFontType << ", eFontSoze= " << eFontSize << endl;
  switch (eFontType){
  case eTFTFont:
    Serial << "ColorDisplay::SelectFont(): eTFTFont selected" << endl;
    GLib.setTextFont(eFontSize);
    break;
  case eFontCreatorFont:
    Serial << "ColorDisplay::SelectFont(): eFontCreatorFont selected" << endl;
    //GLib.setFont(&Redressed_Regular_20);
    //GLib.setFreeFont(&Redressed_Regular_20);
    GLib.setFreeFont((GFXFont*)&Redressed_Regular_20);
    break;
  case eGFXFont:
    Serial << "ColorDisplay::SelectFont(): eGFXFont selected" << endl;
    Serial << "ColorDisplay::SelectFont(): eGFXFont is not yet supported." << endl;
    break;
  default:
    //GLib.set
    Serial << "ColorDisplay::SelectFont() Bad switch= " << eFontType << endl;
  }
  return;
}
//Last line.
void  SelectFont          (FontType eFontType, FontSize eFontSize);

