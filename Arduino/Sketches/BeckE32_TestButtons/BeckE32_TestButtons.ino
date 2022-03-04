const char szSketchName[]  = "BeckE32_TestButtons.ino";
const char szFileDate[]    = "3/4/22h";

#include <EasyButton.h>
#include <Streaming.h>

/*
import <iostream>;
import <chrono>;
import <iomanip>;
*/
#include <ctime>
#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

//Define a "rational real-time constant" representing 1/60 of a second
using r1= ratio<1, 60>;

uint8_t   ucButtonPin = 15;

EasyButton RightFront_Button(ucButtonPin);    //Defaults: 35msec debounce, Pullup enabled, Returns true on button press

void onPressed(){
  //Serial << "onPressed(): You pressed my button." << endl;
  cout << "onPressed(): You pressed my button.\n";
  Serial << "onPressed(): You pressed my button.\n";
  //Testing chrono, Sloeber fails, AIDE doesn't?
  //chrono::duration<long long, milli> d2;
  duration<long long, milli> d2;
  duration<long, ratio<60>> d1 {123};
  return;
} //onPressed


void setup()
{
  Serial.begin(115200);
  Serial << "\nsetup(): Begin " << szSketchName << ", " << szFileDate << "\n";

  Serial << "setup(): Call RightFront_Button.begin()\n";
  RightFront_Button.begin();

  Serial << "setup(): Setup Callback, call RightFront_Button.onPressed(onPressed)\n";
  RightFront_Button.onPressed(onPressed);

  Serial << "setup(): Done\n";
  return;
}

void loop()
{
  RightFront_Button.read();   //This has to get called for onPressed() to get called back
  return;
} //loop
//Last line.
