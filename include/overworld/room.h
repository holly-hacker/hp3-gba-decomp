#pragma once

#include "types.h"
#include "graphics/object.h"
#include "overworld/room_script.h"
#include "overworld/room_object_state.h"

// A pixel coordinate in room space, passed by value.
typedef struct PixelPoint {
    u32 x;
    u32 y;
} PixelPoint;

extern u32 GetCollisionTypeAtPixel_candidate(PixelPoint pixel);  // 0x0802D7A0, see docs/formats/collision.md
extern u32 IsBlockingCollisionType(u32 type);  // 0x0802DF28, nonzero for types 1-25

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
// Entries 0 and 1 of the Time-Turner cutscene's own table, ROM 0x0806BE38 (US).
extern const RoomTableEntry g_aTimeTurnerCutsceneRoomTable[2];

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
// Read here as a full word, not the byte docs/memory-map/game_modes.md's
// plate comment describes elsewhere -- real source likely declares it int.
extern u32 g_bCurrentRoomId;                // 0x03003B50
extern void GetCameraPosition(s32 *pPosition);  // copies g_CameraPosition_candidate out
extern void SetCameraPosition(const s32 *pPosition);  // copies a two-word position into g_CameraPosition_candidate
// Signed camera Y offset in pixels, added to quest event state 0x1B (sub_0803E45C).
extern s8 g_nCameraYOffset;
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
extern void InitRoomBgState_candidate(void);
extern u16 FindBgTileCacheEntry(u16 tileId, u32 sizeClass);
extern void sub_0803EA3C(void);            // frees the room BG state's two blocks (0x030058A0)

extern u16 g_wRoomResourceFlags_candidate;
extern u8 g_abQuestEventState[];

// Fixed indices into g_abQuestEventState; see docs/formats/save.md ("Quest event state").
// Keep these in sync with the QUEST_* .set definitions in asm/room_script.inc.
#define QUEST_STORY_STAGE            0x00
#define QUEST_DEFEAT_WARP_SELECTOR   0x10
#define QUEST_CASTLE_AREA            0x11
#define QUEST_PREV_STORY_STAGE       0x12
#define QUEST_FOLIO_REWARD_FIRST     0x14
#define QUEST_FOLIO_REWARD_LAST      0x18
#define QUEST_OBJECTIVE_INDEX        0x19
#define QUEST_ALT_PRESENTATION       0x1A
#define QUEST_CAMERA_Y_OFFSET        0x1B
#define QUEST_COMPLETION_COUNT       0x1C
#define QUEST_ROOM_BG_VARIANT        0x1D
#define QUEST_UPPER_HALF_FIRST       0x80
#define QUEST_SPAWN_ID_COPY          0xFE
#define QUEST_SCRATCH_RESULT         0xFF

// Leaky Cauldron cellar event flags. Indices 0xDF-0xFD are chapter-scoped scratch: most are reused
// with different meanings in different chapters, so only indices used by a single event are named.
#define QUEST_CELLAR2_XP5_GIVEN           0xEE
#define QUEST_CELLAR2_XP20_GIVEN          0xEF
#define QUEST_CELLAR2_CROOKSHANKS_CAUGHT  0xF2
#define QUEST_CELLAR1_RAT_TONIC_FOUND     0xF3
#define QUEST_CELLAR1_INTRO_DIALOG_SHOWN  0xF7
#define QUEST_CELLAR2_SCABBERS_CAUGHT     0xFC

// Main-menu objective values for QUEST_OBJECTIVE_INDEX (dialog text 0x924 + value).
// Names follow the objective text; _UNUSED values are never set by any room script.
#define QUEST_OBJ_TALK_TO_FUDGE_UNUSED                 0
#define QUEST_OBJ_FIND_HARRYS_ROOM_UNUSED              1
#define QUEST_OBJ_GREET_WEASLEYS                       2
#define QUEST_OBJ_TALK_TO_TOM_UNUSED                   3
#define QUEST_OBJ_FIND_RAT_TONIC                       4
#define QUEST_OBJ_DELIVER_RAT_TONIC_TO_RON             5
#define QUEST_OBJ_FIND_SCABBERS_LEAKY_CAULDRON         6
#define QUEST_OBJ_FIND_CROOKSHANKS                     7
#define QUEST_OBJ_LEAVE_CELLAR_UNUSED                  8
#define QUEST_OBJ_FIND_YOUR_SEAT                       9
#define QUEST_OBJ_FIND_TREVOR                          10
#define QUEST_OBJ_BLOCK_THE_DOORS_UNUSED               11
#define QUEST_OBJ_FIND_CHOCOLATE                       12
#define QUEST_OBJ_FIND_CONDUCTOR                       13
#define QUEST_OBJ_FIND_COMMON_ROOM                     14
#define QUEST_OBJ_GO_TO_TRANSFIGURATION                15
#define QUEST_OBJ_FIND_MCGONAGALL                      16
#define QUEST_OBJ_GO_TO_CARE_OF_MAGICAL_CREATURES      17
#define QUEST_OBJ_FIND_ESCAPED_BOOKS                   18
#define QUEST_OBJ_GO_TO_POTIONS                        19
#define QUEST_OBJ_FIND_POTION_INGREDIENTS              20
#define QUEST_OBJ_RETURN_INGREDIENTS_TO_SNAPE          21
#define QUEST_OBJ_GO_TO_STAFF_ROOM                     22
#define QUEST_OBJ_GO_TO_COMMON_ROOM_AFTER_POTIONS      23
#define QUEST_OBJ_FIND_SCABBERS_COMMON_ROOM            24
#define QUEST_OBJ_FIND_FAT_LADY                        25
#define QUEST_OBJ_GO_TO_DADA                           26
#define QUEST_OBJ_GO_TO_LIBRARY_FOR_DADA               27
#define QUEST_OBJ_FIND_BOOK_PAGES                      28
#define QUEST_OBJ_RETURN_TO_DADA                       29
#define QUEST_OBJ_GO_TO_COMMON_ROOM_AFTER_DADA         30
#define QUEST_OBJ_GO_TO_HAGRIDS_HUT_FIRST              31
#define QUEST_OBJ_GO_TO_LIBRARY_FOR_HERMIONE           32
#define QUEST_OBJ_FIND_HERMIONE                        33
#define QUEST_OBJ_GO_TO_GREAT_HALL                     34
#define QUEST_OBJ_GO_TO_LUPINS_OFFICE                  35
#define QUEST_OBJ_GO_TO_COMMON_ROOM_AFTER_LUPIN        36
#define QUEST_OBJ_GO_TO_BOYS_DORMITORY                 37
#define QUEST_OBJ_GO_TO_COMMON_ROOM_LATE_UNUSED        38
#define QUEST_OBJ_GO_TO_BOYS_DORMITORY_LATE_UNUSED     39
#define QUEST_OBJ_GO_TO_ENTRANCE_HALL_UNUSED           40
#define QUEST_OBJ_RETURN_TO_COMMON_ROOM_UNUSED         41
#define QUEST_OBJ_GO_TO_BOYS_DORMITORY_FINAL_UNUSED    42
#define QUEST_OBJ_FIND_RON_AND_HERMIONE                43
#define QUEST_OBJ_GO_TO_HAGRIDS_HUT_SECOND             44
#define QUEST_OBJ_GO_TO_WHOMPING_WILLOW                45
#define QUEST_OBJ_FIND_PATH_BENEATH_WILLOW             46
#define QUEST_OBJ_FOLLOW_PATH_TO_SHRIEKING_SHACK       47
#define QUEST_OBJ_RETURN_TO_HOGWARTS                   48
#define QUEST_OBJ_WALK_TO_LAKE                         49
#define QUEST_OBJ_SECRET_PATH_TO_HAGRIDS_HUT           50
#define QUEST_OBJ_GO_TO_HAGRIDS_HUT_LATE_UNUSED        51
#define QUEST_OBJ_GO_BACK_TO_LAKE                      52
#define QUEST_OBJ_GO_TO_ROOFTOP                        53
#define QUEST_OBJ_SPEAK_TO_WEASLEYS                    54
#define QUEST_OBJ_FIND_RON                             55
#define QUEST_OBJ_RETURN_TO_LUPIN                      56
#define QUEST_OBJ_RESCUE_SIRIUS                        57
#define QUEST_OBJ_FIND_HIPPOGRIFF_BAITING_BOOK_UNUSED  58
extern u32 g_dwOverworldMonstersDisabled;
extern u8 g_bPendingQuestStateOverride_candidate;
extern u32 g_dwRoomBgFlag_candidate;
extern u32 g_dwPendingCameraFocusFlag;

// One animated room tile, stepped by TickRoomTileAnimations_candidate; see
// docs/memory-map/frame_systems.md.
typedef struct RoomTileAnimation {
    u8 bSet;
    u8 bStep;
    u8 bDelay;
    u8 bFlags;
    u16 wX;
    u16 wY;
} RoomTileAnimation;

#define MAX_ROOM_TILE_ANIMATIONS 32
extern RoomTileAnimation *g_aRoomTileAnimations;
extern u32 g_dwRoomTileAnimationCount;

extern void InitRoomTileAnimationTable(void);

// Snapshot of the current room's non-default objects; see docs/formats/save.md.
#define ROOM_OBJECT_STATE_BUFFER_SIZE 0x20BC
extern void InitRoomState(void);
extern void InitRoomScriptState_candidate(void);
extern void RestoreRoomObjectState(void);
extern void RestoreRoomObjectStateMinimal(void);
extern u8 sub_08005DC0(u32 questState, const void *pRoomResourceBlob);
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
extern void SetCameraFollowTarget_candidate(Object *pTarget, CameraFocusOffset offset, u32 slot);
extern void sub_0800A348(u32 arg0, u32 arg1);
extern void sub_080248E8(void);
extern void sub_0801FA9C(void);
extern void StopScanlineEffects(void);
extern void sub_0802B20C(void);
extern void InitObjTileAllocBitmaps(u8 bgMode);
extern void ShowMapNamePopup(void);
extern void OverworldVBlankCallback(void);
extern void ClearScanlineEffects(void);
