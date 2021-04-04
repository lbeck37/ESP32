#pragma once
const char szFileName2[]  = "BeckDisplayClass.h";
const char szFileDate2[]  = "4/3/21A";

#include <TFT_eSPI.h>
//#include <Adafruit_GFX.h>
//#include <Streaming.h>

//#include <string>
//using namespace std;
//Initially used for TTGO ESP32 module
//  135 x 240, 1.14", 240dpi display

enum ScreenOrientationType {
  eUSBDown= 0,
  eUSBRight,
  eUSBUp,
  eUSBLeft,
  eLastUSBOrientation
};

enum FontLibraryType {
  eNoFont= 0,
  eTFTFont,
  eFontCreatorFont,
  eGFXFont,
  eLastFontType
};

enum FontFaceType {
  eNoFontFace= 0,
  eSerifFace,
  eSansFace,
  eMonoFace,
  eLastFaceType
};

enum FontPointType {
  eNoFontPoint= 0,
  e9point,
  e12point,
  e18point,
  e24point,
  eLastFontPointType
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
  FontLibraryType         _eFontLibrary         = eGFXFont;
  FontFaceType            _eFontFace            = eMonoFace;
  FontPointType           _eFontPoint            = e12point;

public:
  Display();
  virtual ~Display();

  virtual void  SetCursor           (CursorUnit CursorX, CursorUnit CursorY){}
  virtual void  FillScreen          (Colortype FillColor){}
  virtual void  SetBackgroundColor  (Colortype NewBackgroundColor){}
  virtual void  SetTextColor        (Colortype NewTextColor){}
  virtual void  SetTextBGColor      (Colortype NewTextBGColor){}
  virtual void  SelectGFXFont       (FontFaceType eFontFace, FontPointType eFontPoint){}
  virtual void  DrawRectangle       (CursorUnit XUpperLeft, CursorUnit UpperLeft, CursorUnit Width, CursorUnit Height){}
  virtual void  PrintLine           (const char* szLineToPrint){}
};  //Display


class ColorDisplay : public Display {
protected:

public:
  ColorDisplay();
  virtual ~ColorDisplay();

  void  SetCursor           (CursorUnit CursorX, CursorUnit CursorY);
  void  FillScreen          (Colortype FillColor);
  void  SetBackgroundColor  (Colortype NewBackgroundColor);
  void  SetTextColor        (Colortype NewTextColor);
  void  SetTextBGColor      (Colortype NewTextBGColor);
  void  SelectGFXFont       (FontFaceType eFontFace, FontPointType eFontPoint);
  void  DrawRectangle       (CursorUnit XUpperLeft, CursorUnit YUpperLeft, CursorUnit Width, CursorUnit Height);
  void  PrintLine           (const char* szLineToPrint);
};
//Last line.
