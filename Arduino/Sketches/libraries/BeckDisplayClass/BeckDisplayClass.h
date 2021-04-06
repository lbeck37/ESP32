#pragma once
const char szFileName2[]  = "BeckDisplayClass.h";
const char szFileDate2[]  = "4/5/21b";
//Initially used for TTGO ESP32 module. 135 x 240, 1.14", 240dpi display

#include <TFT_eSPI.h>
//#include <Adafruit_GFX.h>
//#include <Streaming.h>


enum ScreenOrientationType {
  eNoScreenOrientation= -1,
  eUSBDown,
  eUSBRight,
  eUSBUp,
  eUSBLeft,
  eLastUSBOrientationType
};

enum FontLibraryType {
  eNoFontLibrary= 0,
  eTFTFont,
  eFontCreatorFont,
  eGFXFont,
  eLastFontLibraryType
};

enum FontFaceType {
  eNoFontFace= 0,
  eTextFace,        //eTextFace are the original Adafruit 1, 2, 4, 6, 7, 8 fonts
  eRedressedFace,
  eRobotoFace,
  eSansFace,
  eMonoFace,
  eLastFaceType
};

enum FontPointType {
  eNoFontPoint= 0,
  e9point,
  e12point,
  e18point,
  e20point,
  e24point,
  e40point,
  e60point,
  e100point,
  e150point,
  eLastFontPointType
};

typedef TFT_eSPI    GraphicsLibrary;
typedef int32_t     Colortype;
typedef int32_t     PUnit;        //Pixel Unit, was CursorUnit but parameter lists were too long
typedef uint8_t     FontSize;
typedef float       DegreeType;

extern PUnit  ScreenWidth;
extern PUnit  ScreenHeight;

extern char sz100CharBuffer[];    //For building strings for display

class Display {
protected:
  GraphicsLibrary         GLib                  = GraphicsLibrary();
  ScreenOrientationType   _eScreenOrientation   = eUSBLeft;
  Colortype               _BackgroundColor      = TFT_WHITE;
  Colortype               _TextColor            = TFT_RED;
  Colortype               _TextBGColor          = TFT_WHITE;
  Colortype               _FillColor            = TFT_WHITE;
  Colortype               _LineColor            = TFT_BLACK;
  PUnit                   _CursorX              = 0;
  PUnit                   _CursorY              = 0;
  FontLibraryType         _eFontLibrary         = eGFXFont;
  FontFaceType            _eFontFace            = eMonoFace;
  FontPointType           _eFontPoint           = e12point;

public:
  Display();
  virtual ~Display();

  virtual void  SetCursor           (PUnit CursorX, PUnit CursorY){}
  virtual void  SetBackgroundColor  (Colortype NewBackgroundColor){}
  virtual void  SetTextColor        (Colortype NewTextColor){}
  virtual void  SetTextBGColor      (Colortype NewTextBGColor){}
  virtual void  SetFillColor        (Colortype NewFillColor){}
  virtual void  SetLineColor        (Colortype NewLineColor){}
  virtual void  SelectFont          (FontFaceType eFontFace, FontPointType eFontPoint){}
  virtual void  FillScreen          (Colortype FillColor){}
  virtual void  DrawLine            (PUnit X1, PUnit Y1, PUnit X2, PUnit Y2){}
  virtual void  DrawRectangle       (PUnit XLeft, PUnit YTop, PUnit Width, PUnit Height){}
  virtual void  Print               (const char* szLineToPrint){}
  virtual void  PrintLine           (const char* szLineToPrint){}
};  //Display


class ColorDisplay : public Display {
protected:

public:
  ColorDisplay();
  virtual ~ColorDisplay();

  void  SetCursor           (PUnit CursorX, PUnit CursorY);
  void  FillScreen          (Colortype FillColor);
  void  SetBackgroundColor  (Colortype NewBackgroundColor);
  void  SetTextColor        (Colortype NewTextColor);
  void  SetTextBGColor      (Colortype NewTextBGColor);
  void  SetFillColor        (Colortype NewFillColor);
  void  SetLineColor        (Colortype NewLineColor);
  void  SelectFont          (FontFaceType eFontFace, FontPointType eFontPoint);
  void  DrawLine            (PUnit X1, PUnit Y1, PUnit X2, PUnit Y2);
  void  DrawRectangle       (PUnit XLeft, PUnit YTop, PUnit Width, PUnit Height);
  void  Print               (const char* szLineToPrint);
  void  PrintLine           (const char* szLineToPrint);
};
//Last line.
