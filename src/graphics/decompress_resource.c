#include "types.h"
#include "graphics/graphics.h"
#include "hw/bios.h"

// Decompresses a level/room resource into work RAM; see docs/formats/graphics.md.
u32 DecompressResource(const void *pResource, void *pDest)
{
    const ResourceHeader *pHeader = pResource;
    u32 type = pHeader->type & ~RESOURCE_DELTA;
    u32 size = pHeader->size;

    switch (type)
    {
    case 0:
        bios_CPUSet((const u8 *)pResource + 4, pDest, (size / 4 & 0x1FFFFF) | 0x04000000);
        break;
    case 1:
        bios_LZ77UnCompWRAM(pResource, pDest);
        break;
    case 2:
        bios_HuffUnComp(pResource, pDest);
        break;
    case 3:
        bios_RLUnCompReadNormalWrite8bit(pResource, pDest);
        break;
    case 4:
        g_pDecompressLzRleEntry(pResource, pDest, &size);
        break;
    case 6:
    {
        const void *pSrc = (const u8 *)pResource + 4;

        g_pDecompressGammaLzEntry(pSrc, pDest, &size);
        break;
    }
    case 5:
    case 7:
    case 8:
        break;
    }

    if (pHeader->type & RESOURCE_DELTA)
        ApplyResourceDeltaPass(pDest, size);

    return pHeader->size;
}
