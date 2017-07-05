
/**
  DMA Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    dma1.c

  @Summary
    This is the generated header file for the DMA driver using MPLAB(c) Code Configurator

  @Description
    This source file provides APIs for DMA.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.15.3
        Device            :  PIC18F25K42
        Driver Version    :  1.00
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

/**
  Section: Included Files
 */

#include <xc.h>
#include "dma1.h"
#include "../rgb_led.h"


//------------------------------------------------------------------------------
#define m_ARBITER_LOCK()    \
      do{ \
           asm("BANKSEL PRLOCK");\
           asm("MOVLW   0x55");\
           asm("MOVWF   (PRLOCK & 0xFF)");\
           asm("MOVLW   0xAA");\
           asm("MOVWF   (PRLOCK & 0xFF)");\
           asm("BSF     (PRLOCK & 0xFF),0");\
        }while(0)
//------------------------------------------------------------------------------
#define m_ARBITER_UNLOCK()  \
      do{ \
           asm("BANKSEL PRLOCK");\
           asm("MOVLW   0x55");\
           asm("MOVWF   (PRLOCK & 0xFF)");\
           asm("MOVLW   0xAA");\
           asm("MOVWF   (PRLOCK & 0xFF)");\
           asm("BCF     (PRLOCK & 0xFF),0");\
        }while(0)

/**
  Section: Global Variables Definitions
 */

/**
  Section: DMA APIs
 */
extern uint8_t MyPixelArray[];

void DMA1_Initialize(void) {   
    
    /* stop and clear DMA 1  */
    DMA1CON0 = 0;

    /* configure DMA 1 */

    /* 1. Program the appropriate Source and Destination addresses for the
     * transaction into the DMAxSSA and DMAxDSA registers
     */
    DMA1SSA = (unsigned short long) & MyPixelArray[0]; /* source address */
    DMA1DSA = (unsigned short long) & SPI1TXB; /* destination address */

    /* 2. Select the source memory region that is being addressed by DMAxSSA
     * register, using the SMR<1:0> bits.
     */
    DMA1CON1bits.SMR = 0b00; /* source pointer points to GPR space */

    /* 3. Program the SMODE and DMODE bits to select the addressing mode.
     */
    DMA1CON1bits.SMODE = 0b01; /* source is incremented after each transfer completion */
    DMA1CON1bits.DMODE = 0b00; /* destination remains unchanged after each transfer completion */

    /* 4. Program the Source size DMAxSSZ and Destination size DMAxDSZ
     * registers with the number of bytes to be transferred. It is recommended
     * for proper operation that the size registers be a multiple of each other.
     */
    DMA1SSZ = RGB_LED_CNT; /* source transfer size is size of array */
    DMA1DSZ = 1; /*  destination size 1 */


    /* 5. If the user desires to disable data transfers once the message has
     * completed, then the SSTP and DSTP bits in DMAxCON0 register need to be set
     */
    DMA1CON1bits.SSTP = 1; /* SIRQEN bit is cleared when source counter reloads */
    DMA1CON1bits.DSTP = 0; /* SIRQEN bit is not cleared when Destination Counter reloads */

    /* 6. If using hardware triggers for data transfer, setup the hardware
     * trigger interrupt sources for the starting and aborting DMA transfers
     * (DMAxSIRQ and DMAxAIRQ), and set the corresponding interrupt request
     * enable bits (SIRQEN and AIRQEN).
     */
    DMA1SIRQ = 21; /* HW trigger is SPI1TX */
    DMA1AIRQ = 0; /* none */

    /* enable hardware source trigger  */
    DMA1CON0bits.DMA1SIRQEN = 0;


    /* 7. Select the priority level for the DMA
     * (see Section 3.1 ?System Arbitration?) and lock the priorities
     * (see Section 3.1.1 ?Priority Lock?)
     * 0 being the highest priority and 4 being the lowest priority.
     */
    m_ARBITER_UNLOCK(); /* unlock Arbiter settings */
    MAINPR = 3;
    ISRPR = 2;
    DMA1PR = 0;
    DMA2PR = 1;
    SCANPR = 4;
    m_ARBITER_LOCK(); /* lock Arbiter settings */

    /* 8. Enable the DMA (DMAxCON0bits. EN = 1)
     */
    DMA1CON0bits.EN = 1;

    /* 9. If using software control for data transfer, set the DGO bit,
     * else this bit will be set by the hardware trigger.
     */
    DMA1CON0bits.DGO = 1;
    
    /*
     * DMA Transfer is started with 
     *    MA1CON0bits.DMA1SIRQEN = 1;
     */

}




/**
  End of File
 */