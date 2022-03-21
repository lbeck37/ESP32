const char szSystemFileName[]  = "BeckButtonsClass.cpp";
const char szSystemFileDate[]  = "3/20/22d";

#include <BeckButtonsClass.h>
#include <BeckCarSetClass.h>
#include <Streaming.h>

//BeckButtonsClass::BeckButtonsClass(void) {
BeckButtonsClass::BeckButtonsClass(void) : _oTestButton(_cButton_Pin1) {
  Serial << "BeckButtonsClass(void): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
/*
  Serial << "BeckButtonsClass(void): Default CTR, Call _oTestButton= EasyButton(_cButton_Pin1)" << endl;
  _oTestButton= EasyButton(_cButton_Pin1);
*/

  Serial << "BeckButtonsClass(void): Default CTR, Call _oTestButton.begin()" << endl;
  _oTestButton.begin();
  Serial << "BeckButtonsClass(void): Default CTR, Call _oTestButton.onPressed(OnPressedTest)" << endl;
  _oTestButton.onPressed(OnPressedTest);
  return;
} //constructor

/*
BeckButtonsClass::BeckButtonsClass(BeckCarSetClass* poCarSet) {
  Serial << "BeckButtonsClass(poCarSet): CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
  _poCarSet= poCarSet;
  return;
} //constructor
*/


BeckButtonsClass::~BeckButtonsClass() {
  Serial << "~BeckButtonsClass(): Destructor" << endl;
  return;
} //destructor


void BeckButtonsClass::ReadButtons(){
  _oTestButton.read();
  return;
} //ReadButtons


void BeckButtonsClass::HandleLoop(){
  //_oTestButton.read();
  ReadButtons();
  return;
} //HandleLoop


/*
void BeckButtonsClass::HandleButton(int wSensorSet){
  Serial << "onPressed1(): You pressed Button " << wSensorSet << "\n";
  //_poCarSet->ReadSensorSet(wSensorSet);
  return;
} //HandleButton
*/

void BeckButtonsClass::OnPressedTest(){
  Serial << ": You pressed the TESTy Green button" << endl;
  return;
} //OnPressedTest

/*
void BeckButtonsClass::onPressed1(){
  int   wSensorSet= 1;
  HandleButton(wSensorSet);
  return;
} //onPressed1

void BeckButtonsClass::onPressed2(){
  int   wSensorSet= 2;
  HandleButton(wSensorSet);
  return;
} //onPressed2

void BeckButtonsClass::onPressed3(){
  int   wSensorSet= 3;
  HandleButton(wSensorSet);
  return;
} //onPressed3

void BeckButtonsClass::onPressed4(){
  int   wSensorSet= 4;
  HandleButton(wSensorSet);
  return;
} //onPressed4
*/
//Last line.
