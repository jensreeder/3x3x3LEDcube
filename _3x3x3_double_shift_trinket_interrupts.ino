#include <ChainedShiftRegister595.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/*
  CONTROL 3X3X3 LED CUBE

  The 27 leds are electrically arranged in a 3x9 sheet.
  Physically, the sheet is folded back onto itself three times,
  thus creating a 3x3x3 cube.
 
  The LEDs are controlled using a trinket micro controller
  (http://www.adafruit.com/products/1500) and two shift registers
  (http://www.adafruit.com/product/450).

  The first nine bits of the two chained 8bit shift register control the first
  dimension with nine LEDs, the upper three bits control the three layers.
  
  The cube is refreshed at 50Hz using an interrupt routine.

 */

int dataPin  = 1;
int clockPin = 2;
int latchPin = 0;
ChainedShiftRegister595 shift = ChainedShiftRegister595(latchPin, clockPin, dataPin);

//global variable storing the actual content to be displayed on the 3x3x3 cube
int display_buffer[3];

void initTimerCounter1(void);

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pins as an output.
  // used to control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin,  OUTPUT);  
  pinMode(clockPin, OUTPUT);

  initTimerCounter1();
  clear();
}

// control display refresh via interrupts
// adapted  from http://forum.arduino.cc/index.php?topic=163393.0
// it happens at 50 Hz, i.e. 8MHz/16384/10, or every 1/50 second.
void initTimerCounter1(void)
{
  TCCR1 = 0;                 //stop the timer
  TCNT1 = 0;                 //zero the timer
  GTCCR = _BV(PSR1);         //reset the prescaler
  OCR1A = 10;                //set the compare value
  OCR1C = 10;
  TIMSK = _BV(OCIE1A);        //interrupt on Compare Match A
  //start timer, ctc mode, prescaler clk/16384    
  TCCR1 = _BV(CTC1) | _BV(CS13) | _BV(CS12) | _BV(CS11) | _BV(CS10);
  sei();
}

ISR(TIMER1_COMPA_vect)
{
  display_frame();
}

// copy content from frames[][] into global display_buffer.
// Actual drawing happens on the next interrupt
void display( int framecount, int frames[][3], int repeat=50, int delay_time=1000){
  for(int i=0; i<repeat; i++){
    for (int frame=0; frame < framecount; frame++){
      display_buffer[0] = frames[frame][0];
      display_buffer[1] = frames[frame][1];
      display_buffer[2] = frames[frame][2];
      delay(delay_time); //show this frame for this long (in ms)
    }
  }
}


// clear the display buffer and turn off all leds
void clear(){

  display_buffer[0]=0;
  display_buffer[1]=0;
  display_buffer[2]=0;

  // B11111110 = 255-1
  shift.write_two_bytes(254, 0);
}

// write content from displaybuffer onto cube via
// shift register
void display_frame(){
  byte high;
  for (int level=0; level<3; level++){
    // First three bits control levels,
    // last bit control led 9, other bits are unused
    high = B11111110;
    bitClear(high, 7-level);

    int slice = display_buffer[level];
    for (int led=0; led<8; led++){
      if(bitRead(slice, led)){
        shift.write_two_bytes(high, bit(led));
      }
      else{
        shift.write_two_bytes(high, 0);
      }
    }
    if(slice>255){
      // we want 9th led controlled by first bit in 2nd register
      shift.write_two_bytes(bitSet(high, 0), 0);
    }
  }
}

//-----------------------
// graphics
//-----------------------

// These are the bits that toggle the leds
// 1  8  64
// 2 16 128
// 4 32 256

// i.e. to turn on the middle row, set the shift register to
//  2+16+128=146

// Some animation patterns
// wheel spins a plane around the central axis
int wheel[4][3] = {

  {
    56, 56, 56             } // 8+16+32
  ,
  {
    84, 84, 84             } // 4+16+64
  ,
  {
    146, 146, 146          } // 2+16+128 
  ,
  {
    273, 273, 273          } // 1+16+256
};

// moves a plane up and down the central axis
int up_n_down[4][3] = {
  { 
    511, 0, 0       }
  ,
  { 
    0, 511, 0       }
  ,
  { 
    0, 0, 511       }
  ,
  { 
    0, 511, 0       } 
};

void loop() {
  display(4, wheel);
  display(4, up_n_down);
}
