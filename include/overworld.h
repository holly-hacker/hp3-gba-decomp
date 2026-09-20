#pragma once

#include "types.h"
#include "battle.h"
#include "encounters.h"

// Wandering-monster overworld state (see docs/formats/encounters.md).
// Touching a wandering monster records its encounter id and kind here;
// every fifth touch respawns replacements via TrySpawnWanderingMonster
// (see HandleWanderingMonsterTouch). Cleared on room load by
// SpawnOverworldMonsterEncounters below.
extern u8 g_bTouchedMonsterRecordCount;
extern u8 g_abTouchedMonsterRecords[20];
extern Object *g_pTouchedWanderingMonster;

// 8-byte wandering-monster spawn-position record, two words.
// Only the low halves reach SpawnWanderingMonsterObject;
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
// Create one wandering-monster object.
void SpawnWanderingMonsterObject(u8 monsterId, u16 x, u16 y, u8 encounterId, u8 variant, u8 kind);

// Controllable-character slots: each 16-byte entry starts with the Object the
// player steers; only slot 0 is ever populated.
typedef struct OverworldControlSlot {
    Object *pObject;
    u8 aUnknown4[12];
} OverworldControlSlot;

typedef struct OverworldControlState {
    OverworldControlSlot aSlots[2];
    // Set to 1 by InitializeOverworld; no other writer found.
    u8 bSlotCount;
    // Active entry of aSlots.
    u8 bSlotIndex;
} OverworldControlState;

extern OverworldControlState g_OverworldControlState;

extern Object *g_pPlayerObject;
// The two party followers' objects; NULL while the slot is empty.
extern Object *g_pFollowerObject0;
extern Object *g_pFollowerObject1;
// Character ids of the leader and the two follower slots.
extern u8 g_bPartyCharId0;
extern u8 g_bPartyCharId1;
extern u8 g_bPartyCharId2;

// Per-slot queued object move, driven by room scripts. Only the state byte is
// known; the array has one record per control slot.
typedef struct QueuedObjectMove {
    u8 pad_00[0x25];
    u8 bState;  // 0 = idle
    u8 pad_26[0x06];
} QueuedObjectMove;
extern QueuedObjectMove g_aQueuedObjectMoves[];
extern u8 g_bControlSlotTicks_candidate;

// Nonzero blocks the overworld Start/Select menus (SetPauseMenuLocked).
extern u32 g_dwPauseMenuLocked;
// Frames until Start/Select may open a menu again; 4 after room init and
// each menu open, counted down by UpdateOverworld.
extern u32 g_dwPauseMenuCooldown;

// Multi-slot bookkeeping that only acts when the slot count exceeds 1.
// Always returns 0.
s32 TickOverworldControlSlots_candidate(void);
// Advances the Owl Care Kit's timers and need counters while walking around.
void TickOwlCareKitFromOverworld(void);
