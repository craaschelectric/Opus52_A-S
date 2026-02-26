/**
  Generated Interrupt Manager Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    interrupt_manager.c

  @Summary:
    This is the Interrupt Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description:
    This header file provides implementations for global interrupt handling.
    For individual peripheral handlers please see the peripheral driver for
    all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F46Q10
        Driver Version    :  2.04
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above or later
        MPLAB 	          :  MPLAB X 5.45
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

#include "interrupt_manager.h"
#include "mcc.h"

void  INTERRUPT_Initialize (void)
{
    // Disable Interrupt Priority Vectors (16CXXX Compatibility Mode)
    INTCONbits.IPEN = 0;
}

void __interrupt() INTERRUPT_InterruptManager (void)
{
    // interrupt handler
    if(PIE0bits.IOCIE == 1 && PIR0bits.IOCIF == 1)
    {
        PIN_MANAGER_IOC();
        if (CLK_PORT==1)// CLK rising
        {
            ClockCount++;

            // Check if this clock is within our address range
            uint8_t bitIndex = ClockCount - BaseAddress - StartAddress;
            
            if ((bitIndex >= 0) && (bitIndex <= (EndAddress - StartAddress)))
            {
                uint8_t bitValue;

                uint8_t byteIndex = (uint8_t)(bitIndex >> 3);   // 0..8
                uint8_t bitInByte = (uint8_t)(bitIndex & 7u);   // 0..7 (LSB-first)
                if(bitInByte==0) 
                {MaskByte=1;} 
                else 
                {MaskByte=MaskByte<<1;}
                
                bitValue = WorkingByteState[byteIndex] & MaskByte;
                
                
                if (bitValue != 0)
                {
                    // Key pressed - drive bus LOW (active)
                    // Note: Protocol uses negative logic on the bus
                    PEROUT_SetLow();
                    PEROUT_SetDigitalOutput();
                }
                else
                {
                    // Key not pressed - release bus (high-Z with pullup)
                    PEROUT_SetHigh();
                    PEROUT_SetDigitalOutput();
                    __delay_us(1);
                    PEROUT_SetDigitalInput();  // Release to high-Z
                }
            }
            else
            {
                // Not our address range - tri-state the output
                PEROUT_SetDigitalInput();
            }
        }//15us from rising edge to output value
            
        if (CLK_PORT==0)// Falling edge read data on masterout
        {
            if(!InputConfig)
            {
/*                if(
                        ((ClockCount-BaseAddress)>=StartAddress)
                     && ((ClockCount-BaseAddress)<=EndAddress)
                    )
                {
                    if((ClockCount-BaseAddress)==StartAddress) {
                            AndingByte=1;CurrentByteState[0]=0;
                        } 
                    else 
                        AndingByte=AndingByte<<1;
                    if(MSTOUT_PORT==1)  CurrentByteState[0]=CurrentByteState[0]|AndingByte;
                }//if in my range
*/                
            }// ~ input config = input from system, output to pins.
        }
            

    }
    else
    {
        //Unhandled Interrupt
    }
}
/**
 End of File
*/
