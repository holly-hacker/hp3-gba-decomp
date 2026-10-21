#pragma once

#include "types.h"

// ARM routines that run from IWRAM copies. Each copy is declared, as a
// function or buffer, in the header of the module whose RAM holds it.

struct Actor;

// Actor passes run by TickActorList; copied by InitActorPool.
void CheckActorCollisions(s32 count, struct Actor **actors);
void SortActorsByDepth(struct Actor **actors, u32 count);

// LZ/RLE resource codec; copied by InstallIwramDecompressCodecs.
void DecompressLzRle(const void *src, void *dst, u32 *pSize);

// Huffman BG tile decoder; copied by InstallBgTileCodec.
// Canonical code table: per code length, the number of codes and the index
// of the length's first symbol, then the symbols.
typedef struct BgTileCodeTable {
    u8 abCount[18];    // 0x00
    u8 abFirst[18];    // 0x12
    u8 abSymbols[1];   // 0x24, variable-length
} BgTileCodeTable;
void DecompressBgTile(u32 bitOffset, u16 *pDest, s32 size, const BgTileCodeTable *pTable);

// OBJ VRAM tile allocator's search for a free run of tiles; copied by
// InstallIwramFindFreeObjTileRun.
u32 FindFreeObjTileRun(const u8 *pBitmap, u32 runLength, u32 bit);
