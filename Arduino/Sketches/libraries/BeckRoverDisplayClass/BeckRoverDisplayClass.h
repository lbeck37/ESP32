// BeckRoverDisplayClass.h, 5/21/21a
#pragma once
#include <BeckDisplayClass.h>

class RoverDisplayClass : public DisplayClass {
public:
  RoverDisplayClass();
  virtual ~RoverDisplayClass();

  virtual void  Setup         (void){}
  virtual void  Handle        (void){}

  void  Begin                 (void);
  void  SetRotation           (uint8_t r);
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
  //From BeckE32_RoverGraphics.ino
  void  DisplayBegin          (void);
  void  DisplayText           (uint16_t usCursorX, uint16_t usCursorY, char *pcText,
                               const GFXfont *pFont, uint8_t ucSize, Colortype Color);
  //For Adafruit_GFX support
  void  DisplayClear          (void);

protected:
};  //RoverDisplayClass
//Last line.
