#include "color.h"

void StopPaletteEffect(s32 handle)
{
    ClearPaletteEffect(&g_aPaletteEffects[handle]);
}
