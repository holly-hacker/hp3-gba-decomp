#include "math.h"

// Turns a 32-step direction one step toward target, taking the shorter way
// (counter-clockwise when already there), and stores the step taken.
u8 StepDirection32Toward(u8 direction, u8 target, s8 *pStep)
{
    if (((direction - target) & 0x1F) <= 16)
        *pStep = -1;
    else
        *pStep = 1;

    direction += *pStep;
    if (direction < 32)
        return direction;
    if (direction == 32)
        return 0;
    return 31;
}
