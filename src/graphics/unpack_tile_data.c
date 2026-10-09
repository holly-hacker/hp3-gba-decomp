#include "types.h"
#include "graphics/graphics.h"
#include "hw/bios.h"

// Decodes tile data into VRAM-safe memory. The header's codec field selects the codec:
// 0 copy, 1 run-length, 2 LZ77, 3 GammaLz.
void UnpackTileData(const TileDataHeader *pHeader, const void *pData, s32 size, void *pDest)
{
    switch (pHeader->bCodec)
    {
    case 0:
        bios_CPUFastSet(pData, pDest, size / 4 & 0x1FFFFF);
        break;
    case 1:
        bios_RLUnCompVRAM(pData, pDest);
        break;
    case 2:
        bios_LZ77UnCompVRAM(pData, pDest);
        break;
    case 3:
        g_pDecompressGammaLzEntry(pData, pDest, 0);
        break;
    }
}
