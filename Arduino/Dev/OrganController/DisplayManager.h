// DisplayManager.h
// TFT display (240x320 portrait) with touchscreen using TeensyUserInterface
//
// Screen State Machine:
//   SCREEN_STANDBY       - Dark screen, "Touch to start", power OFF
//   SCREEN_WAITING       - Waiting for PC, seconds counter, power ON
//   SCREEN_OPERATIONAL   - Normal operation (SysEx lines, Mem+/Mem-, Config, Shutdown)
//   SCREEN_CONFIG        - Settings (toggle/simple, heartbeat timeout)
//   SCREEN_SHUTTING_DOWN - "Shutting down..." waiting for heartbeat timeout

#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include "Config.h"
#include "ConfigData.h"

// ============================================================
// Screen States
// ============================================================

constexpr uint8_t SCREEN_STANDBY       = 0;
constexpr uint8_t SCREEN_WAITING       = 1;
constexpr uint8_t SCREEN_OPERATIONAL   = 2;
constexpr uint8_t SCREEN_CONFIG        = 3;
constexpr uint8_t SCREEN_SHUTTING_DOWN = 4;

// ============================================================
// Display Pin Configuration (Teensy 4.1 standard SPI0)
// ============================================================

constexpr int LCD_CS_PIN    = 10;
constexpr int LCD_DC_PIN    = 9;
constexpr int TOUCH_CS_PIN  = 8;

// ============================================================
// State (readable by main sketch for power control decisions)
// ============================================================

extern uint8_t currentScreen;

// ============================================================
// Functions
// ============================================================

void displayInit();
void displayUpdate();        // State machine: draw current screen, handle transitions
void displayProcessTouch();  // Handle touch input for current screen

// Called by main sketch when heartbeat MIDI is received
void displayOnHeartbeat();

// Returns true if the system should be in power-on state (screens 2-4)
bool displayPowerShouldBeOn();

// Returns true if scan chains should be active (backlight on)
bool displayScanChainsActive();

#endif // DISPLAY_MANAGER_H
