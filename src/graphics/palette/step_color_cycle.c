#include "graphics/palette.h"

// Advances the cycle's current color every bDelay + 1 ticks and marks it for upload.
void StepColorCycle(ColorCycle *pCycle)
{
    if (pCycle->bTimer == 0)
    {
        if (pCycle->bFlags & COLOR_CYCLE_REVERSE)
        {
            if (pCycle->bCurrentColor == pCycle->bStartColor)
                pCycle->bCurrentColor = pCycle->bEndColor;
            else
                pCycle->bCurrentColor--;
        }
        else
        {
            if (pCycle->bCurrentColor == pCycle->bEndColor)
                pCycle->bCurrentColor = pCycle->bStartColor;
            else
                pCycle->bCurrentColor++;
        }

        if (pCycle->bFlags & COLOR_CYCLE_PING_PONG)
        {
            if (pCycle->bFlags & COLOR_CYCLE_REVERSE)
            {
                if (pCycle->bCurrentColor == pCycle->bStartColor)
                    pCycle->bFlags ^= COLOR_CYCLE_REVERSE;
            }
            else
            {
                if (pCycle->bCurrentColor == pCycle->bEndColor)
                    pCycle->bFlags ^= COLOR_CYCLE_REVERSE;
            }
        }

        pCycle->bFlags |= PALETTE_ANIM_DIRTY;
        pCycle->bTimer = pCycle->bDelay;
    }
    else
        pCycle->bTimer--;
}
