#include "types.h"
#include "graphics/oam.h"

const OamShapeSize g_aOamShapeSizes[3][4] = {
    // square
    { { 8, 8, 0x20 }, { 16, 16, 0x80 }, { 32, 32, 0x200 }, { 64, 64, 0x800 } },
    // horizontal
    { { 16, 8, 0x40 }, { 32, 8, 0x80 }, { 32, 16, 0x100 }, { 64, 32, 0x400 } },
    // vertical
    { { 8, 16, 0x40 }, { 8, 32, 0x80 }, { 16, 32, 0x100 }, { 32, 64, 0x400 } },
};
