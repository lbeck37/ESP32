const char szSystemFileName[]  = "BeckButtonsClass.cpp";
const char szSystemFileDate[]  = "3/20/22d";

#include <BeckButtonsClass.h>
#include <BeckCarSetClass.h>
#include <Streaming.h>

BeckButtonsClass::BeckButtonsClass(void) : _oTestButton(_cButton_Pin1) {
  Serial << "BeckButtonsClass(void): Default CTR, " << szSystemFileName << ", " << szSystemFileDate << endl;
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

/*
void BeckButtonsClass::SetupButtons() {
  Serial << "SetupButtons(): Call TireButton1/2/3/4.begin()\n";

  TireButton1.begin();
  TireButton2.begin();
  TireButton3.begin();
  TireButton4.begin();


  Serial << "SetupButtons(): Setup Callback, call onPressed(callback) for the 4 buttons\n";

  TireButton1.onPressed(onPressed1);
  TireButton2.onPressed(onPressed2);
  TireButton3.onPressed(onPressed3);
  TireButton4.onPressed(onPressed4);

  return;
} //SetupButtons
*/

void BeckButtonsClass::ReadButtons(){
/*
  TireButton1.read();   //This has to get called for onPressed() to get called back
  TireButton2.read();
  TireButton3.read();
  TireButton4.read();
*/
  return;
} //ReadButtons


void BeckButtonsClass::HandleLoop(){
  _oTestButton.read();
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
