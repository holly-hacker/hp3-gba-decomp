#pragma once

#include "types.h"
#include "camera.h"
#include "battle/battle.h"
#include "battle/encounters.h"

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

// Controllable-character slots: each 16-byte entry starts with the Actor the
// player steers; only slot 0 is ever populated.
typedef struct OverworldControlSlot {
    Actor *pActor;
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

extern Actor *g_pPlayerActor;
// The two party followers' actors; NULL while the slot is empty.
extern Actor *g_pFollowerActor0;
extern Actor *g_pFollowerActor1;
// Character ids of the leader and the two follower slots.
extern u8 g_bPartyCharId0;
extern u8 g_bPartyCharId1;
extern u8 g_bPartyCharId2;

// Party member sprites and animations, set by SetPartyMemberAnim. The record arrays are
// indexed by character id, the animation tables by Actor.bFacing.
#define PARTY_CHARACTER_COUNT 9
typedef enum {
    PartyAnimStand = 0,
    PartyAnimWalk = 1,
    PartyAnimCast = 2,  // ends on ANIM_EVENT, which triggers the field spell
    PartyAnim3 = 3,
    PartyAnim4 = 4,
} PartyAnim;
extern void SetPartyMemberAnim(Actor *actor, u8 anim);
// Spawns the effect actor of field spell `spell` (an Actor.bFighterIndex value) at
// the caster's anchor 0.
extern void SpawnFieldSpellEffect_candidate(Actor *caster, u8 spell);
// Starts the cast of the selected field spell (action state 0x13).
extern void StartFieldSpellCast(Actor *actor);
// Sets (1) or clears (0) ActorFlagVisible on g_pPlayerShadowActor_candidate.
extern void SetPlayerShadowVisible(u32 visible);
extern void TickHeldRewardActor(Actor *actor);  // pfnTick of the item TickActorReceiveReward spawns
extern Actor *g_pPlayerShadowActor_candidate;
extern const ActorGfxRecord g_UnusedPartyGfx;
extern const ActorGfxRecord g_PartyFocusGfx_candidate;
extern const ActorAssetRecord g_aPartyWalkAssets[PARTY_CHARACTER_COUNT];
extern const ActorAssetRecord g_aPartyAnim3Assets[PARTY_CHARACTER_COUNT];
extern const ActorAssetRecord g_aPartyCastAssets[PARTY_CHARACTER_COUNT];
extern const ActorAssetRecord g_aPartyAnim4Assets[PARTY_CHARACTER_COUNT];
extern const u8 g_abPartyStandFrames[8];
extern const u8 g_abPartyStandFramesChar8[8];
extern const u8 g_aPartyWalkAnims[8][18];
extern const u8 g_aPartyWalkAnimsChar8[8][14];
extern const u8 g_aPartyWalkAnimsChar4[8][18];
extern const u8 g_aPartyCastAnims[8][18];
extern const u8 g_aPartyAnim4Anims[8][4];
extern const u8 g_abPartyAnim3Anim[22];
extern const ActorGfxRecord g_UnusedPartyGfx2;
// Index into the 9-entry field spell table at 0x08060BAC: {u32 spell,
// u8 FighterType, u8 minimum bKnownSpellCount}. Flipendo, Lumos and Diffindo
// for Harry, Flipendo, Reparo and Glacius for Hermione, Flipendo, Alohomora
// and Spongify for Ron; Diffindo and Spongify need 5 known spells, Glacius 6.
// CyclePartyLeaderSelection_candidate steps it; it is saved with the party.
extern u8 g_bSelectedFieldSpell;
// HUD actors, cleared by ResetPartyState and freed by sub_08024BD4.
extern Actor *g_pFieldSpellNameActor;       // selected spell's name text (sub_08023A2C)
extern Actor *g_pMapNameTextActor;          // room name text (ShowMapNamePopup)
extern Actor *g_pFieldSpellPortraitActor;   // face portrait of the spell's character (sub_08023A2C)
extern Actor *g_pMapNamePopupActor;         // 240x16 bar sprite behind the room name (ShowMapNamePopup)
extern u32 g_dwUnk030033A8;  // zeroed by ResetPartyState and sub_080248E8; no reader found

extern void ResetPartyState(void);

// Starts the first slot's camera-shake effect and plays its cue.
extern void sub_0802B138(void);

extern u8 g_bControlSlotTicks_candidate;
extern void TickOverworldBeforeActors_candidate(void);
// Updates g_CameraPosition_candidate from the followed actor and streams BG
// tiles on demand as it crosses tile boundaries.
extern void UpdateOverworldCamera_candidate(u32 mode);
extern void HandleOverworldPauseMenuInput(void);
// Set by the room chain runner while it processes a chain; consumed (cleared)
// once per frame by HandleOverworldPauseMenuInput.
extern u32 g_dwRoomChainRanThisFrame_candidate;
// 1 while RestoreRoomActorState respawns the room's saved actors, and set
// when the overworld pushes a pause menu; the room actor constructed by
// sub_08044C00 and its callbacks branch on it.
extern u8 g_bRestoringRoomActors_candidate;
// Records wandering-monster touches and respawns replacements; see the
// wandering-monster notes above.
extern void HandleWanderingMonsterTouch(void);

// Nonzero blocks the overworld Start/Select menus (SetPauseMenuLocked).
extern u32 g_dwPauseMenuLocked;
// Frames until Start/Select may open a menu again; 4 after room init and
// each menu open, counted down by UpdateOverworld.
extern u32 g_dwPauseMenuCooldown;

// Multi-slot bookkeeping that only acts when the slot count exceeds 1.
// Always returns 0.
s32 TickOverworldControlSlots_candidate(void);

// Overworld teardown helpers called by ExitOverworldScreen.
extern void FreeRoomSharedTileset(void);
extern void sub_0802B210(void);
extern void sub_0802B08C(void);
extern void sub_08024918(void);
