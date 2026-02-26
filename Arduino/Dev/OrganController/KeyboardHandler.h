// KeyboardHandler.h
// Detects key/piston changes in inputBuffer vs inputBufferPrev, sends MIDI notes.
// Supports a SHIFT piston: when held, other inputs send on channel + 8.
// If SHIFT pressed and released alone, sends its own noteOn/noteOff.
// Supports a SET piston: sends NoteOn on press, NoteOff on release.

#ifndef KEYBOARD_HANDLER_H
#define KEYBOARD_HANDLER_H

#include "Config.h"
#include "ConfigData.h"
#include "ScanChain.h"

// True while the SET piston is physically held down.
// Read by DisplayManager to show/hide "SET" indicator.
extern bool setHeld;

void processKeyboards();

#endif // KEYBOARD_HANDLER_H
