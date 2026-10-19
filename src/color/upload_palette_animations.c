#include "color.h"

// Copies the colors of every active color cycle and palette effect flagged dirty to palette RAM.
void UploadPaletteAnimations(void)
{
    u32 i;
    u32 j;
    ColorCycle *pCycle;
    PaletteEffect *pEffect;

    for (i = 0; i < ARRAY_COUNT(g_aColorCycles); i++)
    {
        pCycle = &g_aColorCycles[i];
        if (pCycle->bFlags & PALETTE_ANIM_ACTIVE)
            UploadColorCycle(pCycle);
    }

    for (j = 0; j < ARRAY_COUNT(g_aPaletteEffects); j++)
    {
        pEffect = &g_aPaletteEffects[j];
        if (pEffect->wFlags & PALETTE_ANIM_ACTIVE)
            UploadPaletteEffect(pEffect);
    }
}
