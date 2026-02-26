// ScanChain.h
// Shift register chain driver for 74HC595/597 and Multidrop

#ifndef SCAN_CHAIN_H
#define SCAN_CHAIN_H

#include <Arduino.h>
#include "Config.h"

// ============================================================
// Buffers
// ============================================================

extern uint16_t inputBuffer[MAX_CHAINS][WORDS_PER_CHAIN];
extern uint16_t outputBuffer[MAX_CHAINS][WORDS_PER_CHAIN];

// ============================================================
// Initialization
// ============================================================

void scanChainInit();

// ============================================================
// Typed Scan Functions (specify chain type explicitly)
// ============================================================

void scanChainTyped(uint8_t chain, uint16_t numBits, uint8_t chainType);
void scanInputChainTyped(uint8_t chain, uint16_t numBits, uint8_t chainType);
void scanOutputChainTyped(uint8_t chain, uint16_t numBits, uint8_t chainType);

// ============================================================
// Bit Access - Direct (chain, word, bit indices)
// ============================================================

bool readInputBitDirect(uint8_t chain, uint8_t word, uint8_t bit);
void writeOutputBitDirect(uint8_t chain, uint8_t word, uint8_t bit, uint8_t value);

// ============================================================
// Buffer Management
// ============================================================

void clearOutputBuffer(uint8_t chain);
void clearAllOutputBuffers();
void clearInputBuffer(uint8_t chain);

// ============================================================
// Address Utilities (0xCWB format)
// ============================================================

inline uint16_t makeAddr(uint8_t chain, uint16_t bitIndex) {
    uint8_t word = bitIndex / 16;
    uint8_t bit = bitIndex % 16;
    return ((uint16_t)chain << 8) | (word << 4) | bit;
}

inline void parseAddr(uint16_t addr, uint8_t &chain, uint8_t &word, uint8_t &bit) {
    chain = (addr >> 8) & 0x07;
    word = (addr >> 4) & 0x0F;
    bit = addr & 0x0F;
}

inline uint16_t addrToBitIndex(uint16_t addr) {
    uint8_t word = (addr >> 4) & 0x0F;
    uint8_t bit  = addr & 0x0F;
    return word * 16 + bit;
}

#endif // SCAN_CHAIN_H
