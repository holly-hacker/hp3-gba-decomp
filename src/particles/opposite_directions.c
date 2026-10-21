#include "types.h"
#include "particles.h"
#include "math.h"

// The reverse of each Direction and Direction4; a directional particle
// travels away from its emitter's facing.
const u8 g_abOppositeDirection8[8] = {
    DirectionDown, DirectionDownLeft, DirectionLeft, DirectionUpLeft,
    DirectionUp, DirectionUpRight, DirectionRight, DirectionDownRight,
};

const u8 g_abOppositeDirection4[4] = {
    Direction4Down, Direction4Left, Direction4Up, Direction4Right,
};

// Each Direction with its diagonals mirrored left-right and the four
// cardinals kept. No reader was found.
const u8 g_abUnusedDiagonalMirror8[8] = {
    DirectionUp, DirectionUpLeft, DirectionRight, DirectionDownLeft,
    DirectionDown, DirectionDownRight, DirectionLeft, DirectionUpRight,
};
