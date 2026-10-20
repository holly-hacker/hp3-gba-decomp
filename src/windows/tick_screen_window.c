#include "types.h"
#include "math.h"
#include "windows.h"

// Advances both corners of one window: tweens toward the target over wFrames
// frames, or drifts by the step when wFrames is 0.
void TickScreenWindow(u32 windowId)
{
    ScreenWindow *window = &g_aScreenWindows[windowId];
    WindowCorner *corner;
    u32 i;

    for (i = 0, corner = window->aCorners; i < 2; corner++, i++)
    {
        if (!(corner->wFlags & 2))
            continue;

        if (corner->wFrames != 0)
        {
            if (corner->wFrames > 1)
            {
                corner->pos.x += iwramDivideSignedQuotient(corner->target.x - corner->pos.x, corner->wFrames);
                corner->pos.y += iwramDivideSignedQuotient(corner->target.y - corner->pos.y, corner->wFrames);
            }
            else
            {
                corner->pos.x = corner->target.x;
                corner->pos.y = corner->target.y;
                corner->wFlags &= ~2;
            }
            corner->wFrames--;
        }
        else
        {
            corner->pos.x += corner->step.x;
            corner->pos.y += corner->step.y;
        }

        window->dwFlags |= 1;
    }
}
