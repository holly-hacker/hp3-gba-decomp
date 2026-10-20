#pragma once

#include "windows.h"

// Window logic that the ROM compiles inline into the box wipes.

// The body of TweenScreenWindowCorner: moves a corner to (x, y) over the given frames.
static inline void TweenScreenWindowCornerInline(u32 windowId, u32 corner, s32 x, s32 y, u16 frames)
{
    ScreenWindow *window = &g_aScreenWindows[windowId];
    WindowCorner *pCorner = &window->aCorners[corner];

    pCorner->target.x = x;
    pCorner->target.y = y;
    pCorner->wFrames = frames;
    pCorner->wFlags |= 2;
}
