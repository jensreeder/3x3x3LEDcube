/*
||
|| @author Alexander Brevig
|| @version 1.0
||
|| copied from http://playground.arduino.cc/Code/ShiftRegister595
*/

#ifndef SHIFTREGISTER_H
#define SHIFTREGISTER_H

#include "Arduino.h"

class ShiftRegister{
	public:
		virtual void buffer(byte out)=0;
		virtual void write()=0;
		virtual void write(byte out)=0;
};

#endif

/*
|| Changelog:
||
|| 1.0 2009-04-13 - Alexander Brevig : Initial Release
*/
