// OrganController.ino
// Simplified Organ Controller for Hauptwerk — CR Opus 52
// Teensy 4.1
//
// Architecture:
//   1. Read incoming MIDI (USB + Serial) → update stopCommandedState, fire coils
//   2. Scan all chains → load inputBuffer, write outputBuffer
//   3. Compare inputBuffer to inputBufferPrev:
//      - Keyboards (includes pistons): send note on/off
//      - Stops: send MIDI to Hauptwerk (SAM sense changes)
//   4. Build outputBuffer from commanded state (active coils)
//   5. Save inputBuffer to inputBufferPrev
//   6. Update coil timing, expression pedals, display

#include "Config.h"
#include "ConfigData.h"
#include "PersistentConfig.h"
#include "ScanChain.h"
#include "StopHandler.h"
#include "KeyboardHandler.h"
#include "ExpressionHandler.h"
#include "SerialMidi.h"
#include "SysExParser.h"
#include "DisplayManager.h"
#include "Debug.h"

// ============================================================
// USB MIDI Callbacks
// ============================================================

void handleNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
    uint8_t ch = channel - 1;

    Serial.print("DBG: USB NoteOn ch=");
    Serial.print(channel);
    Serial.print(" note=");
    Serial.print(note);
    Serial.print(" vel=");
    Serial.println(velocity);

    // Heartbeat detection
    if (ch == HEARTBEAT_MIDI_CHANNEL && note == HEARTBEAT_MIDI_NOTE) {
        displayOnHeartbeat();
    }

    if (ch == MIDI_CH_STOPS_1 || ch == MIDI_CH_STOPS_2) {
        onStopMidiReceived(ch, note, true);
    }
}

void handleNoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
    uint8_t ch = channel - 1;

    Serial.print("DBG: USB NoteOff ch=");
    Serial.print(channel);
    Serial.print(" note=");
    Serial.println(note);

    // Heartbeat detection (toggle mode may use noteOff as heartbeat)
    if (ch == HEARTBEAT_MIDI_CHANNEL && note == HEARTBEAT_MIDI_NOTE) {
        displayOnHeartbeat();
    }

    if (ch == MIDI_CH_STOPS_1 || ch == MIDI_CH_STOPS_2) {
        onStopMidiReceived(ch, note, false);
    }
}

void handleSysEx(const uint8_t *data, uint16_t length, bool complete) {
    if (complete) {
        Serial.print("DBG: SysEx received, len=");
        Serial.print(length);
        Serial.print(" data:");
        for (uint16_t i = 0; i < length; i++) {
            Serial.print(' ');
            if (data[i] < 0x10) Serial.print('0');
            Serial.print(data[i], HEX);
        }
        Serial.println();
        parseSysEx(data, length);
    }
}

// ============================================================
// Setup
// ============================================================

void setup() {
    Serial.begin(115200);
    while (!Serial && millis() < 3000) { }
    Serial.println("Organ Controller starting...");

    // Initialize scan chains and clear all buffers
    scanInit();

    // Load persistent configuration (heartbeat mode, timeout)
    configLoad();

    // Initialize stop handler (fires OFF coils to ensure known state)
    stopInit();

    // Initialize expression pedals
    expressionInit();

    // Initialize Serial MIDI input
    SERIAL_MIDI_PORT.begin(SERIAL_MIDI_BAUD);

    // Initialize display
    displayInit();

    // Set up USB MIDI handlers
    usbMIDI.setHandleNoteOn(handleNoteOn);
    usbMIDI.setHandleNoteOff(handleNoteOff);
    usbMIDI.setHandleSystemExclusive(handleSysEx);

    // Do an initial scan to populate inputBufferPrev
    scanAllChains();
    saveInputState();

    // Print debug startup info
    debugInit();
    debugPrintInputs();
    debugPrintOutputs();

    Serial.println("Organ Controller Ready");
}

// ============================================================
// Main Loop
// ============================================================

void loop() {
    // --- 0. millis() rollover guard ---
    // If millis() is within MILLIS_ROLLOVER_GUARD_MS of 0xFFFFFFFF, busy-wait
    // until it rolls over. This ensures no millis()-based timeout spans the
    // rollover boundary. Occurs ~every 49.7 days, blocks for <500ms.
    if (millis() > (0xFFFFFFFFUL - MILLIS_ROLLOVER_GUARD_MS)) {
        while (millis() > MILLIS_ROLLOVER_GUARD_MS) { }
    }

    // --- 1. Process incoming MIDI (always, for heartbeat detection) ---
    while (usbMIDI.read()) { }
    serialMidiProcess();

    // --- 2. Scan all chains (only when backlight is on / chains active) ---
    if (displayScanChainsActive()) {
        scanAllChains();
    }

    // --- 3-4. Only process organ functions when operational ---
    if (currentScreen == SCREEN_OPERATIONAL) {
        // Process inputs: compare inputBuffer to inputBufferPrev
        debugReportChanges();
        processKeyboards();
        processStopInputs();

        // Build outputBuffer from current state
        buildStopOutputs();
        debugCheckOutputChanges();
    }

    // --- 5. Save state for next comparison ---
    saveInputState();

    // --- 6. Housekeeping ---
    updateCoilPulses();
    checkStopRetries();

    if (currentScreen == SCREEN_OPERATIONAL) {
        processExpressions();
    }

    displayUpdate();
    displayProcessTouch();
}
