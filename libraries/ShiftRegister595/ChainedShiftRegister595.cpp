#include "ChainedShiftRegister595.h"

//<<constructor>>
ChainedShiftRegister595::ChainedShiftRegister595( byte userLatchPin, byte userClockPin, byte userDataPin ){

  latchPin	= userLatchPin;
  clockPin	= userClockPin;
  dataPin	= userDataPin;
  bufferByte = 0;
}

void ChainedShiftRegister595::buffer(byte out){
  bufferByte = out;
}

void ChainedShiftRegister595::write(){
  digitalWrite(latchPin, LOW);
  shiftOut(bufferByte);   
  digitalWrite(latchPin, HIGH);
}

void ChainedShiftRegister595::write(byte out){
  digitalWrite(latchPin, LOW);
  shiftOut(out);   
  digitalWrite(latchPin, HIGH);
}

void ChainedShiftRegister595::write_two_bytes(byte out1, byte out2){
  digitalWrite(latchPin, LOW);

  shiftOut(out1);
  shiftOut(out2);

  digitalWrite(latchPin, HIGH);
}

//based on this code http://arduino.cc/en/Tutorial/ShftOut11
void ChainedShiftRegister595::shiftOut(byte out){
  bool pinState = false;
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  digitalWrite(dataPin, LOW);
  digitalWrite(clockPin, LOW);
  for (byte i=7; i>=0; i--)  {
    digitalWrite(clockPin, LOW);
    if ( out & (1<<i) ) {
      pinState= true;
    }
    else {	
      pinState= false;
    }
    digitalWrite(dataPin, pinState);
    digitalWrite(clockPin, HIGH);
    digitalWrite(dataPin, LOW);
  }
  digitalWrite(clockPin, LOW);
}
