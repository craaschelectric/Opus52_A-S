// SerialMidi.h
// Serial MIDI input → USB MIDI forwarding (noteOn, noteOff, CC only)

#ifndef SERIAL_MIDI_H
#define SERIAL_MIDI_H

#include "Config.h"

void serialMidiProcess();  // Call from main loop

#endif // SERIAL_MIDI_H
