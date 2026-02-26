// ScanChain.cpp
// 74HC595/597 and Multidrop shift register chain implementation
//
// 74HC597 input chain:
//   Pins 12 (STCP) and 13 (PL) tied together -> sync must idle HIGH
//   Parallel load: sync LOW -> HIGH, then read Q before each clock
//
// 74HC595 output chain:
//   OE and RCLK tied together -> sync must idle LOW
//   Shift data in, then latch: sync LOW -> HIGH -> LOW
//
// Multidrop: SYNC HIGH->LOW, clock HIGH->LOW, read after falling edge

#include "ScanChain.h"
#include "ConfigData.h"

// ============================================================
// Buffer Allocation
// ============================================================

uint16_t inputBuffer[MAX_CHAINS][WORDS_PER_CHAIN];
uint16_t outputBuffer[MAX_CHAINS][WORDS_PER_CHAIN];

// ============================================================
// Initialization
// ============================================================

void scanChainInit() {
    for (uint8_t c = 0; c < NUM_CHAINS; c++) {
        if (chainClockPin[c] == 255) continue;

        pinMode(chainClockPin[c], OUTPUT);
        digitalWrite(chainClockPin[c], LOW);

        if (chainSyncPin[c] != 255) {
            pinMode(chainSyncPin[c], OUTPUT);
            digitalWrite(chainSyncPin[c], LOW);
        }

        if (chainDataInPin[c] != 255) {
            pinMode(chainDataInPin[c], INPUT);
        }

        if (chainDataOutPin[c] != 255) {
            pinMode(chainDataOutPin[c], OUTPUT);
            digitalWrite(chainDataOutPin[c], LOW);
        }
    }

    clearAllOutputBuffers();

    for (uint8_t c = 0; c < MAX_CHAINS; c++) {
        clearInputBuffer(c);
    }

    // Push cleared output buffers to hardware for output chains
    for (uint8_t c = 0; c < NUM_CHAINS; c++) {
        if (chainDir[c] == CHAIN_DIR_OUTPUT && chainClockPin[c] != 255) {
            scanOutputChainTyped(c, chainBitsUsed[c], chainType[c]);
        }
    }
}

// ============================================================
// Input Scan
// ============================================================

void scanInputChainTyped(uint8_t chain, uint16_t numBits, uint8_t cType) {
    if (chain >= NUM_CHAINS) return;
    if (chainClockPin[chain] == 255) return;

    uint8_t clockPin  = chainClockPin[chain];
    uint8_t syncPin   = chainSyncPin[chain];
    uint8_t dataInPin = chainDataInPin[chain];

    if (cType == CHAIN_TYPE_MULTIDROP) {
        // Multidrop: sync HIGH->LOW
        digitalWrite(syncPin, HIGH);
        delayMicroseconds(SYNC_HIGH_US);
        digitalWrite(syncPin, LOW);
        delayMicroseconds(SYNC_HOLD_US);

        for (uint16_t bitIndex = 0; bitIndex < numBits; bitIndex++) {
            uint8_t word = bitIndex / 16;
            uint8_t bitInWord = bitIndex % 16;

            delayMicroseconds(BIT_TIME_US / 2);
            digitalWrite(clockPin, HIGH);
            delayMicroseconds(BIT_TIME_US / 2);
            digitalWrite(clockPin, LOW);
            delayMicroseconds(4);

            uint8_t inVal = digitalRead(dataInPin);
            if (inVal) {
                inputBuffer[chain][word] |= (1 << bitInWord);
            } else {
                inputBuffer[chain][word] &= ~(1 << bitInWord);
            }
        }
    } else {
        // 74HC597: sync LOW -> HIGH does parallel load
        // Bit 0 is already on Q after load — read before clocking
        digitalWrite(syncPin, LOW);
        delayMicroseconds(SYNC_HIGH_US);
        digitalWrite(syncPin, HIGH);
        delayMicroseconds(SYNC_HOLD_US);

        for (uint16_t bitIndex = 0; bitIndex < numBits; bitIndex++) {
            uint8_t word = bitIndex / 16;
            uint8_t bitInWord = bitIndex % 16;

            // 1. Read Q (present from parallel load or previous clock)
            uint8_t inVal = digitalRead(dataInPin);
            if (inVal) {
                inputBuffer[chain][word] |= (1 << bitInWord);
            } else {
                inputBuffer[chain][word] &= ~(1 << bitInWord);
            }

            // 2. Clock to shift next bit
            delayMicroseconds(BIT_TIME_US / 2);
            digitalWrite(clockPin, HIGH);
            delayMicroseconds(BIT_TIME_US / 2);
            digitalWrite(clockPin, LOW);
        }
        // Sync stays HIGH — correct idle for 597 with pins 12/13 tied
    }
}

// ============================================================
// Output Scan
// ============================================================

void scanOutputChainTyped(uint8_t chain, uint16_t numBits, uint8_t cType) {
    if (chain >= NUM_CHAINS) return;
    if (chainClockPin[chain] == 255) return;

    uint8_t clockPin   = chainClockPin[chain];
    uint8_t syncPin    = chainSyncPin[chain];
    uint8_t dataOutPin = chainDataOutPin[chain];

    if (cType == CHAIN_TYPE_MULTIDROP) {
        for (uint16_t bitIndex = 0; bitIndex < numBits; bitIndex++) {
            uint8_t word = bitIndex / 16;
            uint8_t bitInWord = bitIndex % 16;

            uint8_t outVal = (outputBuffer[chain][word] >> bitInWord) & 0x01;
            digitalWrite(dataOutPin, !outVal);  // Active LOW for multidrop

            delayMicroseconds(BIT_TIME_US / 2);
            digitalWrite(clockPin, HIGH);
            delayMicroseconds(BIT_TIME_US / 2);
            digitalWrite(clockPin, LOW);
        }

        // Sync pulse to latch
        digitalWrite(syncPin, HIGH);
        delayMicroseconds(SYNC_HIGH_US);
        digitalWrite(syncPin, LOW);
    } else {
        // 74HC595: OE and RCLK tied, sync idles LOW
        for (uint16_t bitIndex = 0; bitIndex < numBits; bitIndex++) {
            uint8_t word = bitIndex / 16;
            uint8_t bitInWord = bitIndex % 16;

            uint8_t outVal = (outputBuffer[chain][word] >> bitInWord) & 0x01;
            digitalWrite(dataOutPin, outVal);

            delayMicroseconds(BIT_TIME_US / 2);
            digitalWrite(clockPin, HIGH);
            delayMicroseconds(BIT_TIME_US / 2);
            digitalWrite(clockPin, LOW);
        }

        // Latch: LOW->HIGH->LOW (OE tied to RCLK, idle LOW)
        digitalWrite(syncPin, LOW);
        delayMicroseconds(SYNC_HOLD_US);
        digitalWrite(syncPin, HIGH);
        delayMicroseconds(SYNC_HIGH_US);
        digitalWrite(syncPin, LOW);
    }
}

// ============================================================
// Bidirectional Scan (multidrop only)
// ============================================================

void scanChainTyped(uint8_t chain, uint16_t numBits, uint8_t cType) {
    if (chain >= NUM_CHAINS) return;
    if (chainClockPin[chain] == 255) return;
    if (cType != CHAIN_TYPE_MULTIDROP) return;

    uint8_t clockPin   = chainClockPin[chain];
    uint8_t syncPin    = chainSyncPin[chain];
    uint8_t dataInPin  = chainDataInPin[chain];
    uint8_t dataOutPin = chainDataOutPin[chain];

    digitalWrite(syncPin, HIGH);
    delayMicroseconds(SYNC_HIGH_US);
    digitalWrite(syncPin, LOW);
    delayMicroseconds(SYNC_HOLD_US);

    for (uint16_t bitIndex = 0; bitIndex < numBits; bitIndex++) {
        uint8_t word = bitIndex / 16;
        uint8_t bitInWord = bitIndex % 16;

        uint8_t outVal = (outputBuffer[chain][word] >> bitInWord) & 0x01;
        digitalWrite(dataOutPin, !outVal);

        delayMicroseconds(BIT_TIME_US / 2);
        digitalWrite(clockPin, HIGH);
        delayMicroseconds(BIT_TIME_US / 2);
        digitalWrite(clockPin, LOW);
        delayMicroseconds(4);

        uint8_t inVal = digitalRead(dataInPin);
        if (inVal) {
            inputBuffer[chain][word] |= (1 << bitInWord);
        } else {
            inputBuffer[chain][word] &= ~(1 << bitInWord);
        }
    }
}

// ============================================================
// Bit Access Functions
// ============================================================

bool readInputBitDirect(uint8_t chain, uint8_t word, uint8_t bit) {
    if (chain >= MAX_CHAINS) return false;
    return (inputBuffer[chain][word] >> bit) & 0x01;
}

void writeOutputBitDirect(uint8_t chain, uint8_t word, uint8_t bit, uint8_t value) {
    if (chain >= MAX_CHAINS) return;
    if (value) {
        outputBuffer[chain][word] |= (1 << bit);
    } else {
        outputBuffer[chain][word] &= ~(1 << bit);
    }
}

// ============================================================
// Buffer Management
// ============================================================

void clearOutputBuffer(uint8_t chain) {
    if (chain >= MAX_CHAINS) return;
    memset(outputBuffer[chain], 0, sizeof(outputBuffer[chain]));
}

void clearAllOutputBuffers() {
    memset(outputBuffer, 0, sizeof(outputBuffer));
}

void clearInputBuffer(uint8_t chain) {
    if (chain >= MAX_CHAINS) return;
    memset(inputBuffer[chain], 0, sizeof(inputBuffer[chain]));
}
