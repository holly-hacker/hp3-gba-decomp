#include "color.h"

s32 StartPaletteEffectWithFrameCount(u32 startColor, u32 colorCount, u32 stepTicks, u32 delay, u32 flags,
                                     const u16 *pFrames, u32 frameCount)
{
    s32 slot;
    PaletteEffect *pEffect;

    slot = StartPaletteEffect(startColor, colorCount, stepTicks, delay, flags, pFrames);
    pEffect = &g_aPaletteEffects[slot];
    pEffect->bFrameCount = frameCount;
    return slot;
}
