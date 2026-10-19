#include "color.h"

// Returns the first inactive palette effect slot, or ARRAY_COUNT(g_aPaletteEffects) if none.
u32 AllocPaletteEffectSlot(void)
{
    u8 i;

    for (i = 0; i < ARRAY_COUNT(g_aPaletteEffects); i++)
    {
        if (!(g_aPaletteEffects[i].wFlags & PALETTE_ANIM_ACTIVE))
        {
            g_dwPaletteEffectCount++;
            break;
        }
    }

    return i;
}
