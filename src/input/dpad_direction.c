#include "input.h"

const s8 g_abDpadDirection[16] = {
    DirectionNone,       // none
    DirectionRight,      // right
    DirectionLeft,       // left
    DirectionNone,       // right+left
    DirectionUp,         // up
    DirectionUpRight,    // up+right
    DirectionUpLeft,     // up+left
    DirectionNone,       // up+right+left
    DirectionDown,       // down
    DirectionDownRight,  // down+right
    DirectionDownLeft,   // down+left
    DirectionNone,       // down+right+left
    DirectionNone,       // down+up
    DirectionNone,       // down+up+right
    DirectionNone,       // down+up+left
    DirectionNone,       // all four
};
