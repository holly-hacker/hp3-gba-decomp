#include "types.h"
#include "background.h"
#include "hw/bios.h"
#include "hw/io_regs.h"

void FillBgTile(u32 bg, u16 tile, u16 color)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];
    u32 tileSize;
    u32 charBase;
    u8 *pDest;
    u16 fill;

    tileSize = (pLayer->control.b8bpp + 1) * 32;
    charBase = pLayer->control.bCharBlock << 14;
    pDest = charBase + (u8 *)VRAM_BASE + tileSize * tile;
    if (!pLayer->control.b8bpp)
    {
        color &= 0xF;
        color = (color << 12) + (color << 8) + (color << 4) + color;
    }
    else
    {
        color &= 0xFF;
        color = color + (color << 8);
    }

    fill = color;
    bios_CPUSet(&fill, pDest, (tileSize / 2) | 0x01000000);
}
