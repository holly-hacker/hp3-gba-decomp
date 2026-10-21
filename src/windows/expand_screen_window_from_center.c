#include "types.h"
#include "background.h"
#include "hw/io_regs.h"
#include "windows.h"
#include "windows_inline.h"

// Collapses window 0 to the center of window 1's rectangle, then expands it
// to that rectangle over the given frames.
void ExpandScreenWindowFromCenter(u16 frames)
{
    ScreenWindow *rect = &g_aScreenWindows[1];
    FixedPoint *pStart;
    FixedPoint *pEnd;
    s32 centerX;
    s32 centerY;

    centerX = (rect->aCorners[1].pos.x - rect->aCorners[0].pos.x) / 2 + rect->aCorners[0].pos.x;
    centerY = (rect->aCorners[1].pos.y - rect->aCorners[0].pos.y) / 2 + rect->aCorners[0].pos.y;

    pStart = &g_aScreenWindows[0].aCorners[0].pos;
    pEnd = &g_aScreenWindows[0].aCorners[1].pos;
    pStart->x = centerX;
    pStart->y = centerY;
    pEnd->x = centerX;
    pEnd->y = centerY;
    REG_WIN0H = (centerX >> 16) << 8 | (centerX >> 16);
    REG_WIN0V = (centerY >> 16) << 8 | (centerY >> 16);

    pStart = &rect->aCorners[0].pos;
    pEnd = &rect->aCorners[1].pos;
    TweenScreenWindowCornerInline(0, 0, pStart->x, pStart->y, frames);
    TweenScreenWindowCornerInline(0, 1, pEnd->x, pEnd->y, frames);
    SetDispcntFlag(DISPCNT_WIN0_ON | DISPCNT_WIN1_ON);
}
