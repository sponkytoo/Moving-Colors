/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.15
        Device            :  PIC18F25K42
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40
 */

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
 */

#include <xc.h>
#include <math.h>
#include "mcc_generated_files/mcc.h"
#include "rgb_led.h"

uint8_t MyPxelArray[16][3];

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

    // Enable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighEnable();

    // Enable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowEnable();

    // Disable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighDisable();

    // Disable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowDisable();

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    /* clear the entire RGB matrix */
    for (ix = 0; ix < 16; ix++) {
        MyPxelArray[ix][0] = 0;
        MyPxelArray[ix][1] = 0;
        MyPxelArray[ix][2] = 0;
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
        for (xp = 0; xp < 4; xp++) {
            for (yp = 0; yp < 4; yp++) {

                temp1 = ((xp * 4) - xt_green);
                temp1 *= temp1;
                temp2 = ((yp * 4) - yt_green);
                temp2 *= temp2;
                dt_green = (int16_t) sqrt2(temp1 + temp2);
                brightness_green = 16 - dt_green;
                if (brightness_green < 0)brightness_green = 0;

                temp1 = ((xp * 4) - xt_blue);
                temp1 *= temp1;
                temp2 = ((yp * 4) - yt_blue);
                temp2 *= temp2;
                dt_blue = (int16_t) sqrt2(temp1 + temp2);
                brightness_blue = 16 - dt_blue;
                if (brightness_blue < 0)brightness_blue = 0;

                temp1 = ((xp * 4) - xt_red);
                temp1 *= temp1;
                temp2 = ((yp * 4) - yt_red);
                temp2 *= temp2;
                distance_red = (int16_t) sqrt2(temp1 + temp2);
                brightness_red = 16 - distance_red;
                if (brightness_red < 0)brightness_red = 0;

                ix = xp * 4 + yp;
                MyPxelArray[ix][LED_GREEN] = brightness_green;
                MyPxelArray[ix][LED_BLUE] = brightness_blue;
                MyPxelArray[ix][LED_RED] = brightness_red;
            }
        }

        /* move the dots */
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


/*        
__delay_ms(50);
         
// Set led
MyData[ps][cl] = 0x10;

// reset old led 
if (ps == 0) {
    MyData[16 - 1][GREEN] = 0;
    MyData[16 - 1][RED] = 0;
    MyData[16 - 1][BLUE] = 0;
} else {
    MyData[ps - 1][GREEN] = 0;
    MyData[ps - 1][RED] = 0;
    MyData[ps - 1][BLUE] = 0;
}

// move index
ps++;
if (ps == 16) {
    ps = 0;
    // change color
    cl++;
    if (cl == 3)cl = 0;
}
 */

/*
__delay_ms(200);
for (ix = 0; ix < 16; ix++) {
    MyData[ix][0] = green;
    MyData[ix][1] = red;
    MyData[ix][2] = blue;
}

green += green_st;
if (green == 30 || green == -1) {
    green_st *= -1;
    green += green_st;
}

red += red_st;
if (red == 60 || red == -1) {
    red_st *= -1;
    red += red_st;
}

blue += blue_st;
if (blue == 7 || blue == -1) {
    blue_st *= -1;
    blue += blue_st;
}
 */

/*
__delay_ms(10);
        
for (ix = 0; ix < 16; ix++) {
    MyData[ix][0] = bt;
    MyData[ix][1] = 0;
    MyData[ix][2] = 0;
}
if(bt==5)bt=10;else bt=5;
 */

/*
for (xp = 0; xp < 4; xp++) {
    for (yp = 0; yp < 4; yp++) {
        ix = xp * 4 + yp;
        MyData[ix][BLUE] = 0;
        MyData[ix][GREEN] = 10;
        DMA1CON0bits.DMA1SIRQEN = 1;
        __delay_ms(100);
    }
}

for (yp = 0; yp < 4; yp++) {
    for (xp = 0; xp < 4; xp++) {
        ix = xp * 4 + yp;
        MyData[ix][GREEN] = 0;
        MyData[ix][RED] = 10;
        DMA1CON0bits.DMA1SIRQEN = 1;
        __delay_ms(100);
    }
}

for (xp = 3; xp >= 0; xp--) {
    for (yp = 0; yp < 4; yp++) {
        ix = xp * 4 + yp;
        MyData[ix][RED] = 0;
        MyData[ix][BLUE] = 10;
        DMA1CON0bits.DMA1SIRQEN = 1;
        __delay_ms(100);
    }
}
 */


/**
 End of File
 */