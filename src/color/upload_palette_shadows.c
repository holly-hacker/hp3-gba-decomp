#include "color.h"
#include "hw/io_regs.h"

// Copies both shadows to palette RAM and flags every active color cycle to be uploaded again.
void UploadPaletteShadows(void)
{
    u32 i;

    REG_DMA3.src = g_PaletteState.bg.pShadow;
    REG_DMA3.dst = (void *)BG_PLTT;
    REG_DMA3.cnt = 0x80000100;
    (void)REG_DMA3.cnt;
    REG_DMA3.src = g_PaletteState.obj.pShadow;
    REG_DMA3.dst = (void *)OBJ_PLTT;
    REG_DMA3.cnt = 0x80000100;
    (void)REG_DMA3.cnt;

    for (i = 0; i < ARRAY_COUNT(g_aColorCycles); i++)
    {
        if (g_aColorCycles[i].bFlags & PALETTE_ANIM_ACTIVE)
            g_aColorCycles[i].bFlags |= PALETTE_ANIM_DIRTY;
    }
}
