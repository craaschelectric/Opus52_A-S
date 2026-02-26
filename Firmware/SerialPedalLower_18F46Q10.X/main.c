/*
 * Pedal Scanner - LOW Microcontroller
 * 
 * Target:    PIC18F46Q10 @ 64 MHz HFINTOSC
 * Compiler:  XC8 under MPLAB X
 * 
 * Description:
 *   Scans 24 direct pedal inputs (active-low with internal pull-ups)
 *   every 8ms and outputs serial MIDI at 31250 baud.
 *
 * Input Mapping (active-low, internal weak pull-ups enabled):
 *   RA0-RA7  ->  Pedals 1-8   ->  MIDI Notes 36-43
 *   RC0-RC7  ->  Pedals 9-16  ->  MIDI Notes 44-51
 *   RD0-RD7  ->  Pedals 17-24 ->  MIDI Notes 52-59
 *
 * MIDI Output:
 *   Channel 7 (0-indexed) => Note On 0x97, Note Off 0x87
 *   Velocity:  127 (0x7F) for Note On, 0 for Note Off
 *   TX on RB4 via EUSART1 at 31250 baud
 *
 * Timer:
 *   Timer0, 8-bit mode, FOSC/4 clock, 1:512 prescaler, period=249 => 8ms
 *
 * Architecture:
 *   Polled main loop. No interrupts. Timer0 overflow flag drives scan rate.
 *   Blocking UART transmit (3 bytes = 960us, well within 8ms budget).
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

/* ========================================================================
 * CONFIGURATION BITS
 * ======================================================================== */

// CONFIG1L
#pragma config FEXTOSC = OFF        // External Oscillator not enabled
#pragma config RSTOSC = HFINTOSC_64MHZ // HFINTOSC with HFFRQ = 64 MHz

// CONFIG1H
#pragma config CLKOUTEN = OFF       // Clock Out Enable: CLKOUT disabled
#pragma config CSWEN = ON           // Clock Switch Enable: allowed
#pragma config FCMEN = ON           // Fail-Safe Clock Monitor: enabled

// CONFIG2L
#pragma config MCLRE = EXTMCLR      // MCLR pin enabled
#pragma config PWRTE = OFF          // Power-up Timer: disabled
#pragma config LPBOREN = OFF        // Low-Power BOR: disabled
#pragma config BOREN = SBORDIS      // Brown-out Reset: enabled, SBOREN ignored

// CONFIG2H
//#pragma config BORV = VBOR_245      // Brown-out voltage: 2.45V
#pragma config ZCD = OFF            // ZCD module: disabled at reset
#pragma config PPS1WAY = ON         // PPSLOCK one-way set
#pragma config STVREN = ON          // Stack over/underflow reset: enabled
#pragma config XINST = OFF          // Extended Instruction Set: disabled

// CONFIG3L
#pragma config WDTCPS = WDTCPS_31  // WDT period: software control
#pragma config WDTE = OFF           // WDT: disabled

// CONFIG3H
#pragma config WDTCWS = WDTCWS_7   // WDT window: 100%, software control
#pragma config WDTCCS = SC          // WDT clock: software control

// CONFIG4L
#pragma config WRT0 = OFF
#pragma config WRT1 = OFF
#pragma config WRT2 = OFF
#pragma config WRT3 = OFF

// CONFIG4H
#pragma config WRTC = OFF
#pragma config WRTB = OFF
#pragma config WRTD = OFF
#pragma config SCANE = ON           // Scanner module available
#pragma config LVP = ON             // Low Voltage Programming: enabled

// CONFIG5L
#pragma config CP = OFF             // Code Protection: disabled

// CONFIG5H
#pragma config CPD = OFF            // Data EEPROM Protection: disabled

/* ========================================================================
 * CONSTANTS
 * ======================================================================== */

#define _XTAL_FREQ      64000000UL

#define MIDI_NOTE_ON    0x97        // Note On, channel 7 (0-indexed)
#define MIDI_NOTE_OFF   0x87        // Note Off, channel 7 (0-indexed)
#define MIDI_VEL_ON     0x7F        // Velocity 127
#define MIDI_VEL_OFF    0x00        // Velocity 0

#define BASE_NOTE_A     36          // RA0 = note 36
#define BASE_NOTE_C     44          // RC0 = note 44
#define BASE_NOTE_D     52          // RD0 = note 52

#define NUM_INPUTS_A    8
#define NUM_INPUTS_C    8
#define NUM_INPUTS_D    8

/* ========================================================================
 * STATE VARIABLES
 * ======================================================================== */

// Previous stable state for each port (1=released, 0=pressed)
// Initialize to 0xFF (all released) since inputs are pulled high
static uint8_t prevA = 0xFF;
static uint8_t prevC = 0xFF;
static uint8_t prevD = 0xFF;

/* ========================================================================
 * FUNCTION PROTOTYPES
 * ======================================================================== */

static void InitializeOscillator(void);
static void InitializePins(void);
static void InitializeUART(void);
static void InitializeTimer0(void);
static void SendMIDIByte(uint8_t byte);
static void SendNoteOn(uint8_t note);
static void SendNoteOff(uint8_t note);
static void ProcessPortChanges(uint8_t current, uint8_t *prev, uint8_t baseNote, uint8_t count);
static void ScanAndProcess(void);

/* ========================================================================
 * OSCILLATOR INITIALIZATION
 * ========================================================================
 * Configure HFINTOSC to 64 MHz.
 * OSCFRQ register HFFRQ bits select the frequency.
 *   HFFRQ = 0b1000 = 64 MHz
 */
static void InitializeOscillator(void)
{
    OSCCON1 = 0x60;     // HFINTOSC, divider 1:1
    OSCFRQ  = 0x08;     // 64 MHz
    while (!OSCCON3bits.ORDY);  // Wait for oscillator ready
}

/* ========================================================================
 * PIN INITIALIZATION
 * ========================================================================
 *
 * Inputs (active-low with internal weak pull-ups):
 *   RA0-RA7:  TRISA = 0xFF, ANSELA = 0x00, WPUA = 0xFF
 *   RC0-RC7:  TRISC = 0xFF, ANSELC = 0x00, WPUC = 0xFF
 *   RD0-RD7:  TRISD = 0xFF, ANSELD = 0x00, WPUD = 0xFF
 *
 * UART TX Output:
 *   RB4: output, digital
 */
static void InitializePins(void)
{
    // --- Port A: all 8 bits as digital inputs with pull-ups ---
    TRISA  = 0xFF;      // All input
    ANSELA = 0x00;      // All digital
    WPUA   = 0xFF;      // Weak pull-ups on all

    // --- Port C: all 8 bits as digital inputs with pull-ups ---
    TRISC  = 0xFF;      // All input
    ANSELC = 0x00;      // All digital
    WPUC   = 0xFF;      // Weak pull-ups on all

    // --- Port D: all 8 bits as digital inputs with pull-ups ---
    TRISD  = 0xFF;      // All input
    ANSELD = 0x00;      // All digital
    WPUD   = 0xFF;      // Weak pull-ups on all

    // --- Port B: RB4 as digital output for UART TX ---
    TRISB  &= ~0x10;   // RB4 output (bit 4 = 0)
    ANSELB &= ~0x10;   // RB4 digital
    LATB   |= 0x10;    // RB4 idle high (UART idle state)
}

/* ========================================================================
 * UART INITIALIZATION FOR MIDI (31250 BAUD) ON RB4
 * ========================================================================
 *
 * Uses EUSART1 with PPS routing TX1 to RB4.
 *
 * Baud Rate Calculation (64 MHz, BRG16=1, BRGH=1):
 *   Baud = FOSC / (4 * (SPxBRG + 1))
 *   31250 = 64000000 / (4 * (SPxBRG + 1))
 *   SPxBRG + 1 = 512
 *   SPxBRG = 511 = 0x01FF
 *
 * Verification: 64000000 / (4 * 512) = 31250.0 (exact)
 *
 * PPS Output Routing:
 *   RB4PPS = 0x09  =>  TX1 output routed to RB4
 *   (0x09 = TX1/CK1 per PIC18F46Q10 datasheet Table 16-1)
 *
 * Register Settings:
 *   BAUD1CON = 0x08  BRG16=1
 *   TX1STA   = 0x24  TXEN=1, BRGH=1, async 8-bit
 *   RC1STA   = 0x80  SPEN=1, receiver disabled
 *   SP1BRGL  = 0xFF  (low byte of 511)
 *   SP1BRGH  = 0x01  (high byte of 511)
 */
static void InitializeUART(void)
{
    RC1STAbits.SPEN = 0;           // Disable serial port during config

    // PPS: Route EUSART1 TX to RB4
    RB4PPS = 0x09;                 // TX1 -> RB4

    // Baud rate generator: 31250 baud
    BAUD1CON = 0x08;               // BRG16=1
    SP1BRGL  = 0xFF;               // Low byte of 511
    SP1BRGH  = 0x01;               // High byte of 511

    // Transmit control
    TX1STA = 0x24;                 // TXEN=1, BRGH=1, async

    // Receive/serial port control (TX only, no RX)
    RC1STA = 0x80;                 // SPEN=1, CREN=0
}

/* ========================================================================
 * TIMER0 INITIALIZATION (8ms PERIOD)
 * ========================================================================
 *
 * Clock source: FOSC/4 = 16 MHz
 * Prescaler:    1:512
 * Timer tick:   16 MHz / 512 = 31,250 Hz  (32 us per tick)
 * Period reg:   TMR0H = 249
 * Period:       (249 + 1) * 32 us = 8000 us = 8 ms
 *
 * T0CON1 = 0x49:
 *   Bits 7-5: CS = 010  -> FOSC/4
 *   Bit 4:    ASYNC = 0 -> synchronized
 *   Bits 3-0: CKPS = 1001 -> 1:512 prescaler
 *
 * T0CON0 = 0x80:
 *   Bit 7:    EN = 1     -> Timer enabled
 *   Bit 4:    MD16 = 0   -> 8-bit mode
 *   Bits 3-0: OUTPS = 0000 -> 1:1 postscaler
 */
static void InitializeTimer0(void)
{
    T0CON0 = 0x00;                 // Disable timer during config
    T0CON1 = 0x49;                 // FOSC/4, sync, 1:512 prescaler
    TMR0H  = 249;                  // Period register (8-bit mode)
    TMR0L  = 0x00;                 // Clear counter
    PIR0bits.TMR0IF = 0;           // Clear overflow flag
    T0CON0 = 0x80;                 // Enable timer, 8-bit, 1:1 postscaler
}

/* ========================================================================
 * MIDI TRANSMIT FUNCTIONS
 * ======================================================================== */

/*
 * SendMIDIByte - Blocking transmit of one byte via EUSART1
 * Waits for TSR empty (TRMT=1) before writing to TX1REG.
 */
static void SendMIDIByte(uint8_t byte)
{
    while (!TX1STAbits.TRMT);      // Wait for TSR empty
    TX1REG = byte;
}

static void SendNoteOn(uint8_t note)
{
    SendMIDIByte(MIDI_NOTE_ON);
    SendMIDIByte(note);
    SendMIDIByte(MIDI_VEL_ON);
}

static void SendNoteOff(uint8_t note)
{
    SendMIDIByte(MIDI_NOTE_OFF);
    SendMIDIByte(note);
    SendMIDIByte(MIDI_VEL_OFF);
}

/* ========================================================================
 * PORT CHANGE DETECTION AND MIDI OUTPUT
 * ========================================================================
 *
 * Compares current port reading to previous state.
 * Active-low: bit=0 means pressed, bit=1 means released.
 *
 * XOR of current vs previous gives changed bits.
 * For each changed bit:
 *   - If current bit = 0 (pressed)  -> send Note On
 *   - If current bit = 1 (released) -> send Note Off
 */
static void ProcessPortChanges(uint8_t current, uint8_t *prev, 
                                uint8_t baseNote, uint8_t count)
{
    uint8_t changed = current ^ (*prev);
    
    if (changed)
    {
        for (uint8_t i = 0; i < count; i++)
        {
            if (changed & (1 << i))
            {
                uint8_t note = baseNote + i;
                if (!(current & (1 << i)))
                {
                    // Bit went low -> pedal pressed -> Note On
                    SendNoteOn(note);
                }
                else
                {
                    // Bit went high -> pedal released -> Note Off
                    SendNoteOff(note);
                }
            }
        }
        *prev = current;
    }
}

/* ========================================================================
 * SCAN AND PROCESS
 * ========================================================================
 * Read all three ports and process changes.
 */
static void ScanAndProcess(void)
{
    uint8_t curA = PORTA;
    uint8_t curC = PORTC;
    uint8_t curD = PORTD;

    ProcessPortChanges(curA, &prevA, BASE_NOTE_A, NUM_INPUTS_A);
    ProcessPortChanges(curC, &prevC, BASE_NOTE_C, NUM_INPUTS_C);
    ProcessPortChanges(curD, &prevD, BASE_NOTE_D, NUM_INPUTS_D);
}

/* ========================================================================
 * MAIN
 * ======================================================================== */
void main(void)
{
    InitializeOscillator();
    InitializePins();
    InitializeUART();
    InitializeTimer0();

    // Main loop: poll Timer0 overflow, scan on each 8ms tick
    while (1)
    {
        if (PIR0bits.TMR0IF)
        {
            PIR0bits.TMR0IF = 0;
            ScanAndProcess();
        }
    }
}