#include "camera.h"

// Pan step: moves the focus step units along the 32-way angle toward target, or snaps
// onto it once the direction to it is DirectionNone (within step on both axes).
u8 MoveCameraFocusToward(FixedPoint target, s32 step, u8 slot)
{
    u8 direction;
    FixedPoint move;
    FixedPoint delta;

    if (g_aCameraFocusSlots[slot].focus.y > target.y + step)
    {
        if (g_aCameraFocusSlots[slot].focus.x > target.x + step)
            direction = DirectionUpLeft;
        else if (g_aCameraFocusSlots[slot].focus.x < target.x - step)
            direction = DirectionUpRight;
        else
            direction = DirectionUp;
    }
    else if (g_aCameraFocusSlots[slot].focus.y < target.y - step)
    {
        if (g_aCameraFocusSlots[slot].focus.x > target.x + step)
            direction = DirectionDownLeft;
        else if (g_aCameraFocusSlots[slot].focus.x < target.x - step)
            direction = DirectionDownRight;
        else
            direction = DirectionDown;
    }
    else
    {
        if (g_aCameraFocusSlots[slot].focus.x > target.x + step)
            direction = DirectionLeft;
        else if (g_aCameraFocusSlots[slot].focus.x < target.x - step)
            direction = DirectionRight;
        else
            direction = DirectionNone;
    }

    if (direction != DirectionNone)
    {
        delta.x = target.x - g_aCameraFocusSlots[slot].focus.x;
        delta.y = target.y - g_aCameraFocusSlots[slot].focus.y;
        direction = GetDirection32FromVector(delta);
        move.x = FixedMultiply(g_aDirection32Vectors[direction][0], step);
        move.y = FixedMultiply(g_aDirection32Vectors[direction][1], step);
        g_aCameraFocusSlots[slot].focus.x += move.x;
        g_aCameraFocusSlots[slot].focus.y += move.y;
        g_aCameraFocusSlots[slot].latched = g_aCameraFocusSlots[slot].focus;
        direction = 0;
    }
    else
    {
        g_aCameraFocusSlots[slot].focus.x = target.x;
        g_aCameraFocusSlots[slot].focus.y = target.y;
    }

    return direction;
}
