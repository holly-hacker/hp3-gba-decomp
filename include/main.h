#pragma once

#include "types.h"

// A broad game-mode-state flags word touched by dozens of functions across
// overworld/room/cutscene transitions.
extern u32 g_dwGameModeFlags;
// Read only by WaitForVBlank and written only by AgbMain: the frame-pacing
// target WaitForVBlank busy-waits up to.
extern u32 g_dwFrameSyncTarget;

extern void WaitForVBlank(void);
