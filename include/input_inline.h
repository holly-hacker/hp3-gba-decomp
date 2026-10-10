#pragma once

#include "input.h"

// The ROM compiles StepCursorByKeys into each key-specific variant, and
// the variants into the StepScroll* functions, and also keeps an out-of-line
// copy of each, as one translation unit with inline definitions would. The
// files that emit the out-of-line copies define the linkage macro as empty.
#ifndef STEP_CURSOR_BY_KEYS_LINKAGE
#define STEP_CURSOR_BY_KEYS_LINKAGE extern inline
#endif
#ifndef STEP_CURSOR_UP_DOWN_HELD_LINKAGE
#define STEP_CURSOR_UP_DOWN_HELD_LINKAGE extern inline
#endif
#ifndef STEP_CURSOR_UP_DOWN_LINKAGE
#define STEP_CURSOR_UP_DOWN_LINKAGE extern inline
#endif
#ifndef STEP_CURSOR_LEFT_RIGHT_HELD_LINKAGE
#define STEP_CURSOR_LEFT_RIGHT_HELD_LINKAGE extern inline
#endif
#ifndef STEP_CURSOR_LEFT_RIGHT_LINKAGE
#define STEP_CURSOR_LEFT_RIGHT_LINKAGE extern inline
#endif
#ifndef STEP_CURSOR_SHOULDER_HELD_LINKAGE
#define STEP_CURSOR_SHOULDER_HELD_LINKAGE extern inline
#endif
#ifndef STEP_CURSOR_SHOULDER_LINKAGE
#define STEP_CURSOR_SHOULDER_LINKAGE extern inline
#endif

STEP_CURSOR_BY_KEYS_LINKAGE
u32 StepCursorByKeys(u32 *pValue, u32 min, u32 max, s32 wrap, u16 keys, u16 decrementKeys, u16 incrementKeys)
{
    u32 changed = 1;

    if (keys & decrementKeys)
    {
        if (*pValue <= min)
        {
            if (wrap)
                *pValue = max;
            else
                changed = 0;
        }
        else
        {
            (*pValue)--;
        }
    }
    else if (keys & incrementKeys)
    {
        if (*pValue >= max)
        {
            if (wrap)
                *pValue = min;
            else
                changed = 0;
        }
        else
        {
            (*pValue)++;
        }
    }
    else
    {
        changed = 0;
    }
    return changed;
}

STEP_CURSOR_UP_DOWN_HELD_LINKAGE
u32 StepCursorUpDownHeld(u32 *pValue, u32 min, u32 max, s32 wrap, u32 player)
{
    return StepCursorByKeys(pValue, min, max, wrap, g_awPlayerKeysHeld[player], KeyUp, KeyDown);
}

STEP_CURSOR_UP_DOWN_LINKAGE
u32 StepCursorUpDown(u32 *pValue, u32 min, u32 max, s32 wrap, u32 player)
{
    return StepCursorByKeys(pValue, min, max, wrap, g_awPlayerKeysPressed[player], KeyUp, KeyDown);
}

STEP_CURSOR_LEFT_RIGHT_HELD_LINKAGE
u32 StepCursorLeftRightHeld(u32 *pValue, u32 min, u32 max, s32 wrap, u32 player)
{
    return StepCursorByKeys(pValue, min, max, wrap, g_awPlayerKeysHeld[player], KeyLeft, KeyRight);
}

STEP_CURSOR_LEFT_RIGHT_LINKAGE
u32 StepCursorLeftRight(u32 *pValue, u32 min, u32 max, s32 wrap, u32 player)
{
    return StepCursorByKeys(pValue, min, max, wrap, g_awPlayerKeysPressed[player], KeyLeft, KeyRight);
}

STEP_CURSOR_SHOULDER_HELD_LINKAGE
u32 StepCursorShoulderHeld(u32 *pValue, u32 min, u32 max, s32 wrap, u32 player)
{
    return StepCursorByKeys(pValue, min, max, wrap, g_awPlayerKeysHeld[player], KeyL, KeyR);
}

STEP_CURSOR_SHOULDER_LINKAGE
u32 StepCursorShoulder(u32 *pValue, u32 min, u32 max, s32 wrap, u32 player)
{
    return StepCursorByKeys(pValue, min, max, wrap, g_awPlayerKeysPressed[player], KeyL, KeyR);
}
