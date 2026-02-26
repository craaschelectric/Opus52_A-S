// PersistentConfig.h
// EEPROM-backed persistent configuration
// Stores heartbeat mode (toggle/simple) and timeout duration.
// Uses a magic byte to detect blank/uninitialized EEPROM.

#ifndef PERSISTENT_CONFIG_H
#define PERSISTENT_CONFIG_H

#include <Arduino.h>
#include <EEPROM.h>

// ============================================================
// Heartbeat Mode
// ============================================================

constexpr uint8_t HEARTBEAT_MODE_SIMPLE = 0;
constexpr uint8_t HEARTBEAT_MODE_TOGGLE = 1;

// ============================================================
// Startup Mode
// ============================================================

constexpr uint8_t STARTUP_MODE_TOUCH   = 0;  // Screen 1: Standby, touch to start
constexpr uint8_t STARTUP_MODE_WAITPC  = 1;  // Screen 2: Waiting for PC
constexpr uint8_t STARTUP_MODE_RUN     = 2;  // Screen 3: Operational immediately

// ============================================================
// Defaults (used when EEPROM is blank)
// ============================================================

constexpr uint8_t  DEFAULT_HEARTBEAT_MODE    = HEARTBEAT_MODE_SIMPLE;
constexpr uint8_t  DEFAULT_HEARTBEAT_TIMEOUT = 5;  // seconds
constexpr uint8_t  DEFAULT_STARTUP_MODE      = STARTUP_MODE_RUN;

// ============================================================
// EEPROM Layout
// ============================================================

constexpr uint16_t EEPROM_ADDR_MAGIC       = 0;
constexpr uint16_t EEPROM_ADDR_HB_MODE     = 1;
constexpr uint16_t EEPROM_ADDR_HB_TIMEOUT  = 2;
constexpr uint16_t EEPROM_ADDR_STARTUP     = 3;
constexpr uint8_t  EEPROM_MAGIC_VALUE      = 0xA5;

// ============================================================
// Runtime State (loaded at boot)
// ============================================================

extern uint8_t configHeartbeatMode;     // HEARTBEAT_MODE_SIMPLE or HEARTBEAT_MODE_TOGGLE
extern uint8_t configHeartbeatTimeout;  // seconds
extern uint8_t configStartupMode;       // STARTUP_MODE_TOUCH, STARTUP_MODE_WAITPC, or STARTUP_MODE_RUN

// ============================================================
// Functions
// ============================================================

void configLoad();   // Read from EEPROM (writes defaults if blank)
void configSave();   // Write current values to EEPROM

#endif // PERSISTENT_CONFIG_H
