#pragma once

#include "types.h"

extern void InitDisplayControl(void);
// BG mode is DISPCNT bits 0-2.
extern u32 GetDispcntMode(void);
extern void SetDispcntMode(u16 mode);
// Replaces every DISPCNT bit except the BG mode.
extern void SetDispcntExceptMode(u16 value);
