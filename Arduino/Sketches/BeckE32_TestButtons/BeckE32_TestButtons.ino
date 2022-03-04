const char szSketchName[]  = "BeckE32_TestButtons.ino";
const char szFileDate[]    = "3/4/22b";

#include <EasyButton.h>
#include <Streaming.h>

#include <ctime>
/*
import <iostream>;
import <chrono>;
import <iomanip>;
*/
#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

uint8_t   ucButtonPin = 15;

EasyButton RightFront_Button(ucButtonPin);    //Defaults: 35msec debounce, Pullup enabled, Returns true on button press

void onPressed(){
  Serial << "onPressed(): You pressed my button." << endl;
  //Testing chrono, Sloeber fails, AIDE doesn't?
  //chrono::duration<long long, milli> d2;
  duration<long long, milli> d2;
  duration<long, ratio(60)>> d1 {123};
  return;
} //onPressed


void setup()
{
  Serial.begin(115200);
  Serial << endl << "setup(): Begin " << szSketchName << ", " << szFileDate << endl;

  Serial << "setup(): Call RightFront_Button.begin()" << endl;
  RightFront_Button.begin();

  Serial << "setup(): Setup Callback, call RightFront_Button.onPressed(onPressed)" << endl;
  RightFront_Button.onPressed(onPressed);

  Serial << "setup(): Done" << endl;
  return;
}

void loop()
{
  RightFront_Button.read();   //This has to get called for onPressed() to get called back
  return;
} //loop
//Last line.
