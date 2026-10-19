#include "color.h"

// Returns the effect's slot.
s32 StartPaletteEffect(u32 startColor, u32 colorCount, u32 stepTicks, u32 delay, u32 flags, const u16 *pFrames)
{
    s32 slot = AllocPaletteEffectSlot();
    PaletteEffect *pEffect = &g_aPaletteEffects[slot];

    // NOTE: with every slot active, slot is ARRAY_COUNT(g_aPaletteEffects) and the writes below
    // land past the end of g_aPaletteEffects.
    pEffect->wFlags = flags;
    pEffect->bStepTicks_candidate = stepTicks;
    pEffect->bStepTimer_candidate = stepTicks;
    pEffect->bDelayTimer_candidate = delay;
    pEffect->bDelay_candidate = delay;
    pEffect->bStartColor = startColor;
    pEffect->bEndColor = startColor + colorCount - 1;
    pEffect->wColorCount = colorCount;
    pEffect->bFrameCount = 0;
    pEffect->bFrameIndex = 0;
    pEffect->pFrames = pFrames;
    pEffect->pCurrentFrame = pFrames;
    return slot;
}
