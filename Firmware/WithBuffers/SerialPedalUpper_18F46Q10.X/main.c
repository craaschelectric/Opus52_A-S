/*
 * Pedal Scanner - Unified LOW / HIGH Microcontroller
 * 
 * Target:    PIC18F46Q10 @ 64 MHz HFINTOSC
 * Compiler:  XC8 under MPLAB X
 *
 * Description:
 *   Scans 24 direct inputs every 20ms and transmits MIDI note on/off
 *   messages at 14400 baud.
 *
 *   Compile-time constant LOWER selects the role:
 *
 *   LOWER = true  (LOW PIC):
 *     TX on RB4 via EUSART1.  RB0 pulled up (unused).  No RX.
 *     Base note = 36.  Notes 36-59 across 24 inputs.
 *     Sends to HIGH PIC for merging.
 *
 *   LOWER = false (HIGH PIC):
 *     TX on RB0 via EUSART2.  RX on RB4 via EUSART1.
 *     Base note = 60.  Notes 60-83 across 24 inputs.
 *     Merges locally-generated MIDI with received MIDI from LOW PIC
 *     and outputs the combined stream.
 *
 * Input Mapping (active-low, internal weak pull-ups enabled):
 *   Bits are reversed per port so that pin 7 = lowest note in each group.
 *
 *   reversed(RC7..RC0) ->  Inputs  1-8   ->  Notes base+0  to base+7
 *   reversed(RD7..RD0) ->  Inputs  9-16  ->  Notes base+8  to base+15
 *   reversed(RA7..RA0) ->  Inputs 17-24  ->  Notes base+16 to base+23
 *
 * MIDI I/O:
 *   Channel 7 (0-indexed) => Note On 0x97, Note Off 0x87
 *   Velocity:  127 (0x7F) for Note On, 0 for Note Off
 *   Baud rate: 14400
 *
 * Timer:
 *   Timer0, 16-bit mode, FOSC/4 clock, 1:512 prescaler
 *   Tick: 32 us, period = 625 ticks = 20 ms
 *
 * Buffering:
 *   32-byte software ring buffers on TX (and RX when LOWER=false)
 *   decouple the main loop from hardware FIFO timing.
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

/* ========================================================================
 * ROLE SELECTION
 * ========================================================================
 * Set to true for LOW PIC (TX only on RB4, base note 36).
 * Set to false for HIGH PIC (TX on RB0, RX on RB4, base note 60).
 */
static const bool LOWER = false;

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

#define BASE_NOTE_LOWER 36          // LOW PIC: notes 36-59
#define BASE_NOTE_UPPER 60          // HIGH PIC: notes 60-83

#define NUM_INPUTS      8           // 8 inputs per port

/* ========================================================================
 * RING BUFFER
 * ========================================================================
 * 32-byte ring buffer using power-of-2 masking for index wrap.
 * head = next position to write
 * tail = next position to read
 * Buffer is empty when head == tail.
 * Buffer is full when ((head + 1) & mask) == tail (one slot wasted).
 * Usable capacity = 31 bytes.
 */
#define BUF_SIZE        32
#define BUF_MASK        (BUF_SIZE - 1)

typedef struct {
    uint8_t data[BUF_SIZE];
    uint8_t head;                   // Next write position
    uint8_t tail;                   // Next read position
} RingBuffer;

static RingBuffer txBuf = { .head = 0, .tail = 0 };
static RingBuffer rxBuf = { .head = 0, .tail = 0 };  // Used only when !LOWER

static inline bool BufIsEmpty(const RingBuffer *buf)
{
    return (buf->head == buf->tail);
}

static inline bool BufIsFull(const RingBuffer *buf)
{
    return (((buf->head + 1) & BUF_MASK) == buf->tail);
}

static inline bool BufPut(RingBuffer *buf, uint8_t byte)
{
    if (BufIsFull(buf))
        return false;
    buf->data[buf->head] = byte;
    buf->head = (buf->head + 1) & BUF_MASK;
    return true;
}

static inline bool BufGet(RingBuffer *buf, uint8_t *byte)
{
    if (BufIsEmpty(buf))
        return false;
    *byte = buf->data[buf->tail];
    buf->tail = (buf->tail + 1) & BUF_MASK;
    return true;
}

/* ========================================================================
 * MIDI RECEIVER STATE MACHINE (HIGH PIC only)
 * ========================================================================
 * Collects incoming bytes from the RX ring buffer into complete 3-byte
 * messages. Used only when LOWER = false.
 */
typedef enum {
    RX_WAIT_STATUS,
    RX_WAIT_DATA1,
    RX_WAIT_DATA2
} RxState;

static RxState  rxState  = RX_WAIT_STATUS;
static uint8_t  rxMsg[3];
static bool     rxReady  = false;

/* ========================================================================
 * STATE VARIABLES
 * ======================================================================== */

static uint8_t prevC = 0xFF;       // Previous reversed state, all released
static uint8_t prevD = 0xFF;
static uint8_t prevA = 0xFF;

/* ========================================================================
 * BIT REVERSAL
 * ========================================================================
 * Reverses the bit order of a byte so that pin 7 maps to bit 0
 * (lowest note) and pin 0 maps to bit 7 (highest note).
 */
static uint8_t ReverseBits(uint8_t input)
{
    uint8_t result = 0;
    for (uint8_t bit = 0; bit < 8; bit++)
    {
        result = (result << 1) | (input & 1);
        input >>= 1;
    }
    return result;
}

/* ========================================================================
 * FUNCTION PROTOTYPES
 * ======================================================================== */

static void InitializeOscillator(void);
static void InitializePins(void);
static void InitializeUARTs(void);
static void InitializeTimer0(void);
static void RxService(void);
static void TxService(void);
static void TxEnqueue(uint8_t byte);
static void SendNoteOn(uint8_t note);
static void SendNoteOff(uint8_t note);
static void ForwardMessage(void);
static void ProcessRxBuffer(void);
static void ProcessPortChanges(uint8_t current, uint8_t *prev, uint8_t baseNote);
static void ScanAndProcess(void);

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
 * LOWER = true:
 *   RB4: output (UART TX to HIGH PIC)
 *   RB0: input with pull-up (unused)
 *
 * LOWER = false:
 *   RB4: input (UART RX from LOW PIC)
 *   RB0: output (UART TX merged output)
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

    // --- Port B: role-dependent ---
    if (LOWER)
    {
        // RB4 = TX output, RB0 = unused input with pull-up
        TRISB  &= ~0x10;          // RB4 output
        TRISB  |= 0x01;           // RB0 input
        ANSELB &= ~0x11;          // RB4 and RB0 digital
        LATB   |= 0x10;           // RB4 idle high (UART idle)
        WPUB   |= 0x01;           // RB0 pull-up enabled
    }
    else
    {
        // RB4 = RX input, RB0 = TX output
        TRISB  |= 0x10;           // RB4 input
        TRISB  &= ~0x01;          // RB0 output
        ANSELB &= ~0x11;          // RB4 and RB0 digital
        LATB   |= 0x01;           // RB0 idle high (UART idle)
    }
}

/* ========================================================================
 * UART INITIALIZATION
 * ========================================================================
 *
 * Baud rate: 14400
 * 64 MHz, BRG16=1, BRGH=1 => SPxBRG = (64000000 / (4 * 14400)) - 1
 *                                     = 1110.11 => 1110 = 0x0456
 * Actual baud = 64000000 / (4 * 1111) = 14414.0  (0.1% error)
 *
 * LOWER = true:
 *   EUSART1 TX only on RB4.  RB4PPS = 0x09 (TX1/CK1).
 *
 * LOWER = false:
 *   EUSART1 RX only on RB4.  RX1PPS = 0x0C (RB4 -> RX1).
 *   EUSART2 TX only on RB0.  RB0PPS = 0x0B (TX2/CK2).
 */
static void InitializeUARTs(void)
{
    if (LOWER)
    {
        // --- EUSART1: TX only on RB4 ---
        RC1STAbits.SPEN = 0;

        RB4PPS   = 0x09;          // TX1 -> RB4
        BAUD1CON = 0x08;          // BRG16=1
        SP1BRGL  = 0x56;          // Low byte of 1110
        SP1BRGH  = 0x04;          // High byte of 1110
        TX1STA   = 0x24;          // TXEN=1, BRGH=1, async
        RC1STA   = 0x80;          // SPEN=1, CREN=0
    }
    else
    {
        // --- EUSART1: RX only on RB4 ---
        RC1STAbits.SPEN = 0;

        RX1PPS   = 0x0C;          // RB4 -> RX1
        BAUD1CON = 0x08;          // BRG16=1
        SP1BRGL  = 0x56;          // Low byte of 1110
        SP1BRGH  = 0x04;          // High byte of 1110
        TX1STA   = 0x04;          // TXEN=0, BRGH=1, async
        RC1STA   = 0x90;          // SPEN=1, CREN=1

        // --- EUSART2: TX only on RB0 ---
        RC2STAbits.SPEN = 0;

        RB0PPS   = 0x0B;          // TX2 -> RB0
        BAUD2CON = 0x08;          // BRG16=1
        SP2BRGL  = 0x56;          // Low byte of 1110
        SP2BRGH  = 0x04;          // High byte of 1110
        TX2STA   = 0x24;          // TXEN=1, BRGH=1, async
        RC2STA   = 0x80;          // SPEN=1, CREN=0
    }
}

/* ========================================================================
 * TIMER0 INITIALIZATION (20ms PERIOD)
 * ========================================================================
 *
 * Clock: FOSC/4 = 16 MHz, prescaler 1:512
 * Tick:  32 us
 * Period: 20 ms / 32 us = 625 ticks
 *
 * 16-bit mode required since 625 > 255.
 *
 * T0CON1 = 0x49:  FOSC/4, sync, 1:512
 * T0CON0 = 0x90:  enabled, 16-bit, 1:1 postscaler
 * TMR0H:TMR0L period register = 625 - 1 = 624 = 0x0270
 *
 * Note: In 16-bit mode, TMR0H is the high byte of the period register
 * and TMR0L is the low byte of the counter. The hardware reloads when
 * the counter matches the period value.
 */
static void InitializeTimer0(void)
{
    T0CON0 = 0x00;                 // Disable timer during config
    T0CON1 = 0x49;                 // FOSC/4, sync, 1:512 prescaler
    TMR0H  = 0x02;                 // Period high byte (624 = 0x0270)
    TMR0L  = 0x70;                 // Period low byte
    PIR0bits.TMR0IF = 0;           // Clear overflow flag
    T0CON0 = 0x90;                 // Enable timer, 16-bit, 1:1 postscaler
}

/* ========================================================================
 * RX SERVICE - DRAIN HARDWARE FIFO INTO SOFTWARE BUFFER (HIGH PIC only)
 * ========================================================================
 * Called every main loop iteration when LOWER = false. Reads all
 * available bytes from the EUSART1 hardware FIFO into the RX ring
 * buffer.
 */
static void RxService(void)
{
    if (LOWER)
        return;

    // Handle overrun error: clear by toggling CREN
    if (RC1STAbits.OERR)
    {
        RC1STAbits.CREN = 0;
        RC1STAbits.CREN = 1;
        rxState = RX_WAIT_STATUS;
        return;
    }

    // Drain all available bytes from hardware into software buffer
    while (PIR3bits.RC1IF)
    {
        uint8_t byte = RC1REG;
        BufPut(&rxBuf, byte);
    }
}

/* ========================================================================
 * TX SERVICE - DRAIN SOFTWARE BUFFER INTO HARDWARE
 * ========================================================================
 * Called every main loop iteration. Sends one byte from the TX buffer
 * to the appropriate EUSART hardware if ready. Non-blocking.
 *
 * LOWER = true:  Uses EUSART1 (TX1STA, TX1REG)
 * LOWER = false: Uses EUSART2 (TX2STA, TX2REG)
 */
static void TxService(void)
{
    uint8_t byte;

    if (LOWER)
    {
        if (TX1STAbits.TRMT && BufGet(&txBuf, &byte))
        {
            TX1REG = byte;
        }
    }
    else
    {
        if (TX2STAbits.TRMT && BufGet(&txBuf, &byte))
        {
            TX2REG = byte;
        }
    }
}

/* ========================================================================
 * TX ENQUEUE - NON-BLOCKING BYTE TRANSMIT
 * ======================================================================== */
static void TxEnqueue(uint8_t byte)
{
    BufPut(&txBuf, byte);
}

/* ========================================================================
 * MIDI TRANSMIT HELPERS (via TX ring buffer)
 * ======================================================================== */

static void SendNoteOn(uint8_t note)
{
    TxEnqueue(MIDI_NOTE_ON);
    TxEnqueue(note);
    TxEnqueue(MIDI_VEL_ON);
}

static void SendNoteOff(uint8_t note)
{
    TxEnqueue(MIDI_NOTE_OFF);
    TxEnqueue(note);
    TxEnqueue(MIDI_VEL_OFF);
}

/* ========================================================================
 * FORWARD COMPLETE RECEIVED MESSAGE (HIGH PIC only)
 * ========================================================================
 * Enqueues the 3-byte message assembled from the RX state machine
 * into the TX ring buffer.
 */
static void ForwardMessage(void)
{
    TxEnqueue(rxMsg[0]);
    TxEnqueue(rxMsg[1]);
    TxEnqueue(rxMsg[2]);
    rxReady = false;
}

/* ========================================================================
 * PROCESS RX BUFFER - MIDI INPUT STATE MACHINE (HIGH PIC only)
 * ========================================================================
 * Pulls bytes from the RX ring buffer and feeds them into the MIDI
 * message assembly state machine. Stops if a complete message is
 * assembled (rxReady set) so the main loop can forward it before
 * continuing.
 */
static void ProcessRxBuffer(void)
{
    if (LOWER)
        return;

    uint8_t byte;

    while (!rxReady && BufGet(&rxBuf, &byte))
    {
        // Ignore real-time messages (0xF8-0xFF)
        if (byte >= 0xF8)
            continue;

        switch (rxState)
        {
            case RX_WAIT_STATUS:
                if (byte & 0x80)
                {
                    rxMsg[0] = byte;
                    rxState = RX_WAIT_DATA1;
                }
                break;

            case RX_WAIT_DATA1:
                if (byte & 0x80)
                {
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
                if (byte & 0x80)
                {
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
}

/* ========================================================================
 * PORT CHANGE DETECTION AND MIDI OUTPUT
 * ========================================================================
 * Compares current reversed port reading against previous state.
 * XOR detects changes. Active-low: bit=0 means pressed.
 */
static void ProcessPortChanges(uint8_t current, uint8_t *prev,
                                uint8_t baseNote)
{
    uint8_t changed = current ^ (*prev);

    if (changed)
    {
        for (uint8_t i = 0; i < NUM_INPUTS; i++)
        {
            if (changed & (1 << i))
            {
                uint8_t note = baseNote + i;
                if (!(current & (1 << i)))  // Active-low: 0 = pressed
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
 * ========================================================================
 * Reads all three ports, reverses the bit order of each, then runs
 * change detection. Port scan order matches the note mapping:
 *   PORTC (reversed) -> base + 0
 *   PORTD (reversed) -> base + 8
 *   PORTA (reversed) -> base + 16
 */
static void ScanAndProcess(void)
{
    uint8_t baseNote = LOWER ? BASE_NOTE_LOWER : BASE_NOTE_UPPER;

    uint8_t curC = ReverseBits(PORTC);
    uint8_t curD = ReverseBits(PORTD);
    uint8_t curA = ReverseBits(PORTA);

    ProcessPortChanges(curC, &prevC, baseNote);
    ProcessPortChanges(curD, &prevD, baseNote + 8);
    ProcessPortChanges(curA, &prevA, baseNote + 16);
}

/* ========================================================================
 * MAIN
 * ========================================================================
 *
 * Main loop structure:
 *   1. RxService:       Drain hardware RX FIFO into software buffer (HIGH only).
 *   2. ProcessRxBuffer: Parse RX buffer into MIDI messages (HIGH only).
 *   3. ForwardMessage:  If complete message ready, enqueue to TX (HIGH only).
 *   4. ScanAndProcess:  On 20ms timer tick, scan inputs, enqueue changes.
 *   5. TxService:       Feed one byte from TX buffer to hardware.
 */
void main(void)
{
    InitializeOscillator();
    InitializePins();
    InitializeUARTs();
    InitializeTimer0();

    while (1)
    {
        // RX handling (HIGH PIC only - returns immediately when LOWER)
        RxService();
        ProcessRxBuffer();

        if (!LOWER && rxReady)
        {
            ForwardMessage();
        }

        // Local scan on 20ms timer tick
        if (PIR0bits.TMR0IF)
        {
            PIR0bits.TMR0IF = 0;
            ScanAndProcess();
        }

        // Feed TX buffer to hardware
        TxService();
    }
}