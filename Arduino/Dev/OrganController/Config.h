// Config.h
// Simplified Organ Controller for Hauptwerk
// Teensy 4.1

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ============================================================
// System Limits
// ============================================================

constexpr uint8_t  MAX_CHAINS      = 8;
constexpr uint16_t BITS_PER_CHAIN  = 256;
constexpr uint8_t  WORDS_PER_CHAIN = 16;   // 256 bits / 16 bits per word

constexpr uint16_t MAX_STOPS       = 256;
constexpr uint8_t  MAX_KEYBOARDS   = 8;
constexpr uint8_t  MAX_EXPRESSIONS = 4;
constexpr uint8_t  MAX_ACTIVE_COILS = 64;

constexpr uint16_t ADDR_DISABLED   = 0x800;

// ============================================================
// Timing
// ============================================================

constexpr uint32_t BIT_TIME_US     = 36;     // Clock half-period (microseconds)
constexpr uint32_t SYNC_PULSE_US   = 800;    // Sync pulse width
constexpr uint32_t SYNC_SETTLE_US  = 50;     // Settle time after sync
constexpr uint32_t SAM_PULSE_MS    = 200;    // Default coil on-time

// millis() rollover guard: if millis() is within this many ms of rollover
// (0xFFFFFFFF), the main loop will busy-wait until rollover completes.
// Must be >= the largest millis()-based timeout in the system (SAM pulse +
// debounce + retry increment = 200 + 100 + 100 = 400ms worst case, round up).
constexpr uint32_t MILLIS_ROLLOVER_GUARD_MS = 500;

// ============================================================
// Chain Configuration Constants
// ============================================================

constexpr uint8_t CHAIN_TYPE_MULTIDROP = 0;  // SAM bus: sync HIGH→LOW
constexpr uint8_t CHAIN_TYPE_SHIFTREG  = 1;  // 595/597: sync LOW→HIGH

constexpr uint8_t CHAIN_DIR_INPUT  = 0;
constexpr uint8_t CHAIN_DIR_OUTPUT = 1;

// ============================================================
// Expression Types
// ============================================================

constexpr uint8_t EXPR_ANALOG   = 0;
constexpr uint8_t EXPR_DISCRETE = 1;

// Minimum CC step change required before sending a new expression CC message.
// Prevents jitter at step boundaries from generating a stream of CC messages.
constexpr uint8_t EXPR_CC_DEADBAND = 2;

// ============================================================
// Serial MIDI
// ============================================================

#define SERIAL_MIDI_PORT Serial7       // Hardware serial port for DIN MIDI
constexpr uint32_t SERIAL_MIDI_BAUD = 19200;
constexpr uint8_t  SERIAL_MIDI_RX_PIN = 28;  // Adjust per wiring

// ============================================================
// Address Helper Macros
// ============================================================
// Bit address format: 0xCWB  (C=chain 0-7, W=word 0-F, B=bit 0-F)

#define ADDR_CHAIN(a)  (((a) >> 8) & 0x07)
#define ADDR_WORD(a)   (((a) >> 4) & 0x0F)
#define ADDR_BIT(a)    ((a) & 0x0F)
#define MAKE_ADDR(c,w,b) (((c)<<8)|((w)<<4)|(b))
#define ADDR_VALID(a)  ((a) != ADDR_DISABLED)

#endif // CONFIG_H
