// CoilPulseTester.ino
// Manual coil pulse tester + stop test tool with TeensyUserInterface
//
// Main screen: [-] [coil#] [+] [PULSE] [TestStops]
// Continuously scans chain 0 (keyboards) and chain 2 (sense).
// Displays input changes on LCD, dumps state arrays on USB serial.
//
// Hardware (from ConfigData.h):
//   Chain 0: Multidrop input (keyboards + pistons), 128 bits
//   Chain 1: 595 output (SAM coils), 128 bits
//   Chain 2: 597 input (SAM sense), 128 bits

#include <TeensyUserInterface.h>
#include <font_Arial.h>
#include "Config.h"
#include "ConfigData.h"
#include "ScanChain.h"

// ============================================================
// Chain indices (from ConfigData.h)
// ============================================================

constexpr uint8_t KBD_CHAIN   = 0;   // Multidrop keyboards
constexpr uint8_t COIL_CHAIN  = 1;   // 595 output
constexpr uint8_t SENSE_CHAIN = 2;   // 597 input

// ============================================================
// UI Object
// ============================================================

TeensyUserInterface ui;

// ============================================================
// Colors
// ============================================================

constexpr uint16_t COL_BG        = ILI9341_BLACK;
constexpr uint16_t COL_TEXT      = ILI9341_WHITE;
constexpr uint16_t COL_LABEL     = ILI9341_CYAN;
constexpr uint16_t COL_VALUE_BG  = ILI9341_NAVY;
constexpr uint16_t COL_CHANGE    = ILI9341_YELLOW;
constexpr uint16_t COL_OK        = ILI9341_GREEN;
constexpr uint16_t COL_ERR       = ILI9341_RED;

// ============================================================
// Buttons — BUTTON is {"label", centerX, centerY, width, height}
// ============================================================

BUTTON minusButton    = {"-",         40,  45,  60, 50};
BUTTON plusButton     = {"+",        280,  45,  60, 50};
BUTTON pulseButton    = {"PULSE",    115,  98, 110, 36};
BUTTON testStopButton = {"TestStops",235,  98, 130, 36};

// ============================================================
// Layout
// ============================================================

constexpr int16_t VAL_X = 80,  VAL_Y = 20, VAL_W = 160, VAL_H = 50;

constexpr int16_t LOG_X = 5;
constexpr int16_t LOG_Y = 140;
constexpr int16_t LOG_LINE_H = 13;
constexpr uint8_t MAX_LOG_LINES = 7;

// ============================================================
// State
// ============================================================

static int16_t selectedCoil = 0;
static bool pulseActive = false;
static uint32_t pulseEndTime = 0;
static uint32_t lastScanTime = 0;

constexpr uint32_t SCAN_INTERVAL_MS = 50;

// Previous input state for change detection — one per scanned chain
static uint16_t prevSense[WORDS_PER_CHAIN];
static uint16_t prevKbd[WORDS_PER_CHAIN];

// Change log
static char logLines[MAX_LOG_LINES][42];
static uint8_t logCount = 0;

// ============================================================
// Serial helpers
// ============================================================

static void serialPrintChain(uint8_t chain, uint16_t numBits) {
    uint16_t endWord = (numBits - 1) / 16;
    for (int16_t w = endWord; w >= 0; w--) {
        for (int8_t b = 15; b >= 0; b--) {
            Serial.print((inputBuffer[chain][w] >> b) & 1);
            if (b == 8) Serial.print('_');
        }
        if (w > 0) Serial.print(' ');
    }
    Serial.println();
}

// ============================================================
// Drawing helpers
// ============================================================

static void drawCoilValue() {
    ui.lcdDrawFilledRectangle(VAL_X + 1, VAL_Y + 1,
                              VAL_X + VAL_W - 2, VAL_Y + VAL_H - 2,
                              COL_VALUE_BG);
    ui.lcdDrawRectangle(VAL_X, VAL_Y,
                        VAL_X + VAL_W - 1, VAL_Y + VAL_H - 1,
                        COL_TEXT);

    char buf[8];
    snprintf(buf, sizeof(buf), "%d", selectedCoil);
    ui.lcdSetFont(Arial_18);
    ui.lcdSetFontColor(COL_TEXT);
    int16_t textW = strlen(buf) * 12;
    ui.lcdSetCursorXY(VAL_X + (VAL_W - textW) / 2, VAL_Y + 14);
    ui.lcdPrint(buf);
}

static void drawPulseButton() {
    if (pulseActive) {
        BUTTON activeBtn = {"PULSING", 115, 98, 110, 36};
        ui.drawButton(activeBtn);
    } else {
        ui.drawButton(pulseButton);
    }
}

static void drawLogArea() {
    ui.lcdDrawFilledRectangle(LOG_X, LOG_Y, 315,
                              LOG_Y + MAX_LOG_LINES * LOG_LINE_H, COL_BG);
    ui.lcdSetFont(Arial_9);
    ui.lcdSetFontColor(COL_CHANGE);
    for (uint8_t i = 0; i < logCount; i++) {
        ui.lcdSetCursorXY(LOG_X, LOG_Y + i * LOG_LINE_H);
        ui.lcdPrint(logLines[i]);
    }
}

static void addLogLine(const char* text) {
    if (logCount >= MAX_LOG_LINES) {
        for (uint8_t i = 0; i < MAX_LOG_LINES - 1; i++) {
            strncpy(logLines[i], logLines[i + 1], 41);
        }
        logCount = MAX_LOG_LINES - 1;
    }
    strncpy(logLines[logCount], text, 41);
    logLines[logCount][41] = '\0';
    logCount++;
    drawLogArea();
}

static void drawMainScreen() {
    ui.lcdClearScreen(COL_BG);

    ui.lcdSetFont(Arial_9);
    ui.lcdSetFontColor(COL_LABEL);
    ui.lcdSetCursorXY(5, 5);
    ui.lcdPrint("Coil Pulse Tester");

    ui.drawButton(minusButton);
    ui.drawButton(plusButton);
    drawCoilValue();
    drawPulseButton();
    ui.drawButton(testStopButton);

    ui.lcdDrawLine(0, LOG_Y - 15, 319, LOG_Y - 15, COL_LABEL);

    ui.lcdSetFont(Arial_9);
    ui.lcdSetFontColor(COL_LABEL);
    ui.lcdSetCursorXY(LOG_X, LOG_Y - 13);
    ui.lcdPrint("Input Changes:");

    // Redraw any existing log lines
    drawLogArea();
}

// ============================================================
// Input Change Detection
// ============================================================

static void checkChainChanges(uint8_t chain, uint16_t numBits,
                              uint16_t* prevBuf, const char* label) {
    bool anyChanged = false;
    uint16_t endWord = (numBits - 1) / 16;

    for (uint16_t w = 0; w <= endWord; w++) {
        uint16_t diff = inputBuffer[chain][w] ^ prevBuf[w];
        if (diff == 0) continue;

        anyChanged = true;
        for (uint16_t b = 0; b < 16; b++) {
            if (!((diff >> b) & 1)) continue;

            uint16_t bitNum = w * 16 + b;
            if (bitNum >= numBits) continue;

            bool isOn = (inputBuffer[chain][w] >> b) & 1;
            uint16_t cwb = makeAddr(chain, bitNum);
            char msg[42];
            snprintf(msg, sizeof(msg), "%s 0x%03X (bit %d) %s",
                     label, cwb, bitNum, isOn ? "ON" : "OFF");
            addLogLine(msg);
            Serial.println(msg);
        }
    }

    if (anyChanged) {
        Serial.print(label);
        Serial.print(" chain ");
        Serial.print(chain);
        Serial.print(": ");
        serialPrintChain(chain, numBits);

        for (uint16_t w = 0; w <= endWord; w++) {
            prevBuf[w] = inputBuffer[chain][w];
        }
    }
}

static void scanAndCheckInputs() {
    // Scan keyboard chain (multidrop)
    scanInputChainTyped(KBD_CHAIN, chainBitsUsed[KBD_CHAIN], chainType[KBD_CHAIN]);
    checkChainChanges(KBD_CHAIN, chainBitsUsed[KBD_CHAIN], prevKbd, "Kbd");

    // Scan sense chain (597)
    scanInputChainTyped(SENSE_CHAIN, chainBitsUsed[SENSE_CHAIN], chainType[SENSE_CHAIN]);
    checkChainChanges(SENSE_CHAIN, chainBitsUsed[SENSE_CHAIN], prevSense, "Sns");
}

// ============================================================
// TestStops — walk through all stops, pulse ON/OFF, verify sense
// ============================================================

static void runTestStops() {
    ui.lcdClearScreen(COL_BG);
    ui.lcdSetFont(Arial_12);
    ui.lcdSetFontColor(COL_LABEL);
    ui.lcdSetCursorXY(5, 5);
    ui.lcdPrint("Testing Stops...");

    Serial.println();
    Serial.println("=== TestStops: Verifying all stops ===");

    // ============================================================
    // Bulk phases: ALL ON/OFF, ODD ON/OFF, EVEN ON/OFF
    // ============================================================

    ui.lcdSetFont(Arial_9);
    ui.lcdSetFontColor(COL_TEXT);
    ui.lcdSetCursorXY(5, 28);
    ui.lcdPrint("ALL ON...");
    Serial.println("--- ALL ON ---");

    // ALL ON
    clearOutputBuffer(COIL_CHAIN);
    for (uint8_t i = 0; i < NUM_STOPS; i++) {
        if (stopOnCoilAddr[i] == ADDR_DISABLED) continue;
        uint8_t c, w, b;
        parseAddr(stopOnCoilAddr[i], c, w, b);
        writeOutputBitDirect(c, w, b, 1);
    }
    scanOutputChainTyped(COIL_CHAIN, chainBitsUsed[COIL_CHAIN], chainType[COIL_CHAIN]);
    delay(SAM_PULSE_MS);
    clearOutputBuffer(COIL_CHAIN);
    scanOutputChainTyped(COIL_CHAIN, chainBitsUsed[COIL_CHAIN], chainType[COIL_CHAIN]);
    delay(1000);

    // ALL OFF
    ui.lcdDrawFilledRectangle(0, 25, 319, 45, COL_BG);
    ui.lcdSetCursorXY(5, 28);
    ui.lcdPrint("ALL OFF...");
    Serial.println("--- ALL OFF ---");

    clearOutputBuffer(COIL_CHAIN);
    for (uint8_t i = 0; i < NUM_STOPS; i++) {
        if (stopOffCoilAddr[i] == ADDR_DISABLED) continue;
        uint8_t c, w, b;
        parseAddr(stopOffCoilAddr[i], c, w, b);
        writeOutputBitDirect(c, w, b, 1);
    }
    scanOutputChainTyped(COIL_CHAIN, chainBitsUsed[COIL_CHAIN], chainType[COIL_CHAIN]);
    delay(SAM_PULSE_MS);
    clearOutputBuffer(COIL_CHAIN);
    scanOutputChainTyped(COIL_CHAIN, chainBitsUsed[COIL_CHAIN], chainType[COIL_CHAIN]);
    delay(1000);

    // EVEN ON (i=0,2,4...)
    ui.lcdDrawFilledRectangle(0, 25, 319, 45, COL_BG);
    ui.lcdSetCursorXY(5, 28);
    ui.lcdPrint("EVEN ON...");
    Serial.println("--- EVEN ON ---");

    clearOutputBuffer(COIL_CHAIN);
    for (uint8_t i = 0; i < NUM_STOPS; i += 2) {
        if (stopOnCoilAddr[i] == ADDR_DISABLED) continue;
        uint8_t c, w, b;
        parseAddr(stopOnCoilAddr[i], c, w, b);
        writeOutputBitDirect(c, w, b, 1);
    }
    scanOutputChainTyped(COIL_CHAIN, chainBitsUsed[COIL_CHAIN], chainType[COIL_CHAIN]);
    delay(SAM_PULSE_MS);
    clearOutputBuffer(COIL_CHAIN);
    scanOutputChainTyped(COIL_CHAIN, chainBitsUsed[COIL_CHAIN], chainType[COIL_CHAIN]);
    delay(1000);

    // ALL OFF (after even)
    ui.lcdDrawFilledRectangle(0, 25, 319, 45, COL_BG);
    ui.lcdSetCursorXY(5, 28);
    ui.lcdPrint("ALL OFF...");
    Serial.println("--- ALL OFF (after even) ---");

    clearOutputBuffer(COIL_CHAIN);
    for (uint8_t i = 0; i < NUM_STOPS; i++) {
        if (stopOffCoilAddr[i] == ADDR_DISABLED) continue;
        uint8_t c, w, b;
        parseAddr(stopOffCoilAddr[i], c, w, b);
        writeOutputBitDirect(c, w, b, 1);
    }
    scanOutputChainTyped(COIL_CHAIN, chainBitsUsed[COIL_CHAIN], chainType[COIL_CHAIN]);
    delay(SAM_PULSE_MS);
    clearOutputBuffer(COIL_CHAIN);
    scanOutputChainTyped(COIL_CHAIN, chainBitsUsed[COIL_CHAIN], chainType[COIL_CHAIN]);
    delay(1000);

    // ODD ON (i=1,3,5...)
    ui.lcdDrawFilledRectangle(0, 25, 319, 45, COL_BG);
    ui.lcdSetCursorXY(5, 28);
    ui.lcdPrint("ODD ON...");
    Serial.println("--- ODD ON ---");

    clearOutputBuffer(COIL_CHAIN);
    for (uint8_t i = 1; i < NUM_STOPS; i += 2) {
        if (stopOnCoilAddr[i] == ADDR_DISABLED) continue;
        uint8_t c, w, b;
        parseAddr(stopOnCoilAddr[i], c, w, b);
        writeOutputBitDirect(c, w, b, 1);
    }
    scanOutputChainTyped(COIL_CHAIN, chainBitsUsed[COIL_CHAIN], chainType[COIL_CHAIN]);
    delay(SAM_PULSE_MS);
    clearOutputBuffer(COIL_CHAIN);
    scanOutputChainTyped(COIL_CHAIN, chainBitsUsed[COIL_CHAIN], chainType[COIL_CHAIN]);
    delay(1000);

    // ALL OFF (after odd)
    ui.lcdDrawFilledRectangle(0, 25, 319, 45, COL_BG);
    ui.lcdSetCursorXY(5, 28);
    ui.lcdPrint("ALL OFF...");
    Serial.println("--- ALL OFF (after odd) ---");

    clearOutputBuffer(COIL_CHAIN);
    for (uint8_t i = 0; i < NUM_STOPS; i++) {
        if (stopOffCoilAddr[i] == ADDR_DISABLED) continue;
        uint8_t c, w, b;
        parseAddr(stopOffCoilAddr[i], c, w, b);
        writeOutputBitDirect(c, w, b, 1);
    }
    scanOutputChainTyped(COIL_CHAIN, chainBitsUsed[COIL_CHAIN], chainType[COIL_CHAIN]);
    delay(SAM_PULSE_MS);
    clearOutputBuffer(COIL_CHAIN);
    scanOutputChainTyped(COIL_CHAIN, chainBitsUsed[COIL_CHAIN], chainType[COIL_CHAIN]);
    delay(1000);

    // ============================================================
    // Individual stop tests
    // ============================================================

    ui.lcdDrawFilledRectangle(0, 25, 319, 45, COL_BG);
    ui.lcdSetCursorXY(5, 28);
    ui.lcdPrint("Individual tests...");
    Serial.println("--- Individual stop tests ---");

    uint8_t onPass = 0, onFail = 0, offPass = 0, offFail = 0;

    for (uint8_t i = 0; i < NUM_STOPS; i++) {
        if (stopSenseAddr[i] == ADDR_DISABLED) continue;
        if (stopOnCoilAddr[i] == ADDR_DISABLED) continue;

        uint8_t sChain, sWord, sBit;
        parseAddr(stopSenseAddr[i], sChain, sWord, sBit);

        // Update LCD progress
        ui.lcdDrawFilledRectangle(0, 25, 319, 70, COL_BG);
        ui.lcdSetFont(Arial_9);
        ui.lcdSetFontColor(COL_TEXT);
        ui.lcdSetCursorXY(5, 28);
        char buf[48];
        snprintf(buf, sizeof(buf), "Stop %d/%d  sense 0x%03X", i + 1, NUM_STOPS,
                 stopSenseAddr[i]);
        ui.lcdPrint(buf);

        // --- Read sense before ON ---
        scanInputChainTyped(sChain, chainBitsUsed[sChain], chainType[sChain]);
        bool stateBefore = readInputBitDirect(sChain, sWord, sBit);

        // --- Pulse ON coil ---
        uint8_t onChain, onWord, onBit;
        parseAddr(stopOnCoilAddr[i], onChain, onWord, onBit);
        clearOutputBuffer(onChain);
        writeOutputBitDirect(onChain, onWord, onBit, 1);
        scanOutputChainTyped(onChain, chainBitsUsed[onChain], chainType[onChain]);
        delay(SAM_PULSE_MS);
        writeOutputBitDirect(onChain, onWord, onBit, 0);
        scanOutputChainTyped(onChain, chainBitsUsed[onChain], chainType[onChain]);
        delay(SAM_SETTLE_MS);

        // --- Read sense after ON ---
        scanInputChainTyped(sChain, chainBitsUsed[sChain], chainType[sChain]);
        bool stateAfterOn = readInputBitDirect(sChain, sWord, sBit);

        Serial.print("  Stop ");
        Serial.print(i);
        Serial.print(" (sense 0x");
        char hex[5]; snprintf(hex, sizeof(hex), "%03X", stopSenseAddr[i]);
        Serial.print(hex);
        Serial.print("):");

        if (stateAfterOn != stateBefore) {
            Serial.print(" ON=PASS");
            onPass++;
        } else {
            Serial.print(" ON=FAIL");
            onFail++;
        }

        // --- Pulse OFF coil ---
        if (stopOffCoilAddr[i] != ADDR_DISABLED) {
            uint8_t offChain, offWord, offBit;
            parseAddr(stopOffCoilAddr[i], offChain, offWord, offBit);
            clearOutputBuffer(offChain);
            writeOutputBitDirect(offChain, offWord, offBit, 1);
            scanOutputChainTyped(offChain, chainBitsUsed[offChain], chainType[offChain]);
            delay(SAM_PULSE_MS);
            writeOutputBitDirect(offChain, offWord, offBit, 0);
            scanOutputChainTyped(offChain, chainBitsUsed[offChain], chainType[offChain]);
            delay(SAM_SETTLE_MS);

            scanInputChainTyped(sChain, chainBitsUsed[sChain], chainType[sChain]);
            bool stateAfterOff = readInputBitDirect(sChain, sWord, sBit);

            if (stateAfterOff != stateAfterOn) {
                Serial.print(" OFF=PASS");
                offPass++;
            } else {
                Serial.print(" OFF=FAIL");
                offFail++;
            }
        } else {
            Serial.print(" OFF=SKIP(no addr)");
        }
        Serial.println();

        // Update pass/fail on LCD
        ui.lcdDrawFilledRectangle(0, 75, 319, 130, COL_BG);
        ui.lcdSetFont(Arial_9);
        ui.lcdSetCursorXY(5, 78);
        ui.lcdSetFontColor(COL_OK);
        snprintf(buf, sizeof(buf), "ON pass:%d", onPass);
        ui.lcdPrint(buf);
        ui.lcdSetCursorXY(120, 78);
        ui.lcdSetFontColor(COL_ERR);
        snprintf(buf, sizeof(buf), "fail:%d", onFail);
        ui.lcdPrint(buf);

        ui.lcdSetCursorXY(5, 93);
        ui.lcdSetFontColor(COL_OK);
        snprintf(buf, sizeof(buf), "OFF pass:%d", offPass);
        ui.lcdPrint(buf);
        ui.lcdSetCursorXY(120, 93);
        ui.lcdSetFontColor(COL_ERR);
        snprintf(buf, sizeof(buf), "fail:%d", offFail);
        ui.lcdPrint(buf);

        // Also scan keyboards during the test so we see any activity
        scanInputChainTyped(KBD_CHAIN, chainBitsUsed[KBD_CHAIN], chainType[KBD_CHAIN]);
        checkChainChanges(KBD_CHAIN, chainBitsUsed[KBD_CHAIN], prevKbd, "Kbd");
    }

    // Final summary
    Serial.println();
    Serial.print("ON  test: "); Serial.print(onPass); Serial.print(" pass, ");
    Serial.print(onFail); Serial.println(" fail");
    Serial.print("OFF test: "); Serial.print(offPass); Serial.print(" pass, ");
    Serial.print(offFail); Serial.println(" fail");

    // Show CONTINUE button
    ui.lcdSetFont(Arial_12);
    ui.lcdSetFontColor(COL_LABEL);
    ui.lcdSetCursorXY(5, 150);
    ui.lcdPrint("Test complete.");

    BUTTON contButton = {"CONTINUE", 160, 200, 160, 35};
    ui.drawButton(contButton);

    // Wait for touch
    while (true) {
        ui.getTouchEvents();
        if (ui.checkForButtonClicked(contButton)) break;

        // Keep scanning inputs while waiting
        uint32_t now = millis();
        if (now - lastScanTime >= SCAN_INTERVAL_MS) {
            lastScanTime = now;
            scanAndCheckInputs();
        }
    }

    // Re-read sense baseline after test changed all the stops
    scanInputChainTyped(SENSE_CHAIN, chainBitsUsed[SENSE_CHAIN], chainType[SENSE_CHAIN]);
    uint16_t endWord = (chainBitsUsed[SENSE_CHAIN] - 1) / 16;
    for (uint16_t w = 0; w <= endWord; w++) {
        prevSense[w] = inputBuffer[SENSE_CHAIN][w];
    }

    drawMainScreen();
}

// ============================================================
// Setup
// ============================================================

void setup() {
    // Power supply enable
    pinMode(POWER_SUPPLY_PIN, OUTPUT);
    digitalWrite(POWER_SUPPLY_PIN, LOW);
    pinMode(BACKLIGHT_ON, OUTPUT);
    digitalWrite(BACKLIGHT_ON, HIGH);
    delay(100);

    Serial.begin(115200);
    while (!Serial && millis() < 3000) {}

    // Initialize scan chains
    scanChainInit();

    // Initialize UI
    ui.begin(TFT_CS, TFT_DC, TOUCH_CS,
             LCD_ORIENTATION_LANDSCAPE_4PIN_RIGHT, Arial_9);

    // Read initial state for both input chains
    scanInputChainTyped(KBD_CHAIN, chainBitsUsed[KBD_CHAIN], chainType[KBD_CHAIN]);
    scanInputChainTyped(SENSE_CHAIN, chainBitsUsed[SENSE_CHAIN], chainType[SENSE_CHAIN]);

    uint16_t kbdWords  = (chainBitsUsed[KBD_CHAIN] - 1) / 16 + 1;
    uint16_t snsWords  = (chainBitsUsed[SENSE_CHAIN] - 1) / 16 + 1;
    for (uint16_t w = 0; w < kbdWords; w++)  prevKbd[w]   = inputBuffer[KBD_CHAIN][w];
    for (uint16_t w = 0; w < snsWords; w++)  prevSense[w] = inputBuffer[SENSE_CHAIN][w];

    drawMainScreen();

    Serial.println("Coil Pulse Tester ready.");
    Serial.print("Kbd chain ");   Serial.print(KBD_CHAIN);
    Serial.print(": ");           Serial.print(chainBitsUsed[KBD_CHAIN]);
    Serial.println(" bits (multidrop)");
    Serial.print("Coil chain ");  Serial.print(COIL_CHAIN);
    Serial.print(": ");           Serial.print(chainBitsUsed[COIL_CHAIN]);
    Serial.println(" bits (595 output)");
    Serial.print("Sense chain "); Serial.print(SENSE_CHAIN);
    Serial.print(": ");           Serial.print(chainBitsUsed[SENSE_CHAIN]);
    Serial.println(" bits (597 input)");
    Serial.print("Stops configured: "); Serial.println(NUM_STOPS);
    Serial.print("Initial Kbd:   "); serialPrintChain(KBD_CHAIN, chainBitsUsed[KBD_CHAIN]);
    Serial.print("Initial Sense: "); serialPrintChain(SENSE_CHAIN, chainBitsUsed[SENSE_CHAIN]);
}

// ============================================================
// Loop
// ============================================================

void loop() {
    uint32_t now = millis();

    // Handle pulse timeout
    if (pulseActive && now >= pulseEndTime) {
        clearOutputBuffer(COIL_CHAIN);
        scanOutputChainTyped(COIL_CHAIN, chainBitsUsed[COIL_CHAIN], chainType[COIL_CHAIN]);
        pulseActive = false;
        drawPulseButton();
    }

    // Scan both input chains periodically
    if (now - lastScanTime >= SCAN_INTERVAL_MS) {
        lastScanTime = now;
        scanAndCheckInputs();
    }

    // Process touch events
    ui.getTouchEvents();

    if (ui.checkForButtonClicked(minusButton)) {
        if (selectedCoil > 0) {
            selectedCoil--;
            drawCoilValue();
        }
    }

    if (ui.checkForButtonClicked(plusButton)) {
        if (selectedCoil < (int16_t)(chainBitsUsed[COIL_CHAIN] - 1)) {
            selectedCoil++;
            drawCoilValue();
        }
    }

    if (ui.checkForButtonClicked(pulseButton)) {
        if (!pulseActive) {
            pulseActive = true;
            pulseEndTime = now + SAM_PULSE_MS;

            clearOutputBuffer(COIL_CHAIN);
            writeOutputBitDirect(COIL_CHAIN, selectedCoil / 16, selectedCoil % 16, 1);
            scanOutputChainTyped(COIL_CHAIN, chainBitsUsed[COIL_CHAIN], chainType[COIL_CHAIN]);

            drawPulseButton();

            Serial.print("PULSE coil ");
            Serial.print(selectedCoil);
            Serial.print(" (0x");
            char hex[5]; snprintf(hex, sizeof(hex), "%03X", makeAddr(COIL_CHAIN, selectedCoil));
            Serial.print(hex);
            Serial.print(") for ");
            Serial.print(SAM_PULSE_MS);
            Serial.println("ms");
        }
    }

    if (ui.checkForButtonClicked(testStopButton)) {
        runTestStops();
    }
}
