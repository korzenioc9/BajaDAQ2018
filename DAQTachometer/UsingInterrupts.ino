//--------------------------USING PULSES FROM SENSOR (BUTTON)--------------------------
#include <TimerThree.h>

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
//Pin connected to DS of 74HC595
int dataPin = 11;

int ledPin =  13;      // the number of the LED pin
int buttonPin = 2;     // the number of the pushbutton pin
volatile int buttonState = 0;         // variable for reading the pushbutton status

int rpmCount;
int rpmEncoded;
 
void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  // Attach an interrupt to the ISR vector
  attachInterrupt(0, incrementRpm, CHANGE);
  
  // Initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards
  pinMode(13, OUTPUT);    
  
  Timer3.initialize(100000); // set a timer
  Timer3.attachInterrupt( updateCluster ); // attach the service routine here
}
