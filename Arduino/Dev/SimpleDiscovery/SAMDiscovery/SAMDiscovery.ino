// SAMDiscovery.ino
// Auto-discovery tool for organ SAM (Stop Action Magnet) systems
// Discovers sense inputs, ON coils, and OFF coils on 74HC596/597 chains
//
// Uses ILI9341 LCD + XPT2046 touch for user prompts between phases.
// Results output to Serial as ConfigData.h arrays.

#include <SPI.h>
#include <ILI9341_t3.h>
#include <XPT2046_Touchscreen.h>
#include "Config.h"
#include "ScanChain.h"

// ============================================================
// Display
// ============================================================

static ILI9341_t3 tft(TFT_CS, TFT_DC);
static XPT2046_Touchscreen touch(TOUCH_CS);

// Colors
constexpr uint16_t COL_BG      = ILI9341_BLACK;
constexpr uint16_t COL_TEXT    = ILI9341_WHITE;
constexpr uint16_t COL_HEADER  = ILI9341_CYAN;
constexpr uint16_t COL_OK      = ILI9341_GREEN;
constexpr uint16_t COL_ERR     = ILI9341_RED;
constexpr uint16_t COL_BTN_BG  = ILI9341_BLUE;
constexpr uint16_t COL_BTN_TXT = ILI9341_WHITE;

// CONTINUE button location (bottom center)
constexpr int BTN_X = 60;
constexpr int BTN_Y = 200;
constexpr int BTN_W = 200;
constexpr int BTN_H = 35;

// ============================================================
// Display helpers
// ============================================================

static void lcdClear() {
    tft.fillScreen(COL_BG);
    tft.setCursor(0, 0);
}

static void lcdHeader(const char* text) {
    lcdClear();
    tft.setTextColor(COL_HEADER);
    tft.setTextSize(2);
    tft.println(text);
    tft.println();
    tft.setTextColor(COL_TEXT);
    tft.setTextSize(1);
}

static void lcdPrint(const char* text) {
    tft.setTextColor(COL_TEXT);
    tft.setTextSize(1);
    tft.println(text);
}

static void lcdPrintVal(const char* label, int value) {
    tft.setTextColor(COL_TEXT);
    tft.setTextSize(1);
    tft.print(label);
    tft.println(value);
}

static void lcdDrawButton(const char* label) {
    tft.fillRect(BTN_X, BTN_Y, BTN_W, BTN_H, COL_BTN_BG);
    tft.drawRect(BTN_X, BTN_Y, BTN_W, BTN_H, COL_TEXT);
    tft.setTextColor(COL_BTN_TXT);
    tft.setTextSize(2);
    // Center text in button
    int textWidth = strlen(label) * 12;
    int textX = BTN_X + (BTN_W - textWidth) / 2;
    int textY = BTN_Y + (BTN_H - 16) / 2;
    tft.setCursor(textX, textY);
    tft.print(label);
    tft.setTextSize(1);
    tft.setTextColor(COL_TEXT);
}

static void waitForTouch() {
    // Wait for release first (if already touching)
    while (touch.touched()) { delay(10); }
    delay(50);
    // Wait for new touch
    while (!touch.touched()) { delay(10); }
    // Wait for release
    while (touch.touched()) { delay(10); }
    delay(50);
}

static void lcdProgress(uint16_t current, uint16_t total, uint8_t found) {
    // Overwrite progress line at fixed position
    tft.fillRect(0, 100, 320, 20, COL_BG);
    tft.setCursor(0, 100);
    tft.setTextColor(COL_TEXT);
    tft.setTextSize(1);
    tft.print("Testing bit ");
    tft.print(current);
    tft.print("/");
    tft.print(total);
    tft.print("  Found: ");
    tft.print(found);
}

// ============================================================
// Data Structures
// ============================================================

struct DiscoveredStop {
    uint16_t senseAddr;     // 0xCWB format
    uint16_t onCoilAddr;    // 0xCWB format
    uint16_t offCoilAddr;   // 0xCWB format, ADDR_DISABLED if not found
};

// ============================================================
// Discovery State
// ============================================================

static DiscoveredStop discoveredStops[MAX_STOPS];
static uint8_t numDiscoveredStops = 0;
static uint8_t numErrors = 0;

// Sense state before/after each pulse
static uint16_t senseBefore[WORDS_PER_CHAIN];
static uint16_t senseAfter[WORDS_PER_CHAIN];

// Mask of sense bits already discovered (1 = ignore this bit)
static uint16_t senseMask[WORDS_PER_CHAIN];

// ============================================================
// Bit helpers for packed arrays
// ============================================================

static inline bool getBit(const uint16_t* array, uint16_t index) {
    return (array[index / 16] >> (index % 16)) & 0x01;
}

static inline void setBit(uint16_t* array, uint16_t index, bool value) {
    if (value) {
        array[index / 16] |= (1 << (index % 16));
    } else {
        array[index / 16] &= ~(1 << (index % 16));
    }
}

// ============================================================
// Read all sense inputs into a packed array
// ============================================================

static void readSenseInputs(uint16_t* dest) {
    scanInputChainTyped(SENSE_CHAIN, SENSE_END_BIT + 1, SENSE_CHAIN_TYPE);
    uint16_t numBits = SENSE_END_BIT - SENSE_START_BIT + 1;
    for (uint16_t i = 0; i < numBits; i++) {
        uint16_t bitIndex = SENSE_START_BIT + i;
        bool val = readInputBitDirect(SENSE_CHAIN, bitIndex / 16, bitIndex % 16);
        setBit(dest, i, val);
    }
}

// ============================================================
// Pulse a coil output for SAM_PULSE_MS
// ============================================================

static void pulseCoil(uint16_t bitIndex) {
    writeOutputBitDirect(COIL_CHAIN, bitIndex / 16, bitIndex % 16, 1);
    scanOutputChainTyped(COIL_CHAIN, COIL_END_BIT + 1, COIL_CHAIN_TYPE);
    delay(SAM_PULSE_MS);
    
    writeOutputBitDirect(COIL_CHAIN, bitIndex / 16, bitIndex % 16, 0);
    scanOutputChainTyped(COIL_CHAIN, COIL_END_BIT + 1, COIL_CHAIN_TYPE);
    delay(SAM_SETTLE_MS);
}

// ============================================================
// Sort discovered stops by sense address (ascending)
// ============================================================

static void sortStops() {
    for (uint8_t i = 1; i < numDiscoveredStops; i++) {
        DiscoveredStop temp = discoveredStops[i];
        int j = i - 1;
        while (j >= 0 && discoveredStops[j].senseAddr > temp.senseAddr) {
            discoveredStops[j + 1] = discoveredStops[j];
            j--;
        }
        discoveredStops[j + 1] = temp;
    }
}

// ============================================================
// Output configuration arrays to Serial
// ============================================================

static void outputConfigData() {
    Serial.println();
    Serial.println("// ============================================================");
    Serial.println("// Stop Configuration");
    Serial.println("// Auto-generated by SAM Discovery Tool");
    Serial.println("// ============================================================");
    Serial.println();
    
    Serial.print("constexpr uint8_t NUM_STOPS = ");
    Serial.print(numDiscoveredStops);
    Serial.println(";");
    Serial.println();
    
    // Sense addresses
    Serial.print("constexpr uint16_t stopSenseAddr[NUM_STOPS] = { ");
    for (uint8_t i = 0; i < numDiscoveredStops; i++) {
        if (i > 0) Serial.print(", ");
        if (i > 0 && i % 8 == 0) {
            Serial.println();
            Serial.print("    ");
        }
        char buf[8];
        snprintf(buf, sizeof(buf), "0x%03X", discoveredStops[i].senseAddr);
        Serial.print(buf);
    }
    Serial.println(" };");
    
    // ON coil addresses
    Serial.print("constexpr uint16_t stopOnCoilAddr[NUM_STOPS] = { ");
    for (uint8_t i = 0; i < numDiscoveredStops; i++) {
        if (i > 0) Serial.print(", ");
        if (i > 0 && i % 8 == 0) {
            Serial.println();
            Serial.print("    ");
        }
        char buf[8];
        snprintf(buf, sizeof(buf), "0x%03X", discoveredStops[i].onCoilAddr);
        Serial.print(buf);
    }
    Serial.println(" };");
    
    // OFF coil addresses
    Serial.print("constexpr uint16_t stopOffCoilAddr[NUM_STOPS] = { ");
    for (uint8_t i = 0; i < numDiscoveredStops; i++) {
        if (i > 0) Serial.print(", ");
        if (i > 0 && i % 8 == 0) {
            Serial.println();
            Serial.print("    ");
        }
        char buf[8];
        snprintf(buf, sizeof(buf), "0x%03X", discoveredStops[i].offCoilAddr);
        Serial.print(buf);
    }
    Serial.println(" };");
    
    // Light addresses (all disabled)
    Serial.print("constexpr uint16_t stopLightAddr[NUM_STOPS] = { ");
    for (uint8_t i = 0; i < numDiscoveredStops; i++) {
        if (i > 0) Serial.print(", ");
        if (i > 0 && i % 8 == 0) {
            Serial.println();
            Serial.print("    ");
        }
        Serial.print("0x800");
    }
    Serial.println(" };");
    
    // MIDI channels (all 0)
    Serial.print("constexpr uint8_t stopMidiChannel[NUM_STOPS] = { ");
    for (uint8_t i = 0; i < numDiscoveredStops; i++) {
        if (i > 0) Serial.print(", ");
        if (i > 0 && i % 16 == 0) {
            Serial.println();
            Serial.print("    ");
        }
        Serial.print("0");
    }
    Serial.println(" };");
    
    // MIDI notes (sequential)
    Serial.print("constexpr uint8_t stopMidiNote[NUM_STOPS] = { ");
    for (uint8_t i = 0; i < numDiscoveredStops; i++) {
        if (i > 0) Serial.print(", ");
        if (i > 0 && i % 16 == 0) {
            Serial.println();
            Serial.print("    ");
        }
        Serial.print(i);
    }
    Serial.println(" };");
    
    Serial.println();
    Serial.println("// End of auto-generated configuration");
    Serial.println();
}

// ============================================================
// Setup
// ============================================================

void setup() {
    Serial.begin(115200);
    
    // Start power supply
    pinMode(POWER_ENABLE_PIN, OUTPUT);
    digitalWrite(POWER_ENABLE_PIN, LOW);
    pinMode(PERIPH_ENABLE_PIN, OUTPUT);
    digitalWrite(PERIPH_ENABLE_PIN, HIGH);
    delay(100);
    
    // Initialize display and touch
    tft.begin();
    tft.setRotation(1);  // Landscape
    touch.begin();
    
    // Initialize scan chains
    scanChainInit();
    
    // Clear coil outputs
    clearOutputBuffer(COIL_CHAIN);
    scanOutputChainTyped(COIL_CHAIN, COIL_END_BIT + 1, COIL_CHAIN_TYPE);
    
    numDiscoveredStops = 0;
    numErrors = 0;
    
    uint16_t numSenseBits = SENSE_END_BIT - SENSE_START_BIT + 1;
    uint16_t totalCoilBits = COIL_END_BIT - COIL_START_BIT + 1;
    
    Serial.println("SAM Discovery Tool Starting...");
    Serial.print("Sense chain: "); Serial.print(SENSE_CHAIN);
    Serial.print("  bits "); Serial.print(SENSE_START_BIT);
    Serial.print("-"); Serial.println(SENSE_END_BIT);
    Serial.print("Coil chain:  "); Serial.print(COIL_CHAIN);
    Serial.print("  bits "); Serial.print(COIL_START_BIT);
    Serial.print("-"); Serial.println(COIL_END_BIT);
    Serial.println();
    
    // ============================================================
    // Prompt: Turn all stops OFF
    // ============================================================
    
    lcdHeader("ON Coil Discovery");
    lcdPrint("Turn OFF all stops");
    lcdPrint("then touch CONTINUE");
    lcdDrawButton("CONTINUE");
    waitForTouch();
    
    // ============================================================
    // Phase 1: Discover ON coils
    // ============================================================
    
    lcdHeader("Discovering ON coils");
    Serial.println("=== Phase 1: Discovering ON coils ===");
    
    memset(senseMask, 0, sizeof(senseMask));
    readSenseInputs(senseBefore);
    
    for (uint16_t coilBit = COIL_START_BIT; coilBit <= COIL_END_BIT; coilBit++) {
        uint16_t progress = coilBit - COIL_START_BIT;
        
        lcdProgress(progress, totalCoilBits, numDiscoveredStops);
        
        if (progress % 16 == 0) {
            Serial.print("  Testing bit "); Serial.print(progress);
            Serial.print("/"); Serial.print(totalCoilBits);
            Serial.print("  ("); Serial.print(numDiscoveredStops); Serial.println(" stops found)");
        }
        
        pulseCoil(coilBit);
        readSenseInputs(senseAfter);
        
        for (uint16_t i = 0; i < numSenseBits; i++) {
            if (getBit(senseMask, i)) continue;
            
            bool before = getBit(senseBefore, i);
            bool after = getBit(senseAfter, i);
            
            if (before != after) {
                uint16_t senseAddr = makeAddr(SENSE_CHAIN, SENSE_START_BIT + i);
                uint16_t onCoilAddr = makeAddr(COIL_CHAIN, coilBit);
                
                if (numDiscoveredStops < MAX_STOPS) {
                    discoveredStops[numDiscoveredStops].senseAddr = senseAddr;
                    discoveredStops[numDiscoveredStops].onCoilAddr = onCoilAddr;
                    discoveredStops[numDiscoveredStops].offCoilAddr = ADDR_DISABLED;
                    numDiscoveredStops++;
                }
                
                setBit(senseMask, i, true);
                
                char buf[48];
                snprintf(buf, sizeof(buf), "  -> ON coil 0x%03X -> sense 0x%03X",
                         onCoilAddr, senseAddr);
                Serial.println(buf);
            }
        }
        
        memcpy(senseBefore, senseAfter, sizeof(senseBefore));
    }
    
    Serial.print("ON phase complete: "); Serial.print(numDiscoveredStops);
    Serial.println(" stops found");
    Serial.println();
    
    // Show results on LCD
    lcdHeader("ON Discovery Done");
    lcdPrintVal("Stops found: ", numDiscoveredStops);
    tft.println();
    
    // ============================================================
    // Prompt: Turn all stops ON
    // ============================================================
    
    lcdPrint("Turn ON all stops");
    lcdPrint("then touch CONTINUE");
    lcdDrawButton("CONTINUE");
    waitForTouch();
    
    // ============================================================
    // Phase 2: Discover OFF coils
    // ============================================================
    
    lcdHeader("Discovering OFF coils");
    Serial.println("=== Phase 2: Discovering OFF coils ===");
    
    memset(senseMask, 0, sizeof(senseMask));
    uint8_t matchedCount = 0;
    
    readSenseInputs(senseBefore);
    
    for (uint16_t coilBit = COIL_START_BIT; coilBit <= COIL_END_BIT; coilBit++) {
        uint16_t progress = coilBit - COIL_START_BIT;
        
        lcdProgress(progress, totalCoilBits, matchedCount);
        
        if (progress % 16 == 0) {
            Serial.print("  Testing bit "); Serial.print(progress);
            Serial.print("/"); Serial.print(totalCoilBits);
            Serial.print("  ("); Serial.print(matchedCount); Serial.println(" matched)");
        }
        
        pulseCoil(coilBit);
        readSenseInputs(senseAfter);
        
        for (uint16_t i = 0; i < numSenseBits; i++) {
            if (getBit(senseMask, i)) continue;
            
            bool before = getBit(senseBefore, i);
            bool after = getBit(senseAfter, i);
            
            if (before != after) {
                uint16_t senseAddr = makeAddr(SENSE_CHAIN, SENSE_START_BIT + i);
                uint16_t offCoilAddr = makeAddr(COIL_CHAIN, coilBit);
                
                int stopIndex = -1;
                for (uint8_t s = 0; s < numDiscoveredStops; s++) {
                    if (discoveredStops[s].senseAddr == senseAddr) {
                        stopIndex = s;
                        break;
                    }
                }
                
                if (stopIndex >= 0) {
                    discoveredStops[stopIndex].offCoilAddr = offCoilAddr;
                    matchedCount++;
                    
                    char buf[48];
                    snprintf(buf, sizeof(buf), "  -> OFF coil 0x%03X -> sense 0x%03X",
                             offCoilAddr, senseAddr);
                    Serial.println(buf);
                } else {
                    numErrors++;
                    char buf[64];
                    snprintf(buf, sizeof(buf), "  ERROR: OFF 0x%03X no match (sense 0x%03X)",
                             offCoilAddr, senseAddr);
                    Serial.println(buf);
                }
                
                setBit(senseMask, i, true);
            }
        }
        
        memcpy(senseBefore, senseAfter, sizeof(senseBefore));
    }
    
    Serial.print("OFF phase complete: "); Serial.print(matchedCount);
    Serial.print("/"); Serial.print(numDiscoveredStops);
    Serial.print(" matched, "); Serial.print(numErrors); Serial.println(" errors");
    Serial.println();
    
    // Sort and output
    sortStops();
    outputConfigData();
    
    // Show results on LCD
    lcdHeader("Discovery Complete");
    lcdPrintVal("Stops found: ", numDiscoveredStops);
    lcdPrintVal("ON/OFF matched: ", matchedCount);
    lcdPrintVal("Errors: ", numErrors);
    
    uint8_t unmatchedCount = 0;
    for (uint8_t i = 0; i < numDiscoveredStops; i++) {
        if (discoveredStops[i].offCoilAddr == ADDR_DISABLED) {
            unmatchedCount++;
        }
    }
    if (unmatchedCount > 0) {
        lcdPrintVal("No OFF coil: ", unmatchedCount);
    }
    tft.println();
    
    // ============================================================
    // Prompt: Turn all stops OFF for testing
    // ============================================================
    
    lcdPrint("Turn OFF all stops");
    lcdPrint("then touch CONTINUE");
    lcdDrawButton("CONTINUE");
    waitForTouch();
    
    // ============================================================
    // Phase 3: Test all stops ON/OFF
    // ============================================================
    
    lcdHeader("Testing Stops");
    Serial.println("=== Phase 3: Testing all stops ON/OFF ===");
    Serial.println();
    
    uint8_t onPassCount = 0;
    uint8_t onFailCount = 0;
    uint8_t offPassCount = 0;
    uint8_t offFailCount = 0;
    
    for (uint8_t i = 0; i < numDiscoveredStops; i++) {
        uint8_t senseChain, senseWord, senseBit;
        parseAddr(discoveredStops[i].senseAddr, senseChain, senseWord, senseBit);
        
        // Update LCD progress
        tft.fillRect(0, 60, 320, 40, COL_BG);
        tft.setCursor(0, 60);
        tft.setTextSize(1);
        char buf[64];
        snprintf(buf, sizeof(buf), "Stop %d/%d  sense 0x%03X", i + 1, numDiscoveredStops,
                 discoveredStops[i].senseAddr);
        tft.println(buf);
        
        snprintf(buf, sizeof(buf), "  Stop %d (sense 0x%03X):", i, discoveredStops[i].senseAddr);
        Serial.print(buf);
        
        // Read sense before ON
        scanInputChainTyped(SENSE_CHAIN, SENSE_END_BIT + 1, SENSE_CHAIN_TYPE);
        bool stateBefore = readInputBitDirect(senseChain, senseWord, senseBit);
        
        // Pulse ON coil
        uint8_t onChain, onWord, onBit;
        parseAddr(discoveredStops[i].onCoilAddr, onChain, onWord, onBit);
        writeOutputBitDirect(onChain, onWord, onBit, 1);
        scanOutputChainTyped(COIL_CHAIN, COIL_END_BIT + 1, COIL_CHAIN_TYPE);
        delay(SAM_PULSE_MS);
        writeOutputBitDirect(onChain, onWord, onBit, 0);
        scanOutputChainTyped(COIL_CHAIN, COIL_END_BIT + 1, COIL_CHAIN_TYPE);
        delay(SAM_SETTLE_MS);
        
        // Read sense after ON
        scanInputChainTyped(SENSE_CHAIN, SENSE_END_BIT + 1, SENSE_CHAIN_TYPE);
        bool stateAfterOn = readInputBitDirect(senseChain, senseWord, senseBit);
        
        if (stateAfterOn != stateBefore) {
            Serial.print(" ON=PASS");
            onPassCount++;
        } else {
            Serial.print(" ON=FAIL");
            onFailCount++;
        }
        
        // Pulse OFF coil
        if (discoveredStops[i].offCoilAddr != ADDR_DISABLED) {
            uint8_t offChain, offWord, offBit;
            parseAddr(discoveredStops[i].offCoilAddr, offChain, offWord, offBit);
            writeOutputBitDirect(offChain, offWord, offBit, 1);
            scanOutputChainTyped(COIL_CHAIN, COIL_END_BIT + 1, COIL_CHAIN_TYPE);
            delay(SAM_PULSE_MS);
            writeOutputBitDirect(offChain, offWord, offBit, 0);
            scanOutputChainTyped(COIL_CHAIN, COIL_END_BIT + 1, COIL_CHAIN_TYPE);
            delay(SAM_SETTLE_MS);
            
            scanInputChainTyped(SENSE_CHAIN, SENSE_END_BIT + 1, SENSE_CHAIN_TYPE);
            bool stateAfterOff = readInputBitDirect(senseChain, senseWord, senseBit);
            
            if (stateAfterOff != stateAfterOn) {
                Serial.print(" OFF=PASS");
                offPassCount++;
            } else {
                Serial.print(" OFF=FAIL");
                offFailCount++;
            }
        } else {
            Serial.print(" OFF=SKIP");
        }
        
        Serial.println();
        
        // Update pass/fail on LCD
        tft.fillRect(0, 120, 320, 60, COL_BG);
        tft.setCursor(0, 120);
        tft.setTextColor(COL_OK);
        tft.print("ON pass: "); tft.print(onPassCount);
        tft.setTextColor(COL_ERR);
        tft.print("  fail: "); tft.println(onFailCount);
        tft.setTextColor(COL_OK);
        tft.print("OFF pass: "); tft.print(offPassCount);
        tft.setTextColor(COL_ERR);
        tft.print("  fail: "); tft.println(offFailCount);
        tft.setTextColor(COL_TEXT);
    }
    
    Serial.println();
    Serial.print("ON  test: "); Serial.print(onPassCount); Serial.print(" pass, ");
    Serial.print(onFailCount); Serial.println(" fail");
    Serial.print("OFF test: "); Serial.print(offPassCount); Serial.print(" pass, ");
    Serial.print(offFailCount); Serial.println(" fail");
    Serial.println();
    
    // Final results on LCD
    lcdHeader("Test Complete");
    tft.setTextColor(COL_OK);
    tft.setTextSize(1);
    tft.print("ON  pass: "); tft.print(onPassCount);
    tft.setTextColor(COL_ERR);
    tft.print("  fail: "); tft.println(onFailCount);
    tft.setTextColor(COL_OK);
    tft.print("OFF pass: "); tft.print(offPassCount);
    tft.setTextColor(COL_ERR);
    tft.print("  fail: "); tft.println(offFailCount);
    tft.setTextColor(COL_TEXT);
    tft.println();
    tft.println("Config data sent to Serial.");
    tft.println("Reset to run again.");
    
    Serial.println("Done. Reset to run again.");
}

// ============================================================
// Loop - nothing to do
// ============================================================

void loop() {
    // Discovery runs once in setup()
}
