#include "types.h"
#include "windows.h"

// Starts a corner moving by (stepX, stepY) every frame once any tween ends.
void DriftScreenWindowCorner(u32 windowId, u32 corner, s32 stepX, s32 stepY)
{
    ScreenWindow *window = &g_aScreenWindows[windowId];
    WindowCorner *pCorner = &window->aCorners[corner];

    pCorner->step.x = stepX;
    pCorner->step.y = stepY;
    pCorner->wFlags |= 2;
}
