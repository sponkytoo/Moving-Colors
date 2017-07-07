# Moving-Colors
### PIC18F25K42 drive WS2812B RGB Led with SPI, CLC and DMA

This example show how to use the DMA with SPI and one CLC to drive the famous WS2812B RGB LED of the 4x4 Click Board Matrix.

The interesting thing is, that data transport complete runs in the background. A classic fire and forget while the CPU can do something else.
All other WS28xx examples do poll on the UART or SPI and utilize the a few CLC's. 
 
### Approach with PIC18F25K42
The DMA transports a complete RGB LED data array to SPI in one shot while the SPI invert automatically every byte to MSB->LSB.

The SPI Data-Out is connected with PWM and Serial Clock to achive neccessary 25% (logic "0") and 50% (logic "1") timing with simple CLC boolean equation: D = SCK*(SDO+PWM).
SPI of K42 do have transmit FIFO, this allows with DMA a continous stream.

The MCC is mostly used. Only the DMA initializaiton is changed by myself because I wasn‘t satisfied by MCC‘s job.

### The Graphic Idea 
Three virtual moving dots on a higher resolution grid. Every LED do have a virtual distance to a dot and the brightness is the reversed distance
The calculation of 16x3 the = 48 LED brightness is done with pythagoras.

The sqaring is done in fixpoint and the Square Root is implemented with a fixpoint iteration.

The advantage of the DMA is that calculation can be done continuoes and separate. If ready, just fire the DMA

Measured times:
2.50 ms for calculation
0.48 ms for transport

### How to use
All 16 RGB LED colors are calculated and put into the array.

uint8_t MyPixelArray[16][3];

(The 3 is for the three colors)

Then the DMA Transfer of the array is started with:

DMA1CON0bits.DMA1SIRQEN = 1;

With a delay, the screen play is slowed down.

__delay_ms(100);

In this case every 100ms a new "image" is send to the LED Array.

For example a 128 array, you just have to increase the Array:

uint8_t MyPixelArray[128][3];

