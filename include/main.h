#pragma once

#include "types.h"

// GameModeFlags (modes.h) bits, set and tested across mode, room and screen transitions.
extern u32 g_dwGameModeFlags;
// Read only by WaitForVBlank and written only by AgbMain: the frame-pacing
// target WaitForVBlank busy-waits up to.
extern u32 g_dwFrameSyncTarget;

extern void WaitForVBlank(void);
