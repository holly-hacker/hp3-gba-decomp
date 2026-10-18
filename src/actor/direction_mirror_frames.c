#include "types.h"

// Sprite frame for each direction, counted from Up toward Down, so the left half
// reuses the right half's frames flipped. Not referenced by any code.
const u8 g_abDirection8MirrorFrames[8] = { 0, 1, 2, 3, 4, 3, 2, 1 };

const u8 g_abDirection16MirrorFrames[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 7, 6, 5, 4, 3, 2, 1 };

const u8 g_abDirection32MirrorFrames[32] = {
    0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4,
    4, 4, 3, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0,
};
