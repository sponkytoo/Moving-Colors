/**
  @Generated MPLAB(c) Code Configurator Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    mcc.c

  @Summary:
    This is the mcc.c file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.15.3
        Device            :  PIC18F25K42
        Driver Version    :  1.02
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

// Configuration bits: selected in the GUI

// CONFIG1L
#pragma config FEXTOSC = OFF    // External Oscillator Selection->Oscillator not enabled
#pragma config RSTOSC = HFINTOSC_64MHZ    // Reset Oscillator Selection->HFINTOSC with HFFRQ = 64 MHz and CDIV = 1:1

// CONFIG1H
#pragma config CLKOUTEN = OFF    // Clock out Enable bit->CLKOUT function is disabled
#pragma config PR1WAY = ON    // PRLOCKED One-Way Set Enable bit->PRLOCK bit can be cleared and set only once
#pragma config CSWEN = ON    // Clock Switch Enable bit->Writing to NOSC and NDIV is allowed
#pragma config FCMEN = ON    // Fail-Safe Clock Monitor Enable bit->Fail-Safe Clock Monitor enabled

// CONFIG2L
#pragma config MCLRE = EXTMCLR    // MCLR Enable bit->If LVP = 0, MCLR pin is MCLR; If LVP = 1, RE3 pin function is MCLR 
#pragma config PWRTS = PWRT_OFF    // Power-up timer selection bits->PWRT is disabled
#pragma config MVECEN = OFF    // Multi-vector enable bit->Interrupt contoller does not use vector table to prioritze interrupts
#pragma config IVT1WAY = ON    // IVTLOCK bit One-way set enable bit->IVTLOCK bit can be cleared and set only once
#pragma config LPBOREN = OFF    // Low Power BOR Enable bit->ULPBOR disabled
#pragma config BOREN = SBORDIS    // Brown-out Reset Enable bits->Brown-out Reset enabled , SBOREN bit is ignored

// CONFIG2H
#pragma config BORV = VBOR_2P45    // Brown-out Reset Voltage Selection bits->Brown-out Reset Voltage (VBOR) set to 2.45V
#pragma config ZCD = OFF    // ZCD Disable bit->ZCD disabled. ZCD can be enabled by setting the ZCDSEN bit of ZCDCON
#pragma config PPS1WAY = ON    // PPSLOCK bit One-Way Set Enable bit->PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle
#pragma config STVREN = ON    // Stack Full/Underflow Reset Enable bit->Stack full/underflow will cause Reset
#pragma config DEBUG = OFF    // Debugger Enable bit->Background debugger disabled
#pragma config XINST = OFF    // Extended Instruction Set Enable bit->Extended Instruction Set and Indexed Addressing Mode disabled

// CONFIG3L
#pragma config WDTCPS = WDTCPS_31    // WDT Period selection bits->Divider ratio 1:65536; software control of WDTPS
#pragma config WDTE = OFF    // WDT operating mode->WDT Disabled; SWDTEN is ignored

// CONFIG3H
#pragma config WDTCWS = WDTCWS_7    // WDT Window Select bits->window always open (100%); software control; keyed access not required
#pragma config WDTCCS = SC    // WDT input clock selector->Software Control

// CONFIG4L
#pragma config BBSIZE = BBSIZE_512    // Boot Block Size selection bits->Boot Block size is 512 words
#pragma config BBEN = OFF    // Boot Block enable bit->Boot block disabled
#pragma config SAFEN = OFF    // Storage Area Flash enable bit->SAF disabled
#pragma config WRTAPP = OFF    // Application Block write protection bit->Application Block not write protected

// CONFIG4H
#pragma config WRTB = OFF    // Configuration Register Write Protection bit->Configuration registers (300000-30000Bh) not write-protected
#pragma config WRTC = OFF    // Boot Block Write Protection bit->Boot Block (000000-0007FFh) not write-protected
#pragma config WRTD = OFF    // Data EEPROM Write Protection bit->Data EEPROM not write-protected
#pragma config WRTSAF = OFF    // SAF Write protection bit->SAF not Write Protected
#pragma config LVP = ON    // Low Voltage Programming Enable bit->Low voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored

// CONFIG5L
#pragma config CP = OFF    // PFM and Data EEPROM Code Protection bit->PFM and Data EEPROM code protection disabled

#include "mcc.h"

void SYSTEM_Initialize(void)
{

    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    DMA1_Initialize();
    CLC2_Initialize();
    TMR2_Initialize();
    PWM5_Initialize();
    SPI1_Initialize();
}

void OSCILLATOR_Initialize(void)
{
    // NOSC HFINTOSC; NDIV 1; 
    OSCCON1 = 0x60;
    // CSWHOLD may proceed; SOSCPWR Low power; 
    OSCCON3 = 0x00;
    // MFOEN disabled; LFOEN disabled; ADOEN disabled; SOSCEN disabled; EXTOEN disabled; HFOEN disabled; 
    OSCEN = 0x00;
    // HFFRQ 64_MHz; 
    OSCFRQ = 0x08;
    // TUN 0; 
    OSCTUNE = 0x00;
}


/**
 End of File
*/
