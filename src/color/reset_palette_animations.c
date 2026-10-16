#include "color.h"

void ResetPaletteAnimations(void)
{
    ResetColorCycles();
    ResetPaletteEffects();
    g_dwObjPaletteQueueCount = 0;
}
