// BeckTTGODisplayClass.h, 6/17/21a

#include <BeckDisplayClass.h>

class TTGODisplayClass : public DisplayClass {
public:
  TTGODisplayClass();
  virtual ~TTGODisplayClass();

  virtual void  Setup         (void){}
  virtual void  Handle        (void){}

  PUnit Invert_Y              (PUnit Y1);
  void  Print                 (const char* szTextToPrint);
  void  PrintLine             (const char* szLineToPrint);
  void  SetCursor             (PUnit CursorX, PUnit CursorY);
  void  FillScreen            (void);
  void  FillScreen            (ColorType FillColor);
  void  SetBackgroundColor    (ColorType NewBackgroundColor);
  void  SetTextColor          (ColorType NewTextColor);
  void  SetTextBGColor        (ColorType NewTextBGColor);
  void  SetFillColor          (ColorType NewFillColor);
  void  SetLineColor          (ColorType NewLineColor);
  void  SetFreeFont           (const GFXfont *Font);
  void  SelectFont            (FontFaceType eFontFace, FontPointType eFontPoint);
  void  DrawLine              (PUnit X1, PUnit Y1, PUnit X2, PUnit Y2);
  void  DrawRectangle         (PUnit XLeft, PUnit YTop, PUnit Width, PUnit Height);
  void  DrawFilledRectangle   (PUnit XLeft, PUnit YTop, PUnit Width, PUnit Height);
  void  DrawFilledCircle      (PUnit XCenter, PUnit YCenter, PUnit Radius);
  void  DrawGrid              (void);

protected:
};  //TTGODisplayClass
//Last line.
