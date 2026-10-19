#include "color.h"

s32 StartPaletteEffectFromDesc(const PaletteEffectDesc *pDesc, u32 flags, u32 frameCount)
{
    s32 slot;
    PaletteEffect *pEffect;

    slot = StartPaletteEffect(pDesc->bStartColor, pDesc->bColorCount, pDesc->bStepTicks, pDesc->bDelay,
                              flags, pDesc->pFrames);
    pEffect = &g_aPaletteEffects[slot];
    pEffect->bFrameCount = frameCount;
    return slot;
}
