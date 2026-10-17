#pragma once

#include "types.h"

// ARM routines that run from IWRAM copies. Each copy is declared, as a
// function or buffer, in the header of the module whose RAM holds it.

struct Actor;

// Actor passes run by TickActorList; copied by InitActorPool.
void CheckActorCollisions(void);
void SortActorsByDepth(void);

// LZ/RLE resource codec; copied by InstallIwramDecompressCodecs.
void DecompressLzRle(const void *src, void *dst, u32 *pSize);

// Huffman BG tile decoder; copied by InstallBgTileCodec. See
// docs/formats/graphics.md ("On-demand per-tile BG streaming").
void DecompressBgTile(void);

// OBJ VRAM tile allocator's search for a free run of tiles; copied by
// InstallIwramFindFreeObjTileRun.
u32 FindFreeObjTileRun(const u8 *pBitmap, u32 runLength, u32 startBit);
