#pragma once

#include "types.h"
#include "object.h"
#include "room_script.h"

// A BG tileset and its palette. Tileset A (layers 0 and 3) and tileset B
// (layers 1 and 2) each pair with one; the second pair's palette is not
// confirmed to be read.
typedef struct RoomBgResources {
    const void *pTileset;
    const void *pPalette;
} RoomBgResources;

// One 124-byte record per room, indexed by room id; 55 entries. See
// docs/formats/levels.md. The pointers reference ROM resources.
typedef struct RoomTableEntry {
    const void *pBgTilemap0;
    const void *pBgLayer0Extra;
    u32 dwUnused0_8;
    u32 dwUnused0_c;
    const void *pBgTilemap1;
    const void *pBgLayer1Extra;
    u32 dwUnused1_8;
    u32 dwUnused1_c;
    const void *pBgTilemap2;
    const void *pBgLayer2Extra;
    u32 dwUnused2_8;
    u32 dwUnused2_c;
    const void *pBgTilemap3;
    const void *pBgLayer3Extra;
    u32 dwUnused3_8;
    u32 dwUnused3_c;
    const void *pCollisionBehaviorTable;
    const void *pCollisionTilemap;
    u32 dwUnused_48;
    u32 dwUnused_4c;
    const void *pRoomResourceBlob;
    RoomBgResources aBgResources[2];
    const void *pBgControlOverrideA;
    const void *pBgControlOverrideB;
    u16 wScrollBoundMinX;
    u16 wScrollBoundMinY;
    u16 wScrollBoundMaxX;
    u16 wScrollBoundMaxY;
    u8 bEncounterCountA;
    u8 bEncounterCountB;
    u8 bEncounterCountC;
    u8 bEncounterVariant;
    u8 bDefaultMusicModule;
    u8 bUnused_79;
    u8 bUnused_7a;
    u8 bUnused_7b;
} RoomTableEntry;

extern const RoomTableEntry g_aRoomTable[55];  // ROM 0x08063C8C

// Krawall module id per room, read as a byte at [room * 4]; used instead of
// bDefaultMusicModule while quest event state 0x1A is set.
extern const u32 g_adwRoomQuestMusicOverride[55];

// BGxCNT values applied to each BG layer at room load.
extern const u32 g_dwBg2Control;
extern const u32 g_dwBg1Control;
extern const u32 g_dwBg3Control;
extern const u32 g_dwBg0Control;

// Camera offset applied to the player's follow target.
typedef struct CameraFocusOffset {
    s32 nX;
    s32 nY;
} CameraFocusOffset;
extern const CameraFocusOffset g_PlayerCameraFocusOffset;
extern CameraFocusOffset g_CameraPosition_candidate;

// One band of scanlines for SetupScanlineBands_candidate.
typedef struct ScanlineBand {
    u8 bStartLine;
    u8 bLineCount;
    u8 bParam_candidate;
    u8 bFlags;
} ScanlineBand;

typedef struct ScanlineBandTable {
    u16 wBandCount;
    u16 wUnused;
    ScanlineBand aBands[1];
} ScanlineBandTable;

extern const ScanlineBandTable g_ScanlineBandsDefault;
extern const ScanlineBandTable g_ScanlineBandsRoom12;
extern void SetupScanlineBands_candidate(const ScanlineBandTable *pTable);
extern u32 g_dwScanlineBandActiveMask;

extern u16 g_wRoomResourceFlags_candidate;
extern u8 g_abQuestEventState[];
extern u32 g_dwOverworldMonstersDisabled;
extern u8 g_bPendingQuestStateOverride_candidate;
extern u32 g_dwRoomBgFlag_candidate;
extern u32 g_dwPendingCameraFocusFlag;

extern void RestoreRoomObjectState(void);
extern void RestoreRoomObjectStateMinimal(void);
extern u8 sub_08005DC0(u32 questState, const void *pRoomResourceBlob);
extern void ParseRoomResourceBlob_candidate(const void *pBlob);
extern u32 SetRoomSwitchState(u32 state);
extern u32 GetRoomSwitchState(void);
extern void ApplyRoomSwitchEffect(u32 state);

extern void LoadRoomBgTilemap0_candidate(const void *pTilemap);
extern void LoadRoomBgTilemap1_candidate(const void *pTilemap);
extern void LoadRoomBgTilemap2_candidate(const void *pTilemap);
extern void LoadRoomBgTilemap3_candidate(const void *pTilemap);
extern void LoadRoomBgLayer0Extra_candidate(const void *pExtra, u32 arg1, u32 arg2);
extern void LoadRoomBgLayer1Extra_candidate(const void *pExtra, u32 arg1, u32 arg2);
extern void LoadRoomBgLayer2Extra_candidate(const void *pExtra, u32 arg1, u32 arg2);
extern void LoadRoomBgLayer3Extra_candidate(const void *pExtra, u32 arg1, u32 arg2);
extern void SetupRoomBgControlAndWindows_candidate(u32 ctrl3, u32 ctrl1, u32 ctrl2, u32 ctrl0,
                                                   RoomBgResources resourcesA, RoomBgResources resourcesB);
extern void LoadRoomSharedTileset_candidate(const void *pCollisionBehaviorTable, const void *pCollisionTilemap);
extern void ApplyRoomBgControlOverride_candidate(const void *pOverride);
extern void SetRoomScrollBounds(u32 minX, u32 minY, u32 maxX, u32 maxY);
extern Object *SpawnPlayerObject_candidate(u32 charId);
extern void SetCameraFollowTarget_candidate(Object *pTarget, s32 nOffsetX, s32 nOffsetY, u32 slot);
extern void sub_0800A348(u32 arg0, u32 arg1);
extern void sub_080248E8(void);
extern void sub_0801FA9C(void);
extern void StopScanlineEffects(void);
extern void sub_0802B20C(void);
extern void InitObjTileAllocBitmaps(u32 arg);
extern void ShowMapNamePopup(void);
extern void OverworldVBlankCallback(void);
extern void ClearScanlineEffects(void);
