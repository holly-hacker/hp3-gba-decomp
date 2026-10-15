#pragma once

#include "types.h"

// Resource decompression; see docs/formats/graphics.md.

// The two proprietary resource-compression codecs (dispatch types 4/6;
// not the real BIOS LZ77/Huffman/RLE). InstallIwramDecompressCodecs
// copies both into IWRAM at startup for speed and records each copy's
// address in the matching g_pDecompress*Entry global; the
// resource-decompression dispatcher calls through those, not the ROM
// copies directly.
typedef void (*DecompressFunc)(const void *src, void *dst, u32 *pSize);
void DecompressGammaLz(const void *src, void *dst, u32 *pSize);
extern DecompressFunc g_pDecompressLzRleEntry;
extern DecompressFunc g_pDecompressGammaLzEntry;
extern u8 g_pDecompressGammaLzIwram[0x33C];

// The 4-byte header of a compressed resource. type selects the codec per
// dispatcher; RESOURCE_DELTA in type requests ApplyResourceDeltaPass afterwards.
typedef struct ResourceHeader {
    u32 unused : 4;
    u32 type : 4;
    u32 size : 24;  // decompressed bytes
} ResourceHeader;

#define RESOURCE_DELTA 8

extern u32 GetResourceDecompressedSize(const void *pResource);
extern u32 DecompressResource(const void *pResource, void *pDest);  // returns the size
extern u32 DecompressResourceVram(const void *pResource, void *pDest);  // returns the size
extern void ApplyResourceDeltaPass(u16 *pData, u32 size);
extern void ApplyResourceDeltaPassUnused(u16 *pData, u32 size);
void InstallIwramDecompressCodecs(void);
