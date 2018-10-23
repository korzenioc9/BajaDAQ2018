/*
//--------------------------USING AVG VOLTAGE ON PIN, PWM--------------------------
#include <TimerThree.h>

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
//Pin connected to DS of 74HC595
int dataPin = 11;

int rpmPWM = A0;     // the number of the pushbutton pin
int rpmToVoltage = 0;
int rpmEncoded = 0;
 
void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  Serial.begin(9600);
  
  // Initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards
  pinMode(13, OUTPUT);    
  
  Timer3.initialize(100000); // set a timer of length 100000 microseconds
  Timer3.attachInterrupt( updateCluster ); // attach the service routine here
}
 
void loop(){
}

void updateCluster(){
  encodeRPM();
  // take the latchPin low so 
  // the LEDs don't change while you're sending in bits:
  digitalWrite(latchPin, LOW);
  // shift out the bits:
  shiftOut(dataPin, clockPin, MSBFIRST, rpmEncoded);  

  //take the latch pin high so the LEDs will light up:
  digitalWrite(latchPin, HIGH);
  
  Serial.print("RPM is:");
  Serial.print(rpmToVoltage);
  Serial.print("\n");
}

int encodeRPM(){
  rpmToVoltage = analogRead(rpmPWM);
  if (rpmToVoltage < 125){
    return rpmEncoded = 0;    // 0b00000001
  } 
  else if (rpmToVoltage > 125 && rpmToVoltage <= 250){
    return rpmEncoded = 1;    // 0b00000001
  }
  else if (rpmToVoltage > 250 && rpmToVoltage <= 375){
    return rpmEncoded = 3;    // 0b00000011
  }
  else if (rpmToVoltage > 375 && rpmToVoltage <= 500){
    return rpmEncoded = 7;    // 0b00000111
  }
  else if (rpmToVoltage > 500 && rpmToVoltage <= 625){
    return rpmEncoded = 15;   // 0b00001111
  }
  else if (rpmToVoltage > 625 && rpmToVoltage <= 750){
    return rpmEncoded = 31;   // 0b00011111
  }
  else if (rpmToVoltage > 750 && rpmToVoltage <= 875){
    return rpmEncoded = 63;   // 0b00111111
  }
  else if (rpmToVoltage > 875 && rpmToVoltage <= 1000){
    return rpmEncoded = 127;  // 0b01111111
  }
  else if (rpmToVoltage > 1000)
    return rpmEncoded = 255;  // 0b11111111
}
