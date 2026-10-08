#include "types.h"
#include "graphics/graphics.h"

// OAM size and shape for a sprite of each width and height, indexed
// [height][width] with 0-3 for 8, 16, 32 and 64 pixels. Pairs that have no OAM
// shape map to size 0, shape 0.
const u8 g_abOamSizeForDims[4][4] = {
    { 0, 0, 1, 0 },
    { 0, 1, 2, 0 },
    { 1, 2, 2, 3 },
    { 0, 0, 3, 3 },
};

const u8 g_abOamShapeForDims[4][4] = {
    { 0, 1, 1, 0 },
    { 2, 0, 1, 0 },
    { 2, 2, 0, 1 },
    { 2, 2, 2, 0 },
};
