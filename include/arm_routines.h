#pragma once

#include "types.h"

// ARM routines that run from IWRAM copies. The copies are declared as
// functions or buffers so callers can take their address; the ROM calls
// them through that pointer.

struct Actor;

// Actor passes run by TickActorList; copied by InitActorPool.
void CheckActorCollisions(void);
void SortActorsByDepth(void);
extern void CheckActorCollisionsIwram(u32 count, struct Actor **queue);
extern void SortActorsByDepthIwram(struct Actor **queue, u32 count);

// LZ/RLE resource codec; copied by InstallIwramDecompressCodecs.
void DecompressLzRle(const void *src, void *dst, u32 *pSize);
extern u8 g_pDecompressLzRleIwram[0x1F8];

// Huffman BG tile decoder; copied by InstallBgTileCodec. See
// docs/formats/graphics.md ("On-demand per-tile BG streaming").
void DecompressBgTile(void);
extern u8 g_aDecompressBgTileIwram[0x100];

// OBJ VRAM tile allocator's search for a free run of tiles; copied by
// InstallIwramFindFreeObjTileRun.
u32 FindFreeObjTileRun(const u8 *pBitmap, u32 runLength, u32 startBit);
extern u32 FindFreeObjTileRunIwram(const u8 *pBitmap, u32 runLength, u32 startBit);
