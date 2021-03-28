const char szSketchName[]  = "BeckE32_TFT_eSPI_Demo.ino";
const char szFileDate[]    = "3/27/21b";

//#include <SPI.h>
#include <TFT_eSPI.h>
#include <Adafruit_GFX.h>
//#include <Fonts/FreeSansBold18pt7b.h>
#include <Streaming.h>

TFT_eSPI tft= TFT_eSPI();

int		wRotation;
enum USBOrientationType {
	eUSBDown= 0,
	eUSBRight,
	eUSBUp,
	eUSBLeft,
	eLastUSBOrientation
};

USBOrientationType	eUSBOrientation= eUSBLeft;
bool	bFont8Test= true;

void setup(void) {
  Serial.begin(115200);
  delay(100);
  Serial << endl << "setup(): Sketch: " << szSketchName << ", " << szFileDate << endl;

  // Initialize color screenDown
  tft.init();

  switch (eUSBOrientation){
	case eUSBDown:
	  tft.setRotation(eUSBDown);
	  tft.fillScreen(TFT_BLACK);

	  // Set starting coordinates (x, y), font 4
	  tft.setCursor(0, 0, 4);

	  tft.setTextColor(TFT_WHITE, TFT_BLACK);
	  tft.println("#4 456789");

	  tft.setTextFont(4);
	  tft.setTextColor(TFT_RED, TFT_BLACK);
	  tft.println("#4 456789");

	  tft.setTextFont(2);
	  tft.println("#2 45678901234567");

	  tft.setTextFont(4);
	  tft.setTextColor(TFT_GREEN);
	  tft.println("#4 456789");

	  tft.setTextFont(4);
	  tft.setTextColor(TFT_BLUE, TFT_YELLOW);
	  tft.println("#4 456789");

	  tft.setTextFont(4);
	  tft.setTextColor(TFT_YELLOW);
	  tft.println("#4 456789");

	  tft.setTextFont(7);
	  tft.setTextColor(TFT_PINK);
	  tft.println("7234");
	  tft.println("7234");
	  break;
  	case eUSBLeft:
	  tft.setRotation(eUSBLeft);
	  tft.fillScreen(TFT_BLACK);
	  tft.setTextColor(TFT_WHITE, TFT_BLACK);

	  // Set starting coordinates (x, y)
	  tft.setCursor(0, 0);

	  if (bFont8Test){
		  tft.setTextFont(8);	//75 pixels
		  tft.setTextColor(TFT_RED);
		  tft.print("82");
		  tft.setTextColor(TFT_GREEN);
		  tft.println("34");

		  tft.setTextColor(TFT_PINK);
		  tft.setTextFont(4);	//26 pixels
		  //tft.println("42345678901234567");
		  tft.println("The Dude Rocks567");

		  tft.setTextColor(TFT_WHITE);
		  tft.setTextFont(2);	//16 pixels
		  tft.println("223456789012345678901234567890");
		  tft.println("223456789012345678901234567890");
	  }	//if(bFont8Test)
	  else{
		  tft.setTextFont(2);	//16 pixels
		  tft.println("223456789012345678901234567890");

		  tft.setTextFont(4);	//26 pixels
		  tft.println("42345678901234567");

		  tft.setTextFont(6);	//48 pixels
		  tft.setTextColor(TFT_GREEN);
		  tft.println("62345678");

		  tft.setTextFont(7);	//48 pixels
		  tft.setTextColor(TFT_PINK);
		  tft.println("7234567");
		  break;

		  tft.setTextFont(8);	//75 pixels
		  tft.setTextColor(TFT_PINK);
		  tft.println("8234");
	    }	//if(bFont8Test)else
	break;
  	default:
		Serial << "setup(): Bad switch, eUSBOrientation= " << eUSBOrientation << endl;
	}	//switch

  return;
}	//setup


void loop() {
}
