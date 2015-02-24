/*
||
|| @author Jens Reeder
|| @version 1.0
||
|| adapted from http://playground.arduino.cc/Code/ShiftRegister595
|| original code by Alexander Brevig 
*/

#ifndef CHAINEDSHIFTREGISTER595_H
#define CHAINEDSHIFTREGISTER595_H

#include "Arduino.h"
#include "ShiftRegister.h"

class ChainedShiftRegister595 : public ShiftRegister{
	public:
		ChainedShiftRegister595( byte userLatchPin, byte userClockPin, byte userDataPin );	
		
		virtual void buffer(byte out);
		virtual void write();
		virtual void write(byte out);
                virtual void write_two_bytes(byte out1, byte out2);

	private:
		void shiftOut(byte out);
		byte latchPin;
		byte clockPin;
		byte dataPin;
		byte bufferByte;
};

#endif

/*
|| Changelog:
||
|| 1.0 2014-08-12 New class for two chained shift registers.
*/
