#include "graphics/palette.h"

void TickPaletteEffects(void)
{
    u8 found;
    u32 i;
    PaletteEffect *pEffect;

    found = 0;
    for (i = 0; i < ARRAY_COUNT(g_aPaletteEffects) && found <= g_dwPaletteEffectCount; i++)
    {
        pEffect = &g_aPaletteEffects[i];
        if (pEffect->wFlags & PALETTE_ANIM_ACTIVE)
        {
            StepPaletteEffect(pEffect);
            found++;
        }
    }
}
