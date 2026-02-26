/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F46Q10
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set D0 aliases
#define D0_TRIS                 TRISAbits.TRISA0
#define D0_LAT                  LATAbits.LATA0
#define D0_PORT                 PORTAbits.RA0
#define D0_WPU                  WPUAbits.WPUA0
#define D0_OD                   ODCONAbits.ODCA0
#define D0_ANS                  ANSELAbits.ANSELA0
#define D0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define D0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define D0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define D0_GetValue()           PORTAbits.RA0
#define D0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define D0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define D0_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define D0_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define D0_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define D0_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define D0_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define D0_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set D1 aliases
#define D1_TRIS                 TRISAbits.TRISA1
#define D1_LAT                  LATAbits.LATA1
#define D1_PORT                 PORTAbits.RA1
#define D1_WPU                  WPUAbits.WPUA1
#define D1_OD                   ODCONAbits.ODCA1
#define D1_ANS                  ANSELAbits.ANSELA1
#define D1_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define D1_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define D1_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define D1_GetValue()           PORTAbits.RA1
#define D1_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define D1_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define D1_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define D1_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define D1_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define D1_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define D1_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define D1_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set D2 aliases
#define D2_TRIS                 TRISAbits.TRISA2
#define D2_LAT                  LATAbits.LATA2
#define D2_PORT                 PORTAbits.RA2
#define D2_WPU                  WPUAbits.WPUA2
#define D2_OD                   ODCONAbits.ODCA2
#define D2_ANS                  ANSELAbits.ANSELA2
#define D2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define D2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define D2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define D2_GetValue()           PORTAbits.RA2
#define D2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define D2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define D2_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define D2_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define D2_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define D2_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define D2_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define D2_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set D3 aliases
#define D3_TRIS                 TRISAbits.TRISA3
#define D3_LAT                  LATAbits.LATA3
#define D3_PORT                 PORTAbits.RA3
#define D3_WPU                  WPUAbits.WPUA3
#define D3_OD                   ODCONAbits.ODCA3
#define D3_ANS                  ANSELAbits.ANSELA3
#define D3_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define D3_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define D3_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define D3_GetValue()           PORTAbits.RA3
#define D3_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define D3_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define D3_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define D3_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define D3_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define D3_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define D3_SetAnalogMode()      do { ANSELAbits.ANSELA3 = 1; } while(0)
#define D3_SetDigitalMode()     do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set D4 aliases
#define D4_TRIS                 TRISAbits.TRISA4
#define D4_LAT                  LATAbits.LATA4
#define D4_PORT                 PORTAbits.RA4
#define D4_WPU                  WPUAbits.WPUA4
#define D4_OD                   ODCONAbits.ODCA4
#define D4_ANS                  ANSELAbits.ANSELA4
#define D4_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define D4_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define D4_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define D4_GetValue()           PORTAbits.RA4
#define D4_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define D4_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define D4_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define D4_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define D4_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define D4_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define D4_SetAnalogMode()      do { ANSELAbits.ANSELA4 = 1; } while(0)
#define D4_SetDigitalMode()     do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set D5 aliases
#define D5_TRIS                 TRISAbits.TRISA5
#define D5_LAT                  LATAbits.LATA5
#define D5_PORT                 PORTAbits.RA5
#define D5_WPU                  WPUAbits.WPUA5
#define D5_OD                   ODCONAbits.ODCA5
#define D5_ANS                  ANSELAbits.ANSELA5
#define D5_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define D5_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define D5_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define D5_GetValue()           PORTAbits.RA5
#define D5_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define D5_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define D5_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define D5_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define D5_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define D5_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define D5_SetAnalogMode()      do { ANSELAbits.ANSELA5 = 1; } while(0)
#define D5_SetDigitalMode()     do { ANSELAbits.ANSELA5 = 0; } while(0)

// get/set D6 aliases
#define D6_TRIS                 TRISAbits.TRISA6
#define D6_LAT                  LATAbits.LATA6
#define D6_PORT                 PORTAbits.RA6
#define D6_WPU                  WPUAbits.WPUA6
#define D6_OD                   ODCONAbits.ODCA6
#define D6_ANS                  ANSELAbits.ANSELA6
#define D6_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define D6_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define D6_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define D6_GetValue()           PORTAbits.RA6
#define D6_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define D6_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define D6_SetPullup()          do { WPUAbits.WPUA6 = 1; } while(0)
#define D6_ResetPullup()        do { WPUAbits.WPUA6 = 0; } while(0)
#define D6_SetPushPull()        do { ODCONAbits.ODCA6 = 0; } while(0)
#define D6_SetOpenDrain()       do { ODCONAbits.ODCA6 = 1; } while(0)
#define D6_SetAnalogMode()      do { ANSELAbits.ANSELA6 = 1; } while(0)
#define D6_SetDigitalMode()     do { ANSELAbits.ANSELA6 = 0; } while(0)

// get/set D7 aliases
#define D7_TRIS                 TRISAbits.TRISA7
#define D7_LAT                  LATAbits.LATA7
#define D7_PORT                 PORTAbits.RA7
#define D7_WPU                  WPUAbits.WPUA7
#define D7_OD                   ODCONAbits.ODCA7
#define D7_ANS                  ANSELAbits.ANSELA7
#define D7_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define D7_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define D7_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define D7_GetValue()           PORTAbits.RA7
#define D7_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define D7_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define D7_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define D7_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define D7_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define D7_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define D7_SetAnalogMode()      do { ANSELAbits.ANSELA7 = 1; } while(0)
#define D7_SetDigitalMode()     do { ANSELAbits.ANSELA7 = 0; } while(0)

// get/set SYNC aliases
#define SYNC_TRIS                 TRISBbits.TRISB2
#define SYNC_LAT                  LATBbits.LATB2
#define SYNC_PORT                 PORTBbits.RB2
#define SYNC_WPU                  WPUBbits.WPUB2
#define SYNC_OD                   ODCONBbits.ODCB2
#define SYNC_ANS                  ANSELBbits.ANSELB2
#define SYNC_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define SYNC_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define SYNC_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define SYNC_GetValue()           PORTBbits.RB2
#define SYNC_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define SYNC_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define SYNC_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define SYNC_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define SYNC_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define SYNC_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define SYNC_SetAnalogMode()      do { ANSELBbits.ANSELB2 = 1; } while(0)
#define SYNC_SetDigitalMode()     do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set MSTOUT aliases
#define MSTOUT_TRIS                 TRISBbits.TRISB3
#define MSTOUT_LAT                  LATBbits.LATB3
#define MSTOUT_PORT                 PORTBbits.RB3
#define MSTOUT_WPU                  WPUBbits.WPUB3
#define MSTOUT_OD                   ODCONBbits.ODCB3
#define MSTOUT_ANS                  ANSELBbits.ANSELB3
#define MSTOUT_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define MSTOUT_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define MSTOUT_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define MSTOUT_GetValue()           PORTBbits.RB3
#define MSTOUT_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define MSTOUT_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define MSTOUT_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define MSTOUT_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define MSTOUT_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define MSTOUT_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define MSTOUT_SetAnalogMode()      do { ANSELBbits.ANSELB3 = 1; } while(0)
#define MSTOUT_SetDigitalMode()     do { ANSELBbits.ANSELB3 = 0; } while(0)

// get/set PEROUT aliases
#define PEROUT_TRIS                 TRISBbits.TRISB4
#define PEROUT_LAT                  LATBbits.LATB4
#define PEROUT_PORT                 PORTBbits.RB4
#define PEROUT_WPU                  WPUBbits.WPUB4
#define PEROUT_OD                   ODCONBbits.ODCB4
#define PEROUT_ANS                  ANSELBbits.ANSELB4
#define PEROUT_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define PEROUT_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define PEROUT_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define PEROUT_GetValue()           PORTBbits.RB4
#define PEROUT_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define PEROUT_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define PEROUT_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define PEROUT_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define PEROUT_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define PEROUT_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define PEROUT_SetAnalogMode()      do { ANSELBbits.ANSELB4 = 1; } while(0)
#define PEROUT_SetDigitalMode()     do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set CLK aliases
#define CLK_TRIS                 TRISBbits.TRISB5
#define CLK_LAT                  LATBbits.LATB5
#define CLK_PORT                 PORTBbits.RB5
#define CLK_WPU                  WPUBbits.WPUB5
#define CLK_OD                   ODCONBbits.ODCB5
#define CLK_ANS                  ANSELBbits.ANSELB5
#define CLK_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define CLK_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define CLK_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define CLK_GetValue()           PORTBbits.RB5
#define CLK_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define CLK_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define CLK_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define CLK_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define CLK_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define CLK_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define CLK_SetAnalogMode()      do { ANSELBbits.ANSELB5 = 1; } while(0)
#define CLK_SetDigitalMode()     do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set D8 aliases
#define D8_TRIS                 TRISCbits.TRISC0
#define D8_LAT                  LATCbits.LATC0
#define D8_PORT                 PORTCbits.RC0
#define D8_WPU                  WPUCbits.WPUC0
#define D8_OD                   ODCONCbits.ODCC0
#define D8_ANS                  ANSELCbits.ANSELC0
#define D8_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define D8_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define D8_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define D8_GetValue()           PORTCbits.RC0
#define D8_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define D8_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define D8_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define D8_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define D8_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define D8_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define D8_SetAnalogMode()      do { ANSELCbits.ANSELC0 = 1; } while(0)
#define D8_SetDigitalMode()     do { ANSELCbits.ANSELC0 = 0; } while(0)

// get/set D9 aliases
#define D9_TRIS                 TRISCbits.TRISC1
#define D9_LAT                  LATCbits.LATC1
#define D9_PORT                 PORTCbits.RC1
#define D9_WPU                  WPUCbits.WPUC1
#define D9_OD                   ODCONCbits.ODCC1
#define D9_ANS                  ANSELCbits.ANSELC1
#define D9_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define D9_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define D9_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define D9_GetValue()           PORTCbits.RC1
#define D9_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define D9_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define D9_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define D9_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define D9_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define D9_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define D9_SetAnalogMode()      do { ANSELCbits.ANSELC1 = 1; } while(0)
#define D9_SetDigitalMode()     do { ANSELCbits.ANSELC1 = 0; } while(0)

// get/set D10 aliases
#define D10_TRIS                 TRISCbits.TRISC2
#define D10_LAT                  LATCbits.LATC2
#define D10_PORT                 PORTCbits.RC2
#define D10_WPU                  WPUCbits.WPUC2
#define D10_OD                   ODCONCbits.ODCC2
#define D10_ANS                  ANSELCbits.ANSELC2
#define D10_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define D10_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define D10_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define D10_GetValue()           PORTCbits.RC2
#define D10_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define D10_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define D10_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define D10_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define D10_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define D10_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define D10_SetAnalogMode()      do { ANSELCbits.ANSELC2 = 1; } while(0)
#define D10_SetDigitalMode()     do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set D11 aliases
#define D11_TRIS                 TRISCbits.TRISC3
#define D11_LAT                  LATCbits.LATC3
#define D11_PORT                 PORTCbits.RC3
#define D11_WPU                  WPUCbits.WPUC3
#define D11_OD                   ODCONCbits.ODCC3
#define D11_ANS                  ANSELCbits.ANSELC3
#define D11_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define D11_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define D11_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define D11_GetValue()           PORTCbits.RC3
#define D11_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define D11_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define D11_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define D11_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define D11_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define D11_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define D11_SetAnalogMode()      do { ANSELCbits.ANSELC3 = 1; } while(0)
#define D11_SetDigitalMode()     do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set C8 aliases
#define C8_TRIS                 TRISCbits.TRISC4
#define C8_LAT                  LATCbits.LATC4
#define C8_PORT                 PORTCbits.RC4
#define C8_WPU                  WPUCbits.WPUC4
#define C8_OD                   ODCONCbits.ODCC4
#define C8_ANS                  ANSELCbits.ANSELC4
#define C8_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define C8_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define C8_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define C8_GetValue()           PORTCbits.RC4
#define C8_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define C8_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define C8_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define C8_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define C8_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define C8_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define C8_SetAnalogMode()      do { ANSELCbits.ANSELC4 = 1; } while(0)
#define C8_SetDigitalMode()     do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set C9 aliases
#define C9_TRIS                 TRISCbits.TRISC5
#define C9_LAT                  LATCbits.LATC5
#define C9_PORT                 PORTCbits.RC5
#define C9_WPU                  WPUCbits.WPUC5
#define C9_OD                   ODCONCbits.ODCC5
#define C9_ANS                  ANSELCbits.ANSELC5
#define C9_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define C9_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define C9_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define C9_GetValue()           PORTCbits.RC5
#define C9_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define C9_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define C9_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define C9_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define C9_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define C9_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define C9_SetAnalogMode()      do { ANSELCbits.ANSELC5 = 1; } while(0)
#define C9_SetDigitalMode()     do { ANSELCbits.ANSELC5 = 0; } while(0)

// get/set C10 aliases
#define C10_TRIS                 TRISCbits.TRISC6
#define C10_LAT                  LATCbits.LATC6
#define C10_PORT                 PORTCbits.RC6
#define C10_WPU                  WPUCbits.WPUC6
#define C10_OD                   ODCONCbits.ODCC6
#define C10_ANS                  ANSELCbits.ANSELC6
#define C10_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define C10_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define C10_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define C10_GetValue()           PORTCbits.RC6
#define C10_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define C10_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define C10_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define C10_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define C10_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define C10_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define C10_SetAnalogMode()      do { ANSELCbits.ANSELC6 = 1; } while(0)
#define C10_SetDigitalMode()     do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set C11 aliases
#define C11_TRIS                 TRISCbits.TRISC7
#define C11_LAT                  LATCbits.LATC7
#define C11_PORT                 PORTCbits.RC7
#define C11_WPU                  WPUCbits.WPUC7
#define C11_OD                   ODCONCbits.ODCC7
#define C11_ANS                  ANSELCbits.ANSELC7
#define C11_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define C11_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define C11_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define C11_GetValue()           PORTCbits.RC7
#define C11_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define C11_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define C11_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define C11_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define C11_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define C11_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define C11_SetAnalogMode()      do { ANSELCbits.ANSELC7 = 1; } while(0)
#define C11_SetDigitalMode()     do { ANSELCbits.ANSELC7 = 0; } while(0)

// get/set C0 aliases
#define C0_TRIS                 TRISDbits.TRISD0
#define C0_LAT                  LATDbits.LATD0
#define C0_PORT                 PORTDbits.RD0
#define C0_WPU                  WPUDbits.WPUD0
#define C0_OD                   ODCONDbits.ODCD0
#define C0_ANS                  ANSELDbits.ANSELD0
#define C0_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define C0_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define C0_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define C0_GetValue()           PORTDbits.RD0
#define C0_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define C0_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define C0_SetPullup()          do { WPUDbits.WPUD0 = 1; } while(0)
#define C0_ResetPullup()        do { WPUDbits.WPUD0 = 0; } while(0)
#define C0_SetPushPull()        do { ODCONDbits.ODCD0 = 0; } while(0)
#define C0_SetOpenDrain()       do { ODCONDbits.ODCD0 = 1; } while(0)
#define C0_SetAnalogMode()      do { ANSELDbits.ANSELD0 = 1; } while(0)
#define C0_SetDigitalMode()     do { ANSELDbits.ANSELD0 = 0; } while(0)

// get/set C1 aliases
#define C1_TRIS                 TRISDbits.TRISD1
#define C1_LAT                  LATDbits.LATD1
#define C1_PORT                 PORTDbits.RD1
#define C1_WPU                  WPUDbits.WPUD1
#define C1_OD                   ODCONDbits.ODCD1
#define C1_ANS                  ANSELDbits.ANSELD1
#define C1_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define C1_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define C1_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define C1_GetValue()           PORTDbits.RD1
#define C1_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define C1_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define C1_SetPullup()          do { WPUDbits.WPUD1 = 1; } while(0)
#define C1_ResetPullup()        do { WPUDbits.WPUD1 = 0; } while(0)
#define C1_SetPushPull()        do { ODCONDbits.ODCD1 = 0; } while(0)
#define C1_SetOpenDrain()       do { ODCONDbits.ODCD1 = 1; } while(0)
#define C1_SetAnalogMode()      do { ANSELDbits.ANSELD1 = 1; } while(0)
#define C1_SetDigitalMode()     do { ANSELDbits.ANSELD1 = 0; } while(0)

// get/set C2 aliases
#define C2_TRIS                 TRISDbits.TRISD2
#define C2_LAT                  LATDbits.LATD2
#define C2_PORT                 PORTDbits.RD2
#define C2_WPU                  WPUDbits.WPUD2
#define C2_OD                   ODCONDbits.ODCD2
#define C2_ANS                  ANSELDbits.ANSELD2
#define C2_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define C2_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define C2_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define C2_GetValue()           PORTDbits.RD2
#define C2_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define C2_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define C2_SetPullup()          do { WPUDbits.WPUD2 = 1; } while(0)
#define C2_ResetPullup()        do { WPUDbits.WPUD2 = 0; } while(0)
#define C2_SetPushPull()        do { ODCONDbits.ODCD2 = 0; } while(0)
#define C2_SetOpenDrain()       do { ODCONDbits.ODCD2 = 1; } while(0)
#define C2_SetAnalogMode()      do { ANSELDbits.ANSELD2 = 1; } while(0)
#define C2_SetDigitalMode()     do { ANSELDbits.ANSELD2 = 0; } while(0)

// get/set C3 aliases
#define C3_TRIS                 TRISDbits.TRISD3
#define C3_LAT                  LATDbits.LATD3
#define C3_PORT                 PORTDbits.RD3
#define C3_WPU                  WPUDbits.WPUD3
#define C3_OD                   ODCONDbits.ODCD3
#define C3_ANS                  ANSELDbits.ANSELD3
#define C3_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define C3_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define C3_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define C3_GetValue()           PORTDbits.RD3
#define C3_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define C3_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)
#define C3_SetPullup()          do { WPUDbits.WPUD3 = 1; } while(0)
#define C3_ResetPullup()        do { WPUDbits.WPUD3 = 0; } while(0)
#define C3_SetPushPull()        do { ODCONDbits.ODCD3 = 0; } while(0)
#define C3_SetOpenDrain()       do { ODCONDbits.ODCD3 = 1; } while(0)
#define C3_SetAnalogMode()      do { ANSELDbits.ANSELD3 = 1; } while(0)
#define C3_SetDigitalMode()     do { ANSELDbits.ANSELD3 = 0; } while(0)

// get/set C4 aliases
#define C4_TRIS                 TRISDbits.TRISD4
#define C4_LAT                  LATDbits.LATD4
#define C4_PORT                 PORTDbits.RD4
#define C4_WPU                  WPUDbits.WPUD4
#define C4_OD                   ODCONDbits.ODCD4
#define C4_ANS                  ANSELDbits.ANSELD4
#define C4_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define C4_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define C4_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define C4_GetValue()           PORTDbits.RD4
#define C4_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define C4_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)
#define C4_SetPullup()          do { WPUDbits.WPUD4 = 1; } while(0)
#define C4_ResetPullup()        do { WPUDbits.WPUD4 = 0; } while(0)
#define C4_SetPushPull()        do { ODCONDbits.ODCD4 = 0; } while(0)
#define C4_SetOpenDrain()       do { ODCONDbits.ODCD4 = 1; } while(0)
#define C4_SetAnalogMode()      do { ANSELDbits.ANSELD4 = 1; } while(0)
#define C4_SetDigitalMode()     do { ANSELDbits.ANSELD4 = 0; } while(0)

// get/set C5 aliases
#define C5_TRIS                 TRISDbits.TRISD5
#define C5_LAT                  LATDbits.LATD5
#define C5_PORT                 PORTDbits.RD5
#define C5_WPU                  WPUDbits.WPUD5
#define C5_OD                   ODCONDbits.ODCD5
#define C5_ANS                  ANSELDbits.ANSELD5
#define C5_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define C5_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define C5_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define C5_GetValue()           PORTDbits.RD5
#define C5_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define C5_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define C5_SetPullup()          do { WPUDbits.WPUD5 = 1; } while(0)
#define C5_ResetPullup()        do { WPUDbits.WPUD5 = 0; } while(0)
#define C5_SetPushPull()        do { ODCONDbits.ODCD5 = 0; } while(0)
#define C5_SetOpenDrain()       do { ODCONDbits.ODCD5 = 1; } while(0)
#define C5_SetAnalogMode()      do { ANSELDbits.ANSELD5 = 1; } while(0)
#define C5_SetDigitalMode()     do { ANSELDbits.ANSELD5 = 0; } while(0)

// get/set C6 aliases
#define C6_TRIS                 TRISDbits.TRISD6
#define C6_LAT                  LATDbits.LATD6
#define C6_PORT                 PORTDbits.RD6
#define C6_WPU                  WPUDbits.WPUD6
#define C6_OD                   ODCONDbits.ODCD6
#define C6_ANS                  ANSELDbits.ANSELD6
#define C6_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define C6_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define C6_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define C6_GetValue()           PORTDbits.RD6
#define C6_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define C6_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)
#define C6_SetPullup()          do { WPUDbits.WPUD6 = 1; } while(0)
#define C6_ResetPullup()        do { WPUDbits.WPUD6 = 0; } while(0)
#define C6_SetPushPull()        do { ODCONDbits.ODCD6 = 0; } while(0)
#define C6_SetOpenDrain()       do { ODCONDbits.ODCD6 = 1; } while(0)
#define C6_SetAnalogMode()      do { ANSELDbits.ANSELD6 = 1; } while(0)
#define C6_SetDigitalMode()     do { ANSELDbits.ANSELD6 = 0; } while(0)

// get/set C7 aliases
#define C7_TRIS                 TRISDbits.TRISD7
#define C7_LAT                  LATDbits.LATD7
#define C7_PORT                 PORTDbits.RD7
#define C7_WPU                  WPUDbits.WPUD7
#define C7_OD                   ODCONDbits.ODCD7
#define C7_ANS                  ANSELDbits.ANSELD7
#define C7_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define C7_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define C7_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define C7_GetValue()           PORTDbits.RD7
#define C7_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define C7_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
#define C7_SetPullup()          do { WPUDbits.WPUD7 = 1; } while(0)
#define C7_ResetPullup()        do { WPUDbits.WPUD7 = 0; } while(0)
#define C7_SetPushPull()        do { ODCONDbits.ODCD7 = 0; } while(0)
#define C7_SetOpenDrain()       do { ODCONDbits.ODCD7 = 1; } while(0)
#define C7_SetAnalogMode()      do { ANSELDbits.ANSELD7 = 1; } while(0)
#define C7_SetDigitalMode()     do { ANSELDbits.ANSELD7 = 0; } while(0)

// get/set IO_RE0 aliases
#define IO_RE0_TRIS                 TRISEbits.TRISE0
#define IO_RE0_LAT                  LATEbits.LATE0
#define IO_RE0_PORT                 PORTEbits.RE0
#define IO_RE0_WPU                  WPUEbits.WPUE0
#define IO_RE0_OD                   ODCONEbits.ODCE0
#define IO_RE0_ANS                  ANSELEbits.ANSELE0
#define IO_RE0_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define IO_RE0_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define IO_RE0_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define IO_RE0_GetValue()           PORTEbits.RE0
#define IO_RE0_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define IO_RE0_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define IO_RE0_SetPullup()          do { WPUEbits.WPUE0 = 1; } while(0)
#define IO_RE0_ResetPullup()        do { WPUEbits.WPUE0 = 0; } while(0)
#define IO_RE0_SetPushPull()        do { ODCONEbits.ODCE0 = 0; } while(0)
#define IO_RE0_SetOpenDrain()       do { ODCONEbits.ODCE0 = 1; } while(0)
#define IO_RE0_SetAnalogMode()      do { ANSELEbits.ANSELE0 = 1; } while(0)
#define IO_RE0_SetDigitalMode()     do { ANSELEbits.ANSELE0 = 0; } while(0)

// get/set AddrSel aliases
#define AddrSel_TRIS                 TRISEbits.TRISE1
#define AddrSel_LAT                  LATEbits.LATE1
#define AddrSel_PORT                 PORTEbits.RE1
#define AddrSel_WPU                  WPUEbits.WPUE1
#define AddrSel_OD                   ODCONEbits.ODCE1
#define AddrSel_ANS                  ANSELEbits.ANSELE1
#define AddrSel_SetHigh()            do { LATEbits.LATE1 = 1; } while(0)
#define AddrSel_SetLow()             do { LATEbits.LATE1 = 0; } while(0)
#define AddrSel_Toggle()             do { LATEbits.LATE1 = ~LATEbits.LATE1; } while(0)
#define AddrSel_GetValue()           PORTEbits.RE1
#define AddrSel_SetDigitalInput()    do { TRISEbits.TRISE1 = 1; } while(0)
#define AddrSel_SetDigitalOutput()   do { TRISEbits.TRISE1 = 0; } while(0)
#define AddrSel_SetPullup()          do { WPUEbits.WPUE1 = 1; } while(0)
#define AddrSel_ResetPullup()        do { WPUEbits.WPUE1 = 0; } while(0)
#define AddrSel_SetPushPull()        do { ODCONEbits.ODCE1 = 0; } while(0)
#define AddrSel_SetOpenDrain()       do { ODCONEbits.ODCE1 = 1; } while(0)
#define AddrSel_SetAnalogMode()      do { ANSELEbits.ANSELE1 = 1; } while(0)
#define AddrSel_SetDigitalMode()     do { ANSELEbits.ANSELE1 = 0; } while(0)

// get/set ColLocation aliases
#define ColLocation_TRIS                 TRISEbits.TRISE2
#define ColLocation_LAT                  LATEbits.LATE2
#define ColLocation_PORT                 PORTEbits.RE2
#define ColLocation_WPU                  WPUEbits.WPUE2
#define ColLocation_OD                   ODCONEbits.ODCE2
#define ColLocation_ANS                  ANSELEbits.ANSELE2
#define ColLocation_SetHigh()            do { LATEbits.LATE2 = 1; } while(0)
#define ColLocation_SetLow()             do { LATEbits.LATE2 = 0; } while(0)
#define ColLocation_Toggle()             do { LATEbits.LATE2 = ~LATEbits.LATE2; } while(0)
#define ColLocation_GetValue()           PORTEbits.RE2
#define ColLocation_SetDigitalInput()    do { TRISEbits.TRISE2 = 1; } while(0)
#define ColLocation_SetDigitalOutput()   do { TRISEbits.TRISE2 = 0; } while(0)
#define ColLocation_SetPullup()          do { WPUEbits.WPUE2 = 1; } while(0)
#define ColLocation_ResetPullup()        do { WPUEbits.WPUE2 = 0; } while(0)
#define ColLocation_SetPushPull()        do { ODCONEbits.ODCE2 = 0; } while(0)
#define ColLocation_SetOpenDrain()       do { ODCONEbits.ODCE2 = 1; } while(0)
#define ColLocation_SetAnalogMode()      do { ANSELEbits.ANSELE2 = 1; } while(0)
#define ColLocation_SetDigitalMode()     do { ANSELEbits.ANSELE2 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCBF5 pin functionality
 * @Example
    IOCBF5_ISR();
 */
void IOCBF5_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCBF5 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCBF5 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF5_SetInterruptHandler(MyInterruptHandler);

*/
void IOCBF5_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCBF5 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCBF5_SetInterruptHandler() method.
    This handler is called every time the IOCBF5 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF5_SetInterruptHandler(IOCBF5_InterruptHandler);

*/
extern void (*IOCBF5_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCBF5 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCBF5_SetInterruptHandler() method.
    This handler is called every time the IOCBF5 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF5_SetInterruptHandler(IOCBF5_DefaultInterruptHandler);

*/
void IOCBF5_DefaultInterruptHandler(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/