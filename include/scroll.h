#pragma once

#include "types.h"
#include "camera.h"
#include "arm_routines.h"

// A BG tileset and its palette. Tileset A (layers 0 and 3) and tileset B
// (layers 1 and 2) each pair with one; the second pair's palette is not
// confirmed to be read.
typedef struct RoomBgResources {
    const u8 *pTileset;
    const void *pPalette;
} RoomBgResources;

// World-space camera origin used for actor visibility.
extern CameraFocusOffset g_CameraPosition;

// Pixel size of the current room.
typedef struct RoomSizePixels {
    u32 dwWidth;
    u32 dwHeight;
} RoomSizePixels;

extern RoomSizePixels g_RoomSizePixels;

// Updates g_CameraPosition from the followed actor and streams BG
// tiles on demand as it crosses tile boundaries.
extern void UpdateOverworldCamera(u32 snap);
extern void ReloadRoomBgTiles(void);
extern void FreeRoomBgBlockData(void);
extern void LoadRoomBgBlockTiles0(const void *pBlockTiles, u32 unused8, u32 unusedC);
extern void GetCameraPosition(s32 *pPosition);  // copies g_CameraPosition out
extern void SetCameraPosition(const s32 *pPosition);  // copies a two-word position into g_CameraPosition
extern void ResetCameraPosition(void);  // zeroes g_CameraPosition
extern IntPoint GetCameraTargetPosition(void);
extern s32 StepScrollToward(s32 current, s32 target);

// Nonzero for each BG layer UpdateOverworldCamera scrolls.
extern u32 g_adwBgScrollEnabled[4];
extern u32 g_dwUnk030059AC;  // zeroed by InitRoomBgState; no other literal reference found

// Room BG tile VRAM cache, per tile-size class (layers 0/3 and 1/2): see
// docs/formats/graphics.md ("The runtime streaming/caching path").
typedef struct BgTileCacheEntry {
    u16 wRefcount;
    u16 wTileId;
    u16 wNext;  // next entry in the hash chain, 0xFFFF ends it
    u16 pad_06;
} BgTileCacheEntry;
extern BgTileCacheEntry *g_apBgTileCacheEntries[2];  // 0x400 and 0x200 entries
extern u16 *g_apBgTileCacheBuckets[2];               // chain heads by tile id & 0x7FF / 0x3FF
extern u16 *g_apBgTileCacheFreeSlots[2];             // stack of free entry indices
// Per tile size class: where each tile's compressed pixels start and the Huffman code table
// shared by all of them (see docs/formats/graphics.md, "The runtime streaming/caching path").
typedef struct BgTileset {
    const BgTileCodeTable *pRomCodeTable;  // in the tileset resource; copied to pCodeTable
    const u8 *pTileData;                   // compressed tiles, right after the code table
    u32 *pTileBitOffsets;  // ROM bit offset of each tile's compressed data, indexed by tile id
    BgTileCodeTable *pCodeTable;
} BgTileset;
extern BgTileset g_aBgTilesets[2];
extern u16 g_awBgLayerTileCount[4];
extern u16 g_awBgTileCacheFreeCount[2];
// BGxCNT as shadowed per BG layer.
typedef struct RoomBgControl {
    u32 bPriority : 2;
    u32 bCharBlock : 2;
    u32 bUnused : 4;
    u32 bScreenBlock : 5;  // 2 KB screen block holding the layer's tilemap
    u32 dwRest : 19;
} RoomBgControl;
extern RoomBgControl g_aBgControl[4];

// Per BG layer, a map of 32x32-pixel blocks (u16: block id in the low 11 bits) and a block table:
// 16 u16 tile ids per block (4x4 tiles), followed by 16 attribute bytes per block, each shifted
// into bits 10+ of the tile's tilemap entry. g_adwBgBlockAttrOffset holds the attribute bytes' offset.
typedef struct RoomBgBlockData {
    u16 *apBlockMaps[4];
    u16 (*apBlockTiles[4])[16];
} RoomBgBlockData;
extern RoomBgBlockData g_RoomBgBlockData;
extern u32 g_adwBgBlockAttrOffset[4];
extern IntPoint g_BgScroll;        // scroll position the layers' tiles are streamed for
extern IntPoint g_BgLoadedScroll;  // g_BgScroll as of the last tile load
extern void InitRoomBgState(void);
extern u16 FindBgTileCacheEntry(u16 tileId, u32 sizeClass);
typedef struct RoomBgAux {
    u8 bFlags;
    u8 pad_01[3];
    s32 aPosA[2];
    s32 aPosB[2];
} RoomBgAux;
extern RoomBgAux g_RoomBgAux;
// Per BG layer, the room's size in tiles and in 32x32-pixel blocks.
extern u16 g_wRoomBgLayer0TilesWide;
extern u16 g_wRoomBgLayer0TilesHigh;
extern u16 g_wRoomBgLayer0BlocksWide;
extern u16 g_wRoomBgLayer0BlocksHigh;
extern u16 g_wRoomBgLayer1TilesWide;
extern u16 g_wRoomBgLayer1TilesHigh;
extern u16 g_wRoomBgLayer1BlocksWide;
extern u16 g_wRoomBgLayer1BlocksHigh;
extern u16 g_wRoomBgLayer2TilesWide;
extern u16 g_wRoomBgLayer2TilesHigh;
extern u16 g_wRoomBgLayer2BlocksWide;
extern u16 g_wRoomBgLayer2BlocksHigh;
extern u16 g_wRoomBgLayer3TilesWide;
extern u16 g_wRoomBgLayer3TilesHigh;
extern u16 g_wRoomBgLayer3BlocksWide;
extern u16 g_wRoomBgLayer3BlocksHigh;
// Byte size of each layer's block map; no reader found.
extern u16 g_wRoomBgLayer0MapSize;
extern u16 g_wRoomBgLayer1MapSize;
extern u16 g_wRoomBgLayer2MapSize;
extern u16 g_wRoomBgLayer3MapSize;
// Heap blocks of each layer's block map and block tile table (see RoomBgBlockData). A tiles
// block pointer is advanced past the table's leading block count once it is read.
extern u8 *g_pRoomBgLayer0MapAlloc;
extern u8 *g_pRoomBgLayer1MapAlloc;
extern u8 *g_pRoomBgLayer2MapAlloc;
extern u8 *g_pRoomBgLayer3MapAlloc;
extern u32 *g_pRoomBgLayer0TilesAlloc;
extern u32 *g_pRoomBgLayer1TilesAlloc;
extern u32 *g_pRoomBgLayer2TilesAlloc;
extern u32 *g_pRoomBgLayer3TilesAlloc;
// The first word of each layer's block tile table; no reader found.
extern u32 g_dwRoomBgLayer0TileWord0;
extern u32 g_dwRoomBgLayer1TileWord0;
extern u32 g_dwRoomBgLayer2TileWord0;
extern u32 g_dwRoomBgLayer3TileWord0;
extern u8 g_bUnk030059B0;  // zeroed by LoadRoomBgTilemap0; no other literal reference found

// A tile column (entry 0) or row (entry 1) whose tiles left the loaded window; x is
// BG_STRIP_NONE when nothing is queued.
#define BG_STRIP_NONE 3
typedef struct BgStripRelease {
    s32 x;
    s32 y;
} BgStripRelease;
extern BgStripRelease g_aBgStripReleases[2];
extern void QueueBgStripRelease(s32 x, s32 y, u32 axis);
extern void FlushBgStripReleases(void);
extern void LoadBgTileColumn(u32 x, u32 y);
extern void LoadBgTileRow(u32 x, u32 y);
extern void ReleaseBgTileColumn(u32 x, u32 y);
extern void ReleaseBgTileRow(u32 x, u32 y);
extern void WriteBgTilemapEntry(u16 tileId, u32 sizeClass, u32 layer, u32 x, u32 y, u16 blockId);

// Per tile size class, the Huffman code table copied out of the tileset and the tile count.
extern u8 g_aBgTileCodeTableBuffers[2][0x124];
extern u32 g_adwBgTilesetTileCount[2];
extern const void *g_apRoomBgTilesets[2];
extern u32 DecodeBgTilesetOffsetTable(RoomBgResources resources, BgTileset *pTileset,
                                                BgTileCodeTable *pCodeTable);
extern u16 *GetRoomBgBlockMapEntryPtr(u16 x, u16 y, u8 layer);  // the block map entry covering pixel (x, y)
extern u32 ReleaseBgTileCacheEntry(u16 tileId, u32 sizeClass, u32 layer);
extern u32 AcquireBgTileCacheEntry(u32 tileId, u32 sizeClass, u32 unused, u32 layer);
extern void FreeBgTileBitOffsets(void);            // frees the room BG state's two blocks (0x030058A0)
extern void WriteRoomBgBlock(u16 x, u16 y, u16 blockId, u8 layer);
extern u16 GetRoomBgBlockEntry(u16 x, u16 y, u8 layer);  // the room BG entry WriteRoomBgBlock writes

// Set or clear bits 1, 2 and 3 of g_RoomBgAux.bFlags, and set its two positions.
extern void SetRoomBgAuxFlag2(void);
extern void ClearRoomBgAuxFlag2(void);
extern void SetRoomBgAuxFlag4(void);
extern void ClearRoomBgAuxFlag4(void);
extern void SetRoomBgAuxFlag8(void);
extern void ClearRoomBgAuxFlag8(void);
extern void SetRoomBgAuxPosA(const s32 *pos);
extern void SetRoomBgAuxPosB(const s32 *pos);
extern void GetRoomBgLayer0SizePixels(s32 *size);
extern void GetRoomBgLayer1SizePixels(s32 *size);
extern void DisableBgLayerScroll(u32 layer);
extern void EnableBgLayerScroll(u32 layer);

extern void LoadRoomBgTilemap0(const void *pTilemap);
extern void LoadRoomBgTilemap1(const void *pTilemap);
extern void LoadRoomBgTilemap2(const void *pTilemap);
extern void LoadRoomBgTilemap3(const void *pTilemap);
extern void LoadRoomBgBlockTiles1(const void *pBlockTiles, u32 unused8, u32 unusedC);
extern void LoadRoomBgBlockTiles2(const void *pBlockTiles, u32 unused8, u32 unusedC);
extern void LoadRoomBgBlockTiles3(const void *pBlockTiles, u32 unused8, u32 unusedC);
extern void SetupRoomBgControlAndTilesets(u32 ctrl3, u32 ctrl1, u32 ctrl2, u32 ctrl0,
                                                   RoomBgResources resourcesA, RoomBgResources resourcesB);
