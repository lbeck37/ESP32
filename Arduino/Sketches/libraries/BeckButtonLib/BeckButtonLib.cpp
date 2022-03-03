const char szSystemFileName[]  = "BeckButtonLib.cpp";
const char szSystemFileDate[]  = "3/3/22b";

#include <EasyButton.h>
#include <Streaming.h>
#define DO_BUTTONS    false

static const int       sUp                   = 0;
static const int       sDown                 = 1;

static const boolean   bButtonPullUp         = true;

//Digital Pins
static const int       sUpButton             =  2;
static const int       sDownButton           =  4;

static const int       sMaxButtonPresses  = 10;

//Create EasyButton objects to handle button presses.
/*
EasyButton UpButton     (sUpButton,     NULL, CALL_NONE, bButtonPullUp);
EasyButton DownButton   (sDownButton,   NULL, CALL_NONE, bButtonPullUp);
*/
EasyButton UpButton     (sUpButton);
EasyButton DownButton   (sDownButton);

//Number of unhandled presses, up to sMaxButtonPresses
static int              sButtonCount[]       = { 0, 0, 0};
static boolean          abButtonBeingHeld[]  = { false, false, false};

static boolean     bButtonsChanged          = true;

void CheckButtons(void) {
/*Algorithm to determine when a button has been pressed or held.
 * Use IsRelease() to indicate the button has been pressed
 * Use IsHold() to indicate the button has been held down
 * States (Initial idea, not sure how close method is to this 4/25/15)
 *    0 - Button open
 *    1 - Button pressed, IsPushed() returned true once
 *          Moves State to 2 when InPush() first returns true
 *    2 - InPush() returning true, button is down
 *    3 - IsRelease() returned true, button has been released
 *          Moves State to 0
 *    4 - IsHold() returned true, button  held past threshhold
 *          Moves State to 0 when IsRelease returns true.
 * sUpButtonCount will be:
 *    0   Nothing to be done
 *   99   Button was held and not yet released
 *   1-10 Number of button presses not yet handled, max 10
 */
  //static int   sLocalButtonState[]  = {0, 0};
  boolean      bReturn              = false;
  int          sButton;

#if DO_BUTTONS
  UpButton.update();
  DownButton.update();
  //SelectButton.update();

   //Run through the buttons, use short-circuiting to select
   for (sButton= sUp; sButton <= sDown; sButton++) {
      //Check for IsRelease for all buttons.
      if ( ((sButton == sUp)   && UpButton.IsRelease  ()) ||
      ((sButton == sDown) && DownButton.IsRelease()) ) {
         Serial << sLineCount++ << " sCheckButtons(): Button " << sButton
                << " was released." << endl;
         //Check to see if button is being held
         //if (sLocalButtonState[sButton] != sButtonHeld) {
         if ( !abButtonBeingHeld[sButton]) {
            if (sButtonCount[sButton] < sMaxButtonPresses) {
               //Increment the count of button presses to be handled.
               //Serial << sLineCount++ << " sCheckButtons(): Button " << sButton << " count incremented." << endl;
               sButtonCount[sButton]++;
               bButtonsChanged= true;
            } //if(sLocalUpButtonState!=sButtonHeld)
         }    //if(sLocalButtonState!=...
         else {
            //The button was being held down, update the state variable..
            Serial << sLineCount++ << " sCheckButtons(): Button " << sButton
                   << " done being held." << endl;
            //sLocalButtonState[sButton]= sButtonOpen;
            abButtonBeingHeld[sButton]= false;
         } //if(sLocalUpButtonState!=sButtonHeld)else
         bReturn= true;
      }   //if(((sButton==sUp)&&...

      //Check IsHold for up and down buttons.
      if (!bReturn &&
      (((sButton == sUp)   && UpButton.IsHold  ()) ||
       ((sButton == sDown) && DownButton.IsHold()) )) {
         Serial << sLineCount++ << " sCheckButtons(): Button " << sButton
                << " being held." << endl;
         //Set state to indicate in hold.
         //sLocalButtonState[sButton]= sButtonHeld;
         //sButtonCount[sButton]= sHoldCode;
         abButtonBeingHeld[sButton] = true;
         sButtonCount[sButton]      = 0;  //Clear the count
         bButtonsChanged= true;
      }   //if(!bReturn&&UpButton.IsHold()
      bReturn= false;
   } //for (sButton= sUp...
#endif  //DO_BUTTONS
  return;
}  //CheckButtons


void TestButtonPins() {
  int sUpButtonLocal    = 2;
  int sDownButtonLocal  = 4;
  Serial << "SetupPins(): Call pinMode(" << sUpButtonLocal << ", INPUT_PULLUP) for Up" << endl;
  pinMode(sUpButtonLocal, INPUT_PULLUP);

  Serial << "SetupPins(): Call pinMode(" << sDownButtonLocal << ", INPUT_PULLUP) for Down" << endl;
  pinMode(sDownButtonLocal, INPUT_PULLUP);

  int sValueUp;
  int sValueDown;
  for (int i= 0; i<10; i++){
    Serial << "SetupPins(): Read buttons, Try= " << i << endl;
    sValueUp= digitalRead(sUpButtonLocal);
    sValueDown= digitalRead(sDownButtonLocal);
    Serial << "SetupPins(): Read buttons, Pin "
        << sUpButtonLocal << "= " << sValueUp << ", Pin " << sDownButtonLocal <<  "= " << sValueDown << endl;
    delay(1000);
  } //for(inti= 0;...
  return;
}  //TestButtonPins
//Last line.
