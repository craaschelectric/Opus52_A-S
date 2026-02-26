// ScanChain.cpp
// Low-level scan chain I/O driver

#include "ScanChain.h"

// ============================================================
// Buffers
// ============================================================

uint16_t inputBuffer[MAX_CHAINS][WORDS_PER_CHAIN];
uint16_t inputBufferPrev[MAX_CHAINS][WORDS_PER_CHAIN];
uint16_t outputBuffer[MAX_CHAINS][WORDS_PER_CHAIN];
uint16_t outputBufferPrev[MAX_CHAINS][WORDS_PER_CHAIN];

// ============================================================
// Initialization
// ============================================================

void scanInit() {
    memset(inputBuffer, 0, sizeof(inputBuffer));
    memset(inputBufferPrev, 0, sizeof(inputBufferPrev));
    memset(outputBuffer, 0, sizeof(outputBuffer));
    memset(outputBufferPrev, 0xFF, sizeof(outputBufferPrev));  // Force first scan to see a change

    for (uint8_t c = 0; c < NUM_CHAINS; c++) {
        pinMode(chainClockPin[c], OUTPUT);
        pinMode(chainSyncPin[c], OUTPUT);
        
        if (chainDir[c] == CHAIN_DIR_INPUT) {
            pinMode(chainDataInPin[c], INPUT);
        } else {
            pinMode(chainDataOutPin[c], OUTPUT);
        }
        
        if (chainType[c] == CHAIN_TYPE_MULTIDROP) {
            digitalWrite(chainSyncPin[c], LOW);
        } else if (chainDir[c] == CHAIN_DIR_OUTPUT) {
            digitalWrite(chainSyncPin[c], LOW);   // 595: RCLK+/OE idle LOW (outputs enabled)
        } else {
            digitalWrite(chainSyncPin[c], HIGH);   // 597: idle HIGH
        }
        
        digitalWrite(chainClockPin[c], LOW);
    }
}

// ============================================================
// Check if any output chain has changed
// ============================================================

static bool outputChanged() {
    for (uint8_t c = 0; c < NUM_CHAINS; c++) {
        if (chainDir[c] != CHAIN_DIR_OUTPUT) continue;
        for (uint8_t w = 0; w < WORDS_PER_CHAIN; w++) {
            if (outputBuffer[c][w] != outputBufferPrev[c][w]) return true;
        }
    }
    return false;
}

// ============================================================
// Debug: log non-zero output buffer contents
// ============================================================

static void debugLogOutputBuffer() {
#if DEBUG_ENABLED
    for (uint8_t c = 0; c < NUM_CHAINS; c++) {
        if (chainDir[c] != CHAIN_DIR_OUTPUT) continue;
        for (uint8_t w = 0; w < WORDS_PER_CHAIN; w++) {
            if (outputBuffer[c][w] != 0) {
                Serial.print("DBG: OutBuf[");
                Serial.print(c);
                Serial.print("][");
                Serial.print(w);
                Serial.print("]=0x");
                Serial.println(outputBuffer[c][w], HEX);
            }
        }
    }
#endif
}

// ============================================================
// Scan Input Chains (597 + multidrop)
// ============================================================

static void scanInputChains() {
    uint16_t maxBits = 0;
    for (uint8_t c = 0; c < NUM_CHAINS; c++) {
        if (chainDir[c] != CHAIN_DIR_INPUT) continue;
        if (chainBitsUsed[c] > maxBits) maxBits = chainBitsUsed[c];
    }
    if (maxBits == 0) return;

    // Sync pulse: assert (597: LOW to load, multidrop: HIGH to latch)
    for (uint8_t c = 0; c < NUM_CHAINS; c++) {
        if (chainDir[c] != CHAIN_DIR_INPUT) continue;
        if (chainType[c] == CHAIN_TYPE_MULTIDROP)
            digitalWrite(chainSyncPin[c], HIGH);
        else
            digitalWrite(chainSyncPin[c], LOW);
    }
    delayMicroseconds(SYNC_PULSE_US);

    // Sync pulse: de-assert
    for (uint8_t c = 0; c < NUM_CHAINS; c++) {
        if (chainDir[c] != CHAIN_DIR_INPUT) continue;
        if (chainType[c] == CHAIN_TYPE_MULTIDROP)
            digitalWrite(chainSyncPin[c], LOW);
        else
            digitalWrite(chainSyncPin[c], HIGH);
    }
    delayMicroseconds(SYNC_SETTLE_US);

    // Clock through all bits
    for (uint16_t bitIdx = 0; bitIdx < maxBits; bitIdx++) {
        uint8_t word = bitIdx / 16;
        uint8_t bit  = bitIdx % 16;

        // 74HC597: Read Q before clocking (data present after parallel load)
        for (uint8_t c = 0; c < NUM_CHAINS; c++) {
            if (bitIdx >= chainBitsUsed[c]) continue;
            if (chainDir[c] != CHAIN_DIR_INPUT) continue;
            if (chainType[c] != CHAIN_TYPE_SHIFTREG) continue;
            bool inVal = digitalReadFast(chainDataInPin[c]);
            if (inVal)
                inputBuffer[c][word] |= (1 << bit);
            else
                inputBuffer[c][word] &= ~(1 << bit);
        }

        delayMicroseconds(BIT_TIME_US);

        // Clock HIGH
        for (uint8_t c = 0; c < NUM_CHAINS; c++) {
            if (bitIdx >= chainBitsUsed[c]) continue;
            if (chainDir[c] != CHAIN_DIR_INPUT) continue;
            digitalWriteFast(chainClockPin[c], HIGH);
        }

        delayMicroseconds(BIT_TIME_US);

        // Clock LOW
        for (uint8_t c = 0; c < NUM_CHAINS; c++) {
            if (bitIdx >= chainBitsUsed[c]) continue;
            if (chainDir[c] != CHAIN_DIR_INPUT) continue;
            digitalWriteFast(chainClockPin[c], LOW);
        }

        delayMicroseconds(BIT_TIME_US);

        // Multidrop: Read input data (valid after falling edge)
        for (uint8_t c = 0; c < NUM_CHAINS; c++) {
            if (bitIdx >= chainBitsUsed[c]) continue;
            if (chainDir[c] != CHAIN_DIR_INPUT) continue;
            if (chainType[c] != CHAIN_TYPE_MULTIDROP) continue;
            bool inVal = digitalReadFast(chainDataInPin[c]);
            if (inVal)
                inputBuffer[c][word] |= (1 << bit);
            else
                inputBuffer[c][word] &= ~(1 << bit);
        }
    }
}

// ============================================================
// Shift Out Output Chains (595 only, when changed)
// ============================================================

static void scanOutputChains() {
    if (!outputChanged()) return;

    debugLogOutputBuffer();

    uint16_t maxBits = 0;
    for (uint8_t c = 0; c < NUM_CHAINS; c++) {
        if (chainDir[c] != CHAIN_DIR_OUTPUT) continue;
        if (chainBitsUsed[c] > maxBits) maxBits = chainBitsUsed[c];
    }
    if (maxBits == 0) return;

    // Shift in all bits
    for (uint16_t bitIdx = 0; bitIdx < maxBits; bitIdx++) {
        uint8_t word = bitIdx / 16;
        uint8_t bit  = bitIdx % 16;

        // Set DS data before clock rise
        for (uint8_t c = 0; c < NUM_CHAINS; c++) {
            if (bitIdx >= chainBitsUsed[c]) continue;
            if (chainDir[c] != CHAIN_DIR_OUTPUT) continue;
            bool outVal = (outputBuffer[c][word] >> bit) & 1;
            digitalWrite(chainDataOutPin[c], outVal);
        }

        delayMicroseconds(BIT_TIME_US);

        // Clock HIGH - shifts data in
        for (uint8_t c = 0; c < NUM_CHAINS; c++) {
            if (bitIdx >= chainBitsUsed[c]) continue;
            if (chainDir[c] != CHAIN_DIR_OUTPUT) continue;
            digitalWriteFast(chainClockPin[c], HIGH);
        }

        delayMicroseconds(BIT_TIME_US);

        // Clock LOW
        for (uint8_t c = 0; c < NUM_CHAINS; c++) {
            if (bitIdx >= chainBitsUsed[c]) continue;
            if (chainDir[c] != CHAIN_DIR_OUTPUT) continue;
            digitalWriteFast(chainClockPin[c], LOW);
        }

        delayMicroseconds(BIT_TIME_US);
    }

    // Latch: pulse RCLK HIGH then LOW (idles LOW since /OE is tied to RCLK)
    for (uint8_t c = 0; c < NUM_CHAINS; c++) {
        if (chainDir[c] != CHAIN_DIR_OUTPUT) continue;
        digitalWrite(chainSyncPin[c], HIGH);
    }
    delayMicroseconds(SYNC_PULSE_US);
    for (uint8_t c = 0; c < NUM_CHAINS; c++) {
        if (chainDir[c] != CHAIN_DIR_OUTPUT) continue;
        digitalWrite(chainSyncPin[c], LOW);
    }
    delayMicroseconds(SYNC_SETTLE_US);

    // Save output state for change detection
    for (uint8_t c = 0; c < NUM_CHAINS; c++) {
        if (chainDir[c] != CHAIN_DIR_OUTPUT) continue;
        memcpy(outputBufferPrev[c], outputBuffer[c], sizeof(outputBuffer[c]));
    }
}

// ============================================================
// Core Scan - All Chains
// ============================================================
//
// Input chains (597 + multidrop) scan every cycle.
// Output chains (595) only shift and latch when outputBuffer has changed.

void scanAllChains() {
    scanInputChains();

    // Apply inversion mask to input chains
    for (uint8_t c = 0; c < NUM_CHAINS; c++) {
        if (chainDir[c] != CHAIN_DIR_INPUT) continue;
        uint8_t words = (chainBitsUsed[c] + 15) / 16;
        for (uint8_t w = 0; w < words; w++) {
            inputBuffer[c][w] ^= inputInvertMask[c][w];
        }
    }

    scanOutputChains();
}

// ============================================================
// Buffer Management
// ============================================================

void saveInputState() {
    memcpy(inputBufferPrev, inputBuffer, sizeof(inputBuffer));
}
