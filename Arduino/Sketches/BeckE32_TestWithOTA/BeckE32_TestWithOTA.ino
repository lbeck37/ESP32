const char szSketchName[]  = "BeckE32_TestWithOTA.ino";
const char szFileDate[]    = "3/27/22e";
//Beck: This uses a basic test case format which has WiFi and OTA support
#include <BeckE32_Defines.h>

#ifdef DO_OTA
  #undef DO_OTA
#endif
#define DO_OTA          true
#if DO_OTA
  #include <BeckE32_OTALib.h>
  #include <WiFi.h>
#endif
#include <Streaming.h>

#define TEST_ITERATOR   false
#if TEST_ITERATOR
  import <vector>;
  import <iterator>;
  import <iostream>;
#endif
#include <vector>
#include <iterator>
#include <iostream>

using namespace std;

const char*       szRouterName            = "Aspot24b";
const char*       szRouterPW              = "Qazqaz11";
const char*       szWebHostName           = "Test_Template";

unsigned long     ulNextHandleLoopMsec    =    0;
unsigned long     ulHandleLoopPeriodMsec  = 5000; //mSec between handling probes

//Protos
void setup      ();
void loop       ();
void SetupCode  ();
void LoopCode   ();

/*
template<typename Iter>
void myPrint(Iter begin, Iter end)
{
  for (auto iter{ begin }; iter != end; ++iter) {
    Serial << *iter << " ";
  }
}

void TestIterator() {
  vector values{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  for (auto iter{ cbegin(values) }; iter != cend(values); ++iter) {
    Serial << *iter << " ";
  }
  Serial << endl;

  myPrint(cbegin(values), cend(values));
  Serial << endl;
} //TestIterator
*/

void TestVector()
{
  vector<double> doubleVector(10); // Create a vector of 10 doubles.

  // Initialize max to smallest number
  double max{ -numeric_limits<double>::infinity() };

  for (size_t i{ 0 }; i < doubleVector.size(); i++) {
    Serial << format("Enter score {}: ", i + 1);
    cin >> doubleVector[i];
    if (doubleVector[i] > max) {
      max = doubleVector[i];
    }
  }

  max /= 100.0;
  for (auto& element : doubleVector) {
    element /= max;
    Serial << element << " ";
  }
  Serial << "\n";
}


void SetupCode() {
  //Put code for setting up test here.

  return;
} //SetupCode


void LoopCode() {
  if (millis() > ulNextHandleLoopMsec){
    ulNextHandleLoopMsec= millis() + ulHandleLoopPeriodMsec;
    Serial << "LoopCode(): HandleLoop timer fired\n";
    //Put code here to do every time the HandleLoop timer fires.

  } //if (millis()>ulNextHandleLoopMsec)

  return;
} //LoopCode


void setup() {
  Serial.begin(115200);
  Serial << "\nsetup(): Begin " << szSketchName << ", " << szFileDate << "\n";
  delay(500);
#if DO_OTA
  // Start WiFi and wait for connection to the network
  WiFi.begin(szRouterName, szRouterPW);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial << "\nsetup(): Connected to " << szRouterName << ", IP address to connect to is " << WiFi.localIP() << "\n";
  Serial << "setup(): Call SetupWebServer(" << szWebHostName << ")\n";
  SetupWebserver(szWebHostName);
#endif
  SetupCode();
  return;
} //setup

void loop() {
#if DO_OTA
  HandleOTAWebserver();
#endif
  LoopCode();
  return;
} //loop
//Last line.