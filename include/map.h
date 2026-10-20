#pragma once

#include "types.h"
#include "actor.h"
#include "color.h"
#include "char_block.h"
#include "overworld/room.h"
#include "overworld/room_actor_state.h"

extern void InitializeOverworld(void);
extern void ExitOverworldScreen(void);
// Loads the room's alternate (night) BG palette while QUEST_ALT_PRESENTATION is set.
extern void LoadRoomAltPresentationPalette(void);
void DeserializeRoomActorState(void);
void SerializeRoomActorState(void);
extern void CaptureRoomActorState(void);
extern void RestoreRoomActorState(void);
extern void RestoreRoomActorStateMinimal(void);
extern void HandleOverworldPauseMenuInput(void);
extern void InitRoomState(void);
extern void UpdateOverworld(void);
// CaptureRoomActorState for ExitOverworldScreen, when leaving for a mode that returns to the room.
extern void SaveRoomActorStateOnExit(void);
// Empty and unreferenced.
extern void NoopOverworldUnusedA(void);
extern void NoopOverworldUnusedB(void);
// Multi-slot bookkeeping that only acts when the slot count exceeds 1.
// Always returns 0.
s32 TickOverworldControlSlots_candidate(void);
extern void TickOverworldBeforeActors_candidate(void);
extern void ClearRoomActorStateBuffer(void);  // memsets g_pRoomActorStateBuffer (0x20BC bytes); see docs/formats/save.md
extern u32 SetRoomSwitchState(u32 state);  // returns nonzero if the state changed
// Starts the first slot's camera shake with no time limit and plays its cue.
extern void StartEndlessCameraShake(void);
extern void OverworldVBlankCallback(void);
extern void RegisterRoomBgTileAnimation(const BgTileAnimHeader *pAnimation);
// Empty; InitializeOverworld calls it after loading the room's shared tileset.
extern void NoopOverworldRoomLoad(void);
// FreeBgTileBitOffsets for ExitOverworldScreen.
extern void FreeOverworldBgTileBitOffsets(void);

// Wandering-monster overworld state (see docs/formats/encounters.md).
// Touching a wandering monster records its encounter id and kind here;
// every fifth touch respawns replacements via TrySpawnWanderingMonster
// (see HandleWanderingMonsterTouch). Cleared on room load by
// SpawnOverworldMonsterEncounters below.
typedef struct TouchedMonsterRecord {
    u8 bEncounterId;
    u8 bKind;
} TouchedMonsterRecord;  // 4 bytes after agbcc's rounding

extern u8 g_bTouchedMonsterRecordCount;
extern TouchedMonsterRecord g_aTouchedMonsterRecords[5];
extern Actor *g_pTouchedWanderingMonster;

// Read here as a full word, not the byte docs/memory-map/game_modes.md's
// plate comment describes elsewhere -- real source likely declares it int.
extern u32 g_bCurrentRoomId;
extern u8 g_bControlSlotTicks_candidate;
extern u8 g_bPendingQuestStateOverride_candidate;
extern u32 g_dwRoomBgFlag_candidate;
// Nonzero blocks the overworld Start/Select menus (SetPauseMenuLocked).
extern u32 g_dwPauseMenuLocked;
extern u8 g_bRoomSwitchState;  // 0 or 1
extern RoomActorStateBuffer *g_pRoomActorStateBuffer;
// Frames until Start/Select may open a menu again; 4 after room init and
// each menu open, counted down by UpdateOverworld.
extern u32 g_dwPauseMenuCooldown;

// A wandering-monster spawn position in room pixels.
typedef IntPoint SpawnPosition;

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
s32 FindWanderingMonsterSpawnPosition(SpawnPosition *pOutPos, u32 terrainType, const SpawnPosition *pPlacedPositions, u32 placedCount);
// Strongest-damage monster id among one variant cell's slots 0-2.
u32 PickMaxDamageMonster(const u8 *pSlots);
// Create one wandering-monster actor.
Actor *SpawnWanderingMonsterActor(u8 monsterId, u16 x, u16 y, u8 encounterId, u8 variant, u8 kind);
// Spawn one replacement wandering monster of the encounter's kind, at a random
// position of its spawn terrain; gives up after 200 attempts.
void TrySpawnWanderingMonster(u32 encounterId, u32 kind);
void TickWanderingMonsterActor(Actor *pActor);
void HandleWanderingMonsterCollision(Actor *pSelf, Actor *pOther);
void PickWanderingMonsterRoamTarget(Actor *pActor);
u32 TrySetWanderingMonsterMoveTarget(Actor *pActor, s32 x, s32 y);
void ResetWanderingMonsterTouchState(void);
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

// Wandering-monster resources, src/map/wandering_monster.globals.c.
extern const u32 g_adwEncounterKindTerrainTypes[3];
extern const ActorAssetRecord g_UnknownWanderingMonsterAsset;
extern const ActorGfxRecord g_UnusedWanderingMonsterGfx;
extern const u8 g_WanderingMonsterAnimData[];
extern const u8 g_UnknownWanderingMonsterAnimData[];
