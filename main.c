/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC18F47K42
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */

#include <math.h>
#include "rgb_led.h"

uint8_t MyPixelArray[LED_CNT][3];

#define LED_GREEN   0
#define LED_RED     1
#define LED_BLUE    2

/* fixpoint square root iteration */
uint32_t SquareRoot(uint32_t a_nInput) {
    uint32_t op = a_nInput;
    uint32_t res = 0;
    
    /* Reducing the count of iterations
     * use 1uL << 14 for uint16_t type; 
     * use 1uL << 30 for uint32_t type
     */
    uint32_t one = 1uL << 14; 

    /* "one" starts at the highest power of four <= than the argument.*/
    while (one > op) {
        one >>= 2;
    }

    while (one != 0) {
        if (op >= res + one) {
            op = op - (res + one);
            res = res + 2 * one;
        }
        res >>= 1;
        one >>= 2;
    }
    return res;
}

/* square root wrapper */
uint32_t sqrt2(uint32_t x) {

    return SquareRoot(x);
    //   return sqrt(x);
}

/* Main application */
void main(void) {
    uint8_t ix = 0;

    int16_t brightness_green = 0;
    int16_t xt_green, yt_green;
    int16_t xt_st_green, yt_st_green;
    int16_t dt_green;

    int16_t brightness_blue = 0;
    int16_t xt_blue, yt_blue;
    int16_t xt_st_blue, yt_st_blue;
    int16_t dt_blue;

    int16_t brightness_red = 0;
    int16_t xt_red, yt_red;
    int16_t xt_st_red, yt_st_red;
    int16_t distance_red;

    int16_t xp, yp;

    int16_t temp1, temp2;

    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    /* clear the entire RGB matrix */
    for (ix = 0; ix < LED_CNT; ix++) {
        MyPixelArray[ix][0] = 0;
        MyPixelArray[ix][1] = 0;
        MyPixelArray[ix][2] = 0;
    }
    /* Trigger the SPI to start DMA */
    SPI1INTFbits.SPI1TXUIF = 1;
    __delay_ms(10);

    /* start position of the virtual moving dots */
    xt_green = 0;
    yt_green = 0;
    xt_st_green = -1;
    yt_st_green = 1;

    xt_blue = 0;
    yt_blue = 0;
    xt_st_blue = 1;
    yt_st_blue = 1;

    xt_red = 0;
    yt_red = 16;
    xt_st_red = 1;
    yt_st_red = -1;

    while (1) {

        /* wait to slow down the display action */
        __delay_ms(100);

        /** Trigger RA3 for measuring the calculation time */
        LATAbits.LA3 = 1;
        
        /* calculate brightness of every LED (currently 2.46ms)*/
        for (xp = 0; xp < X_LED_N; xp++) {
            for (yp = 0; yp < Y_LED_N; yp++) {

                /* x^2 */
                temp1 = ((xp * SCALE_FACTOR) - xt_green);
                temp1 *= temp1;
                temp2 = ((yp * SCALE_FACTOR) - yt_green);
                temp2 *= temp2;
                /* Square Root of sum gives distance */
                dt_green = (int16_t) sqrt2(temp1 + temp2);
                /* reverse the distance and use it as brightness */
                brightness_green = MAX_BRIGHTNESS - dt_green;
                /* clamp the result that no brightness overshoot happens */
                if (brightness_green < 0)brightness_green = 0;

                temp1 = ((xp * SCALE_FACTOR) - xt_blue);
                temp1 *= temp1;
                temp2 = ((yp * SCALE_FACTOR) - yt_blue);
                temp2 *= temp2;
                dt_blue = (int16_t) sqrt2(temp1 + temp2);
                brightness_blue = MAX_BRIGHTNESS - dt_blue;
                if (brightness_blue < 0)brightness_blue = 0;

                temp1 = ((xp * SCALE_FACTOR) - xt_red);
                temp1 *= temp1;
                temp2 = ((yp * SCALE_FACTOR) - yt_red);
                temp2 *= temp2;
                distance_red = (int16_t) sqrt2(temp1 + temp2);
                brightness_red = MAX_BRIGHTNESS - distance_red;
                if (brightness_red < 0)brightness_red = 0;

                /* calculate index from coordinates */
                ix = xp * X_LED_N + yp;
                /* set brightness in pixel array */
                MyPixelArray[ix][LED_GREEN] = brightness_green*10;
                MyPixelArray[ix][LED_BLUE] = brightness_blue*10;
                MyPixelArray[ix][LED_RED] = brightness_red*10;
            }
        }

        /* move the dots and change direction if border is reached */
        xt_green += xt_st_green;
        if ((xt_green >= 32) || (xt_green <= -16)) {
            xt_st_green *= -1;
            xt_green += xt_st_green;
        }
        yt_green += yt_st_green;
        if ((yt_green >= 32) || (yt_green <= -16)) {
            yt_st_green *= -1;
            yt_green += yt_st_green;
        }

        xt_blue += xt_st_blue;
        if ((xt_blue >= 32) || (xt_blue <= -20)) {
            xt_st_blue *= -1;
            xt_green += xt_st_blue;
        }
        yt_blue += yt_st_blue;
        ;
        if ((yt_blue >= 32) || (yt_blue <= -20)) {
            yt_st_blue *= -1;
            yt_blue += yt_st_blue;
        }

        xt_red += xt_st_red;
        if ((xt_red >= 32) || (xt_red <= -24)) {
            xt_st_red *= -1;
            xt_green += xt_st_red;
        }
        yt_red += yt_st_red;
        if ((yt_red >= 32) || (yt_red <= -24)) {
            yt_st_red *= -1;
            yt_red += yt_st_red;
        }
        
        /* measuring time over */
        LATAbits.LA3 = 0;

        /* Trigger the DMA Transfer */
        DMA1CON0bits.DMA1SIRQEN = 1;


    }
}
/**
 End of File
*/
