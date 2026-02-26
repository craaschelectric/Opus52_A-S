// ScanChain.cpp
// 74HC596/597 and Multidrop shift register chain implementation
//
// No bidirectional 597 chains — input and output are separate chains.
//
// 74HC597 input chain:
//   Pins 12 (STCP) and 13 (PL) tied together → sync must idle HIGH
//   Parallel load: sync LOW -> HIGH, then read Q before each clock
//
// 74HC595 output chain:
//   OE and RCLK tied together → sync must idle LOW
//   Shift data in, then latch: sync LOW -> HIGH -> LOW
//
// Multidrop: SYNC HIGH->LOW, clock HIGH->LOW, read after falling edge

#include "ScanChain.h"

// ============================================================
// Buffer Allocation
// ============================================================

uint16_t inputBuffer[MAX_CHAINS][WORDS_PER_CHAIN];
uint16_t outputBuffer[MAX_CHAINS][WORDS_PER_CHAIN];

// ============================================================
// Initialization
// ============================================================

void scanChainInit() {
    for (uint8_t c = 0; c < NUMBER_OF_CHAINS; c++) {
        if (CHAIN_CLOCK_PIN[c] == 255) continue;
        
        pinMode(CHAIN_CLOCK_PIN[c], OUTPUT);
        pinMode(CHAIN_SYNC_PIN[c], OUTPUT);
        pinMode(CHAIN_DATA_IN_PIN[c], INPUT);
        pinMode(CHAIN_DATA_OUT_PIN[c], OUTPUT);
        
        digitalWrite(CHAIN_CLOCK_PIN[c], LOW);
        digitalWrite(CHAIN_DATA_OUT_PIN[c], LOW);
        
        // Sync idle state set LOW for all chains at init.
        // scanInputChainTyped will set it HIGH for 597 input chains.
        // scanOutputChainTyped keeps it LOW for 595 output chains.
        digitalWrite(CHAIN_SYNC_PIN[c], LOW);
    }
    
    clearAllOutputBuffers();
    
    for (uint8_t c = 0; c < MAX_CHAINS; c++) {
        clearInputBuffer(c);
    }
    
    // Push cleared output buffers to hardware
    for (uint8_t c = 0; c < NUMBER_OF_CHAINS; c++) {
        if (CHAIN_CLOCK_PIN[c] != 255) {
            scanOutputChainTyped(c, MAX_BITS_PER_CHAIN, CHAIN_TYPE[c]);
        }
    }
}

// ============================================================
// Input Scan
// ============================================================

void scanInputChainTyped(uint8_t chain, uint16_t numBits, uint8_t chainType) {
    if (chain >= NUMBER_OF_CHAINS) return;
    if (CHAIN_CLOCK_PIN[chain] == 255) return;
    
    uint8_t clockPin = CHAIN_CLOCK_PIN[chain];
    uint8_t syncPin = CHAIN_SYNC_PIN[chain];
    uint8_t dataInPin = CHAIN_DATA_IN_PIN[chain];
    
    if (chainType == CHAIN_TYPE_MULTIDROP) {
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
        // 74HC597: pins 12 (STCP) and 13 (PL) tied together
        // Sync must be HIGH during clocking (PL HIGH = serial shift mode)
        // Parallel load: pulse sync LOW then back HIGH
        digitalWrite(syncPin, LOW);
        delayMicroseconds(SYNC_HIGH_US);
        digitalWrite(syncPin, HIGH);
        delayMicroseconds(SYNC_HOLD_US);
        
        // Bit 0 is already on Q after parallel load — read before clocking
        for (uint16_t bitIndex = 0; bitIndex < numBits; bitIndex++) {
            uint8_t word = bitIndex / 16;
            uint8_t bitInWord = bitIndex % 16;
            
            // 1. Read Q (present from parallel load or previous clock edge)
            uint8_t inVal = digitalRead(dataInPin);
            if (inVal) {
                inputBuffer[chain][word] |= (1 << bitInWord);
            } else {
                inputBuffer[chain][word] &= ~(1 << bitInWord);
            }
            
            // 2. Clock HIGH (shifts to next bit)
            delayMicroseconds(BIT_TIME_US / 2);
            digitalWrite(clockPin, HIGH);
            
            // 3. Clock LOW
            delayMicroseconds(BIT_TIME_US / 2);
            digitalWrite(clockPin, LOW);
        }
        // Sync stays HIGH — correct idle state for 597 with pins 12/13 tied
    }
}

// ============================================================
// Output Scan
// ============================================================

void scanOutputChainTyped(uint8_t chain, uint16_t numBits, uint8_t chainType) {
    if (chain >= NUMBER_OF_CHAINS) return;
    if (CHAIN_CLOCK_PIN[chain] == 255) return;
    
    uint8_t clockPin = CHAIN_CLOCK_PIN[chain];
    uint8_t syncPin = CHAIN_SYNC_PIN[chain];
    uint8_t dataOutPin = CHAIN_DATA_OUT_PIN[chain];
    
    if (chainType == CHAIN_TYPE_MULTIDROP) {
        for (uint16_t bitIndex = 0; bitIndex < numBits; bitIndex++) {
            uint8_t word = bitIndex / 16;
            uint8_t bitInWord = bitIndex % 16;
            
            uint8_t outVal = (outputBuffer[chain][word] >> bitInWord) & 0x01;
            digitalWrite(dataOutPin, !outVal);  // Active LOW
            
            delayMicroseconds(BIT_TIME_US / 2);
            digitalWrite(clockPin, HIGH);
            delayMicroseconds(BIT_TIME_US / 2);
            digitalWrite(clockPin, LOW);
        }
        
        // Sync pulse to latch outputs
        digitalWrite(syncPin, HIGH);
        delayMicroseconds(SYNC_HIGH_US);
        digitalWrite(syncPin, LOW);
    } else {
        // 74HC595: OE and RCLK tied, sync idles LOW (outputs disabled)
        // Shift all data in first
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
        
        // Latch outputs: LOW->HIGH->LOW (OE tied to RCLK, idle LOW)
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

void scanChainTyped(uint8_t chain, uint16_t numBits, uint8_t chainType) {
    if (chain >= NUMBER_OF_CHAINS) return;
    if (CHAIN_CLOCK_PIN[chain] == 255) return;
    
    // Bidirectional only supported for multidrop
    if (chainType != CHAIN_TYPE_MULTIDROP) return;
    
    uint8_t clockPin = CHAIN_CLOCK_PIN[chain];
    uint8_t syncPin = CHAIN_SYNC_PIN[chain];
    uint8_t dataInPin = CHAIN_DATA_IN_PIN[chain];
    uint8_t dataOutPin = CHAIN_DATA_OUT_PIN[chain];
    
    // Multidrop: sync HIGH->LOW to start
    digitalWrite(syncPin, HIGH);
    delayMicroseconds(SYNC_HIGH_US);
    digitalWrite(syncPin, LOW);
    delayMicroseconds(SYNC_HOLD_US);
    
    for (uint16_t bitIndex = 0; bitIndex < numBits; bitIndex++) {
        uint8_t word = bitIndex / 16;
        uint8_t bitInWord = bitIndex % 16;
        
        // Set output data (active LOW for multidrop)
        uint8_t outVal = (outputBuffer[chain][word] >> bitInWord) & 0x01;
        digitalWrite(dataOutPin, !outVal);
        
        delayMicroseconds(BIT_TIME_US / 2);
        digitalWrite(clockPin, HIGH);
        delayMicroseconds(BIT_TIME_US / 2);
        digitalWrite(clockPin, LOW);
        delayMicroseconds(4);
        
        // Read input after falling edge
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
