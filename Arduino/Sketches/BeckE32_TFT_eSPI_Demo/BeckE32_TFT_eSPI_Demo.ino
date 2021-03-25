const char szSketchName[]  = "BeckE32_TFT_eSPI_Demo.ino";
const char szFileDate[]    = "3/25/21b";

//#include <SPI.h>
#include <TFT_eSPI.h>
#include <Streaming.h>

TFT_eSPI tft = TFT_eSPI();

void setup(void) {
  Serial.begin(115200);
  delay(100);
  Serial << endl << "setup(): Sketch: " << szSketchName << ", " << szFileDate << endl;

  // Initialize color screen
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);

  // Set starting coordinates (x, y), font 4
  //tft.setCursor(20, 10, 4);
  tft.setCursor(0, 0, 4);

  // Set text color to white, black text background
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  // Set the displayed text. Note that there is a line break here \ n
  //tft.println("White #4\n");
  tft.println("#4 456789");

  tft.setTextFont(4);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  //tft.println("Next White #4");
  tft.println("#4 456789");

  // Set starting coordinates (10, 100), font 2, text color red, white text background
  //tft.setCursor(10, 100);
  tft.setTextFont(2);
  //tft.setTextColor(TFT_RED, TFT_WHITE);
  //tft.println("Red Text, White Background");
  tft.println("#2 45678901234567");

  // Set starting coordinates (10, 140), font 4, text color green, no background setting
  //tft.setCursor(10, 140, 4);
  tft.setTextFont(4);
  tft.setTextColor(TFT_GREEN);
  //tft.println("Green text");
  tft.println("#4 456789");

  // Set starting coordinates (70, 180), font unchanged, text color blue, yellow text background
  //tft.setCursor(70, 180);
  tft.setTextFont(4);
  tft.setTextColor(TFT_BLUE, TFT_YELLOW);
  //tft.println("Blue text");
  tft.println("#4 456789");

  // Set starting coordinates (50, 220), font 4, text color yellow, no background setting
  //tft.setCursor(50, 220);
  tft.setTextFont(4);
  tft.setTextColor(TFT_YELLOW);
  //tft.println("2020-06-16");
  tft.println("#4 456789");

  // Set starting coordinates (50, 260), font 7, text color pink, no background setting
  //tft.setCursor(50, 260);
  tft.setTextFont(7);
  tft.setTextColor(TFT_PINK);
  //tft.println("20:35");
  //tft.println("20:35");
  tft.println("7234");
  tft.println("7234");

  return;
}	//setup


void loop() {
}
