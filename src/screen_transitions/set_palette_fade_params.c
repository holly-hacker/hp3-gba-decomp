#include "types.h"
#include "screen_transitions.h"

void SetPaletteFadeParams(u32 color, u32 stepTicks)
{
    g_dwPaletteFadeColor = color;
    g_dwPaletteFadeStepTicks = stepTicks;
}
