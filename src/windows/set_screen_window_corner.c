#include "types.h"
#include "windows.h"

// Places a corner without marking the rectangle changed.
void SetScreenWindowCorner(u32 windowId, u32 corner, s32 x, s32 y)
{
    ScreenWindow *window = &g_aScreenWindows[windowId];
    WindowCorner *pCorner = &window->aCorners[corner];

    pCorner->pos.x = x;
    pCorner->pos.y = y;
}
