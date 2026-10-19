#pragma once

#include "types.h"

// None of these LCD helpers has a caller in the ROM.
extern u32 IsInVBlank(void);
extern u16 IsForcedBlank(void);
extern void WaitForVBlankFlag(void);
extern void DisableForcedBlank(void);
extern void EnableForcedBlank(void);
extern void DisableForcedBlankAtVBlank(void);
extern void EnableForcedBlankAtVBlank(void);
