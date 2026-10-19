#include "color.h"
#include "hw/io_regs.h"

void UploadPaletteEffect(PaletteEffect *pEffect)
{
    PaletteBuffer *pBuffer;

    if (pEffect->wFlags & PALETTE_ANIM_DIRTY)
    {
        pEffect->wFlags &= ~PALETTE_ANIM_DIRTY;
        if (pEffect->wFlags & PALETTE_ANIM_OBJ)
            pBuffer = &g_PaletteState.obj;
        else
            pBuffer = &g_PaletteState.bg;

        REG_DMA3.src = pBuffer->pShadow + pEffect->bStartColor;
        REG_DMA3.dst = (void *)(pBuffer->pPaletteRam + pEffect->bStartColor);
        REG_DMA3.cnt = pEffect->wColorCount | 0x80000000;
        (void)REG_DMA3.cnt;
    }
}
