// BeckTTGODisplayClass.h, 6/14/21a

#include <BeckDisplayClass.h>

class TTGODisplayClass : public DisplayClass {
public:
  TTGODisplayClass();
  virtual ~TTGODisplayClass();

  virtual void  Setup         (void){}
  virtual void  Handle        (void){}

  PUnit Invert_Y              (PUnit Y1);
  void  SetCursor             (PUnit CursorX, PUnit CursorY);
  void  FillScreen            (void);
  void  FillScreen            (ColorType FillColor);
  void  SetBackgroundColor    (ColorType NewBackgroundColor);
  void  SetTextColor          (ColorType NewTextColor);
  void  SetTextBGColor        (ColorType NewTextBGColor);
  void  SetFillColor          (ColorType NewFillColor);
  void  SetLineColor          (ColorType NewLineColor);
  void  SelectFont            (FontFaceType eFontFace, FontPointType eFontPoint);
  void  DrawLine              (PUnit X1, PUnit Y1, PUnit X2, PUnit Y2);
  void  DrawRectangle         (PUnit XLeft, PUnit YTop, PUnit Width, PUnit Height);
  void  DrawFilledRectangle   (PUnit XLeft, PUnit YTop, PUnit Width, PUnit Height);
  void  DrawFilledCircle      (PUnit XCenter, PUnit YCenter, PUnit Radius);
  void  DrawGrid              (void);
  void  Print                 (const char* szLineToPrint);
  void  PrintLine             (const char* szLineToPrint);

protected:
};  //TTGODisplayClass
//Last line.
