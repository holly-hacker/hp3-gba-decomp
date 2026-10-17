#pragma once

#include "types.h"
#include "actor.h"
#include "scroll.h"

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

// Snapshot of the current room's non-default actors; see docs/formats/save.md.
#define ROOM_ACTOR_STATE_BUFFER_SIZE 0x20BC
extern u32 GetRoomSwitchState(void);
extern Actor *SpawnPlayerActor_candidate(u32 charId);
extern void ShowMapNamePopup(void);
