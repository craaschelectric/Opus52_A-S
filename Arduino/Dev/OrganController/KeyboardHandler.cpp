// KeyboardHandler.cpp
// Keyboard and piston input processing with SHIFT and SET support.
//
// SHIFT behavior:
//   - SHIFT held + another input pressed → that input sends on channel + 8
//   - SHIFT pressed and released alone → sends its own noteOn then noteOff
//   - NoteOff always uses the same channel the noteOn was sent on
//
// SET behavior:
//   - NoteOn on press, NoteOff on release
//   - setHeld flag read by DisplayManager for on-screen indicator

#include "KeyboardHandler.h"
#include "Debug.h"

// ============================================================
// SHIFT State
// ============================================================

static bool shiftHeld = false;
static bool shiftConsumed = false;  // True if another input was pressed while SHIFT held

// Track which channel offset each key was pressed with, so noteOff matches.
static uint16_t pressedShifted[MAX_CHAINS][WORDS_PER_CHAIN];

// ============================================================
// SET State
// ============================================================

bool setHeld = false;

// ============================================================
// Helpers
// ============================================================

static inline void setShiftedFlag(uint8_t chain, uint8_t word, uint8_t bit, bool shifted) {
    if (shifted)
        pressedShifted[chain][word] |= (1 << bit);
    else
        pressedShifted[chain][word] &= ~(1 << bit);
}

static inline bool getShiftedFlag(uint8_t chain, uint8_t word, uint8_t bit) {
    return (pressedShifted[chain][word] >> bit) & 1;
}

// Check if a bit index matches a special-purpose input address on the given chain
static inline bool isSpecialInput(uint8_t chain, uint16_t bitIdx, uint16_t addr) {
    if (!ADDR_VALID(addr)) return false;
    if (chain != ADDR_CHAIN(addr)) return false;
    return bitIdx == (ADDR_WORD(addr) * 16 + ADDR_BIT(addr));
}

// ============================================================
// Process Keyboards (and pistons, SHIFT, SET)
// ============================================================

void processKeyboards() {
    // --- Step 1: Update SHIFT state ---
    if (ADDR_VALID(SHIFT_INPUT_ADDR) && inputChanged(SHIFT_INPUT_ADDR)) {
        bool pressed = readInput(SHIFT_INPUT_ADDR);
        
        if (pressed) {
            shiftHeld = true;
            shiftConsumed = false;
        } else {
            // SHIFT released
            if (!shiftConsumed) {
                uint8_t ch = SHIFT_MIDI_CHANNEL + 1;
                debugSendNoteOn(SHIFT_MIDI_NOTE, 127, ch);
                debugSendNoteOff(SHIFT_MIDI_NOTE, 0, ch);
            }
            shiftHeld = false;
            shiftConsumed = false;
        }
    }
    
    // --- Step 2: Update SET state ---
    if (ADDR_VALID(SET_INPUT_ADDR) && inputChanged(SET_INPUT_ADDR)) {
        bool pressed = readInput(SET_INPUT_ADDR);
        uint8_t ch = SET_MIDI_CHANNEL + 1;
        
        if (pressed) {
            setHeld = true;
            debugSendNoteOn(SET_MIDI_NOTE, 127, ch);
            Serial.println("DBG: SET pressed");
        } else {
            setHeld = false;
            debugSendNoteOff(SET_MIDI_NOTE, 0, ch);
            Serial.println("DBG: SET released");
        }
    }
    
    // --- Step 3: Process all keyboard/piston ranges ---
    for (uint8_t k = 0; k < NUM_KEYBOARDS; k++) {
        uint8_t chain = kbdChain[k];
        
        for (uint16_t bitIdx = kbdStartBit[k]; bitIdx <= kbdEndBit[k]; bitIdx++) {
            // Skip special-purpose inputs — handled in Steps 1-2
            if (isSpecialInput(chain, bitIdx, SHIFT_INPUT_ADDR)) continue;
            if (isSpecialInput(chain, bitIdx, SET_INPUT_ADDR)) continue;

            uint8_t word = bitIdx / 16;
            uint8_t bit  = bitIdx % 16;
            
            bool current  = (inputBuffer[chain][word] >> bit) & 1;
            bool previous = (inputBufferPrev[chain][word] >> bit) & 1;
            
            if (current == previous) continue;
            
            uint8_t midiNote = kbdLowNote[k] + (bitIdx - kbdStartBit[k]);
            uint8_t baseCh = kbdMidiChannel[k];
            
            // 1 = on/pressed, 0 = off/released
            if (current && !previous) {
                // Key/piston pressed
                bool shifted = shiftHeld;
                if (shifted) shiftConsumed = true;
                
                setShiftedFlag(chain, word, bit, shifted);
                
                uint8_t ch = baseCh + (shifted ? SHIFT_CHANNEL_OFFSET : 0) + 1;
                debugSendNoteOn(midiNote, kbdVelocity[k], ch);
                
            } else {
                // Key/piston released — use the channel it was pressed on
                bool wasShifted = getShiftedFlag(chain, word, bit);
                uint8_t ch = baseCh + (wasShifted ? SHIFT_CHANNEL_OFFSET : 0) + 1;
                debugSendNoteOff(midiNote, 0, ch);
            }
        }
    }
}
