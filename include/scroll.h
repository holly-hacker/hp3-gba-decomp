#pragma once

#include "types.h"
#include "camera.h"
#include "arm_routines.h"

// A BG tileset and its palette. Tileset A (layers 0 and 3) and tileset B
// (layers 1 and 2) each pair with one; the second pair's palette is not
// confirmed to be read.
typedef struct RoomBgResources {
    const void *pTileset;
    const void *pPalette;
} RoomBgResources;

// World-space camera origin used for actor visibility.
extern CameraFocusOffset g_CameraPosition_candidate;

// Pixel size of the current room.
typedef struct RoomSizePixels {
    u32 dwWidth;
    u32 dwHeight;
} RoomSizePixels;

extern RoomSizePixels g_RoomSizePixels;

// Updates g_CameraPosition_candidate from the followed actor and streams BG
// tiles on demand as it crosses tile boundaries.
extern void UpdateOverworldCamera_candidate(u32 mode);
extern void sub_0803DB68(void);
extern void sub_0803DC44(void);
extern void LoadRoomBgLayer0Extra_candidate(const void *pExtra, u32 arg1, u32 arg2);
extern void GetCameraPosition(s32 *pPosition);  // copies g_CameraPosition_candidate out
extern void SetCameraPosition(const s32 *pPosition);  // copies a two-word position into g_CameraPosition_candidate
extern void ResetCameraPosition(void);  // zeroes g_CameraPosition_candidate

// Nonzero for each BG layer UpdateOverworldCamera_candidate scrolls.
extern u32 g_adwBgScrollEnabled[4];
extern u32 g_dwUnk030059AC;  // zeroed by InitRoomBgState_candidate; no other literal reference found

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
    u32 dwUnk00;
    u32 dwUnk04;
    u32 *pTileBitOffsets;  // ROM bit offset of each tile's compressed data, indexed by tile id
    const BgTileCodeTable *pCodeTable;
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
extern s32 g_BgScroll[2];        // scroll position (x, y) the layers' tiles are streamed for
extern s32 g_BgLoadedScroll[2];  // g_BgScroll as of the last tile load
extern void InitRoomBgState_candidate(void);
extern u16 FindBgTileCacheEntry(u16 tileId, u32 sizeClass);
typedef struct RoomBgAux {
    u8 bFlags;
    u8 pad_01[3];
    s32 aPosA[2];
    s32 aPosB[2];
} RoomBgAux;
extern RoomBgAux g_RoomBgAux;
extern u16 g_wRoomBgLayer0BlocksWide;
extern u16 g_wRoomBgLayer1TilesWide;
extern u16 g_wRoomBgLayer1TilesHigh;
extern u16 g_wRoomBgLayer1BlocksWide;
extern u16 g_wRoomBgLayer2BlocksWide;
extern u16 g_wRoomBgLayer3BlocksWide;
extern u16 *GetRoomBgBlockMapEntryPtr(u16 x, u16 y, u8 layer);  // the block map entry covering pixel (x, y)
extern u32 ReleaseBgTileCacheEntry(u16 tileId, u32 sizeClass, u32 layer);
extern u32 DecompressBgTileToVram_candidate(u32 tileId, u32 sizeClass, u32 arg2, u32 layer);
extern void sub_0803EA3C(void);            // frees the room BG state's two blocks (0x030058A0)
extern void WriteRoomBgTile_candidate(u16 x, u16 y, u16 tileId, u8 layer);
extern u16 GetRoomBgBlockEntry(u16 x, u16 y, u8 layer);  // the room BG entry WriteRoomBgTile_candidate writes

// Set or clear bits 1, 2 and 3 of g_RoomBgAux.bFlags, and set its two positions.
extern void SetRoomBgAuxFlag2(void);
extern void ClearRoomBgAuxFlag2(void);
extern void SetRoomBgAuxFlag4(void);
extern void ClearRoomBgAuxFlag4(void);
extern void SetRoomBgAuxFlag8(void);
extern void ClearRoomBgAuxFlag8(void);
extern void SetRoomBgAuxPosA(const s32 *pos);
extern void SetRoomBgAuxPosB(const s32 *pos);
extern void GetRoomBgLayer1SizePixels(s32 *size);
extern void DisableBgLayerScroll(u32 layer);
extern void EnableBgLayerScroll(u32 layer);

extern void LoadRoomBgTilemap0_candidate(const void *pTilemap);
extern void LoadRoomBgTilemap1_candidate(const void *pTilemap);
extern void LoadRoomBgTilemap2_candidate(const void *pTilemap);
extern void LoadRoomBgTilemap3_candidate(const void *pTilemap);
extern void LoadRoomBgLayer1Extra_candidate(const void *pExtra, u32 arg1, u32 arg2);
extern void LoadRoomBgLayer2Extra_candidate(const void *pExtra, u32 arg1, u32 arg2);
extern void LoadRoomBgLayer3Extra_candidate(const void *pExtra, u32 arg1, u32 arg2);
extern void SetupRoomBgControlAndWindows_candidate(u32 ctrl3, u32 ctrl1, u32 ctrl2, u32 ctrl0,
                                                   RoomBgResources resourcesA, RoomBgResources resourcesB);
