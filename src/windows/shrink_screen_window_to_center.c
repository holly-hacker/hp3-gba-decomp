#include "types.h"
#include "background.h"
#include "hw/io_regs.h"
#include "windows.h"
#include "windows_inline.h"

// Sets window 0 to window 1's rectangle, then shrinks it to the rectangle's
// center over the given frames.
void ShrinkScreenWindowToCenter(u16 frames)
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
    pStart->x = rect->aCorners[0].pos.x;
    pStart->y = rect->aCorners[0].pos.y;
    pEnd->x = rect->aCorners[1].pos.x;
    pEnd->y = rect->aCorners[1].pos.y;
    REG_WIN0H = (rect->aCorners[0].pos.x >> 16) << 8 | (rect->aCorners[1].pos.x >> 16);
    REG_WIN0V = (rect->aCorners[0].pos.y >> 16) << 8 | (rect->aCorners[1].pos.y >> 16);

    TweenScreenWindowCornerInline(0, 0, centerX, centerY, frames);
    TweenScreenWindowCornerInline(0, 1, centerX, centerY, frames);
    SetDispcntFlag(DISPCNT_WIN0_ON | DISPCNT_WIN1_ON);
}
