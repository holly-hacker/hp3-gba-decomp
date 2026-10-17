#pragma once

#include "types.h"
#include "actor.h"
#include "color.h"
#include "graphics/display.h"
#include "overworld/room.h"

extern void InitializeOverworld(void);
extern void ExitOverworldScreen(void);
void DeserializeRoomActorState(void);
void SerializeRoomActorState(void);
extern void RestoreRoomActorState(void);
extern void RestoreRoomActorStateMinimal(void);
extern void HandleOverworldPauseMenuInput(void);
extern void InitRoomState(void);
extern void UpdateOverworld(void);
extern void sub_0802B08C(void);
// Multi-slot bookkeeping that only acts when the slot count exceeds 1.
// Always returns 0.
s32 TickOverworldControlSlots_candidate(void);
extern void TickOverworldBeforeActors_candidate(void);
extern void ClearRoomActorStateBuffer(void);  // memsets g_pRoomActorStateBuffer (0x20BC bytes); see docs/formats/save.md
extern u32 SetRoomSwitchState(u32 state);  // returns nonzero if the state changed
// Starts the first slot's camera-shake effect and plays its cue.
extern void sub_0802B138(void);
extern void OverworldVBlankCallback(void);
extern void ApplyRoomBgControlOverride_candidate(const void *pOverride);
extern void sub_0802B20C(void);
extern void sub_0802B210(void);

// Wandering-monster overworld state (see docs/formats/encounters.md).
// Touching a wandering monster records its encounter id and kind here;
// every fifth touch respawns replacements via TrySpawnWanderingMonster
// (see HandleWanderingMonsterTouch). Cleared on room load by
// SpawnOverworldMonsterEncounters below.
extern u8 g_bTouchedMonsterRecordCount;
extern u8 g_abTouchedMonsterRecords[20];
extern Actor *g_pTouchedWanderingMonster;

// 8-byte wandering-monster spawn-position record, two words.
// Only the low halves reach SpawnWanderingMonsterActor;
// FindWanderingMonsterSpawnPosition fills both words.
typedef struct SpawnPosition {
    u32 x;
    u32 y;
} SpawnPosition;

// Room load: spawn each kind's level-table count (offsets 0x74-0x76) of
// wandering monsters for encounter id (level-table offset 0x77), picking
// each spawn's random variant up front. See docs/formats/encounters.md.
void SpawnOverworldMonsterEncounters(u32 countA, u32 countB, u32 countC, u32 encounterId);
// Collision-type table lookup by encounter kind, selecting the spawn
// terrain for that kind.
u32 GetEncounterKindTerrainType(u32 kind);
// Find a valid spawn position for one monster, recording it in the
// placed-position buffer for overlap checks. Returns 0 after 200 failed
// attempts.
s32 FindWanderingMonsterSpawnPosition(u32 *pOutPos, u32 terrainType, SpawnPosition *pPlacedPositions, u32 placedCount);
// Strongest-damage monster id among one variant cell's slots 0-2.
u32 PickMaxDamageMonster(const u8 *pSlots);
// Create one wandering-monster actor.
void SpawnWanderingMonsterActor(u8 monsterId, u16 x, u16 y, u8 encounterId, u8 variant, u8 kind);
// Records wandering-monster touches and respawns replacements; see the
// wandering-monster notes above.
extern void HandleWanderingMonsterTouch(void);

// BGxCNT values applied to each BG layer at room load.
extern const u32 g_dwBg2Control;
extern const u32 g_dwBg1Control;
extern const u32 g_dwBg3Control;
extern const u32 g_dwBg0Control;

// Scene-effect resources selected by room-script opcode 0x33.
extern const BgTileAnimation128 g_aSpecialSceneBg2;  // 0x08063074
extern const BgTileAnimation128 g_aSpecialSceneBg0;  // 0x0806347C
extern const BgTileAnimation128 g_aSpecialSceneBg1;  // 0x08063884

extern const RoomTableEntry g_aRoomTable[55];  // ROM 0x08063C8C

// Krawall module id per room, read as a byte at [room * 4]; used instead of
// bDefaultMusicModule while quest event state 0x1A is set.
extern const u32 g_adwRoomQuestMusicOverride[55];

extern const ColorCycleTable g_ColorCyclesDefault;
extern const ColorCycleTable g_ColorCyclesRoom12;
