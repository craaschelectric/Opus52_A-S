// Debug.h
// USB Serial debug output for scan chain diagnostics
//
// Provides:
//   debugInit()          - Print startup banner
//   debugPrintInputs()   - Print full inputBuffer for all active chains
//   debugPrintOutputs()  - Print full outputBuffer for all active chains
//   debugReportChange()  - Print CWB address of changed input bit
//   debugCheckOutputs()  - Detect and print outputBuffer changes

#ifndef DEBUG_H
#define DEBUG_H

#include "Config.h"
#include "ConfigData.h"
#include "ScanChain.h"

// Enable/disable debug output at compile time
#define DEBUG_ENABLED 1

#if DEBUG_ENABLED

void debugInit();
void debugPrintInputs();
void debugPrintOutputs();
void debugReportChanges();     // Print CWB of every changed input bit
void debugCheckOutputChanges(); // Compare outputBuffer to saved copy, print if changed

// MIDI send wrappers — log all outgoing USB MIDI
inline void debugSendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel) {
    Serial.print("MIDI TX: NoteOn  ch=");
    Serial.print(channel);
    Serial.print(" note=");
    Serial.print(note);
    Serial.print(" vel=");
    Serial.println(velocity);
    usbMIDI.sendNoteOn(note, velocity, channel);
}

inline void debugSendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel) {
    Serial.print("MIDI TX: NoteOff ch=");
    Serial.print(channel);
    Serial.print(" note=");
    Serial.println(note);
    usbMIDI.sendNoteOff(note, velocity, channel);
}

inline void debugSendCC(uint8_t cc, uint8_t value, uint8_t channel) {
    Serial.print("MIDI TX: CC      ch=");
    Serial.print(channel);
    Serial.print(" cc=");
    Serial.print(cc);
    Serial.print(" val=");
    Serial.println(value);
    usbMIDI.sendControlChange(cc, value, channel);
}

#else

inline void debugInit() {}
inline void debugPrintInputs() {}
inline void debugPrintOutputs() {}
inline void debugReportChanges() {}
inline void debugCheckOutputChanges() {}

// Pass-through without logging when debug disabled
inline void debugSendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel) {
    usbMIDI.sendNoteOn(note, velocity, channel);
}
inline void debugSendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel) {
    usbMIDI.sendNoteOff(note, velocity, channel);
}
inline void debugSendCC(uint8_t cc, uint8_t value, uint8_t channel) {
    usbMIDI.sendControlChange(cc, value, channel);
}

#endif

#endif // DEBUG_H
