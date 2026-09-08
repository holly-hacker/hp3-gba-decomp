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
