// ExpressionHandler.cpp

#include "ExpressionHandler.h"
#include "Debug.h"

static uint8_t exprLastSent[MAX_EXPRESSIONS];

void expressionInit() {
    memset(exprLastSent, 0xFF, sizeof(exprLastSent));  // Force first send
    
    for (uint8_t i = 0; i < NUM_EXPRESSIONS; i++) {
        if (exprType[i] == EXPR_ANALOG) {
            pinMode(exprAnalogPin[i], INPUT);
        }
        // Discrete inputs are already configured by scanInit()
    }
}

void processExpressions() {
    for (uint8_t i = 0; i < NUM_EXPRESSIONS; i++) {
        uint8_t value;
        
        if (exprType[i] == EXPR_ANALOG) {
            uint16_t raw = analogRead(exprAnalogPin[i]);
            value = raw >> 3;  // 10-bit to 7-bit (0-127)
            
        } else {
            // EXPR_DISCRETE: count HIGH inputs in the CWB range
            uint16_t startAddr = exprDiscreteStart[i];
            uint16_t endAddr   = exprDiscreteEnd[i];
            if (!ADDR_VALID(startAddr)) continue;
            
            uint8_t chain = ADDR_CHAIN(startAddr);
            uint16_t startBit = ADDR_WORD(startAddr) * 16 + ADDR_BIT(startAddr);
            uint16_t endBit   = ADDR_WORD(endAddr) * 16 + ADDR_BIT(endAddr);
            
            uint8_t activeCount = 0;
            for (uint16_t bitIdx = startBit; bitIdx <= endBit; bitIdx++) {
                uint8_t word = bitIdx / 16;
                uint8_t bit  = bitIdx % 16;
                if ((inputBuffer[chain][word] >> bit) & 1) {
                    activeCount++;
                }
            }
            value = activeCount;
        }
        
        // Deadband check
        int16_t diff = (int16_t)value - (int16_t)exprLastSent[i];
        if (diff == 0) continue;
        if (diff < 0 && diff > -(int16_t)exprDeadband[i]) continue;
        if (diff > 0 && diff < (int16_t)exprDeadband[i]) continue;
        
        // Send all intermediate values between old and new
        uint8_t ch = exprMidiChannel[i] + 1;  // usbMIDI 1-indexed
        uint8_t cc = exprMidiCC[i];
        
        if (exprLastSent[i] == 0xFF) {
            // First send after init — just send current value
            debugSendCC(cc, value, ch);
        } else if (value > exprLastSent[i]) {
            for (uint8_t v = exprLastSent[i] + 1; v <= value; v++) {
                debugSendCC(cc, v, ch);
            }
        } else {
            for (uint8_t v = exprLastSent[i] - 1; v != (uint8_t)(value - 1); v--) {
                debugSendCC(cc, v, ch);
            }
        }
        
        exprLastSent[i] = value;
    }
}
