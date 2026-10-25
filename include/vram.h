#pragma once

#include "types.h"

// OBJ VRAM tile allocator: tiles are handed out
// in runs tracked by one bit per 32-byte tile (1024 tiles). The ARM search
// routine FindFreeObjTileRun and its IWRAM copy are declared in arm_routines.h.

struct Actor;
struct ActorAssetRecord;
struct ActorFrameData;

// A set bit in g_abObjTileAllocBitmap marks a tile in use. Freeing a run
// clears its bits in g_abObjTileFreeMask only; ApplyDeferredObjTileFrees
// folds the mask into the bitmap on a vblank that swaps the OAM buffers.
extern u8 g_abObjTileAllocBitmap[128];
extern u8 g_abObjTileFreeMask[128];
// IWRAM copy of FindFreeObjTileRun.
extern u32 FindFreeObjTileRunIwram(const u8 *pBitmap, u32 runLength, u32 bit);

extern void InstallIwramFindFreeObjTileRun(void);
extern void InitObjTileAllocBitmaps(u8 bgMode);
// Frees every OBJ tile and clears pending deferred frees.
extern void FreeAllObjVramTiles(void);
// Returns the first allocated tile, or 0xFFFF when none are free.
extern u32 AllocObjVramTiles(struct ActorAssetRecord *record, u32 pixelCount, u32 is8bpp);
// Decompresses tileGfx into OBJ VRAM at the actor's wVramTileAllocId.
extern void LoadObjTile(struct Actor *actor, void *tileGfx);
// Decompresses tileGfx into OBJ VRAM at tile allocId; other arguments are unused.
extern void LoadObjTileAt(struct ActorFrameData *frameData, void *tileGfx, u16 allocId, u16 frame,
                          u16 pixelCount);
// Releases an allocation immediately; FreeObjVramTileAllocation defers it to the next OAM swap.
extern void FreeObjVramTileAllocationNow(u16 allocId, u32 pixelCount, u8 is8bpp);
// Frees the OBJ VRAM tiles of an allocation of pixelCount pixels.
extern void FreeObjVramTileAllocation(u16 allocId, u32 pixelCount, u8 is8bpp);
extern void ApplyDeferredObjTileFrees(void);
// Decompresses every frame of record's tile graphics into consecutive OBJ VRAM tiles starting at
// tile firstTile.
extern void LoadObjTileSheet(const struct ActorAssetRecord *record, u16 firstTile);
// AllocObjVramTiles without the allocation: loads record's tile sheet at firstTile when record
// is given and returns firstTile. pixelCount is unused.
extern u16 LoadObjVramTilesAt(const struct ActorAssetRecord *record, u32 pixelCount, u8 is8bpp,
                              u16 firstTile);
// Range helpers on the OBJ tile bitmaps; firstTile 0xFFFF (no allocation) is ignored by the clears.
extern void MarkObjTilesInUse(u16 firstTile, u16 tileCount);
extern void ClearObjTileAllocBits(u16 firstTile, u16 tileCount);
extern void ClearObjTileFreeMaskBits(u16 firstTile, u16 tileCount);
