// Config.h
// SAM Discovery Tool - Hardcoded Configuration

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ============================================================
// Chain Configuration
// ============================================================

// Number of chains actually in use
constexpr uint8_t NUMBER_OF_CHAINS = 2;
// Maximum chains supported
constexpr uint8_t MAX_CHAINS = 8;

// Chain types
constexpr uint8_t CHAIN_TYPE_597 = 0;       // 74HC596/597 chains
constexpr uint8_t CHAIN_TYPE_MULTIDROP = 1; // Multidrop SAM bus

// Chain Pin Configuration (order: in/out/sync/clock)
// Pins for chains 2-7 are placeholders (255 = unused)
//                                     Chain:    0     1     2     3     4     5     6     7
constexpr uint8_t CHAIN_DATA_IN_PIN[]        = {   35,    23,  255,  255,  255,  255,  255,  255 };
constexpr uint8_t CHAIN_DATA_OUT_PIN[]       = {   14,    22,  255,  255,  255,  255,  255,  255 };
constexpr uint8_t CHAIN_SYNC_PIN[]           = {   34,   21,  255,  255,  255,  255,  255,  255 };
constexpr uint8_t CHAIN_CLOCK_PIN[]          = {   33,   0,  255,  255,  255,  255,  255,  255 };
constexpr uint8_t CHAIN_TYPE[]               = {   0,    0,    0,    0,    0,    0,    0,    0 }; // 0=597, 1=MULTIDROP

// ============================================================
// SAM Discovery Configuration (hardcoded)
// ============================================================

// Stop sense inputs
constexpr uint8_t SENSE_CHAIN = 0;
constexpr uint8_t SENSE_CHAIN_TYPE = CHAIN_TYPE_597;
constexpr uint16_t SENSE_START_BIT = 0;
constexpr uint16_t SENSE_END_BIT = 127;

// Stop coil outputs
constexpr uint8_t COIL_CHAIN = 1;
constexpr uint8_t COIL_CHAIN_TYPE = CHAIN_TYPE_597;
constexpr uint16_t COIL_START_BIT = 0;
constexpr uint16_t COIL_END_BIT = 127;

// ============================================================
// Timing Constants
// ============================================================

constexpr uint32_t BIT_TIME_US = 10;
constexpr uint32_t SYNC_HIGH_US = 10;
constexpr uint32_t SYNC_HOLD_US = 10;
constexpr uint32_t SAM_PULSE_MS = 200;
constexpr uint32_t SAM_SETTLE_MS = 250;

// ============================================================
// Display Pins (ILI9341 320x240)
// ============================================================

constexpr uint8_t TFT_CS = 10;
constexpr uint8_t TFT_DC = 9;
constexpr uint8_t TOUCH_CS = 8;

// ============================================================
// Power Supply
// ============================================================

constexpr uint8_t POWER_ENABLE_PIN = 17;
constexpr uint8_t PERIPH_ENABLE_PIN = 1;

// ============================================================
// System Limits
// ============================================================

constexpr uint8_t MAX_STOPS = 255;
constexpr uint8_t WORDS_PER_CHAIN = 16;  // 16 words x 16 bits = 256 bits per chain
constexpr uint16_t MAX_BITS_PER_CHAIN = 256;

// Disabled address marker
constexpr uint16_t ADDR_DISABLED = 0x800;

#endif // CONFIG_H
