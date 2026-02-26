// DisplayManager.cpp
// TFT display state machine with 5 screens.
// 240x320 portrait orientation (BOTTOM).
//
// All drawing is event-driven:
//   - Screen transitions trigger full redraw
//   - SysEx content changes trigger operational redraw
//   - Waiting counter redraws only when elapsed seconds changes
//
// Screen flow:
//   STANDBY → (touch) → WAITING → (heartbeat) → OPERATIONAL
//   OPERATIONAL → (shutdown) → SHUTTING_DOWN (toggle mode) or STANDBY (simple mode)
//   SHUTTING_DOWN → (heartbeat timeout) → STANDBY
//   OPERATIONAL → (config) → CONFIG → (back) → OPERATIONAL
//   WAITING → (shutdown) → STANDBY
//   OPERATIONAL → (heartbeat timeout, toggle mode) → WAITING

#include "DisplayManager.h"
#include "Debug.h"
#include "SysExParser.h"
#include "PersistentConfig.h"
#include "ScanChain.h"
#include "KeyboardHandler.h"
#include <TeensyUserInterface.h>
#include <font_Arial.h>

// ============================================================
// Display Dimensions (240x320 portrait)
// ============================================================

constexpr int SCREEN_W = 240;
constexpr int SCREEN_H = 320;

// ============================================================
// Display State
// ============================================================

uint8_t currentScreen = SCREEN_STANDBY;

static TeensyUserInterface ui;
static bool screenNeedsFullRedraw = true;

// ============================================================
// Colors
// ============================================================

constexpr uint16_t COLOR_BG     = 0x0000;  // Black
constexpr uint16_t COLOR_TEXT   = 0xFFFF;  // White
constexpr uint16_t COLOR_LABEL  = 0x07FF;  // Cyan
constexpr uint16_t COLOR_LINE   = 0x4208;  // Dark gray
constexpr uint16_t COLOR_WARN   = 0xFD20;  // Orange

// ============================================================
// Touch Debug Helper + X-axis correction
// ============================================================
// With PORTRAIT_4PIN_TOP, the touch X axis is mirrored relative
// to the display. Correct by remapping after each getTouchEvents().

static void correctAndLogTouch() {
    if (ui.touchEventType != TOUCH_NO_EVENT) {
        ui.touchEventX = SCREEN_W - ui.touchEventX;
        Serial.print("DBG: Touch type=");
        Serial.print(ui.touchEventType);
        Serial.print(" x=");
        Serial.print(ui.touchEventX);
        Serial.print(" y=");
        Serial.println(ui.touchEventY);
    }
}

// ============================================================
// Screen 1 (Standby) State
// ============================================================

static uint32_t standbyEnteredAt = 0;
static bool     standbyBacklightOn = false;

// ============================================================
// Screen 2 (Waiting) State
// ============================================================

static uint32_t waitingEnteredAt = 0;
static uint32_t waitingLastDrawnSeconds = 0xFFFFFFFF;  // Force first draw

static BUTTON waitingShutdownButton = {"Shutdown", 120, 285, 140, 70};

// ============================================================
// Screen 3 (Operational) State
// ============================================================
// 2x2 button grid, 110x70 each
// Row 1 y-center = 213: MEM- (left), MEM+ (right)
// Row 2 y-center = 285: Shutdown (left), Save (right)

static BUTTON memDownButton      = {"Mem -",     60, 213, 110, 70};
static BUTTON memUpButton        = {"Mem +",    180, 213, 110, 70};
static BUTTON operShutdownButton = {"Shutdown",  60, 285, 110, 70};
static BUTTON operSaveButton     = {"Save",     180, 285, 110, 70};
static BUTTON operConfigButton   = {"Config",    60, 285, 110, 70};  // hidden when HIDE_CONFIG_SCREEN

// Shutdown sequencing state
static bool     shutdownPending    = false;
static uint32_t shutdownTriggerAt  = 0;
constexpr uint32_t SHUTDOWN_DELAY_MS = 10000;

// SET indicator position (centered in the empty space between SysEx lines and buttons)
constexpr int SET_INDICATOR_X = 70;
constexpr int SET_INDICATOR_Y = 135;
constexpr int SET_INDICATOR_W = 100;
constexpr int SET_INDICATOR_H = 30;
static bool setIndicatorShown = false;

// ============================================================
// Screen 4 (Config) State
// ============================================================

static BUTTON cfgModeButton    = {"Mode",     60,  70,  110, 35};
static BUTTON cfgTimeoutUp     = {"+ ",      165, 115,   50, 35};
static BUTTON cfgTimeoutDown   = {"- ",      220, 115,   50, 35};
static BUTTON cfgStartupButton = {"Startup",  60, 185, 110, 35};
static BUTTON cfgBackButton    = {"Back",    120, 260, 140, 50};

// ============================================================
// Screen 5 (Shutting Down) State
// ============================================================

static uint32_t shuttingDownEnteredAt = 0;

// ============================================================
// Heartbeat Tracking
// ============================================================

static uint32_t lastHeartbeatAt = 0;
static bool     heartbeatEverReceived = false;

// ============================================================
// Backlight Control
// ============================================================

static void setBacklight(bool on) {
    digitalWrite(BACKLIGHT_PIN, on ? HIGH : LOW);
}

// ============================================================
// Power Supply Control
// ============================================================

static void setPowerSupply(bool on) {
    // LOW = power on, HIGH = power off
    digitalWrite(POWER_SUPPLY_PIN, on ? LOW : HIGH);
}

// ============================================================
// Screen Transition Helper
// ============================================================

static void transitionTo(uint8_t newScreen) {
    uint8_t oldScreen = currentScreen;
    currentScreen = newScreen;
    screenNeedsFullRedraw = true;

    Serial.print("DBG: Screen ");
    Serial.print(oldScreen);
    Serial.print(" -> ");
    Serial.println(newScreen);

    switch (newScreen) {
        case SCREEN_STANDBY:
            setPowerSupply(false);
            setBacklight(true);
            standbyEnteredAt = millis();
            standbyBacklightOn = true;
            break;

        case SCREEN_WAITING:
            setPowerSupply(true);
            setBacklight(true);
            waitingEnteredAt = millis();
            waitingLastDrawnSeconds = 0xFFFFFFFF;  // Force first draw
            break;

        case SCREEN_OPERATIONAL:
            setPowerSupply(true);
            setBacklight(true);
            displayDirty = true;  // Force SysEx content redraw
            setIndicatorShown = false;  // Reset SET indicator
            break;

        case SCREEN_CONFIG:
            setPowerSupply(true);
            setBacklight(true);
            break;

        case SCREEN_SHUTTING_DOWN:
            setPowerSupply(true);
            setBacklight(true);
            shuttingDownEnteredAt = millis();
            break;
    }
}

// ============================================================
// Initialization
// ============================================================

void displayInit() {
    // Power supply pin setup
    pinMode(POWER_SUPPLY_PIN, OUTPUT);
    setPowerSupply(false);  // Start with power off

    // Backlight pin setup
    pinMode(BACKLIGHT_PIN, OUTPUT);
    digitalWrite(BACKLIGHT_PIN, LOW);

    // Teensy 4.1 uses default SPI0 pins (11=MOSI, 12=MISO, 13=SCK)
    ui.begin(LCD_CS_PIN, LCD_DC_PIN, TOUCH_CS_PIN,
             LCD_ORIENTATION_PORTRAIT_4PIN_TOP, Arial_10);

    // Start on the configured startup screen
    switch (configStartupMode) {
        case STARTUP_MODE_TOUCH:
            transitionTo(SCREEN_STANDBY);
            break;
        case STARTUP_MODE_WAITPC:
            transitionTo(SCREEN_WAITING);
            break;
        case STARTUP_MODE_RUN:
        default:
            transitionTo(SCREEN_OPERATIONAL);
            break;
    }
}

// ============================================================
// Screen 1: Standby
// ============================================================

static void drawStandby() {
    if (!screenNeedsFullRedraw) return;
    screenNeedsFullRedraw = false;

    ui.lcdDrawFilledRectangle(0, 0, SCREEN_W, SCREEN_H, COLOR_BG);
    ui.lcdSetFont(Arial_10);
    ui.lcdSetFontColor(COLOR_TEXT);
    ui.lcdSetCursorXY(65, 155);
    ui.lcdPrint("Touch to start");
}

static void updateStandby() {
    // Turn off backlight after configured duration
    if (standbyBacklightOn) {
        uint32_t elapsed = (millis() - standbyEnteredAt) / 1000;
        if (elapsed >= SCREEN1_BACKLIGHT_SECONDS) {
            setBacklight(false);
            standbyBacklightOn = false;
        }
    }
}

static void touchStandby() {
    ui.getTouchEvents();
    correctAndLogTouch();
    if (ui.checkForTouchEventInRect(TOUCH_PUSHED_EVENT, 5, 5, SCREEN_W - 5, SCREEN_H - 5)) {
        transitionTo(SCREEN_WAITING);
    }
}

// ============================================================
// Screen 2: Waiting for PC
// ============================================================

static void drawWaiting() {
    uint32_t now = millis();
    uint32_t elapsedSeconds = (now - waitingEnteredAt) / 1000;

    // Full redraw on screen entry
    if (screenNeedsFullRedraw) {
        screenNeedsFullRedraw = false;

        ui.lcdDrawFilledRectangle(0, 0, SCREEN_W, SCREEN_H, COLOR_BG);

        // Title
        ui.lcdSetFont(Arial_10);
        ui.lcdSetFontColor(COLOR_LABEL);
        ui.lcdSetCursorXY(10, 5);
        ui.lcdPrint("CR Opus 52");

        ui.lcdDrawFilledRectangle(5, 22, SCREEN_W - 10, 1, COLOR_LINE);

        // Status message
        ui.lcdSetFontColor(COLOR_TEXT);
        ui.lcdSetCursorXY(25, 60);
        ui.lcdPrint("Waiting for Hauptwerk...");

        // Mode indicator
        ui.lcdSetFontColor(COLOR_LINE);
        ui.lcdSetCursorXY(20, 140);
        if (configHeartbeatMode == HEARTBEAT_MODE_TOGGLE) {
            ui.lcdPrint("Mode: Toggle (");
            ui.lcdPrint((int)configHeartbeatTimeout);
            ui.lcdPrint("s timeout)");
        } else {
            ui.lcdPrint("Mode: Simple");
        }

        // Separator and shutdown button
        ui.lcdDrawFilledRectangle(5, 245, SCREEN_W - 10, 1, COLOR_LINE);
        ui.drawButton(waitingShutdownButton);

        // Force counter draw
        waitingLastDrawnSeconds = 0xFFFFFFFF;
    }

    // Redraw elapsed counter only when the value changes
    if (elapsedSeconds != waitingLastDrawnSeconds) {
        waitingLastDrawnSeconds = elapsedSeconds;

        // Clear the counter area
        ui.lcdDrawFilledRectangle(50, 95, 140, 20, COLOR_BG);

        ui.lcdSetFont(Arial_10);
        ui.lcdSetFontColor(COLOR_LABEL);
        ui.lcdSetCursorXY(60, 100);
        ui.lcdPrint("Elapsed: ");
        ui.lcdPrint((int)elapsedSeconds);
        ui.lcdPrint("s");
    }
}

static void touchWaiting() {
    ui.getTouchEvents();
    correctAndLogTouch();

    if (ui.checkForButtonClicked(waitingShutdownButton)) {
        Serial.println("DBG: Waiting - Shutdown pressed");
        transitionTo(SCREEN_STANDBY);
    }
}

// ============================================================
// Screen 3: Operational
// ============================================================

static void drawOperational() {
    // Redraw if screen just entered or SysEx content changed
    if (!screenNeedsFullRedraw && !displayDirty) return;

    Serial.print("DBG: drawOperational screen=");
    Serial.print(currentScreen);
    Serial.print(" fullRedraw=");
    Serial.print(screenNeedsFullRedraw);
    Serial.print(" dirty=");
    Serial.println(displayDirty);

    screenNeedsFullRedraw = false;
    displayDirty = false;

    ui.lcdDrawFilledRectangle(0, 0, SCREEN_W, SCREEN_H, COLOR_BG);

    // Title
    ui.lcdSetFont(Arial_10);
    ui.lcdSetFontColor(COLOR_LABEL);
    ui.lcdSetCursorXY(10, 5);
    ui.lcdPrint("CR Opus 52");

    ui.lcdDrawFilledRectangle(5, 22, SCREEN_W - 10, 1, COLOR_LINE);

    // SysEx display lines
    int yPos = 32;
    for (uint8_t i = 0; i < NUM_DISPLAY_LINES; i++) {
        if (displayLineLCD[i] == 0xFF) continue;

        ui.lcdSetFontColor(COLOR_LABEL);
        ui.lcdSetCursorXY(10, yPos);
        if (displayLineLabel[i][0] != '\0') {
            ui.lcdPrint(displayLineLabel[i]);
            ui.lcdPrint(": ");
        }

        ui.lcdSetFontColor(COLOR_TEXT);
        if (displayLineText[i][0] != '\0') {
            ui.lcdPrint(displayLineText[i]);
        } else {
            ui.lcdPrint("---");
        }

        yPos += 28;
    }

    // Separator above buttons
    ui.lcdDrawFilledRectangle(5, 173, SCREEN_W - 10, 1, COLOR_LINE);

    // 2x2 button grid
    ui.drawButton(memDownButton);
    ui.drawButton(memUpButton);
    ui.drawButton(operShutdownButton);
    ui.drawButton(operSaveButton);
}

static void updateOperational() {
    // In toggle mode, check for heartbeat timeout → return to Waiting
    if (configHeartbeatMode == HEARTBEAT_MODE_TOGGLE && heartbeatEverReceived) {
        uint32_t elapsed = (millis() - lastHeartbeatAt) / 1000;
        if (elapsed >= configHeartbeatTimeout) {
            Serial.println("DBG: Heartbeat timeout, returning to Waiting");
            heartbeatEverReceived = false;
            transitionTo(SCREEN_WAITING);
        }
    }

    // Shutdown sequence: 10s after MIDI sent, send Alt-F4 x4 then Return
    if (shutdownPending && millis() >= shutdownTriggerAt) {
        shutdownPending = false;
        Serial.println("DBG: Sending Alt-F4 x4 + Return");
        for (uint8_t i = 0; i < 4; i++) {
            Keyboard.press(KEY_LEFT_ALT);
            Keyboard.press(KEY_F4);
            delay(50);
            Keyboard.releaseAll();
            delay(100);
        }
        Keyboard.press(KEY_RETURN);
        delay(50);
        Keyboard.releaseAll();
    }

    // SET indicator: show/hide only on state change
    if (setHeld && !setIndicatorShown) {
        ui.lcdSetFont(Arial_14);
        ui.lcdSetFontColor(COLOR_WARN);
        ui.lcdSetCursorXY(SET_INDICATOR_X + 25, SET_INDICATOR_Y + 5);
        ui.lcdPrint("SET");
        setIndicatorShown = true;
    } else if (!setHeld && setIndicatorShown) {
        ui.lcdDrawFilledRectangle(SET_INDICATOR_X, SET_INDICATOR_Y, SET_INDICATOR_W, SET_INDICATOR_H, COLOR_BG);
        setIndicatorShown = false;
    }
}

static void touchOperational() {
    ui.getTouchEvents();
    correctAndLogTouch();

    if (ui.checkForButtonClicked(memDownButton)) {
        debugSendNoteOn(MEM_DOWN_MIDI_NOTE, 127, MEM_DOWN_MIDI_CHANNEL + 1);
        debugSendNoteOff(MEM_DOWN_MIDI_NOTE, 0, MEM_DOWN_MIDI_CHANNEL + 1);
        Serial.println("DBG: Touch - Memory Down");
    }

    if (ui.checkForButtonClicked(memUpButton)) {
        debugSendNoteOn(MEM_UP_MIDI_NOTE, 127, MEM_UP_MIDI_CHANNEL + 1);
        debugSendNoteOff(MEM_UP_MIDI_NOTE, 0, MEM_UP_MIDI_CHANNEL + 1);
        Serial.println("DBG: Touch - Memory Up");
    }

    if (ui.checkForButtonClicked(operShutdownButton)) {
        debugSendNoteOn(SHUTDOWN_BUTTON_MIDI_NOTE, 127, SHUTDOWN_BUTTON_MIDI_CHANNEL + 1);
        debugSendNoteOff(SHUTDOWN_BUTTON_MIDI_NOTE, 0, SHUTDOWN_BUTTON_MIDI_CHANNEL + 1);
        shutdownPending   = true;
        uint32_t now = millis();
        shutdownTriggerAt = (now > (0xFFFFFFFFUL - SHUTDOWN_DELAY_MS)) ? 0xFFFFFFFFUL : now + SHUTDOWN_DELAY_MS;
        Serial.println("DBG: Touch - Shutdown (MIDI sent, keystrokes in 10s)");
    }

    if (!HIDE_CONFIG_SCREEN && ui.checkForButtonClicked(operConfigButton)) {
        Serial.println("DBG: Touch - Config");
        transitionTo(SCREEN_CONFIG);
    }

    if (ui.checkForButtonClicked(operSaveButton)) {
        debugSendNoteOn(SAVE_BUTTON_MIDI_NOTE, 127, SAVE_BUTTON_MIDI_CHANNEL + 1);
        debugSendNoteOff(SAVE_BUTTON_MIDI_NOTE, 0, SAVE_BUTTON_MIDI_CHANNEL + 1);
        Serial.println("DBG: Touch - Save");
    }
}

// ============================================================
// Screen 4: Configuration
// ============================================================

static const char* startupModeLabel() {
    switch (configStartupMode) {
        case STARTUP_MODE_TOUCH:  return "TouchOn";
        case STARTUP_MODE_WAITPC: return "WaitPC";
        case STARTUP_MODE_RUN:    return "RunMenu";
        default:                  return "RunMenu";
    }
}

static void drawConfig() {
    if (!screenNeedsFullRedraw) return;
    screenNeedsFullRedraw = false;

    ui.lcdDrawFilledRectangle(0, 0, SCREEN_W, SCREEN_H, COLOR_BG);

    // Title
    ui.lcdSetFont(Arial_10);
    ui.lcdSetFontColor(COLOR_LABEL);
    ui.lcdSetCursorXY(10, 5);
    ui.lcdPrint("Configuration");

    ui.lcdDrawFilledRectangle(5, 22, SCREEN_W - 10, 1, COLOR_LINE);

    // Heartbeat mode
    ui.lcdSetFontColor(COLOR_TEXT);
    ui.lcdSetCursorXY(10, 35);
    ui.lcdPrint("Heartbeat Mode:");

    if (configHeartbeatMode == HEARTBEAT_MODE_TOGGLE) {
        cfgModeButton = {"Toggle", 60, 70, 110, 35};
    } else {
        cfgModeButton = {"Simple", 60, 70, 110, 35};
    }
    ui.drawButton(cfgModeButton);

    // Timeout setting
    ui.lcdSetFontColor(COLOR_TEXT);
    ui.lcdSetCursorXY(10, 100);
    ui.lcdPrint("Heartbeat Timeout:");

    ui.lcdSetFontColor(COLOR_LABEL);
    ui.lcdSetCursorXY(10, 120);
    ui.lcdPrint((int)configHeartbeatTimeout);
    ui.lcdPrint(" seconds");

    if (configHeartbeatMode == HEARTBEAT_MODE_TOGGLE) {
        ui.drawButton(cfgTimeoutUp);
        ui.drawButton(cfgTimeoutDown);
    }

    // Startup mode
    ui.lcdDrawFilledRectangle(5, 150, SCREEN_W - 10, 1, COLOR_LINE);

    ui.lcdSetFontColor(COLOR_TEXT);
    ui.lcdSetCursorXY(10, 160);
    ui.lcdPrint("Power-On Start:");

    cfgStartupButton = {startupModeLabel(), 60, 185, 110, 35};
    ui.drawButton(cfgStartupButton);

    // Back button
    ui.lcdDrawFilledRectangle(5, 230, SCREEN_W - 10, 1, COLOR_LINE);
    ui.drawButton(cfgBackButton);
}

static void touchConfig() {
    ui.getTouchEvents();
    correctAndLogTouch();

    if (ui.checkForButtonClicked(cfgModeButton)) {
        if (configHeartbeatMode == HEARTBEAT_MODE_SIMPLE) {
            configHeartbeatMode = HEARTBEAT_MODE_TOGGLE;
        } else {
            configHeartbeatMode = HEARTBEAT_MODE_SIMPLE;
        }
        configSave();
        screenNeedsFullRedraw = true;
        Serial.print("DBG: Config mode -> ");
        Serial.println(configHeartbeatMode == HEARTBEAT_MODE_TOGGLE ? "TOGGLE" : "SIMPLE");
    }

    if (configHeartbeatMode == HEARTBEAT_MODE_TOGGLE) {
        if (ui.checkForButtonClicked(cfgTimeoutUp)) {
            if (configHeartbeatTimeout < 60) {
                configHeartbeatTimeout++;
                configSave();
                screenNeedsFullRedraw = true;
            }
        }

        if (ui.checkForButtonClicked(cfgTimeoutDown)) {
            if (configHeartbeatTimeout > 1) {
                configHeartbeatTimeout--;
                configSave();
                screenNeedsFullRedraw = true;
            }
        }
    }

    if (ui.checkForButtonClicked(cfgStartupButton)) {
        // Cycle: TouchOn -> WaitPC -> RunMenu -> TouchOn
        configStartupMode++;
        if (configStartupMode > STARTUP_MODE_RUN) {
            configStartupMode = STARTUP_MODE_TOUCH;
        }
        configSave();
        screenNeedsFullRedraw = true;
        Serial.print("DBG: Config startup -> ");
        Serial.println(startupModeLabel());
    }

    if (ui.checkForButtonClicked(cfgBackButton)) {
        Serial.println("DBG: Config - Back");
        transitionTo(SCREEN_OPERATIONAL);
    }
}

// ============================================================
// Screen 5: Shutting Down (toggle mode only)
// ============================================================

static void drawShuttingDown() {
    if (!screenNeedsFullRedraw) return;
    screenNeedsFullRedraw = false;

    ui.lcdDrawFilledRectangle(0, 0, SCREEN_W, SCREEN_H, COLOR_BG);

    ui.lcdSetFont(Arial_10);
    ui.lcdSetFontColor(COLOR_WARN);
    ui.lcdSetCursorXY(40, 120);
    ui.lcdPrint("Shutting down...");

    ui.lcdSetFontColor(COLOR_TEXT);
    ui.lcdSetCursorXY(10, 160);
    ui.lcdPrint("Waiting for Hauptwerk");
    ui.lcdSetCursorXY(60, 180);
    ui.lcdPrint("to stop");
}

static void updateShuttingDown() {
    // Wait for heartbeat to timeout, then go to standby
    uint32_t elapsed = (millis() - lastHeartbeatAt) / 1000;

    // If we never received a heartbeat, or timeout has elapsed
    if (!heartbeatEverReceived || elapsed >= configHeartbeatTimeout) {
        Serial.println("DBG: Shutting down - heartbeat timed out, entering standby");
        heartbeatEverReceived = false;
        transitionTo(SCREEN_STANDBY);
    }
}

// ============================================================
// Public: Heartbeat Reception
// ============================================================

void displayOnHeartbeat() {
    lastHeartbeatAt = millis();
    heartbeatEverReceived = true;

    // If we're on the Waiting screen, transition to Operational
    if (currentScreen == SCREEN_WAITING) {
        Serial.println("DBG: Heartbeat received, entering Operational");
        transitionTo(SCREEN_OPERATIONAL);
    }

    // If we're shutting down and a heartbeat arrives, reset the timer
    // (the timeout check in updateShuttingDown will handle transition)
}

// ============================================================
// Public: Power State Query
// ============================================================

bool displayPowerShouldBeOn() {
    return currentScreen != SCREEN_STANDBY;
}

bool displayScanChainsActive() {
    // Scan chains are active whenever backlight is on.
    // In standby, backlight turns off after timeout; all other screens keep it on.
    if (currentScreen != SCREEN_STANDBY) return true;
    return standbyBacklightOn;
}

// ============================================================
// Public: Display Update (call from main loop)
// ============================================================

void displayUpdate() {
    switch (currentScreen) {
        case SCREEN_STANDBY:
            drawStandby();
            updateStandby();
            break;
        case SCREEN_WAITING:
            drawWaiting();
            break;
        case SCREEN_OPERATIONAL:
            drawOperational();
            updateOperational();
            break;
        case SCREEN_CONFIG:
            drawConfig();
            break;
        case SCREEN_SHUTTING_DOWN:
            drawShuttingDown();
            updateShuttingDown();
            break;
    }
}

// ============================================================
// Public: Touch Processing (call from main loop)
// ============================================================

void displayProcessTouch() {
    switch (currentScreen) {
        case SCREEN_STANDBY:
            touchStandby();
            break;
        case SCREEN_WAITING:
            touchWaiting();
            break;
        case SCREEN_OPERATIONAL:
            touchOperational();
            break;
        case SCREEN_CONFIG:
            touchConfig();
            break;
        case SCREEN_SHUTTING_DOWN:
            // No touch interaction while shutting down
            break;
    }
}
