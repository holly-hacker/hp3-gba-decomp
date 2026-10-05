#pragma once

#include "types.h"

// Four timers, each stepped once per call of the tick function at
// US 0x08042DC8. That tick and the control functions after ResetGameTimer
// (0x08042E70-0x08042F04) have no callers found, so only the startup reset
// runs.
typedef enum {
    GameTimerStopped   = 0,  // the tick returns 1
    GameTimerCountDown = 1,  // dwValue decrements; the tick returns 1 once it reaches 0
    GameTimerCountUp   = 2,  // dwValue increments every tick
} GameTimerMode;

typedef struct GameTimer {
    u32 dwIndex;       // 0x00, the slot's own index
    u32 dwMode;        // 0x04, GameTimerMode
    u8 fPaused : 1;    // 0x08, the tick leaves dwValue alone while set
    u32 dwValue;       // 0x0C
} GameTimer;

extern GameTimer g_aGameTimers[4];

extern void ResetAllGameTimers(void);
extern void ResetGameTimer(u32 index);
