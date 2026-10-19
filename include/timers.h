#pragma once

#include "types.h"

// Four timers, each stepped once per TickGameTimer call. Only the startup
// reset has callers; none were found for the tick or the
// start/pause/resume/get functions.
typedef enum {
    GameTimerStopped   = 0,  // TickGameTimer returns 1
    GameTimerCountDown = 1,  // dwValue decrements; TickGameTimer returns 1 once it is 0
    GameTimerCountUp   = 2,  // dwValue increments every tick
} GameTimerMode;

typedef struct GameTimer {
    u32 dwIndex;       // 0x00, the slot's own index
    u32 dwMode;        // 0x04, GameTimerMode
    u8 fPaused : 1;    // 0x08, TickGameTimer leaves dwValue alone while set
    u32 dwValue;       // 0x0C
} GameTimer;

extern GameTimer g_aGameTimers[4];

extern u32 TickGameTimer(u32 index);
extern void ResetAllGameTimers(void);
extern void ResetGameTimer(u32 index);
extern void StartGameTimerCountDown(u32 index, u32 ticks);
extern void StartGameTimerCountUp(u32 index);
extern void PauseGameTimer(u32 index);
extern void ResumeGameTimer(u32 index);
extern u32 GetGameTimerValue(u32 index);
