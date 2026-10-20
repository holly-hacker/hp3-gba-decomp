#include "types.h"
#include "hw/io_regs.h"
#include "windows.h"

void SetScreenWindowRect(u32 windowId, s32 x0, s32 y0, s32 x1, s32 y1)
{
    ScreenWindow *window = &g_aScreenWindows[windowId];

    window->aCorners[0].pos.x = x0;
    window->aCorners[0].pos.y = y0;
    window->aCorners[1].pos.x = x1;
    window->aCorners[1].pos.y = y1;
    REG_WINH(windowId) = (x0 >> 16) << 8 | (x1 >> 16);
    REG_WINV(windowId) = (y0 >> 16) << 8 | (y1 >> 16);
}
