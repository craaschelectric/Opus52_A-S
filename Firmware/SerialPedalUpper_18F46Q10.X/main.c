/*
 * Pedal Scanner - HIGH Microcontroller
 * 
 * Target:    PIC18F46Q10 @ 64 MHz HFINTOSC
 * Compiler:  XC8 under MPLAB X
 *
 * Description:
 *   Scans 24 direct inputs (pedals 25-32 and toe pistons 1-16) every 8ms.
 *   Receives serial MIDI from the LOW microcontroller on RB4.
 *   Merges locally-generated MIDI with received MIDI and outputs the
 *   combined stream on RB0 at 31250 baud.
 *
 *   The merger ensures that a complete 3-byte MIDI message is received
 *   from the LOW PIC before forwarding it, preventing interleaving of
 *   local and remote bytes in the output stream.
 *
 * Input Mapping (active-low, internal weak pull-ups enabled):
 *   RA0-RA7  ->  Pedals 25-32     ->  MIDI Notes 60-67
 *   RC0-RC7  ->  Toe Pistons 1-8  ->  MIDI Notes 68-75
 *   RD0-RD7  ->  Toe Pistons 9-16 ->  MIDI Notes 76-83
 *
 * MIDI I/O:
 *   Channel 7 (0-indexed) => Note On 0x97, Note Off 0x87
 *   Velocity:  127 (0x7F) for Note On, 0 for Note Off
 *   RX input:  RB4 via EUSART1 RX at 31250 baud (from LOW PIC)
 *   TX output: RB0 via EUSART2 TX at 31250 baud (merged output)
 *
 * Timer:
 *   Timer0, 8-bit mode, FOSC/4 clock, 1:512 prescaler, period=249 => 8ms
 *
 * Merger Architecture:
 *   The EUSART1 RX collects incoming bytes into a 3-byte MIDI message
 *   buffer using a simple state machine. When a complete message is
 *   assembled, it is forwarded out EUSART2 TX as a block. Local scan
 *   messages are sent directly on EUSART2 TX. Since both sources are
 *   checked each loop iteration and messages are sent as complete 3-byte
 *   blocks, bytes from different sources never interleave.
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

/* ========================================================================
 * CONFIGURATION BITS
 * ======================================================================== */

// CONFIG1L
#pragma config FEXTOSC = OFF
#pragma config RSTOSC = HFINTOSC_64MHZ

// CONFIG1H
#pragma config CLKOUTEN = OFF
#pragma config CSWEN = ON
#pragma config FCMEN = ON

// CONFIG2L
#pragma config MCLRE = EXTMCLR
#pragma config PWRTE = OFF
#pragma config LPBOREN = OFF
#pragma config BOREN = SBORDIS

// CONFIG2H
#pragma config BORV = VBOR_245
#pragma config ZCD = OFF
#pragma config PPS1WAY = ON
#pragma config STVREN = ON
#pragma config XINST = OFF

// CONFIG3L
#pragma config WDTCPS = WDTCPS_31
#pragma config WDTE = OFF

// CONFIG3H
#pragma config WDTCWS = WDTCWS_7
#pragma config WDTCCS = SC

// CONFIG4L
#pragma config WRT0 = OFF
#pragma config WRT1 = OFF
#pragma config WRT2 = OFF
#pragma config WRT3 = OFF

// CONFIG4H
#pragma config WRTC = OFF
#pragma config WRTB = OFF
#pragma config WRTD = OFF
#pragma config SCANE = ON
#pragma config LVP = ON

// CONFIG5L
#pragma config CP = OFF

// CONFIG5H
#pragma config CPD = OFF

/* ========================================================================
 * CONSTANTS
 * ======================================================================== */

#define _XTAL_FREQ      64000000UL

#define MIDI_NOTE_ON    0x97        // Note On, channel 7 (0-indexed)
#define MIDI_NOTE_OFF   0x87        // Note Off, channel 7 (0-indexed)
#define MIDI_VEL_ON     0x7F
#define MIDI_VEL_OFF    0x00

#define BASE_NOTE_A     60          // RA0 = note 60
#define BASE_NOTE_C     68          // RC0 = note 68
#define BASE_NOTE_D     76          // RD0 = note 76

#define NUM_INPUTS_A    8
#define NUM_INPUTS_C    8
#define NUM_INPUTS_D    8

/* ========================================================================
 * MIDI RECEIVER STATE MACHINE
 * ========================================================================
 * Collects incoming bytes from the LOW PIC into complete 3-byte messages.
 *
 * States:
 *   WAIT_STATUS  - Waiting for a status byte (bit 7 set)
 *   WAIT_DATA1   - Have status, waiting for first data byte
 *   WAIT_DATA2   - Have status + data1, waiting for second data byte
 *
 * When all 3 bytes are collected, rxReady is set true and the message
 * can be forwarded. Any unexpected status byte resets the state machine.
 * Real-time messages (0xF8-0xFF) are ignored (not expected in this system).
 */
typedef enum {
    RX_WAIT_STATUS,
    RX_WAIT_DATA1,
    RX_WAIT_DATA2
} RxState;

static RxState  rxState  = RX_WAIT_STATUS;
static uint8_t  rxMsg[3];          // Assembled incoming message
static bool     rxReady  = false;  // True when a complete message is ready

/* ========================================================================
 * STATE VARIABLES
 * ======================================================================== */

static uint8_t prevA = 0xFF;       // Previous state, all released
static uint8_t prevC = 0xFF;
static uint8_t prevD = 0xFF;

/* ========================================================================
 * FUNCTION PROTOTYPES
 * ======================================================================== */

static void InitializeOscillator(void);
static void InitializePins(void);
static void InitializeUART1_RX(void);
static void InitializeUART2_TX(void);
static void InitializeTimer0(void);
static void SendMIDIByte(uint8_t byte);
static void SendNoteOn(uint8_t note);
static void SendNoteOff(uint8_t note);
static void ForwardMessage(void);
static void ProcessPortChanges(uint8_t current, uint8_t *prev, uint8_t baseNote, uint8_t count);
static void ScanAndProcess(void);
static void PollReceiver(void);

/* ========================================================================
 * OSCILLATOR INITIALIZATION
 * ======================================================================== */
static void InitializeOscillator(void)
{
    OSCCON1 = 0x60;                // HFINTOSC, divider 1:1
    OSCFRQ  = 0x08;                // 64 MHz
    while (!OSCCON3bits.ORDY);     // Wait for oscillator ready
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
 * UART RX Input:
 *   RB4: input, digital
 *
 * UART TX Output:
 *   RB0: output, digital
 */
static void InitializePins(void)
{
    // --- Port A: all 8 bits as digital inputs with pull-ups ---
    TRISA  = 0xFF;
    ANSELA = 0x00;
    WPUA   = 0xFF;

    // --- Port C: all 8 bits as digital inputs with pull-ups ---
    TRISC  = 0xFF;
    ANSELC = 0x00;
    WPUC   = 0xFF;

    // --- Port D: all 8 bits as digital inputs with pull-ups ---
    TRISD  = 0xFF;
    ANSELD = 0x00;
    WPUD   = 0xFF;

    // --- Port B: RB4 as digital input (UART RX), RB0 as digital output (UART TX) ---
    TRISB  |= 0x10;               // RB4 input (bit 4 = 1)
    TRISB  &= ~0x01;              // RB0 output (bit 0 = 0)
    ANSELB &= ~0x11;              // RB4 and RB0 digital
    LATB   |= 0x01;               // RB0 idle high (UART idle state)
}

/* ========================================================================
 * UART1 INITIALIZATION - RECEIVE ONLY (RB4)
 * ========================================================================
 *
 * EUSART1 configured for RX only at 31250 baud.
 *
 * Baud: 64 MHz, BRG16=1, BRGH=1 => SPxBRG = 511 = 0x01FF
 *
 * PPS Input Routing:
 *   RX1PPS = 0x0C  =>  RB4 mapped to EUSART1 RX input
 *   (Port B = 0x08 base + pin 4 = 0x0C, per datasheet Table 16-2)
 *
 * Register Settings:
 *   BAUD1CON = 0x08  BRG16=1
 *   TX1STA   = 0x04  TXEN=0 (TX disabled), BRGH=1
 *   RC1STA   = 0x90  SPEN=1, CREN=1 (continuous receive)
 *   SP1BRGL  = 0xFF
 *   SP1BRGH  = 0x01
 */
static void InitializeUART1_RX(void)
{
    RC1STAbits.SPEN = 0;           // Disable serial port during config

    // PPS: Route RB4 to EUSART1 RX
    RX1PPS = 0x0C;                 // RB4 -> RX1 (0x08 + 4)

    // Baud rate generator: 31250 baud
    BAUD1CON = 0x08;               // BRG16=1
    SP1BRGL  = 0xFF;               // Low byte of 511
    SP1BRGH  = 0x01;               // High byte of 511

    // TX disabled on EUSART1 (we only receive on this module)
    TX1STA = 0x04;                 // TXEN=0, BRGH=1, async

    // Enable serial port and continuous receive
    RC1STA = 0x90;                 // SPEN=1, CREN=1
}

/* ========================================================================
 * UART2 INITIALIZATION - TRANSMIT ONLY (RB0)
 * ========================================================================
 *
 * EUSART2 configured for TX only at 31250 baud.
 *
 * Baud: 64 MHz, BRG16=1, BRGH=1 => SPxBRG = 511 = 0x01FF
 *
 * PPS Output Routing:
 *   RB0PPS = 0x0B  =>  TX2 output routed to RB0
 *   (0x0B = TX2/CK2 per PIC18F46Q10 datasheet Table 16-1)
 *
 * Register Settings:
 *   BAUD2CON = 0x08  BRG16=1
 *   TX2STA   = 0x24  TXEN=1, BRGH=1, async
 *   RC2STA   = 0x80  SPEN=1, CREN=0 (no receive)
 *   SP2BRGL  = 0xFF
 *   SP2BRGH  = 0x01
 */
static void InitializeUART2_TX(void)
{
    RC2STAbits.SPEN = 0;           // Disable serial port during config

    // PPS: Route EUSART2 TX to RB0
    RB0PPS = 0x0B;                 // TX2 -> RB0

    // Baud rate generator: 31250 baud
    BAUD2CON = 0x08;               // BRG16=1
    SP2BRGL  = 0xFF;               // Low byte of 511
    SP2BRGH  = 0x01;               // High byte of 511

    // Transmit control
    TX2STA = 0x24;                 // TXEN=1, BRGH=1, async

    // Serial port enable (TX only, no RX)
    RC2STA = 0x80;                 // SPEN=1, CREN=0
}

/* ========================================================================
 * TIMER0 INITIALIZATION (8ms PERIOD)
 * ========================================================================
 *
 * Identical to LOW PIC.
 *
 * Clock: FOSC/4 = 16 MHz, prescaler 1:512
 * Tick:  32 us, period = 250 ticks = 8 ms
 *
 * T0CON1 = 0x49:  FOSC/4, sync, 1:512
 * T0CON0 = 0x80:  enabled, 8-bit, 1:1 postscaler
 * TMR0H  = 249:   period register
 */
static void InitializeTimer0(void)
{
    T0CON0 = 0x00;                 // Disable timer during config
    T0CON1 = 0x49;                 // FOSC/4, sync, 1:512 prescaler
    TMR0H  = 249;                  // Period register
    TMR0L  = 0x00;                 // Clear counter
    PIR0bits.TMR0IF = 0;           // Clear overflow flag
    T0CON0 = 0x80;                 // Enable timer, 8-bit, 1:1 postscaler
}

/* ========================================================================
 * MIDI TRANSMIT FUNCTIONS (via EUSART2)
 * ======================================================================== */

/*
 * SendMIDIByte - Blocking transmit of one byte via EUSART2.
 * Waits for TSR empty (TRMT=1) before writing to TX2REG.
 */
static void SendMIDIByte(uint8_t byte)
{
    while (!TX2STAbits.TRMT);
    TX2REG = byte;
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
 * FORWARD COMPLETE RECEIVED MESSAGE
 * ========================================================================
 * Sends the 3-byte message assembled from EUSART1 RX out via EUSART2 TX.
 */
static void ForwardMessage(void)
{
    SendMIDIByte(rxMsg[0]);
    SendMIDIByte(rxMsg[1]);
    SendMIDIByte(rxMsg[2]);
    rxReady = false;
}

/* ========================================================================
 * POLL RECEIVER - MIDI INPUT STATE MACHINE
 * ========================================================================
 *
 * Called from main loop (not only on timer tick) to ensure no bytes are
 * missed. Reads any available byte from EUSART1 RX and feeds it into
 * the state machine.
 *
 * Handles overrun errors (OERR) by toggling CREN to clear the error
 * and reset the receive logic.
 *
 * When a complete 3-byte message is assembled, rxReady is set true.
 * The message is not forwarded here; that happens in the main loop
 * to maintain control over output ordering.
 */
static void PollReceiver(void)
{
    // Handle overrun error: clear by toggling CREN
    if (RC1STAbits.OERR)
    {
        RC1STAbits.CREN = 0;
        RC1STAbits.CREN = 1;
        rxState = RX_WAIT_STATUS;  // Reset state machine on error
        return;
    }

    // Check if a byte is available
    if (!PIR3bits.RC1IF)
        return;

    uint8_t byte = RC1REG;        // Read byte (also clears RC1IF)

    // Ignore real-time messages (0xF8-0xFF) - not expected but be safe
    if (byte >= 0xF8)
        return;

    switch (rxState)
    {
        case RX_WAIT_STATUS:
            if (byte & 0x80)       // Status byte?
            {
                rxMsg[0] = byte;
                rxState = RX_WAIT_DATA1;
            }
            // else: data byte without status - discard
            break;

        case RX_WAIT_DATA1:
            if (byte & 0x80)       // Unexpected status byte?
            {
                // New message starting - restart with this as status
                rxMsg[0] = byte;
                rxState = RX_WAIT_DATA1;
            }
            else
            {
                rxMsg[1] = byte;
                rxState = RX_WAIT_DATA2;
            }
            break;

        case RX_WAIT_DATA2:
            if (byte & 0x80)       // Unexpected status byte?
            {
                // Abort current message, start new one
                rxMsg[0] = byte;
                rxState = RX_WAIT_DATA1;
            }
            else
            {
                rxMsg[2] = byte;
                rxReady = true;
                rxState = RX_WAIT_STATUS;
            }
            break;
    }
}

/* ========================================================================
 * PORT CHANGE DETECTION AND MIDI OUTPUT
 * ========================================================================
 * Same logic as LOW PIC: XOR detects changes, active-low sensing.
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
                    SendNoteOn(note);
                }
                else
                {
                    SendNoteOff(note);
                }
            }
        }
        *prev = current;
    }
}

/* ========================================================================
 * SCAN AND PROCESS
 * ======================================================================== */
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
 * ========================================================================
 *
 * Main loop structure:
 *   1. Always poll the UART receiver to collect incoming bytes promptly.
 *   2. If a complete received message is ready, forward it immediately.
 *   3. On each 8ms timer tick, scan local inputs and send any changes.
 *
 * This ordering ensures:
 *   - Received bytes are never missed (polled every iteration).
 *   - Complete messages from LOW PIC are forwarded without byte mixing.
 *   - Local scan output is interleaved at message boundaries only.
 */
void main(void)
{
    InitializeOscillator();
    InitializePins();
    InitializeUART1_RX();
    InitializeUART2_TX();
    InitializeTimer0();

    while (1)
    {
        // Always check for incoming MIDI from LOW PIC
        PollReceiver();

        // Forward any complete received message
        if (rxReady)
        {
            ForwardMessage();
        }

        // Local scan on 8ms timer tick
        if (PIR0bits.TMR0IF)
        {
            PIR0bits.TMR0IF = 0;
            ScanAndProcess();
        }
    }
}