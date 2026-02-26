
// WalkingHigh.ino
// Walks a single HIGH through the 128-element output chain (chain 1)
// with 500ms per step. After each shift, reads and displays
// all 64 inputs from the input chain (chain 0).
//
// Hardware: Teensy 4.1 with 74HC595/597 shift register chains
// Chain 0: Input  (597) - 64 bits  - pins: dataIn=1, dataOut=0, sync=2,  clock=3
// Chain 1: Output (595) - 128 bits - pins: dataIn=6, dataOut=5, sync=10, clock=11

#include <Arduino.h>

// ============================================================
// Pin Configuration
// ============================================================

// Input chain (chain 0) - 597 input side
constexpr uint8_t IN_DATA_IN   = 35;
constexpr uint8_t IN_DATA_OUT  = 14;   // 595 output on same chain (unused here)
constexpr uint8_t IN_SYNC      = 34;
constexpr uint8_t IN_CLOCK     = 33;
constexpr uint16_t IN_NUM_BITS =128;

// Output chain (chain 1) - 595 output side
constexpr uint8_t OUT_DATA_IN  = 23;   // 597 input on same chain (unused here)
constexpr uint8_t OUT_DATA_OUT = 22;
constexpr uint8_t OUT_SYNC     = 21;
constexpr uint8_t OUT_CLOCK    = 0;
constexpr uint16_t OUT_NUM_BITS = 128;

// Power supply enable
constexpr uint8_t POWER_EN_PIN = 17;
constexpr uint8_t PERIPH_EN_PIN = 1;


// Walk range (inclusive) — set these to walk a subset of the output chain
constexpr uint16_t WALK_START_BIT = 0;
constexpr uint16_t WALK_END_BIT   = 128;

// Timing
constexpr uint32_t BIT_TIME_US  = 10;
constexpr uint32_t SYNC_HIGH_US = 10;
constexpr uint32_t SYNC_HOLD_US = 10;
constexpr uint32_t STEP_MS      = 500;

// ============================================================
// Buffers
// ============================================================

constexpr uint16_t IN_WORDS  = (IN_NUM_BITS + 15) / 16;   // 4
constexpr uint16_t OUT_WORDS = (OUT_NUM_BITS + 15) / 16;   // 8

uint16_t inputBuffer[IN_WORDS];
uint16_t inputBufferPrev[IN_WORDS];
uint16_t outputBuffer[OUT_WORDS];

// ============================================================
// Scan Functions
// ============================================================

// Read all 64 input bits from chain 0 (597)
// 597 timing: SYNC LOW loads parallel data, SYNC HIGH latches.
// After sync, bit 0 is already on Q — read before first clock.
void scanInputChain() {
    // Clear buffer
    for (uint16_t w = 0; w < IN_WORDS; w++) {
        inputBuffer[w] = 0;
    }

    // Parallel load: SYNC LOW -> HIGH
    digitalWrite(IN_SYNC, LOW);
    delayMicroseconds(SYNC_HIGH_US);
    digitalWrite(IN_SYNC, HIGH);
    delayMicroseconds(SYNC_HOLD_US);

    for (uint16_t bitIndex = 0; bitIndex < IN_NUM_BITS; bitIndex++) {
        uint16_t word = bitIndex / 16;
        uint16_t bitInWord = bitIndex % 16;

        // 1. Read Q (bit 0 already present from parallel load, subsequent bits from previous clock)
        if (digitalRead(IN_DATA_IN)) {
            inputBuffer[word] |= (1 << bitInWord);
        }

        // 2. Clock HIGH (shifts 597 to next bit)
        delayMicroseconds(BIT_TIME_US / 2);
        digitalWrite(IN_CLOCK, HIGH);

        // 3. Clock LOW
        delayMicroseconds(BIT_TIME_US / 2);
        digitalWrite(IN_CLOCK, LOW);
    }
}

// Write all 128 output bits to chain 1 (595)
// 595 timing: shift data in on rising clock edge, then latch with SYNC pulse.
void scanOutputChain() {
    for (uint16_t bitIndex = 0; bitIndex < OUT_NUM_BITS; bitIndex++) {
        uint16_t word = bitIndex / 16;
        uint16_t bitInWord = bitIndex % 16;

        // Set data on DS
        uint8_t outVal = (outputBuffer[word] >> bitInWord) & 0x01;
        digitalWrite(OUT_DATA_OUT, outVal);

        // Clock HIGH (595 captures DS on rising edge)
        delayMicroseconds(BIT_TIME_US / 2);
        digitalWrite(OUT_CLOCK, HIGH);

        // Clock LOW
        delayMicroseconds(BIT_TIME_US / 2);
        digitalWrite(OUT_CLOCK, LOW);
    }

    // Latch: LOW -> HIGH transfers shift register to output latches
    // Then back LOW to enable outputs (OE is tied to RCLK)
    digitalWrite(OUT_SYNC, LOW);
    delayMicroseconds(SYNC_HIGH_US);
    digitalWrite(OUT_SYNC, HIGH);
    delayMicroseconds(SYNC_HOLD_US);
    digitalWrite(OUT_SYNC, LOW);
}

// ============================================================
// Display Functions
// ============================================================

void printInputState() {
    Serial.print("  Inputs [");
    Serial.print(IN_NUM_BITS - 1);
    Serial.print("..0]: ");

    // Print from MSB to LSB for natural left-to-right reading
    for (int16_t bitIndex = IN_NUM_BITS - 1; bitIndex >= 0; bitIndex--) {
        uint16_t word = bitIndex / 16;
        uint16_t bitInWord = bitIndex % 16;

        Serial.print((inputBuffer[word] >> bitInWord) & 0x01);

        // Group separator every 8 bits for readability
        if (bitIndex > 0 && (bitIndex % 8) == 0) {
            Serial.print(' ');
        }
    }
    Serial.println();
}

void printChangedBits() {
    bool anyChanged = false;
    for (uint16_t bitIndex = 0; bitIndex < IN_NUM_BITS; bitIndex++) {
        uint16_t word = bitIndex / 16;
        uint16_t bitInWord = bitIndex % 16;
        uint8_t curr = (inputBuffer[word] >> bitInWord) & 0x01;
        uint8_t prev = (inputBufferPrev[word] >> bitInWord) & 0x01;
        if (curr != prev) {
            if (anyChanged) Serial.print(", ");
            Serial.print(bitIndex);
            Serial.print(curr ? "->ON" : "->OFF");
            anyChanged = true;
        }
    }
    if (anyChanged) {
        Serial.println();
    } else {
        Serial.println("  (no change)");
    }
}

// Save current input buffer as previous for next comparison
void saveInputState() {
    for (uint16_t w = 0; w < IN_WORDS; w++) {
        inputBufferPrev[w] = inputBuffer[w];
    }
}

// ============================================================
// Setup & Loop
// ============================================================

void setup() {
    // Power supply enable
    pinMode(POWER_EN_PIN, OUTPUT);
    digitalWrite(POWER_EN_PIN, LOW);
    pinMode(PERIPH_EN_PIN,OUTPUT);
    digitalWrite(PERIPH_EN_PIN,HIGH);
    delay(100);

    Serial.begin(115200);
    while (!Serial && millis() < 3000) {}  // Wait for serial, but not forever

    // Configure input chain pins
    pinMode(IN_DATA_IN, INPUT);
    pinMode(IN_DATA_OUT, OUTPUT);
    digitalWrite(IN_DATA_OUT, LOW);
    pinMode(IN_SYNC, OUTPUT);
    digitalWrite(IN_SYNC, HIGH);   // 597 idle HIGH
    pinMode(IN_CLOCK, OUTPUT);
    digitalWrite(IN_CLOCK, LOW);

    // Configure output chain pins
    pinMode(OUT_DATA_IN, INPUT);
    pinMode(OUT_DATA_OUT, OUTPUT);
    digitalWrite(OUT_DATA_OUT, LOW);
    pinMode(OUT_SYNC, OUTPUT);
    digitalWrite(OUT_SYNC, LOW);   // 595 OE tied to RCLK — LOW enables outputs
    pinMode(OUT_CLOCK, OUTPUT);
    digitalWrite(OUT_CLOCK, LOW);
while(1){
    // Reset shift registers
    pinMode(4, OUTPUT);
    pinMode(12, OUTPUT);
    digitalWrite(4, HIGH);
    digitalWrite(12, HIGH);
    delay(1);
    digitalWrite(4, LOW);
    digitalWrite(12, LOW);
    delay(1);
    digitalWrite(4, HIGH);
    digitalWrite(12, HIGH);

    // Clear output buffer
    for (uint16_t w = 0; w < OUT_WORDS; w++) {
        outputBuffer[w] = 0;
    }

    // Push all-zeros to outputs to start clean
    scanOutputChain();

    Serial.println("========================================");
    Serial.println("Walking HIGH Test");
    Serial.print("Output bits ");
    Serial.print(WALK_START_BIT);
    Serial.print(" to ");
    Serial.print(WALK_END_BIT);
    Serial.print(" (");
    Serial.print(WALK_END_BIT - WALK_START_BIT + 1);
    Serial.println(" steps)");
    Serial.println("500ms per step, reading 64 inputs each step");
    Serial.println("========================================");
    Serial.println();

    // Read and display baseline inputs before starting
    // Initialize prev buffer to zeros so baseline shows all initial states as changes
    for (uint16_t w = 0; w < IN_WORDS; w++) {
        inputBufferPrev[w] = 0;
    }
    scanInputChain();
    Serial.println("Baseline (all outputs LOW):");
    printInputState();
    Serial.print("  Changed: ");
    printChangedBits();
    saveInputState();
    Serial.println();

    // Walk a HIGH through the specified output bit range
    for (uint16_t outBit = WALK_START_BIT; outBit <= WALK_END_BIT; outBit++) {
        // Clear entire output buffer
        for (uint16_t w = 0; w < OUT_WORDS; w++) {
            outputBuffer[w] = 0;
        }

        // Set only the current bit
        uint16_t word = outBit / 16;
        uint16_t bitInWord = outBit % 16;
        outputBuffer[word] = (1 << bitInWord);

        // Shift out to hardware
        scanOutputChain();

        // Wait for things to settle, then read inputs
        delay(STEP_MS);
        scanInputChain();

        // Display
        Serial.print("Output bit ");
        if (outBit < 100) Serial.print(' ');
        if (outBit < 10) Serial.print(' ');
        Serial.print(outBit);
        Serial.print(": ");
        printInputState();
        Serial.print("  Changed: ");
        printChangedBits();
        saveInputState();
    }

    // Clear outputs when done
    for (uint16_t w = 0; w < OUT_WORDS; w++) {
        outputBuffer[w] = 0;
    }
    scanOutputChain();

    Serial.println();
    Serial.println("========================================");
    Serial.println("Walking HIGH test complete.");
    Serial.println("========================================");
}
}
void loop() {
    // Nothing — test runs once in setup()
}