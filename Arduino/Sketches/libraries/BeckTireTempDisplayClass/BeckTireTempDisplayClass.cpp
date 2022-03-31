const char szSystemFileName[]  = "BeckTireTempDisplayClass.cpp";
const char szSystemFileDate[]  = "3/30/22e";

#include <BeckTireTempDisplayClass.h>
#include <BeckLogLib.h>
#include <Adafruit_GFX.h>
#include <Streaming.h>
#include <exception>
#include <stdexcept>

BeckTireTempDisplayClass::BeckTireTempDisplayClass() {
  Serial << "BeckTireTempDisplayClass(): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
  return;
} //constructor

BeckTireTempDisplayClass::BeckTireTempDisplayClass(BeckDataMgrClass* poDataMgr) {
  Serial << "BeckTireTempDisplayClass(poDataMgr): CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
  _poDataMgr= poDataMgr;
  return;
} //constructor

BeckTireTempDisplayClass::~BeckTireTempDisplayClass() {
  Serial << "~BeckTireTempDisplayClass(): Destructor, deleting _poTCoupleSensor" << endl;
  return;
} //destructor


void BeckTireTempDisplayClass::DisplayBegin() {
  Serial << LOG0 << "DisplayBegin(): Call RoverLCD.begin()\n";
  RoverLCD.begin();
  RoverLCD.setRotation(1);
  DisplayClear();
  return;
}  //DisplayBegin


void BeckTireTempDisplayClass::DisplaySensorSet(int wSensorSetID) {
  Serial << "BeckTireTempDisplayClass::DisplaySensorSet(): wSensorSetID= " << wSensorSetID << endl;
  if (wSensorSetID == _wLogSensorSetID){
    Serial << "BeckTireTempDisplayClass::DisplaySensorSet(): Call DisplayLogTemps()" << endl;
    DisplayLogTemps();
  } //if (wSensorSetID==_wLogSensorSetID)
  else{
    Serial << "BeckTireTempDisplayClass::DisplaySensorSet(): Call DisplayTemperature()" << endl;
    DisplayTemperature();
  } //if (wSensorSetID==_wLogSensorSetID)else
  Serial << "BeckTireTempDisplayClass::DisplaySensorSet(): Done" << endl;
  return;
}  //DisplaySensorSet


void BeckTireTempDisplayClass::DisplayLogTemps(float fDegf1, float fDegf2, float fDegf3){
  Serial << "BeckTireTempDisplayClass::DisplayLogTemps(" << fDegf1 << ", " << fDegf2 << "): Begin" << endl;

  sprintf(sz100CharString, "%6.1f   %6.1f   %6.1f", fDegf1, fDegf2, fDegf3);
  Serial << "BeckTireTempDisplayClass::DisplayLogTemps(): Call DisplayText() String= " << sz100CharString << endl;
  DisplayText( usCursorX, usCursorY, sz100CharString, pFont, ucSize, usColor);

  return;
} //DisplayLogTemps(float,float,float)
/*
void BeckTireTempDisplayClass::DisplayLogTemps(){
  Serial << "BeckTireTempDisplayClass::DisplayLogTemps():  Begin" << endl;
  const GFXfont   *pFont        = &FreeSansOblique18pt7b;
  uint16_t        usCursorX     = 45;
  uint16_t        usCursorY     = 232;    //Was 72
  uint8_t         ucSize        = 1;
  ColorType       usColor       = WROVER_CYAN;

  Serial << "BeckTireTempDisplayClass::DisplayLogTemps():  Initialize afDegF[]" << endl;
  float afDegF[_wNumSensors + 1] {0.0};


  for(int wSensor= 1; wSensor <= _wNumSensors; wSensor++){
    afDegF[wSensor]= _poDataMgr->fGetDegF(_wLogSensorSetID, wSensor);
  } //for

  Serial << "BeckTireTempDisplayClass::DisplayLogTemps():  Call _poDataMgr->TestPtr() iside a try/catch" << endl;
  try {
      _poDataMgr->TestPtr();

    //Serial << "BeckTireTempDisplayClass::DisplayLogTemps():  Check _poDataMgr= " << _poDataMgr << ", *_poDataMgr= " << *_poDataMgr << endl;
    Serial << "BeckTireTempDisplayClass::DisplayLogTemps():  Check _poDataMgr" << endl;
    if (_poDataMgr != nullptr){
      Serial << "BeckTireTempDisplayClass::DisplayLogTemps():  Call _poDataMgr->fGetDegF(1)" << endl;
      afDegF[1]= _poDataMgr->fGetDegF(_wLogSensorSetID, 1);
      Serial << "BeckTireTempDisplayClass::DisplayLogTemps():  Call _poDataMgr->fGetDegF(2)" << endl;
      afDegF[2]= _poDataMgr->fGetDegF(_wLogSensorSetID, 2);
      Serial << "BeckTireTempDisplayClass::DisplayLogTemps():  Call _poDataMgr->fGetDegF(3)" << endl;
      afDegF[3]= _poDataMgr->fGetDegF(_wLogSensorSetID, 3);
    } //if (_poDataMgr!=nullptr)
    else{
      Serial << "BeckTireTempDisplayClass::DisplayLogTemps(): _poDataMgr is a nullptr" << endl;
    } //if (_poDataMgr!=nullptr)else
  } //try

  catch (const runtime_error& e) {
    Serial << "BeckTireTempDisplayClass::DisplayLogTemps():  Call  to _poDataMgr->TestPtr() threw Exception |" << e.what() << endl;
  }

  catch (...) {
    Serial << "BeckTireTempDisplayClass::DisplayLogTemps():  Call  to _poDataMgr->TestPtr() threw Exception" << endl;
  } //catch(...)

  sprintf(sz100CharString, "%6.1f   %6.1f   %6.1f", afDegF[1], afDegF[2], afDegF[3]);
  Serial << "BeckTireTempDisplayClass::DisplayLogTemps(): Call DisplayText() String= " << sz100CharString << endl;
  DisplayText( usCursorX, usCursorY, sz100CharString, pFont, ucSize, usColor);

  return;
} //DisplayLogTemps
*/


void BeckTireTempDisplayClass::DisplayClear() {
  FillScreen(BackgroundColor);
  return;
}  //DisplayClear

void BeckTireTempDisplayClass::FillScreen(uint16_t usColor) {
  RoverLCD.fillScreen(usColor);
  return;
}  //FillScreen


void BeckTireTempDisplayClass::DisplayTemperature() {
  uint16_t          usTextCursorX   =  100;
  uint16_t          usTextCursorY   =  15;  //Zero for font is lower-left
  uint16_t          usTempCursorX   =   0;
  uint16_t          usTempCursorY   = 100;
  uint8_t           ucSize          =   1;
  ColorType       usColor         = WROVER_WHITE;
  float           fDegFValue      = 0.0;

  //if(true || TireTempData.bDegFChanged()) {
  if(true) {
    //Erase the currently displayed value by overwriting it with the background color
/*
    float fLastDegFValue= TireTempData.GetLastDegF_Value();
    sprintf(sz100CharString, "%6.1f", fLastDegFValue);
*/
    sprintf(sz100CharString, "%6.1f", 37.37);
    DisplayText( usTempCursorX, usTempCursorY, sz100CharString, &FreeMonoBold24pt7b, ucSize, BackgroundColor);

    //Display the new value
/*
    fDegFValue= TireTempData.GetDegF_Value();
    sprintf(sz100CharString, "%6.1f", fDegFValue);
    DisplayText( usTempCursorX, usTempCursorY, sz100CharString, &FreeMonoBold24pt7b, ucSize, usColor);
*/

    sprintf(sz100CharString, "Front Tires");
    DisplayText( usTextCursorX, usTextCursorY, sz100CharString, &FreeSans9pt7b, ucSize, usColor);

    usTextCursorX  =  0;
    usTextCursorY += 20;
    sprintf(sz100CharString, "179  167  159    209  104  178");
    DisplayText( usTextCursorX, usTextCursorY, sz100CharString, &FreeSans9pt7b, ucSize, usColor);

    //Set the last value to be the displayed value
    //TireTempData.SetLastDegF_Value(fDegFValue);
  } //if(TireTempData.bDegFChanged())
  return;
}  //DisplayTemperature


void BeckTireTempDisplayClass::DisplayText(uint16_t usCursorX, uint16_t usCursorY, char *pcText,
                 const GFXfont *pFont, uint8_t ucSize, uint16_t usColor) {
  //240x320 3.2", 10 lines => 24 pixels/line
  RoverLCD.setFont(pFont);
  RoverLCD.setTextColor(usColor);
  RoverLCD.setTextSize(ucSize);
  RoverLCD.setTextWrap(false);
  RoverLCD.setCursor(usCursorX, usCursorY);
  RoverLCD.print(pcText);
  return;
}  //DisplayText

void BeckTireTempDisplayClass::ClearTextBackground(INT16 sUpperLeftX, INT16 sUpperLeftY, uint16_t usWidth, uint16_t usHeight){
  RoverLCD.fillRect(sUpperLeftX, sUpperLeftY, usWidth, usHeight, BackgroundColor);
  return;
} //ClearTextBackground
//Last line.
