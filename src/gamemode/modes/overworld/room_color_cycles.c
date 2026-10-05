#include "types.h"
#include "graphics/palette.h"

// Rotates BG palette colors 0x08-0x0F (room 12: 0x68-0x6F) one step every
// 4 ticks.
const ColorCycleTable g_ColorCyclesDefault = { 1, 0, { { 0x08, 8, 3, PALETTE_ANIM_ACTIVE } } };
const ColorCycleTable g_ColorCyclesRoom12 = { 1, 0, { { 0x68, 8, 3, PALETTE_ANIM_ACTIVE } } };
