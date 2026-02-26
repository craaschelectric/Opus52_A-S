// BusMonitor.ino
// Teensy 4.1 - Multi-drop bus state monitor
// Scans all buses in parallel, prints state array and CWB of any changed input
//
// CWB address format: 0xCWB
//   C = chain (0-7)
//   W = word  (0-F, each word is 16 bits)
//   B = bit   (0-F, bit within word)

#include <Arduino.h>

// ============================================================
// Configuration - adjust these to match your hardware
// ============================================================

#define NUM_BUSES       1       // Number of buses to scan in parallel
#define BITS_PER_BUS    128     // 256 bits per bus (16 words × 16 bits)
#define WORDS_PER_BUS   8      // 16-bit words per bus
#define FRAME_BITS      128     // Total bits clocked per frame

// Timing
#define SYNC_HIGH_US    1000    // SYNC pulse width (PIC scan time)
#define HALF_BIT_US     18       // Clock half-period (~14 µs per bit)

// Pin assignments per bus: {SYNC, CLK, MOSI, MISO}
const uint8_t busPins[NUM_BUSES][4] = {
    { 21,  20,  23,  22}   // Bus 0
};

enum { PIN_SYNC = 0, PIN_CLK = 1, PIN_MOSI = 2, PIN_MISO = 3 };

// ============================================================
// Buffers - uint16_t words to match 0xCWB addressing
// ============================================================

uint16_t inputBuffer[NUM_BUSES][WORDS_PER_BUS];
uint16_t inputBufferPrev[NUM_BUSES][WORDS_PER_BUS];
uint16_t outputBuffer[NUM_BUSES][WORDS_PER_BUS];  // tx data (zeros for read-only monitor)

// ============================================================
// Bus initialization
// ============================================================

void busInit() {
    for (int bus = 0; bus < NUM_BUSES; bus++) {
        pinMode(busPins[bus][PIN_SYNC], OUTPUT);
        pinMode(busPins[bus][PIN_CLK],  OUTPUT);
        pinMode(busPins[bus][PIN_MOSI], OUTPUT);
        pinMode(busPins[bus][PIN_MISO], INPUT_PULLUP);

        digitalWriteFast(busPins[bus][PIN_SYNC], LOW);
        digitalWriteFast(busPins[bus][PIN_CLK],  LOW);
        digitalWriteFast(busPins[bus][PIN_MOSI], LOW);
    }
    memset(inputBuffer,     0, sizeof(inputBuffer));
    memset(inputBufferPrev, 0, sizeof(inputBufferPrev));
    memset(outputBuffer,    0, sizeof(outputBuffer));
}

// ============================================================
// Scan all buses in parallel
// Clocks 256 bits, packing received data into uint16_t words
// Bit 0 of word 0 arrives first on the wire
// ============================================================

void scanAllBuses() {
    // Save previous state
    memcpy(inputBufferPrev, inputBuffer, sizeof(inputBuffer));

    // Clear rx buffers
    memset(inputBuffer, 0, sizeof(inputBuffer));

    // SYNC pulse - PICs scan their matrices during this time
    for (int b = 0; b < NUM_BUSES; b++)
        digitalWriteFast(busPins[b][PIN_SYNC], HIGH);
    delayMicroseconds(SYNC_HIGH_US);
    for (int b = 0; b < NUM_BUSES; b++)
        digitalWriteFast(busPins[b][PIN_SYNC], LOW);
    delayMicroseconds(HALF_BIT_US);

    // Clock out 256 bits per bus
    // Frame bit 0 → word 0 bit 0, frame bit 15 → word 0 bit 15
    // frame bit 16 → word 1 bit 0, etc.
    // PIC sends MSB-first per byte on the SPI shift register,
    // but we reconstruct into 16-bit words using the CWB mapping:
    //   word index = frameBit / 16
    //   bit index  = frameBit % 16
    for (int frameBit = 0; frameBit < FRAME_BITS; frameBit++) {
        int wordIdx = frameBit / 16;
        int bitIdx  = frameBit % 16;
        uint16_t bitMask = (1 << bitIdx);

        // Set MOSI on all buses (output data to peripherals)
        for (int b = 0; b < NUM_BUSES; b++) {
            if (outputBuffer[b][wordIdx] & bitMask)
                digitalWriteFast(busPins[b][PIN_MOSI], HIGH);
            else
                digitalWriteFast(busPins[b][PIN_MOSI], LOW);
        }

        // Rising edge - PICs shift data
        for (int b = 0; b < NUM_BUSES; b++)
            digitalWriteFast(busPins[b][PIN_CLK], HIGH);
        delayMicroseconds(HALF_BIT_US);

        // Sample MISO from all buses
        for (int b = 0; b < NUM_BUSES; b++) {
            if (digitalReadFast(busPins[b][PIN_MISO]))
                inputBuffer[b][wordIdx] |= bitMask;
        }

        // Falling edge - PICs update TRIS for next bit
        for (int b = 0; b < NUM_BUSES; b++)
            digitalWriteFast(busPins[b][PIN_CLK], LOW);
        delayMicroseconds(HALF_BIT_US);
    }
}

// ============================================================
// Print helpers
// ============================================================

void printHex4(uint16_t val) {
    if (val < 0x1000) Serial.print('0');
    if (val < 0x0100) Serial.print('0');
    if (val < 0x0010) Serial.print('0');
    Serial.print(val, HEX);
}

// Print full state array for one bus: "Bus N: FFFF FFFF ... (16 words)"
void printBusState(uint8_t bus) {
    Serial.print("Bus ");
    Serial.print(bus);
    Serial.print(": ");
    for (int w = 0; w < WORDS_PER_BUS; w++) {
        printHex4(inputBuffer[bus][w]);
        Serial.print(' ');
    }
    Serial.println();
}

// Print CWB address as "0xCWB"
void printCWB(uint8_t chain, uint8_t word, uint8_t bit) {
    Serial.print("0x");
    Serial.print(chain, HEX);
    Serial.print(word, HEX);
    Serial.print(bit, HEX);
}

// ============================================================
// Detect and report changes
// ============================================================

void reportChanges() {
    bool anyChange = false;

    for (int c = 0; c < NUM_BUSES; c++) {
        for (int w = 0; w < WORDS_PER_BUS; w++) {
            uint16_t changed = inputBuffer[c][w] ^ inputBufferPrev[c][w];
            if (changed == 0) continue;

            if (!anyChange) {
                anyChange = true;
                Serial.println("--- State Change ---");
                for (int b = 0; b < NUM_BUSES; b++)
                    printBusState(b);
            }

            // Report each changed bit with its CWB and new value
            for (int bit = 0; bit < 16; bit++) {
                if (changed & (1 << bit)) {
                    uint8_t newVal = (inputBuffer[c][w] >> bit) & 0x01;
                    printCWB(c, w, bit);
                    Serial.print(newVal ? " ON" : " OFF");
                    Serial.println();
                }
            }
        }
    }
}

// ============================================================
// Setup & Loop
// ============================================================

void setup() {
    Serial.begin(115200);
    while (!Serial && millis() < 3000) {}  // Wait for USB serial, max 3 sec

    busInit();

    Serial.println("Multi-drop Bus Monitor");
    Serial.print("Buses: ");
    Serial.println(NUM_BUSES);
    Serial.print("Frame time: ~");
    Serial.print(SYNC_HIGH_US + (FRAME_BITS * HALF_BIT_US * 2));
    Serial.println(" us");
    Serial.println("Waiting for changes...");
    Serial.println();

    // Do one initial scan to populate baseline state
    scanAllBuses();
}

void loop() {
    scanAllBuses();
    reportChanges();
}
