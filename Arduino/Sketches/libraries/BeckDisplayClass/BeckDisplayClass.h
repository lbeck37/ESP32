#pragma once
const char szFileName2[]  = "BeckDisplayClass.h";
const char szFileDate2[]  = "4/2/21a";

#include <TFT_eSPI.h>
//#include <Adafruit_GFX.h>
//#include <Streaming.h>

//#include <string>
//using namespace std;

enum ScreenOrientationType {
  eUSBDown= 0,
  eUSBRight,
  eUSBUp,
  eUSBLeft,
  eLastUSBOrientation
};

enum FontType {
  eNoFont= 0,
  eTFTFont,
  eFontCreatorFont,
  eGFXFont,
  eLastFontType
};

typedef TFT_eSPI    GraphicsLibrary;
typedef uint32_t    Colortype;
typedef uint16_t    CursorUnit;
typedef uint8_t     FontSize;
typedef float       DegreeType;

extern char sz100CharBuffer[];    //For building strings for display

class Display {
protected:
  GraphicsLibrary         GLib                  = GraphicsLibrary();
  ScreenOrientationType   _eScreenOrientation   = eUSBLeft;
  Colortype               _BackgroundColor      = TFT_BLACK;
  Colortype               _TextColor            = TFT_WHITE;
  Colortype               _TextBGColor          = TFT_BLACK;
  Colortype               _FillColor            = TFT_RED;
  CursorUnit              _CursorX              = 0;
  CursorUnit              _CursorY              = 0;
  FontType                _FontType             = eTFTFont;

public:
  Display();
  virtual ~Display();

  virtual void  PrintLine           (const char* szLineToPrint){}
  virtual void  FillScreen          (void){}
  virtual void  FillScreen          (Colortype FillColor){}
  virtual void  SetBackgroundColor  (Colortype NewBackgroundColor){}
  virtual void  SetTextColor        (Colortype NewTextColor){}
  virtual void  SetTextBGColor      (Colortype NewTextBGColor){}
  virtual void  SelectFont          (FontType eFontType, FontSize eFontSize){}
};  //Display


class ColorDisplay : public Display {
protected:

public:
  ColorDisplay();
  virtual ~ColorDisplay();

  void  PrintLine           (const char* szLineToPrint);
  void  FillScreen          (void);
  void  FillScreen          (Colortype FillColor);
  void  SetBackgroundColor  (Colortype NewBackgroundColor);
  void  SetTextColor        (Colortype NewTextColor);
  void  SetTextBGColor      (Colortype NewTextBGColor);
  void  SelectFont          (FontType eFontType, FontSize eFontSize);
};
//Last line.
