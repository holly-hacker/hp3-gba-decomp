#include "graphics/palette.h"

void ResetPaletteAnimations(void)
{
    ResetColorCycles();
    ResetPaletteEffects();
    g_dwObjPaletteQueueCount = 0;
}
