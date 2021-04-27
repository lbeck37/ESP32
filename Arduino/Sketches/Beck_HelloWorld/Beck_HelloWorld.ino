const char szSketchName[]  = "BeckE32_HelloWorld.ino";
const char szFileDate[]    = "4/26/21j";
#include<Streaming.h>

//#define PICO_KIT

int NumberOfPins;
#ifdef PICO_KIT
//int Pins[]= {0, 2, 4, 5, 12, 13, 14, 15, 18, 19, 21, 22 , 23, 25, 26, 27, 32, 33, 34, 35, 37, 38};
int Pins[]= {0, 2, 4, 5, 12, 13, 14, 15, 18, 19, 21, 22 , 23, 25, 26, 27, 32, 33, 34, 35, 37, 38};
#else
//TTGO
int Pins[] = {2, 12, 13, 15, 25, 26, 27, 32, 33, 36, 37, 38, 39};
#endif

void setup(){
  Serial.begin(115200);
  delay(500);
  Serial << endl << "setup(): Sketch: " << szSketchName << ", " << szFileDate << endl;
#ifdef PICO_KIT
  Serial << "Setting up for Pico Kit" << endl;
#endif
  NumberOfPins = sizeof(Pins)/sizeof(Pins[0]);
  Serial << "setup(): The number of pins is: " << NumberOfPins << endl;

  Serial << "setup(): Use pinMode(pin#, OUPUT): ";
  for (int PinCount=0; PinCount < NumberOfPins; PinCount++){
    Serial << Pins[PinCount] << ", ";
    pinMode(Pins[PinCount], OUTPUT);
  } //for(intPinCount=0;...
  Serial << endl << endl;
  return;
} //setup


void loop()
{
  for (int PinState= 0; PinState <= 1; PinState++){
    Serial << "loop(): Use digitalWrite(pin#, " << PinState << ") to set pins to " << PinState << ": ";
    for (int PinCount=0; PinCount < NumberOfPins; PinCount++){
      Serial << Pins[PinCount] << ", " ;
      digitalWrite(Pins[PinCount], PinState);
    } //for(intPinCount=0;...
    Serial << endl;
    delay(5000);
  } //for(int PinState=0;...
  Serial << endl;
  return;
} //loop
//Last line.
