#include <Nextion.h>

const int led = 13;

// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;

//Declare your Nextion objects , pageid, component id., component name

NexButton b0 = NexButton(0,1,"b0");
NexButton b1 = NexButton(0,2,"b1");
NexText t0 = NexText(0,3,"t0");

// defines variables
long duration;
int distance;

//Register a button object to the touch event list

NexTouch *nex_listen_list[] = {
&b0,
&b1,
NULL
};

//Button b0 component popcallback function
// When ON button is Released the LED turns ON and the state text changes

void b0PopCallback(void *ptr){
//t0.setText ("State:ON");
digitalWrite(led,HIGH);
}

//Button b1 component popcallback function
// When OFF button is released the LED turns OFF and the state text changes

void b1PopCallback(void *ptr){
t0.setText("State:OFF");
digitalWrite(led,LOW);
}
void setup(void) {
Serial.begin(9600);
nexInit();
//Register the pop event callback function of the components

b0.attachPop(b0PopCallback,&b0);
b1.attachPop(b1PopCallback,&b1);

pinMode(led,OUTPUT);
digitalWrite(led,LOW);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input



}

void loop() {
nexLoop(nex_listen_list);
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);

}
