#include "color.h"
#include "screen_transitions.h"
#include "hw/bios.h"
#include "hw/io_regs.h"

// Gamma-corrects colorCount colors from pColors into the buffer's shadow, from color firstColor
// on, and DMA-copies them to palette RAM. While g_dwPaletteRedirect is set they go to
// g_pPaletteWorkBuffer instead and are copied to g_pScreenPaletteBackup.
void LoadPaletteColors(const u16 *pColors, u32 firstColor, u32 colorCount, PaletteBuffer *pBuffer)
{
    u32 size = colorCount * 2;
    u32 offset;
    u16 *pSrc;
    u16 *pDst;

    if (g_dwPaletteRedirect)
    {
        offset = ((u32)pBuffer->pPaletteRam & 0x200) + firstColor * 2;
        ApplyGammaToColors((u16 *)((u8 *)g_pPaletteWorkBuffer + offset), pColors, size);
        bios_CPUSet((u8 *)g_pPaletteWorkBuffer + offset, (u8 *)g_pScreenPaletteBackup + offset,
                    (size / 2) & 0x1FFFFF);
    }
    else
    {
        pDst = pBuffer->pShadow + firstColor;
        ApplyGammaToColors(pDst, pColors, size);
        pSrc = pDst;
        pDst = (u16 *)(pBuffer->pPaletteRam + firstColor);
        REG_DMA3.src = pSrc;
        REG_DMA3.dst = pDst;
        REG_DMA3.cnt = (size / 2) | 0x80000000;
        (void)REG_DMA3.cnt;
    }
}
