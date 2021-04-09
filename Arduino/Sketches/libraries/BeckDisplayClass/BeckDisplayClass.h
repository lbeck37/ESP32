#pragma once
const char szFileName2[]  = "BeckDisplayClass.h";
const char szFileDate2[]  = "4/9/21a";
//Initially used for TTGO ESP32 module. 135 x 240, 1.14", 240dpi display

#include <BeckBiotaLib.h>
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

typedef TFT_eSPI      GraphicsLibrary;
typedef int32_t       Colortype;
typedef int32_t       PUnit;        //Pixel Unit
typedef uint8_t       FontSize;
typedef float         DegreeType;

extern PUnit          ScreenWidth;
extern PUnit          ScreenHeight;
extern uint8_t        DegreeSymbol;

extern char sz100CharBuffer[];    //For building strings for display


struct ThermoStruct {
  float   fCurrentDegF;
  float   fSetpointDegF;
  float   fMaxHeatRangeF;
  bool    bThermoOn;
};

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


class Display {
protected:
  GraphicsLibrary         GLib                  = GraphicsLibrary();
  ProjectType             _eProjectType         = eThermoDev;
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
  int                     _wDisplayCount        = 0;
  int                     _wFrequency           = 5;          //Display updates every _wFrequency times Update() is called
  char                    _szLastDegF[10]       = "99.9";

public:
  Display();
  virtual ~Display();

  //virtual void  SetProjectType        (ProjectType eProjectType){}
  virtual void  Update                (ThermoStruct stData){}
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
};  //Display class


class ColorDisplay : public Display {
protected:

public:
  ColorDisplay();
  virtual ~ColorDisplay();

  //void  SetProjectType        (ProjectType eProjectType);
  //void  Update                (ThermoStruct stData);
  virtual void  Update        (ThermoStruct stData){}
  //virtual bool  bIsDataNew    (ThermoStruct stData){}
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
};  //ColorDisplay class


class ThermoColorDisplay : public ColorDisplay {
protected:
  //Show the current temperature in very large font as in "89.4"
  PUnit           DegF_XLeftSide    =  5;
  PUnit           DegF_YBaseline    = 97;
  Colortype       DegF_Color        = TFT_BLACK;
  FontFaceType    eDegF_Font        = eRobotoCondensedFace;
  FontPointType   eDegF_PointSize   = e130point;

  //Fat bar under the large current temperature display
  //Is present when thermostat (not just the heat) is on.
  PUnit     BarLeft     =   0;
  PUnit     BarTop      = 102;
  PUnit     BarWidth    = 240;
  PUnit     BarHeight   =  10;
  Colortype BarColor    = TFT_RED;

  //Display setpoint and offpoint at the bottom as in "Set= 87.0, Off= 87.1"
  PUnit           Setpoint_XLeft            = 10;
  PUnit           Setpoint_YTop             = 113;
  Colortype       Setpoint_Color            = TFT_BLACK;
  FontFaceType    eSetpoint_TextFace        = eTextFace;
  FontPointType   eSetpoint_TextPointSize   = eText26px;

public:
  ThermoColorDisplay();
  virtual ~ThermoColorDisplay();

  void  Update        (ThermoStruct stData);
  //bool  bIsDataNew    (ThermoStruct stData);
};  //ThermoColorDisplay class

//Last line.
