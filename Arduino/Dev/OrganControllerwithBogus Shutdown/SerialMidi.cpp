// SerialMidi.cpp
// Serial MIDI input → USB MIDI forwarding
// Parses raw MIDI byte stream, forwards noteOn, noteOff, CC to usbMIDI.

#include "SerialMidi.h"

static uint8_t midiState = 0;
static uint8_t midiData[2];
static uint8_t midiDataIdx = 0;
static uint8_t midiDataNeeded = 0;

void serialMidiProcess() {
    while (SERIAL_MIDI_PORT.available()) {
        uint8_t byte = SERIAL_MIDI_PORT.read();
        
        if (byte & 0x80) {
            if (byte >= 0xF8) continue;          // Real-time: ignore
            if (byte >= 0xF0) {                   // System common: reset
                midiState = 0;
                midiDataIdx = 0;
                continue;
            }
            midiState = byte;
            midiDataIdx = 0;
            uint8_t cmd = byte & 0xF0;
            midiDataNeeded = (cmd == 0xC0 || cmd == 0xD0) ? 1 : 2;
        } else {
            if (midiState == 0) continue;
            midiData[midiDataIdx++] = byte;
            
            if (midiDataIdx >= midiDataNeeded) {
                uint8_t cmd = midiState & 0xF0;
                uint8_t ch  = (midiState & 0x0F) + 1;
                
                switch (cmd) {
                    case 0x90:  // Note On
                        if (midiData[1] == 0) {
                            usbMIDI.sendNoteOff(midiData[0], 0, ch);
                            Serial.print("DBG: SerMIDI NoteOff ch=");
                            Serial.print(ch); Serial.print(" note=");
                            Serial.println(midiData[0]);
                        } else {
                            usbMIDI.sendNoteOn(midiData[0], midiData[1], ch);
                            Serial.print("DBG: SerMIDI NoteOn ch=");
                            Serial.print(ch); Serial.print(" note=");
                            Serial.print(midiData[0]); Serial.print(" vel=");
                            Serial.println(midiData[1]);
                        }
                        break;
                    case 0x80:  // Note Off
                        usbMIDI.sendNoteOff(midiData[0], midiData[1], ch);
                        Serial.print("DBG: SerMIDI NoteOff ch=");
                        Serial.print(ch); Serial.print(" note=");
                        Serial.println(midiData[0]);
                        break;
                    case 0xB0:  // CC
                        usbMIDI.sendControlChange(midiData[0], midiData[1], ch);
                        Serial.print("DBG: SerMIDI CC ch=");
                        Serial.print(ch); Serial.print(" cc=");
                        Serial.print(midiData[0]); Serial.print(" val=");
                        Serial.println(midiData[1]);
                        break;
                }
                midiDataIdx = 0;  // Reset for running status
            }
        }
    }
}
