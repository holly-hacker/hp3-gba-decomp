#pragma once

#include "types.h"

extern void WaitForVBlank(void);

// See ram_symbols.us.inc: 0x03003B48, read only by WaitForVBlank and
// written only by AgbMain -- the frame-pacing target WaitForVBlank busy-waits up to.
extern u32 g_dwFrameSyncTarget;
