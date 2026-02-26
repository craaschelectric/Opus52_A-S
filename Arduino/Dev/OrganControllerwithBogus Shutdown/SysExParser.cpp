// SysExParser.cpp

#include "SysExParser.h"
#include <string.h>

char displayLineText[NUM_DISPLAY_LINES][32];
bool displayDirty = false;

bool parseSysEx(const uint8_t *data, uint16_t length) {
    // Hauptwerk format: F0 7D 01 <lcd#> 00 <ascii...> F7
    // Teensy passes full message including F0 and F7.
    // Skip F0 prefix if present.
    if (length > 0 && data[0] == 0xF0) {
        data++;
        length--;
    }
    // Strip F7 suffix if present
    if (length > 0 && data[length - 1] == 0xF7) {
        length--;
    }

    // Hauptwerk format after stripping F0/F7:
    //   data[0]=7D  data[1]=01  data[2]=00  data[3]=<lcd#>  data[4]=00  data[5+]=<ascii>

    if (length < 6) return false;
    if (data[0] != HW_SYSEX_MFG_ID) return false;
    if (data[1] != HW_SYSEX_MSG_TYPE) return false;

    uint8_t lcdNum = data[3];
    bool matched = false;
    
    // Check each display line config to see if this LCD number matches
    for (uint8_t line = 0; line < NUM_DISPLAY_LINES; line++) {
        if (displayLineLCD[line] == 0xFF) continue;  // Line not configured
        if (lcdNum != displayLineLCD[line]) continue;
        
        // Extract text at the configured offset
        uint8_t start = displayLineOffset[line];
        uint8_t len = displayLineLen[line];
        
        if (start >= length) continue;
        if (start + len > length) len = length - start;
        if (len > 31) len = 31;
        
        // Copy and null-terminate
        char newText[32];
        memcpy(newText, &data[start], len);
        newText[len] = '\0';
        
        // Trim trailing spaces
        while (len > 0 && newText[len - 1] == ' ') {
            newText[--len] = '\0';
        }

        // Ignore empty messages entirely — don't store or trigger redraw
        if (len == 0) continue;
        
        // Only mark dirty if text actually changed
        if (strcmp(newText, displayLineText[line]) != 0) {
            memcpy(displayLineText[line], newText, len + 1);

            Serial.print("DBG: SysEx line ");
            Serial.print(line);
            Serial.print(" lcd=0x");
            if (lcdNum < 0x10) Serial.print('0');
            Serial.print(lcdNum, HEX);
            Serial.print(" text=\"");
            Serial.print(displayLineText[line]);
            Serial.print("\" len=");
            Serial.println(len);

            // Only trigger redraw if at least one line has content
            displayDirty = true;
        }
        
        matched = true;
    }
    
    return matched;
}
