#include "types.h"
#include "background.h"
#include "hw/bios.h"

void FillBgTilemap(u32 bg, u16 tile, u16 color)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];
    u32 size;
    u16 fill;

    FillBgTile(bg, tile, color);
    if (!pLayer->control.bits.b8bpp)
        tile |= (color >> 4) << 12;

    switch (pLayer->control.bits.bSize)
    {
    case 0:
        size = 0x800;
        break;
    case 1:
    case 2:
        size = 0x1000;
        break;
    case 3:
        size = 0x2000;
        break;
    default:
        size = 0;
        break;
    }

    fill = tile;
    bios_CPUSet(&fill, pLayer->pScreenBase, (size / 2) | 0x01000000);
}
