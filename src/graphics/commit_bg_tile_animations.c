#include "types.h"
#include "graphics/display.h"
#include "hw/dma.h"
#include "hw/io_regs.h"
#include "overworld/room.h"

// Vblank upload of the BG tile animations whose decoded frame changed (flag 4). Flag 8 copies the
// whole buffer to the character block in one DMA; otherwise each tile goes to the VRAM slot the
// room BG tile cache holds for it, and tiles the cache does not hold are skipped.
void CommitBgTileAnimations(void)
{
    u32 i;
    u32 size;
    u32 tile;
    u32 tileOffset;
    u32 sizeClass;
    u32 slot;
    u32 isCached;

    for (i = 0; i < g_bBgTileAnimationCount; i++)
    {
        if (!(g_aBgTileAnimations[i].bFlags & 4))
            continue;

        size = g_aBgTileAnimations[i].pAnimation->dwBufferSize;
        if (g_aBgTileAnimations[i].bFlags & 8)
        {
            REG_DMA3.src = g_apBgTileAnimationBuffers[i];
            REG_DMA3.dst = (u8 *)VRAM_BASE + g_aBgTileAnimations[i].pBgControl->bCharBlock * 0x4000
                         + g_aBgTileAnimations[i].wTileOffset * 32;
            REG_DMA3.cnt = (size >> 1) | 0x80000000;
            (void)REG_DMA3.cnt;
        }
        else
        {
            sizeClass = 0;
            if ((u32)g_aBgTileAnimations[i].pBgControl->bCharBlock > 1)
                sizeClass = 1;
            tileOffset = g_aBgTileAnimations[i].wTileOffset;
            for (tile = 0; tile < (size >> 5); tile++)
            {
                slot = FindBgTileCacheEntry(tileOffset + tile, sizeClass);
                isCached = slot != 0xFFFF;
                if (isCached)
                {
                    REG_DMA3.src = (u8 *)g_apBgTileAnimationBuffers[i] + tile * 32;
                    REG_DMA3.dst = (u8 *)VRAM_BASE
                                 + g_aBgTileAnimations[i].pBgControl->bCharBlock * 0x4000 + slot * 32;
                    REG_DMA3.cnt = 0x80000010;
                    (void)REG_DMA3.cnt;
                }
            }
        }

        g_aBgTileAnimations[i].bFlags &= ~4;
    }
}
