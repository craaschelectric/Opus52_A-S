// Config.h
// System-wide constants and limits
// Hardware-specific pin assignments and chain config are in ConfigData.h

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ============================================================
// System Limits
// ============================================================

constexpr uint8_t MAX_CHAINS = 8;
constexpr uint8_t WORDS_PER_CHAIN = 16;   // 16 words x 16 bits = 256 bits per chain
constexpr uint16_t MAX_BITS_PER_CHAIN = 256;
constexpr uint8_t MAX_STOPS = 255;
constexpr uint8_t MAX_KEYBOARDS = 8;
constexpr uint8_t MAX_EXPRESSIONS = 4;

// Disabled address marker
constexpr uint16_t ADDR_DISABLED = 0x800;

// ============================================================
// Chain Type Constants
// ============================================================

constexpr uint8_t CHAIN_TYPE_MULTIDROP = 0;
constexpr uint8_t CHAIN_TYPE_SHIFTREG  = 1;

// Chain direction (used by ConfigData, not by scan functions directly)
constexpr uint8_t CHAIN_DIR_INPUT  = 0;
constexpr uint8_t CHAIN_DIR_OUTPUT = 1;

// Expression types
constexpr uint8_t EXPR_ANALOG   = 0;
constexpr uint8_t EXPR_DISCRETE = 1;

// ============================================================
// Timing Constants
// ============================================================

constexpr uint32_t BIT_TIME_US   = 10;
constexpr uint32_t SYNC_HIGH_US  = 10;
constexpr uint32_t SYNC_HOLD_US  = 10;
constexpr uint32_t SAM_PULSE_MS  = 200;
constexpr uint32_t SAM_SETTLE_MS = 250;

// ============================================================
// Display Pins (ILI9341 320x240)
// ============================================================

constexpr uint8_t TFT_CS   = 10;
constexpr uint8_t TFT_DC   = 9;
constexpr uint8_t TOUCH_CS = 8;

#endif // CONFIG_H
