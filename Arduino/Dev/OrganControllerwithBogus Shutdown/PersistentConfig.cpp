// PersistentConfig.cpp

#include "PersistentConfig.h"

uint8_t configHeartbeatMode    = DEFAULT_HEARTBEAT_MODE;
uint8_t configHeartbeatTimeout = DEFAULT_HEARTBEAT_TIMEOUT;
uint8_t configStartupMode     = DEFAULT_STARTUP_MODE;

void configLoad() {
    uint8_t magic = EEPROM.read(EEPROM_ADDR_MAGIC);
    
    if (magic != EEPROM_MAGIC_VALUE) {
        // EEPROM is blank or corrupted — write defaults
        configHeartbeatMode    = DEFAULT_HEARTBEAT_MODE;
        configHeartbeatTimeout = DEFAULT_HEARTBEAT_TIMEOUT;
        configStartupMode     = DEFAULT_STARTUP_MODE;
        configSave();
        Serial.println("DBG: EEPROM blank, wrote defaults");
        return;
    }
    
    configHeartbeatMode    = EEPROM.read(EEPROM_ADDR_HB_MODE);
    configHeartbeatTimeout = EEPROM.read(EEPROM_ADDR_HB_TIMEOUT);
    configStartupMode     = EEPROM.read(EEPROM_ADDR_STARTUP);
    
    // Sanity checks
    if (configHeartbeatMode > HEARTBEAT_MODE_TOGGLE) {
        configHeartbeatMode = DEFAULT_HEARTBEAT_MODE;
    }
    if (configHeartbeatTimeout == 0 || configHeartbeatTimeout > 60) {
        configHeartbeatTimeout = DEFAULT_HEARTBEAT_TIMEOUT;
    }
    if (configStartupMode > STARTUP_MODE_RUN) {
        configStartupMode = DEFAULT_STARTUP_MODE;
    }
    
    Serial.print("DBG: Config loaded - mode=");
    Serial.print(configHeartbeatMode == HEARTBEAT_MODE_TOGGLE ? "TOGGLE" : "SIMPLE");
    Serial.print(" timeout=");
    Serial.print(configHeartbeatTimeout);
    Serial.print("s startup=");
    Serial.println(configStartupMode == STARTUP_MODE_TOUCH ? "TOUCH" :
                   configStartupMode == STARTUP_MODE_WAITPC ? "WAITPC" : "RUN");
}

void configSave() {
    EEPROM.write(EEPROM_ADDR_MAGIC, EEPROM_MAGIC_VALUE);
    EEPROM.write(EEPROM_ADDR_HB_MODE, configHeartbeatMode);
    EEPROM.write(EEPROM_ADDR_HB_TIMEOUT, configHeartbeatTimeout);
    EEPROM.write(EEPROM_ADDR_STARTUP, configStartupMode);
    
    Serial.print("DBG: Config saved - mode=");
    Serial.print(configHeartbeatMode == HEARTBEAT_MODE_TOGGLE ? "TOGGLE" : "SIMPLE");
    Serial.print(" timeout=");
    Serial.print(configHeartbeatTimeout);
    Serial.print("s startup=");
    Serial.println(configStartupMode == STARTUP_MODE_TOUCH ? "TOUCH" :
                   configStartupMode == STARTUP_MODE_WAITPC ? "WAITPC" : "RUN");
}
