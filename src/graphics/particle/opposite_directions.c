#include "types.h"
#include "graphics/graphics.h"
#include "graphics/object.h"

// The reverse of each Direction and Direction4; a directional particle
// travels away from its emitter's facing.
const u8 g_abOppositeDirection8[8] = {
    DirectionDown, DirectionDownLeft, DirectionLeft, DirectionUpLeft,
    DirectionUp, DirectionUpRight, DirectionRight, DirectionDownRight,
};

const u8 g_abOppositeDirection4[4] = {
    Direction4Down, Direction4Left, Direction4Up, Direction4Right,
};
