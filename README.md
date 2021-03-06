## CONTROL 3x3x3 LED CUBE ##

This projects demonstrates how to control a 3x3x3 led cube using a Trinket,
an Arduino compatible microcontroller (http://www.adafruit.com/products/1500)
Since the trinket has only very few IO pins, I am using two shift registers
(http://www.adafruit.com/product/450) to address the individual LEDs.


The 27 leds are electrically arranged in a 3x9 sheet. Physically, the sheet is folded back onto itself three times, thus creating a 3x3x3 cube.
 
The first nine bits of the two chained 8bit shift register control the first dimension with nine LEDs, the upper three bits control the three layers.
  
The cube is refreshed at 50Hz using an interrupt routine.

Looking from the top of the cube, the individual LEDs are controlled by sending
these values to the shift register:


    1 |  8 | 64
    2 | 16 |128
    4 | 32 |256

Note that the last led (256) uses the first bit of the second register.
The levels of the cubes are adressed using the highest three bits of the second register.

