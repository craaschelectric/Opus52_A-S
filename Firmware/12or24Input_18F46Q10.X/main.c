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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F46Q10
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
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
   
        WPUA=0xFF;
        WPUD=0xFF;
        WPUC=0xFF;
        WPUE=0x7;
        TRISA=0xFF;
        TRISB=0xFF;
        TRISC=0xFF;
        TRISE=0x7;
    MSTOUT_SetPullup();
    MSTOUT_SetDigitalInput();
    PEROUT_SetDigitalInput();
    PEROUT_SetPullup();
 // Reed12_24
    //RE0=J3-1
    //RE0=12 or 24.  Off = 24
    //  RE1/2=offset
    //  RE1 = +24.  So on = +24, off = 0
    //  RE2 = +12.  So on = +12, off = +0
    //J5-3/4 = +48.  On=+48, off = +0
    
//    if((PORTB&0x1)==0) BaseAddress=BaseAddress+48;
//    if((PORTE&0x4)==0) BaseAddress=BaseAddress+12;
//    if((PORTE&0x2)==0) BaseAddress=BaseAddress+24;
//    if((PORTE&0x1)==1) {
//        EndAddress=EndAddress+12;
//        a24inputs=true;
//    }
  

    
    BaseAddress=48;

    
    while (1)
    {
        if(CurrentStateSync==0&&SYNC_PORT==1) //sync RISING edge (This is emulating a 597, latches on rising edge)
        {   // Bits are in this order 
            // Virtual Ground = RA0 RA1
            // RA4 RA5 RC0 RC1 RC2 RC3 RD4 RD5 RD6 RD7 RC6 RC7 : Keys
            
            uint32_t rows=0;
            CurrentByteState[2]=0;
            if (PORTAbits.RA0 == 0) rows |= (1 << 0);   // Row 0
            if (PORTCbits.RC0 == 0) rows |= (1 << 1);   // Row 1
            if (PORTAbits.RA1 == 0) rows |= (1 << 2);   // Row 2
            if (PORTCbits.RC1 == 0) rows |= (1 << 3);   // Row 3
            if (PORTAbits.RA2 == 0) rows |= (1 << 4);   // Row 4
            if (PORTCbits.RC2 == 0) rows |= (1 << 5);   // Row 5
            if (PORTAbits.RA3 == 0) rows |= (1 << 6);   // Row 6
            if (PORTCbits.RC3 == 0) rows |= (1 << 7);   // Row 7
            if (PORTAbits.RA4 == 0) rows |= (1 << 8);   // Row 8
            if (PORTCbits.RC4 == 0) rows |= (1 << 9);   // Row 9
            if (PORTAbits.RA5 == 0) rows |= (1 << 10);  // Row 10
            if (PORTCbits.RC5 == 0) rows |= (1 << 11);  // Row 11
            if (PORTAbits.RA6 == 0) rows |= (1 << 12);   // Row 0
            if (PORTCbits.RC6 == 0) rows |= (1 << 13);   // Row 1
            if (PORTAbits.RA7 == 0) rows |= (1 << 14);   // Row 0
            if (PORTCbits.RC7 == 0) rows |= ((uint32_t)(1 << 15));   // Row 1
            if (PORTDbits.RD0 == 0) CurrentByteState[2] |= (1 << 0);   // Row 1
            if (PORTDbits.RD4 == 0) CurrentByteState[2] |= (1 << 1);
            if (PORTDbits.RD1 == 0) CurrentByteState[2] |= (1 << 2);
            if (PORTDbits.RD5 == 0) CurrentByteState[2] |= (1 << 3);
            if (PORTDbits.RD2 == 0) CurrentByteState[2] |= (1 << 4);
            if (PORTDbits.RD6 == 0) CurrentByteState[2] |= (1 << 5);
            if (PORTDbits.RD3 == 0) CurrentByteState[2] |= (1 << 6);
            if (PORTDbits.RD7 == 0) CurrentByteState[2] |= (1 << 7);
            
            CurrentByteState[0]=((uint8_t)(rows&0xFF));
            CurrentByteState[1]=((uint8_t)((rows>>8)&0xFF));
            
             
            CurrentStateSync=1;
            WorkingByteState[0]=CurrentByteState[0];
            WorkingByteState[1]=CurrentByteState[1];
            WorkingByteState[2]=CurrentByteState[2];
            ClockCount=-1;
            
            
        }//sync rising edge   
        if(CurrentStateSync==1&&SYNC_PORT==0){
//            PEROUT_SetDigitalOutput();
//            PEROUT_SetHigh();
//            WorkingByteState[0]=CurrentByteState[0];
//          PEROUT_SetDigitalInput(); //if it's not mine, better not drive the bus.
            CurrentStateSync=0;
//            PEROUT_SetLow();
        }//sync falling edge
    }
}


/**
 End of File
*/