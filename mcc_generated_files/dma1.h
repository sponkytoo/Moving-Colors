/**
  DMA Generated Driver API Header File
  
  @Company
    Microchip Technology Inc.

  @File Name
    dma1.h
	
  @Summary
    This is the generated header file for the DMA driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for DMA CHANNEL1.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC18F47K42
        Driver Version    :  2.10
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.00
        MPLAB 	          :  MPLAB X 5.10
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

/**
  Section: Included Files
*/
#ifndef DMA1_H
#define DMA1_H

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
        
/**
  Section: Interface Routines
*/

/**
  @Summary
    This function initializes DMA channel 1 instance : 

  @Description
    This routine initializes the DMA channel driver instance for : 
    index, making it ready for clients to open and use it. It also initializes any
    internal data structures.
    This routine must be called before any other DMA routine is called. 

  @Preconditions
    None.

  @Param
    None.

  @Returns
    None.

  @Comment
    
 
  @Example
    <code>
        unsigned short int srcArray[100];
        unsigned short int dstArray[100];
        int i;
        int count;
        for (i=0; i<100; i++)
        {
            srcArray[i] = i+1;
            dstArray[i] = 0;
        }
        DMA1_Initialize();
        // lock priority for accessing program flash
        asm ("BANKSEL PRLOCK");
        asm ("MOVLW 0x55");
        asm ("MOVWF PRLOCK");
        asm ("MOVLW 0xAA");
        asm ("MOVWF PRLOCK");
        asm ("BSF PRLOCK, 0");
    //  hardware trigger source set as Timer 1
        TMR1_StartTimer();// start the trigger source 
    </code>

*/
void DMA1_Initialize(void);




#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
    
#endif  // dma1.h