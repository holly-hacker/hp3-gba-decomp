#include "color.h"
#include "hw/io_regs.h"

// Copies the cycle's colors from the shadow to palette RAM, rotated so that shadow color
// bStartColor lands at bCurrentColor.
void UploadColorCycle(ColorCycle *pCycle)
{
    PaletteBuffer *pBuffer;
    u32 count;
    u32 wrapColor;

    if (pCycle->bFlags & PALETTE_ANIM_DIRTY)
    {
        pCycle->bFlags &= ~PALETTE_ANIM_DIRTY;
        if (pCycle->bFlags & PALETTE_ANIM_OBJ)
            pBuffer = &g_PaletteState.obj;
        else
            pBuffer = &g_PaletteState.bg;

        if (pCycle->bCurrentColor == pCycle->bStartColor)
        {
            REG_DMA3.src = pBuffer->pShadow + pCycle->bStartColor;
            REG_DMA3.dst = (void *)(pBuffer->pPaletteRam + pCycle->bStartColor);
            REG_DMA3.cnt = pCycle->bColorCount | 0x80000000;
            (void)REG_DMA3.cnt;
        }
        else
        {
            count = pCycle->bEndColor - pCycle->bCurrentColor + 1;
            REG_DMA3.src = pBuffer->pShadow + pCycle->bStartColor;
            REG_DMA3.dst = (void *)(pBuffer->pPaletteRam + pCycle->bCurrentColor);
            REG_DMA3.cnt = count | 0x80000000;
            (void)REG_DMA3.cnt;

            count = pCycle->bCurrentColor - pCycle->bStartColor;
            wrapColor = pCycle->bEndColor - count + 1;
            REG_DMA3.src = pBuffer->pShadow + wrapColor;
            REG_DMA3.dst = (void *)(pBuffer->pPaletteRam + pCycle->bStartColor);
            REG_DMA3.cnt = count | 0x80000000;
            (void)REG_DMA3.cnt;
        }
    }
}
