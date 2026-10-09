#pragma once

#include "types.h"

// Angles are 0-255 for a full turn. g_anSineTable is 16.16 fixed point.
extern const s32 g_anSineTable[256];

// Return sin/cos of angle in 8.8 fixed point.
s16 Sin8_8(u8 angle);
s16 Cos8_8(u8 angle);

// (a * b) >> 8 for 8.8 operands.
s16 Multiply8_8(s16 a, s16 b);
