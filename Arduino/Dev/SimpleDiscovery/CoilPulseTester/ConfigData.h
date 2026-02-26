// ConfigData.h
// Organ-specific configuration data
// Replace this file for each installation

#ifndef CONFIG_DATA_H
#define CONFIG_DATA_H

#include "Config.h"

// ============================================================
// Chain Configuration (parallel arrays)
// ============================================================
//   Chain 0: Multidrop input (keyboards + pistons), 128 bits
//   Chain 1: 595 output (SAM coils), 128 bits
//   Chain 2: 597 input (SAM sense), 128 bits
// Pin 255 = unused (don't-care for unidirectional chains)

constexpr uint8_t NUM_CHAINS = 3;

const uint8_t  chainDataInPin[MAX_CHAINS]  = {  4, 255,  35 };// KbdIn, (unused), SensIn
const uint8_t  chainDataOutPin[MAX_CHAINS] = {255,  22, 255 };// (unused), CoilData, (unused)
const uint8_t  chainClockPin[MAX_CHAINS]   = {  6,   0,  33 };// KbdCLK, CoilCLK, SensCLK
const uint8_t  chainSyncPin[MAX_CHAINS]    = {  5,  21,  34 };// KbdLOAD, CoilLOAD, SensLOAD
const uint16_t chainBitsUsed[MAX_CHAINS]   = {128, 128, 128 };
const uint8_t  chainType[MAX_CHAINS]       = { CHAIN_TYPE_MULTIDROP, CHAIN_TYPE_SHIFTREG, CHAIN_TYPE_SHIFTREG };
const uint8_t  chainDir[MAX_CHAINS]        = { CHAIN_DIR_INPUT, CHAIN_DIR_OUTPUT, CHAIN_DIR_INPUT };

// ============================================================
// Power Management & Display Backlight
// ============================================================

constexpr uint8_t  POWER_SUPPLY_PIN          = 7;    // LOW = power on, HIGH = power off
constexpr uint8_t  BACKLIGHT_ON              = 1;    // HIGH = backlight on
constexpr uint8_t  SCREEN1_BACKLIGHT_SECONDS = 10;    // Backlight on-time in Screen 1 (standby)

// ============================================================
// Heartbeat Configuration
// ============================================================
// Hauptwerk sends periodic MIDI to indicate it's running.
// Mode (toggle/simple) and timeout are stored in EEPROM.
// Note and channel are fixed per installation.

constexpr uint8_t  HEARTBEAT_MIDI_CHANNEL = 0;   // 0-indexed channel
constexpr uint8_t  HEARTBEAT_MIDI_NOTE    = 0;   // Note number

// ============================================================
// MIDI Channel Assignments (0-indexed)
// ============================================================

constexpr uint8_t MIDI_CH_STOPS_1       = 0;   // Stops 0-127
constexpr uint8_t MIDI_CH_STOPS_2       = 1;   // Stops 128-255
constexpr uint8_t MIDI_CH_EXPRESSION    = 11;  // Expression CCs

// Keyboard MIDI channels (per keyboard entry)
constexpr uint8_t MIDI_CH_KEYBOARD_BASE = 3;   // Keyboards start at channel 4

// SHIFT offset: when SHIFT is held, MIDI channel += this value
constexpr uint8_t SHIFT_CHANNEL_OFFSET  = 8;

// ============================================================
// SHIFT Piston Configuration
// ============================================================
// A single special-purpose input bit. When held with another input,
// that input sends on channel + SHIFT_CHANNEL_OFFSET instead.
// If pressed and released alone, sends its own noteOn/noteOff.

constexpr uint16_t SHIFT_INPUT_ADDR     = ADDR_DISABLED;  // CWB address (placeholder)
constexpr uint8_t  SHIFT_MIDI_CHANNEL   = MIDI_CH_KEYBOARD_BASE;  // 0-indexed
constexpr uint8_t  SHIFT_MIDI_NOTE      = 127;

// ============================================================
// Keyboard Configuration (parallel arrays)
// ============================================================
// Each entry is a contiguous range of input bits on a scan chain.
// MIDI note sent = lowNote + (bit position - startBit)
// Pistons are simply keyboard entries with their own channel/notes.

constexpr uint8_t NUM_KEYBOARDS = 6; // Gt 1-60, Gt 61, Sw 1-48, Sw 49-60, Sw 61, Pistons

const uint8_t  kbdChain[MAX_KEYBOARDS]       = {  0,  2,    0,    0,  2,   2 };
const uint16_t kbdStartBit[MAX_KEYBOARDS]    = {  0,  0x21,0x48,0x3C, 0x20, 0x60};
const uint16_t kbdEndBit[MAX_KEYBOARDS]      = { 59,  0x21,0x77,0x47, 0x20, 0x77};
const uint8_t  kbdMidiChannel[MAX_KEYBOARDS] = {
    MIDI_CH_KEYBOARD_BASE + 0,  // Gt 1-60
    MIDI_CH_KEYBOARD_BASE + 0,  // Gt 61
    MIDI_CH_KEYBOARD_BASE + 1,      // Sw 1-48
    MIDI_CH_KEYBOARD_BASE + 1,      // Sw 49-60
    MIDI_CH_KEYBOARD_BASE + 1,      // Sw 61
    MIDI_CH_KEYBOARD_BASE + 2       // Pistons
};
const uint8_t  kbdLowNote[MAX_KEYBOARDS]     = { 36,  96, 36, 84, 96, 0 };
const uint8_t  kbdVelocity[MAX_KEYBOARDS]    = {127, 127, 127, 127, 127, 127 };

// ============================================================
// Stop Configuration (parallel arrays)
// ============================================================
// 49 stops. Coils on chain 1 (595 output), sense on chain 2 (597 input).
// Addresses from SAM discovery tool.
//
// Stops are mapped to MIDI:
//   stopIndex 0-127  → MIDI_CH_STOPS_1, note = stopIndex
//   stopIndex 128-255 → MIDI_CH_STOPS_2, note = stopIndex - 128
//
// Sense LOW = tab ON for SAM stops.

constexpr uint8_t NUM_STOPS = 49;

// Physical sense input (CWB address) - chain 2 input
const uint16_t stopSenseAddr[MAX_STOPS] = {
    0x25F, // [ 0] 16 Subbass (bit 95)
    0x25E, // [ 1] 16 Quintadena (bit 94)
    0x25D, // [ 2] 8 Principal (bit 93)
    0x25C, // [ 3] 8 Bassfloete (bit 92)
    0x25B, // [ 4] 4 Choralbass (bit 91)
    0x25A, // [ 5] III Mixture (bit 90)
    0x259, // [ 6] 16 Fagot (bit 89)
    0x258, // [ 7] 8 Fagot (bit 88)
    0x24A, // [ 8] 4 Fagot (bit 74)
    0x24B, // [ 9] Gt/Ped 8 (bit 75)
    0x24C, // [10] Gt/Ped 4 (bit 76)
    0x24D, // [11] Sw/Ped 8 (bit 77)
    0x24E, // [12] Sw/Ped 4 (bit 78)
    0x24F, // [13] 8 Gedeckt (bit 79)
    0x252, // [14] 8 Viola (bit 82)
    0x253, // [15] 8 Viola Celest (bit 83)
    0x254, // [16] 4 Principal (bit 84)
    0x255, // [17] 4 Spitzfloete (bit 85)
    0x256, // [18] 2 Flachfloete (bit 86)
    0x257, // [19] 1 1/3 Quint (bit 87)
    0x242, // [20] III Scharf (bit 66)
    0x243, // [21] 8 Oboe (bit 67)
    0x244, // [22] 8 Krummhorn (bit 68)
    0x245, // [23] Tremulant (bit 69)
    0x246, // [24] Sw Sub (bit 70)
    0x247, // [25] Sw UO (bit 71)
    0x27F, // [26] Sw Super (bit 127)
    0x27D, // [27] 8 Bourdon (bit 125)
    0x27E, // [28] 4 Principal (bit 126)
    0x263, // [29] III Mixture (bit 99)
    0x264, // [30] 8 Trumpet (bit 100)
    0x27A, // [31] 16 Quintadena (bit 122)
    0x277, // [32] 8 Principal (bit 119)
    0x276, // [33] 8 Rohrfloete (bit 118)
    0x275, // [34] 8 Erzahler (bit 117)
    0x274, // [35] 4 Octave (bit 116)
    0x273, // [36] 4 Blockfloete (bit 115)
    0x272, // [37] 2 2/3 Nazard (bit 114)
    0x26F, // [38] 2 Fifteenth (bit 111)
    0x26E, // [39] 1 3/5 Tierce (bit 110)
    0x26D, // [40] IV Mixture (bit 109)
    0x26C, // [41] 8 Trumpet (bit 108)
    0x26B, // [42] Chimes (bit 107)
    0x26A, // [43] Great Sub (bit 106)
    0x267, // [44] Great UO (bit 103)
    0x266, // [45] Great Super (bit 102)
    0x265, // [46] Sw/Gt 16 (bit 101)
    0x27C, // [47] Sw/Gt 8 (bit 124)
    0x27B  // [48] Sw/Gt 4 (bit 123)
};

// SAM ON coil output (CWB address) - chain 1 output
const uint16_t stopOnCoilAddr[MAX_STOPS] = {
    0x17F, // [ 0] 16 Subbass (bit 127)
    0x17D, // [ 1] 16 Quintadena (bit 125)
    0x17B, // [ 2] 8 Principal (bit 123)
    0x179, // [ 3] 8 Bassfloete (bit 121)
    0x16F, // [ 4] 4 Choralbass (bit 111)
    0x16D, // [ 5] III Mixture (bit 109)
    0x148, // [ 6] 16 Fagot (bit 72)
    0x169, // [ 7] 8 Fagot (bit 105)
    0x177, // [ 8] 4 Fagot (bit 119)
    0x175, // [ 9] Gt/Ped 8 (bit 117)
    0x159, // [10] Gt/Ped 4 (bit 89)
    0x171, // [11] Sw/Ped 8 (bit 113)
    0x167, // [12] Sw/Ped 4 (bit 103)
    0x141, // [13] 8 Gedeckt (bit 65)
    0x163, // [14] 8 Viola (bit 99)
    0x161, // [15] 8 Viola Celest (bit 97)
    0x15F, // [16] 4 Principal (bit 95)
    0x15D, // [17] 4 Spitzfloete (bit 93)
    0x15B, // [18] 2 Flachfloete (bit 91)
    0x155, // [19] 1 1/3 Quint (bit 85)
    0x153, // [20] III Scharf (bit 83)
    0x151, // [21] 8 Oboe (bit 81)
    0x14F, // [22] 8 Krummhorn (bit 79)
    0x14D, // [23] Tremulant (bit 77)
    0x14B, // [24] Sw Sub (bit 75)
    0x147, // [25] Sw UO (bit 71)
    0x145, // [26] Sw Super (bit 69)
    0x118, // [27] 8 Bourdon (bit 24)
    0x138, // [28] 4 Principal (bit 56)
    0x108, // [29] III Mixture (bit 8)
    0x105, // [30] 8 Trumpet (bit 5)
    0x101, // [31] 16 Quintadena (bit 1)
    0x13A, // [32] 8 Principal (bit 58)
    0x13B, // [33] 8 Rohrfloete (bit 59)
    0x133, // [34] 8 Erzahler (bit 51)
    0x127, // [35] 4 Octave (bit 39)
    0x125, // [36] 4 Blockfloete (bit 37)
    0x121, // [37] 2 2/3 Nazard (bit 33)
    0x11F, // [38] 2 Fifteenth (bit 31)
    0x137, // [39] 1 3/5 Tierce (bit 55)
    0x11B, // [40] IV Mixture (bit 27)
    0x117, // [41] 8 Trumpet (bit 23)
    0x115, // [42] Chimes (bit 21)
    0x113, // [43] Great Sub (bit 19)
    0x10F, // [44] Great UO (bit 15)
    0x10D, // [45] Great Super (bit 13)
    0x10B, // [46] Sw/Gt 16 (bit 11)
    0x12F, // [47] Sw/Gt 8 (bit 47)
    0x12D  // [48] Sw/Gt 4 (bit 45)
};

// SAM OFF coil output (CWB address) - chain 1 output
const uint16_t stopOffCoilAddr[MAX_STOPS] = {
    0x17E, // [ 0] 16 Subbass (bit 126)
    0x17C, // [ 1] 16 Quintadena (bit 124)
    0x17A, // [ 2] 8 Principal (bit 122)
    0x178, // [ 3] 8 Bassfloete (bit 120)
    0x16E, // [ 4] 4 Choralbass (bit 110)
    0x16C, // [ 5] III Mixture (bit 108)
    0x16A, // [ 6] 16 Fagot (bit 106)
    0x168, // [ 7] 8 Fagot (bit 104)
    0x176, // [ 8] 4 Fagot (bit 118)
    0x174, // [ 9] Gt/Ped 8 (bit 116)
    0x158, // [10] Gt/Ped 4 (bit 88)
    0x170, // [11] Sw/Ped 8 (bit 112)
    0x166, // [12] Sw/Ped 4 (bit 102)
    0x140, // [13] 8 Gedeckt (bit 64)
    0x162, // [14] 8 Viola (bit 98)
    0x160, // [15] 8 Viola Celest (bit 96)
    0x15E, // [16] 4 Principal (bit 94)
    0x15C, // [17] 4 Spitzfloete (bit 92)
    0x15A, // [18] 2 Flachfloete (bit 90)
    0x154, // [19] 1 1/3 Quint (bit 84)
    0x152, // [20] III Scharf (bit 82)
    0x150, // [21] 8 Oboe (bit 80)
    0x14E, // [22] 8 Krummhorn (bit 78)
    0x14C, // [23] Tremulant (bit 76)
    0x14A, // [24] Sw Sub (bit 74)
    0x146, // [25] Sw UO (bit 70)
    0x149, // [26] Sw Super (bit 73)
    0x100, // [27] 8 Bourdon (bit 0)
    0x139, // [28] 4 Principal (bit 57)
    0x106, // [29] III Mixture (bit 6)
    0x104, // [30] 8 Trumpet (bit 4)
    0x12A, // [31] 16 Quintadena (bit 42)
    0x136, // [32] 8 Principal (bit 54)
    0x134, // [33] 8 Rohrfloete (bit 52)
    0x132, // [34] 8 Erzahler (bit 50)
    0x120, // [35] 4 Octave (bit 32)
    0x123, // [36] 4 Blockfloete (bit 35)
    0x122, // [37] 2 2/3 Nazard (bit 34)
    0x11E, // [38] 2 Fifteenth (bit 30)
    0x11C, // [39] 1 3/5 Tierce (bit 28)
    0x11A, // [40] IV Mixture (bit 26)
    0x116, // [41] 8 Trumpet (bit 22)
    0x114, // [42] Chimes (bit 20)
    0x112, // [43] Great Sub (bit 18)
    0x109, // [44] Great UO (bit 9)
    0x10C, // [45] Great Super (bit 12)
    0x10A, // [46] Sw/Gt 16 (bit 10)
    0x12E, // [47] Sw/Gt 8 (bit 46)
    0x12C  // [48] Sw/Gt 4 (bit 44)
};

// Light output (ADDR_DISABLED for all SAM stops - no separate indicators)
const uint16_t stopLightAddr[MAX_STOPS] = {
    ADDR_DISABLED, ADDR_DISABLED, ADDR_DISABLED, ADDR_DISABLED,
    ADDR_DISABLED, ADDR_DISABLED, ADDR_DISABLED, ADDR_DISABLED,
    ADDR_DISABLED, ADDR_DISABLED, ADDR_DISABLED, ADDR_DISABLED,
    ADDR_DISABLED, ADDR_DISABLED, ADDR_DISABLED, ADDR_DISABLED,
    ADDR_DISABLED, ADDR_DISABLED, ADDR_DISABLED, ADDR_DISABLED,
    ADDR_DISABLED, ADDR_DISABLED, ADDR_DISABLED, ADDR_DISABLED,
    ADDR_DISABLED, ADDR_DISABLED, ADDR_DISABLED, ADDR_DISABLED,
    ADDR_DISABLED, ADDR_DISABLED, ADDR_DISABLED, ADDR_DISABLED,
    ADDR_DISABLED, ADDR_DISABLED, ADDR_DISABLED, ADDR_DISABLED,
    ADDR_DISABLED, ADDR_DISABLED, ADDR_DISABLED, ADDR_DISABLED,
    ADDR_DISABLED, ADDR_DISABLED, ADDR_DISABLED, ADDR_DISABLED,
    ADDR_DISABLED, ADDR_DISABLED, ADDR_DISABLED, ADDR_DISABLED,
    ADDR_DISABLED
};

// Per-stop SAM pulse time override (0 = use default SAM_PULSE_MS)
const uint16_t stopPulseMs[MAX_STOPS] = { 0 };

// ============================================================
// Expression Configuration
// ============================================================
// Two types:
//   EXPR_ANALOG:   Reads analog pin, CC = raw >> 3 (0-127)
//   EXPR_DISCRETE: Counts HIGH inputs in CWB range, CC = count of HIGHs
//
// Both types send all intermediate CC values when value changes.

constexpr uint8_t NUM_EXPRESSIONS = 2;  // Example: 2 analog + 1 discrete

// Type: EXPR_ANALOG or EXPR_DISCRETE
const uint8_t exprType[MAX_EXPRESSIONS] = { EXPR_DISCRETE , EXPR_DISCRETE };

// Common: MIDI CC number, channel, deadband
const uint8_t exprMidiCC[MAX_EXPRESSIONS]      = { 11, 12};
const uint8_t exprMidiChannel[MAX_EXPRESSIONS]  = { MIDI_CH_EXPRESSION, MIDI_CH_EXPRESSION };
const uint8_t exprDeadband[MAX_EXPRESSIONS]     = { 0, 0 };  // 0 deadband for discrete (every change matters)

// Analog-only: pin (ignored for discrete)
const uint8_t exprAnalogPin[MAX_EXPRESSIONS]    = { 43, 43 };

// Discrete-only: start and end CWB addresses (ignored for analog)
// CC value = number of HIGH inputs in [start..end] range. All on same chain.
const uint16_t exprDiscreteStart[MAX_EXPRESSIONS] = { ADDR_DISABLED, ADDR_DISABLED };  // Placeholder CWB
const uint16_t exprDiscreteEnd[MAX_EXPRESSIONS]   = { ADDR_DISABLED, ADDR_DISABLED };  // Placeholder CWB

// ============================================================
// SysEx Configuration
// ============================================================
// Hauptwerk SysEx format: F0 7D 01 <lcd#> 00 <ascii data...> F7

constexpr uint8_t HW_SYSEX_MFG_ID  = 0x7D;
constexpr uint8_t HW_SYSEX_MSG_TYPE = 0x01;

// ============================================================
// Display Line Configuration (4 lines, each from SysEx)
// ============================================================

const uint8_t displayLineLCD[4]    = { 0x05, 0x05, 0xFF, 0xFF };
const uint8_t displayLineOffset[4] = {    5,   25,    0,    0 };
const uint8_t displayLineLen[4]    = {   16,   16,    0,    0 };
const char* const displayLineLabel[4]  = { "Memory", "Crescendo", "", "" };

#endif // CONFIG_DATA_H
