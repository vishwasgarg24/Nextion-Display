/* 
The following sketch is an example of how to use the Nextion display with Arduino.

Connection with Arduino Uno/Nano:
* +5V = 5V
* TX  = pin 0 (RX)
* RX  = pin 1 (TX)
* GND = GND


Made by InterlinkKnight
Last update: 04/27/2018
*/




byte PotentiometerPin = A0;  // Set the pin for the potentiometer.

int PotentiometerValue;  // This variable stores the value of the potentiometer.
int GaugeValue;  // This variable stores the value that we are going to send to the gauge on the display.
int ProgressBarValue;  // This variable stores the value that we are going to send to the progress bar on the display.


int CurrentPage = 0;  // Create a variable to store which page is currently loaded







#include <Nextion.h>  // Include the nextion library (the official one) https://github.com/itead/ITEADLIB_Arduino_Nextion
                      // Make sure you edit the NexConfig.h file on the library folder to set the correct serial port for the display.
                      // By default it's set to Serial1, which most arduino boards don't have.
                      // Change "#define nexSerial Serial1" to "#define nexSerial Serial" if you are using arduino uno, nano, etc.





// Declare objects that we are going to read from the display. This includes buttons, sliders, text boxes, etc:
// Format: <type of object> <object name> = <type of object>(<page id>, <object id>, "<object name>");
/* ***** Types of objects:
 * NexButton - Button
 * NexDSButton - Dual-state Button
 * NexHotspot - Hotspot, that is like an invisible button
 * NexCheckbox - Checkbox
 * NexRadio - "Radio" checkbox, that it's exactly like the checkbox but with a rounded shape
 * NexSlider - Slider
 * NexGauge - Gauge
 * NexProgressBar - Progress Bar
 * NexText - Text box
 * NexScrolltext - Scroll text box
 * NexNumber - Number box
 * NexVariable - Variable inside the nextion display
 * NexPage - Page touch event
 * NexGpio - To use the Expansion Board add-on for Enhanced Nextion displays
 * NexRtc - To use the real time clock for Enhanced Nextion displays
 * *****
 */
NexButton b1 = NexButton(1, 2, "b1");  // Button added
NexDSButton bt0 = NexDSButton(1, 3, "bt0");  // Dual state button added



// Declare pages:
// Sending data to the display to nonexistent objects on the current page creates an error code sent by the display.
// Any error sent by the display creates lag on the arduino loop because arduino tries to read it, thinking it's a touch event.
// So to avoid this, I am only going to send data depending on the page the display is on.
// That's the reason I want the arduino to know which page is loaded on the display.
// To let arduino know what page is currently loaded, we are creating a touch event for each page.
// On the nextion project, each page most send a simulated "Touch Press Event" in the "Preinitialize Event" section so
// we can register that a new page was loaded.
NexPage page0 = NexPage(0, 0, "page0");  // Page added as a touch event
NexPage page1 = NexPage(1, 0, "page1");  // Page added as a touch event






// Declare touch event objects to the touch event list: 
// You just need to add the names of the objects that send a touch event.
// Format: &<object name>,

NexTouch *nex_listen_list[] = 
{
  &b1,  // Button added
  &bt0,  // Dual state button added
  &page0,  // Page added as a touch event
  &page1,  // Page added as a touch event

  NULL  // String terminated
};  // End of touch event list
















////////////////////////// Touch events:
// Each of the following sections are going to run everytime the touch event happens:
// Is going to run the code inside each section only ones for each touch event.

void b1PushCallback(void *ptr)  // Press event for button b1
{
  digitalWrite(13, HIGH);  // Turn ON internal LED
}  // End of press event





void b1PopCallback(void *ptr)  // Release event for button b1
{
  digitalWrite(13, LOW);  // Turn OFF internal LED
}  // End of release event









void bt0PushCallback(void *ptr)  // Press event for dual state button bt0
{
  uint32_t number5 = 0;  // Create variable to store value we are going to get
  bt0.getValue(&number5);  // Read value of dual state button to know the state (0 or 1)

  if(number5 == 1){  // If dual state button is equal to 1 (meaning is ON)...
    digitalWrite(13, HIGH);  // Turn ON internal LED
  }else{  // Since the dual state button is OFF...
    digitalWrite(13, LOW);  // Turn OFF internal LED
  }
}  // End of press event










// Page change event:
void page0PushCallback(void *ptr)  // If page 0 is loaded on the display, the following is going to execute:
{
  CurrentPage = 0;  // Set variable as 0 so from now on arduino knows page 0 is loaded on the display
}  // End of press event


// Page change event:
void page1PushCallback(void *ptr)  // If page 1 is loaded on the display, the following is going to execute:
{
  CurrentPage = 1;  // Set variable as 1 so from now on arduino knows page 1 is loaded on the display
}  // End of press event










void setup()  // Start of setup
{

  pinMode(PotentiometerPin, INPUT);  // Establish the PotentiometerPin as input.

  Serial.begin(9600);  // Start serial comunication at baud=9600. For Arduino mega you would have to add a
                       // number (example: "Serial1.begin(9600);").
                       // If you use an Arduino mega, you have to also edit everything on this sketch that
                       // says "Serial" and replace it with "Serial1" (or whatever number you are using).




  /*
  // I am going to change the Serial baud to a faster rate (optional):
  delay(500);  // This dalay is just in case the nextion display didn't start yet, to be sure it will receive the following command.
  Serial.print("baud=115200");  // Set new baud rate of nextion to 115200, but is temporal. Next time the display is
                               // powered on, it will retore to default baud rate of 9600.
                               // To take effect, make sure to reboot the arduino (reseting arduino is not enough).
                               // If you want to change the default baud rate, send the command as "bauds=115200", instead of "baud=115200".
                               // If you change default, everytime the display is powered on is going to have that baud rate.
  Serial.write(0xff);  // We always have to send this three lines after each command sent to nextion.
  Serial.write(0xff);
  Serial.write(0xff);

  Serial.end();  // End the serial comunication of baud=9600.

  Serial.begin(115200);  // Start serial comunication at baud=115200.
  */





  // Register the event callback functions of each touch event:
  // You need to register press events and release events seperatly.
  // Format for press events: <object name>.attachPush(<object name>PushCallback);
  // Format for release events: <object name>.attachPop(<object name>PopCallback);
  b1.attachPush(b1PushCallback);  // Button press
  b1.attachPop(b1PopCallback);  // Button release
  bt0.attachPush(bt0PushCallback);  // Dual state button bt0 press
  page0.attachPush(page0PushCallback);  // Page press event
  page1.attachPush(page1PushCallback);  // Page press event

  // End of registering the event callback functions

  pinMode(13, OUTPUT);









}  // End of setup








void loop()  // Start of loop
{

  delay(100);  // This is the only delay on this loop.
              // I put this delay because without it, the timer on the display would stop running.
              // The timer I am talking about is the one called tm0 on page 0 (of my example nextion project).
              // Aparently we shouldn't send data to the display too often.


  PotentiometerValue = analogRead(PotentiometerPin);  // Read the potentiometer. Value returned will be from 0 to 1023.






  if(CurrentPage == 0){  // If the display is on page 1, do the following:
  
  // We are going to send the value of the potentiometer to the object called n0:
  // After the name of the object you need to put the dot val because val is the atribute we want to change on that object.
  Serial.print("n0.val=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.print(PotentiometerValue);  // This is the value you want to send to that object and atribute mention before.
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);




  // We are going to update the text to show "Hot" when the variable is greater than 800, and show "Normal" otherwise.
  if(PotentiometerValue > 800)  // If the variable is greater than 800...
  {
    Serial.print("t0.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");  // Since we are sending text we need to send double quotes before and after the actual text.
    Serial.print("Hot");  // This is the text we want to send to that object and atribute mention before.
    Serial.print("\"");  // Since we are sending text we need to send double quotes before and after the actual text.
    Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  }
  else  // If condition was false, do the following:
  {
    Serial.print("t0.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");  // Since we are sending text we need to send double quotes before and after the actual text.
    Serial.print("Normal");  // This is the text we want to send to that object and atribute mention before.
    Serial.print("\"");  // Since we are sending text we need to send double quotes before and after the actual text.
    Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  }







  // We are going to send a value to the gauge corresponding to the potentiometer value.
  // The gauge range goes from 0 (pointing to the left) to 359.
  // The starting point of the gauge for this project is 315. When it reaches 360, it should start from 0.
  // For this reason we need to remap the values and check if is above 359 to change alter the value to start form 0.

  GaugeValue = map(PotentiometerValue, 0, 1023, 315, 585);  // Remaps values stored on PotentiometerValue from 0 to 1023 and converts them into a range from 315 to 585.

  if(GaugeValue > 359)  // If gauge value is above 359...
  {
    GaugeValue = GaugeValue - 360;  // Subtract 360 from value to continue from 0 degrees.
  }

  // Now that we have the value to send to the gauge, there are two ways to update the gauge.
/*
  // Option 1: Send the value directly to the gauge, updating the gauge every loop cycle.
  Serial.print("z0.val=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.print(GaugeValue);  // This is the value you want to send to that object and atribute mention before.
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);
*/

  // Option 2: Send the value to a variable called va0 on the display so a timer on the display (tm0) can
  // compare if the variable and the current state of the gauge are different. This way we can update the gauge only if
  // the new value for the gauge is different than the previous value.
  // This is to reduce the flickering on the gauge.
  Serial.print("va0.val=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.print(GaugeValue);  // This is the value you want to send to that object and atribute mention before.
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);











  // We are going to update the progress bar to show the value of the potentiometer.
  // The progress bar range goes from 0 to 100, so we need to remap the values:
  ProgressBarValue = map(PotentiometerValue, 0, 1023, 0, 100);  // Remaps values stored on PotentiometerValue from 0 to 1023 and converts them into a range from 0 to 100.
  
  Serial.print("j0.val=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.print(ProgressBarValue);  // This is the value you want to send to that object and atribute mention before.
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);

}







  // We are going to check the list of touch events we enter previously to
  // know if any touch event just happened, and excecute the corresponding instructions:

  nexLoop(nex_listen_list);  // Check for any touch event








}  // End of loop
