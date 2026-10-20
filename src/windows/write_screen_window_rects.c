#include "types.h"
#include "hw/io_regs.h"
#include "windows.h"

void WriteScreenWindowRects(void)
{
    u32 i;
    ScreenWindow *window;
    u32 horizontal;
    u32 vertical;

    for (i = 0; i < ARRAY_COUNT(g_aScreenWindows); i++)
    {
        window = &g_aScreenWindows[i];
        if (!(window->dwFlags & 1))
            continue;

        window->dwFlags &= ~1;
        horizontal = (s16)(window->aCorners[0].pos.x >> 16) << 8 | (s16)(window->aCorners[1].pos.x >> 16);
        vertical = (s16)(window->aCorners[0].pos.y >> 16) << 8 | (s16)(window->aCorners[1].pos.y >> 16);
        REG_WINH(i) = horizontal;
        REG_WINV(i) = vertical;
    }
}
