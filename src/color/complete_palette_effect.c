#include "color.h"
#include "hw/bios.h"

// Stops the effect after setting its colors to the first frame's.
void CompletePaletteEffect(s32 handle)
{
    PaletteEffect *pEffect = &g_aPaletteEffects[handle];
    PaletteBuffer *pBuffer;

    if (pEffect->wFlags & PALETTE_ANIM_OBJ)
        pBuffer = &g_PaletteState.obj;
    else
        pBuffer = &g_PaletteState.bg;

    bios_CPUSet(pEffect->pFrames + (pEffect->bStartColor & 0xF), pBuffer->pShadow + pEffect->bStartColor,
                pEffect->wColorCount);
    bios_CPUSet(pBuffer->pShadow + pEffect->bStartColor, pBuffer->pPaletteRam + pEffect->bStartColor,
                pEffect->wColorCount);
    ClearPaletteEffect(pEffect);
}
