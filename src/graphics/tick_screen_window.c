#include "types.h"
#include "math.h"
#include "graphics/display.h"

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
                corner->nX += iwramDivideSignedQuotient(corner->nTargetX - corner->nX, corner->wFrames);
                corner->nY += iwramDivideSignedQuotient(corner->nTargetY - corner->nY, corner->wFrames);
            }
            else
            {
                corner->nX = corner->nTargetX;
                corner->nY = corner->nTargetY;
                corner->wFlags &= ~2;
            }
            corner->wFrames--;
        }
        else
        {
            corner->nX += corner->nStepX;
            corner->nY += corner->nStepY;
        }

        window->dwFlags |= 1;
    }
}
