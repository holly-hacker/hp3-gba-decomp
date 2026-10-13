#include "types.h"
#include "background.h"
#include "hw/bios.h"

void CopyBgTiles(u32 bg, u16 firstTile, u16 tileCount, const void *pSrc)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];

    if (pLayer->control.bits.b8bpp)
    {
        firstTile *= 2;
        tileCount *= 2;
    }

    bios_CPUSet(pSrc, pLayer->pCharBase + firstTile * 32, tileCount * 16);
}
