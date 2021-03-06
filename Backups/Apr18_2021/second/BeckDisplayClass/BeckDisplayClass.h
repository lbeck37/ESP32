// 4/18/21g, BeckDisplayClass.h
#pragma once
//Initially used for TTGO ESP32 module. 135 x 240, 1.14", 240dpi display
#include <TFT_eSPI.h>

//Remove the "//" in front of the #define for a font you use
//   Mono and Text files are included in TFT_eSPI library already.
//#define REDRESSED__REGULAR_20
//#define ROBOTO_CONDENSED_30
//#define ROBOTO_MEDIUM_40
//#define ROBOTO_MEDIUM_100
#define ROBOTO_CONDENSED_130
//#define ROBOTO_CONDENSED_BOLD_130
//#define ROBOTO_MEDIUM_150

//typedef TFT_eSPI      GraphicsLibrary;
typedef int32_t       Colortype;
typedef int32_t       PUnit;        //Pixel Unit
typedef uint8_t       FontSize;
typedef float         DegreeType;

#define GraphicsLibrary   TFT_eSPI

//TTGO 1.4" display
const PUnit          ScreenWidth  = 240;
const PUnit          ScreenHeight = 135;;
//uint8_t        DegreeSymbol;

extern char           sz100CharDisplayBuffer[100];    //For building strings for display

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
  eMonoFace,
  eTextFace,                  //Adafruit 1=9px, 2= 16px, 4= 26px, 6=48pt, 7=48px 7seg, 8=75px narrow
  eRedressedRegularFace,      //20pt
  eRobotoMediumFace,          //40, 100, 150pt
  eRobotoCondensedFace,       //30, 130pt
  eRobotoCondensedBoldFace,   //130pt
  eLastFaceType
};

enum FontPointType {
  eNoFontPoint= 0,
  eText9px,
  eText16px,
  eText26px,
  eText48px,
  eText48px7seg,
  eText75px,
  eText75pxNarrow,
  e9point,
  e12point,
  e18point,
  e20point,
  e24point,
  e30point,
  e40point,
  e60point,
  e100point,
  e130point,
  e150point,
  eLastFontPointType
};

class DisplayClass {
protected:
  GraphicsLibrary         GLib                  = GraphicsLibrary();
  ScreenOrientationType   _eScreenOrientation   = eUSBLeft;
  Colortype               _BackgroundColor      = TFT_WHITE;
  Colortype               _TextColor            = TFT_BLACK;
  Colortype               _TextBGColor          = TFT_WHITE;
  Colortype               _FillColor            = TFT_WHITE;
  Colortype               _LineColor            = TFT_BLACK;
  PUnit                   _CursorX              = 0;
  PUnit                   _CursorY              = 0;
  FontLibraryType         _eFontLibrary         = eGFXFont;
  FontFaceType            _eFontFace            = eMonoFace;
  FontPointType           _eFontPoint           = e12point;

public:
  DisplayClass();
  virtual ~DisplayClass();

  PUnit Invert_Y                      (PUnit Y1);       //Implemented at the Display Class level

  virtual void  Setup                 (void){}
  virtual void  Handle                (void){}
  virtual void  SetCursor             (PUnit CursorX, PUnit CursorY){}
  virtual void  SetBackgroundColor    (Colortype NewBackgroundColor){}
  virtual void  SetTextColor          (Colortype NewTextColor){}
  virtual void  SetTextBGColor        (Colortype NewTextBGColor){}
  virtual void  SetFillColor          (Colortype NewFillColor){}
  virtual void  SetLineColor          (Colortype NewLineColor){}
  virtual void  SelectFont            (FontFaceType eFontFace, FontPointType eFontPoint){}
  virtual void  FillScreen            (void){}
  virtual void  FillScreen            (Colortype FillColor){}
  virtual void  DrawLine              (PUnit X1, PUnit Y1, PUnit X2, PUnit Y2){}
  virtual void  DrawRectangle         (PUnit XLeft, PUnit YTop, PUnit Width, PUnit Height){}
  virtual void  DrawFilledRectangle   (PUnit XLeft, PUnit YTop, PUnit Width, PUnit Height){}
  virtual void  DrawFilledCircle      (PUnit XCenter, PUnit YCenter, PUnit Radius){}
  virtual void  DrawGrid              (void){}
  virtual void  Print                 (const char* szLineToPrint){}
  virtual void  PrintLine             (const char* szLineToPrint){}
};  //DisplayClass

class TTGO_DisplayClass : public DisplayClass {
protected:
public:
  TTGO_DisplayClass();
  virtual ~TTGO_DisplayClass();

  PUnit Invert_Y              (PUnit Y1);
  void  SetCursor             (PUnit CursorX, PUnit CursorY);
  void  FillScreen            (void);
  void  FillScreen            (Colortype FillColor);
  void  SetBackgroundColor    (Colortype NewBackgroundColor);
  void  SetTextColor          (Colortype NewTextColor);
  void  SetTextBGColor        (Colortype NewTextBGColor);
  void  SetFillColor          (Colortype NewFillColor);
  void  SetLineColor          (Colortype NewLineColor);
  void  SelectFont            (FontFaceType eFontFace, FontPointType eFontPoint);
  void  DrawLine              (PUnit X1, PUnit Y1, PUnit X2, PUnit Y2);
  void  DrawRectangle         (PUnit XLeft, PUnit YTop, PUnit Width, PUnit Height);
  void  DrawFilledRectangle   (PUnit XLeft, PUnit YTop, PUnit Width, PUnit Height);
  void  DrawFilledCircle      (PUnit XCenter, PUnit YCenter, PUnit Radius);
  void  DrawGrid              (void);
  void  Print                 (const char* szLineToPrint);
  void  PrintLine             (const char* szLineToPrint);
};  //TTGO_DisplayClass
//Last line.
