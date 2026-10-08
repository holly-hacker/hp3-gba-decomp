#include "types.h"
#include "graphics/graphics.h"
#include "hw/bios.h"

// Decompresses an OBJ tile resource with VRAM-safe codecs; see docs/formats/graphics.md.
u32 DecompressResourceVram(const void *pResource, void *pDest)
{
    const ResourceHeader *pHeader = pResource;
    u32 type = pHeader->type & ~RESOURCE_DELTA;
    u32 size = pHeader->size;

    switch (type)
    {
    case 0:
        bios_CPUFastSet((const u8 *)pResource + 4, pDest, size / 4 & 0x1FFFFF);
        break;
    case 1:
        bios_LZ77UnCompVRAM(pResource, pDest);
        break;
    case 2:
        DecompressHuffTree((const HuffTreeNode *)((const u8 *)pResource + 4), pDest, size);
        break;
    case 3:
        bios_RLUnCompVRAM((const u8 *)pResource + 4, pDest);
        break;
    case 7:
        g_pDecompressLzRleEntry((const u8 *)pResource + 4, pDest, &size);
        break;
    case 6:
    {
        const void *pSrc = (const u8 *)pResource + 4;

        g_pDecompressGammaLzEntry(pSrc, pDest, &size);
        break;
    }
    case 4:
    case 5:
    case 8:
        break;
    }

    if (pHeader->type & RESOURCE_DELTA)
        ApplyResourceDeltaPass(pDest, size);

    return pHeader->size;
}
