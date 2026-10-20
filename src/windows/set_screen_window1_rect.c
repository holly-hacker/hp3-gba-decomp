#include "types.h"
#include "hw/io_regs.h"
#include "windows.h"

void SetScreenWindow1Rect(s32 x0, s32 y0, s32 x1, s32 y1)
{
    g_aScreenWindows[1].aCorners[0].pos.x = x0;
    g_aScreenWindows[1].aCorners[0].pos.y = y0;
    g_aScreenWindows[1].aCorners[1].pos.x = x1;
    g_aScreenWindows[1].aCorners[1].pos.y = y1;
    REG_WIN1H = (x0 >> 16) << 8 | (x1 >> 16);
    REG_WIN1V = (y0 >> 16) << 8 | (y1 >> 16);
}
