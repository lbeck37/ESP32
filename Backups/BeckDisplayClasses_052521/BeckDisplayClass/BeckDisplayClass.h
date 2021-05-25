// BeckDisplayClass.h, 5/22/21b
#pragma once
//Initially used for TTGO ESP32 module. 135 x 240, 1.14", 240dpi display

#include <BeckBiotaDefines.h>
#if DO_ROVER
  #include <WROVER_KIT_LCD.h>
#endif

#if DO_TTGO
  #include <TFT_eSPI.h>
#endif

//Remove the "//" in front of the #define for a font you use
//   Mono and Text files are included in TFT_eSPI library already.
//#define REDRESSED__REGULAR_20
#define MONOSPACED_BOLD_30
#define ROBOTO_CONDENSED_30
//#define ROBOTO_MEDIUM_40
#define LATO_BLACK_60
#define MONOSPACED_BOLD_60
//#define ROBOTO_MEDIUM_100
#define ROBOTO_CONDENSED_130
//#define ROBOTO_CONDENSED_BOLD_130
//#define ROBOTO_MEDIUM_150

/*
#if DO_ROVER
  typedef WROVER_KIT_LCD      GraphicsLibrary;
#endif
*/

#if DO_TTGO
  typedef TFT_eSPI            GraphicsLibrary;
#endif

//typedef int32_t       Colortype;
typedef int16_t       Colortype;      //See Adafruit_GFX.h
typedef int32_t       PUnit;          //Pixel Unit
typedef uint8_t       FontSize;
typedef float         DegreeType;

//TTGO 1.14" display
const PUnit          ScreenWidth  = 240;
const PUnit          ScreenHeight = 135;;

extern char           sz100CharDisplayBuffer[100];    //For building strings for display

// Color definitions, ripped off from WROVER_KIT_LCD.h
#define BECK_BLACK       0x0000 /*   0,   0,   0 */
#define BECK_NAVY        0x000F /*   0,   0, 128 */
#define BECK_DARKGREEN   0x03E0 /*   0, 128,   0 */
#define BECK_DARKCYAN    0x03EF /*   0, 128, 128 */
#define BECK_MAROON      0x7800 /* 128,   0,   0 */
#define BECK_PURPLE      0x780F /* 128,   0, 128 */
#define BECK_OLIVE       0x7BE0 /* 128, 128,   0 */
#define BECK_LIGHTGREY   0xC618 /* 192, 192, 192 */
#define BECK_DARKGREY    0x7BEF /* 128, 128, 128 */
#define BECK_BLUE        0x001F /*   0,   0, 255 */
#define BECK_GREEN       0x07E0 /*   0, 255,   0 */
#define BECK_CYAN        0x07FF /*   0, 255, 255 */
#define BECK_RED         0xF800 /* 255,   0,   0 */
#define BECK_MAGENTA     0xF81F /* 255,   0, 255 */
#define BECK_YELLOW      0xFFE0 /* 255, 255,   0 */
#define BECK_WHITE       0xFFFF /* 255, 255, 255 */
#define BECK_ORANGE      0xFD20 /* 255, 165,   0 */
#define BECK_GREENYELLOW 0xAFE5 /* 173, 255,  47 */
#define BECK_PINK        0xF81F

enum ScreenType{
  eNoScreenType= -1,
  eDegFScreen,
  eSetpointScreen,
  eLastScreenType
};
const int   NumberOfScreens= eLastScreenType;

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
  eLatoBlack,                 //60pt
  eMonospacedBold,            //30, 60pt
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
public:
  DisplayClass();
  virtual ~DisplayClass();

          PUnit Invert_Y              (PUnit Y1);       //Implemented at the Display Class level
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
  virtual void  DrawRectangle         (PUnit XLeft, PUnit YBottom, PUnit Width, PUnit Height){}
  virtual void  DrawFilledRectangle   (PUnit XLeft, PUnit YBottom, PUnit Width, PUnit Height){}
  virtual void  DrawFilledCircle      (PUnit XCenter, PUnit YCenter, PUnit Radius){}
  virtual void  DrawGrid              (void){}
  virtual void  Print                 (const char* szLineToPrint){}
  virtual void  PrintLine             (const char* szLineToPrint){}

protected:
#if DO_ROVER
  //WROVER_KIT_LCD          GLib    = WROVER_KIT_LCD();
  WROVER_KIT_LCD          GLib;
  //typedef WROVER_KIT_LCD      GraphicsLibrary;
#endif

#if DO_TTGO
  GraphicsLibrary         GLib                  = GraphicsLibrary();
#endif
  ScreenOrientationType   _eScreenOrientation   = eUSBLeft;
  Colortype               _BackgroundColor      = BECK_BLACK;
  Colortype               _TextColor            = BECK_WHITE;
  Colortype               _TextBGColor          = BECK_BLACK;
  Colortype               _FillColor            = BECK_GREEN;
  Colortype               _LineColor            = BECK_WHITE;
  PUnit                   _CursorX              = 0;
  PUnit                   _CursorY              = 0;
  FontLibraryType         _eFontLibrary         = eGFXFont;
  FontFaceType            _eFontFace            = eMonoFace;
  FontPointType           _eFontPoint           = e12point;
  char                    sz100CharDisplayBuffer[100];    //For building strings for display
};  //DisplayClass
//Last line.
